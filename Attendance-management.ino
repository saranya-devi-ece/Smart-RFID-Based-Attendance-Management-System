#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define GREEN_LED 2
#define RED_LED 3
#define BUZZER 4

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27,16,2);

// Attendance status
bool student1 = false;
bool student2 = false;
bool student3 = false;

void setup() {

  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("RFID Attendance");
  lcd.setCursor(0,1);
  lcd.print("Scan Card");
  Serial.println("RFID Attendance System");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  String uid="";

  for(byte i=0;i<rfid.uid.size;i++) {
    if(rfid.uid.uidByte[i] < 0x10)
      uid += "0";

    uid += String(rfid.uid.uidByte[i],HEX);
  }

  uid.toUpperCase();

  Serial.print("UID : ");
  Serial.println(uid);
  lcd.clear();

  // STUDENT 1
  if(uid=="55667788") {

    if(!student1){
      student1=true;

      lcd.print("Saranya");
      lcd.setCursor(0,1);
      lcd.print("Attendance OK");

      Serial.println("Saranya Attendance Marked");

      digitalWrite(GREEN_LED,HIGH);
      tone(BUZZER,1000,200);
      delay(1000);
      digitalWrite(GREEN_LED,LOW);
    }
    else{
      lcd.print("Saranya");
      lcd.setCursor(0,1);
      lcd.print("Already Marked");
    }
  }

  // STUDENT 2
  else if(uid=="01020304") {

    if(!student2){
      student2=true;

      lcd.print("Dhanush");
      lcd.setCursor(0,1);
      lcd.print("Attendance OK");

      Serial.println("Dhanush Attendance Marked");

      digitalWrite(GREEN_LED,HIGH);
      tone(BUZZER,1000,200);
      delay(1000);
      digitalWrite(GREEN_LED,LOW);
    }
    else{
      lcd.print("Dhanush");
      lcd.setCursor(0,1);
      lcd.print("Already Marked");
    }
  }

  // STUDENT 3
  else if(uid=="11223344") {

    if(!student3){
      student3=true;

      lcd.print("Devi");
      lcd.setCursor(0,1);
      lcd.print("Attendance OK");

      Serial.println("Devi Attendance Marked");

      digitalWrite(GREEN_LED,HIGH);
      tone(BUZZER,1000,200);
      delay(1000);
      digitalWrite(GREEN_LED,LOW);
    }
    else{
      lcd.print("Devi");
      lcd.setCursor(0,1);
      lcd.print("Already Marked");
    }
  }

  // INVALID CARD
  else {

    lcd.print("Access Denied");
    lcd.setCursor(0,1);
    lcd.print("Invalid Card");

    Serial.println("Invalid Card");

    digitalWrite(RED_LED,HIGH);
    tone(BUZZER,500,1000);
    delay(1000);
    digitalWrite(RED_LED,LOW);
  }
  delay(2000);

  lcd.clear();
  lcd.print("Scan Card");
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
