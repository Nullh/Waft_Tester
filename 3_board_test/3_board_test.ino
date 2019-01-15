/*
*   BOARD 1 WIRING
*   Head down at male
*   -----------------------------
*   9  10  11  12  13  14  15  16
*   8   7   6   5   4   3   2   1
*   -----------      ------------
*   8 - SDA/SS
*   10 - SCK
*   11 - MOSI
*   12 - MISO
*   14  - Ground
*   15 - RST
*   16 - 3.3v
*   
*   ARDUINO WIRING
*   Ardu Pin      Board 1 Conn Pin      Decription
*   --------      ----------------      ----------
*   GND           14                    Ground
*   13            10                    SCK
*   12            12                    MISO
*   11            11                    MOSI
*   10            8                     SDA/SS 1
*   9             15                    RST 1
*   8             -                     To LED
*   6             -                     SDA/SS 3
*   5             -                     RST 3
*   3             -                     SDA/SS 2
*   2             -                     RST 2
*   
*   
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST1_PIN         9          // Configurable, see typical pin layout above
#define SS1_PIN          10          // Configurable, see typical pin layout above
#define RST2_PIN        2
#define SS2_PIN         3
#define LED_PIN         4
#define RST3_PIN        5
#define SS3_PIN         6
#define SERVO_PIN       7

#define OK_1            0
#define OK_2            1
#define OK_3            8

bool board1ok = 0;
bool board2ok = 0;
bool board3ok = 0;
bool opened = 0;
bool unlocked = 0;
int pos = 10;

MFRC522 board1(SS1_PIN, RST1_PIN);  // Create MFRC522 instance
MFRC522 board2(SS2_PIN, RST2_PIN);
MFRC522 board3(SS3_PIN, RST3_PIN);
Servo myServo;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(OK_1, OUTPUT);
  pinMode(OK_2, OUTPUT);
  pinMode(OK_3, OUTPUT);
  pinMode(RST1_PIN, OUTPUT);
  pinMode(RST2_PIN, OUTPUT);
  pinMode(RST3_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
<<<<<<< HEAD
  digitalWrite(OK_1, LOW);
  digitalWrite(OK_2, LOW);
  digitalWrite(OK_3, LOW);
  digitalWrite(RST1_PIN, HIGH);
  digitalWrite(RST2_PIN, HIGH);
  digitalWrite(RST3_PIN, HIGH);
  //Serial.begin(9600);   // Initialize serial communications with the PC
  //while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  board1.PCD_Init();   // Init MFRC522
  board2.PCD_Init();
  board3.PCD_Init();
  //board1.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  //board2.PCD_DumpVersionToSerial();
  //board3.PCD_DumpVersionToSerial();
  myServo.attach(SERVO_PIN);
  open_door();
  myServo.write(10);
  //Serial.println(F("Waft a card near the reader!"));
}

void loop() {
  digitalWrite(RST1_PIN, LOW);
  if (board1.PICC_IsNewCardPresent()) {
    //Serial.println(F("Card 1 OK"));
    digitalWrite(OK_1, HIGH);
    board1.PICC_HaltA();
    board1.PCD_StopCrypto1();
    board1ok = 1;
  }
  digitalWrite(RST1_PIN, HIGH);
  digitalWrite(RST2_PIN, LOW);
  if (board2.PICC_IsNewCardPresent()) {
    //Serial.println(F("Card 2 OK"));
    digitalWrite(OK_2, HIGH);
    board2.PICC_HaltA();
    board2.PCD_StopCrypto1();
    board2ok = 1;
  }
  digitalWrite(RST2_PIN, HIGH);
  digitalWrite(RST3_PIN, LOW);
  if (board3.PICC_IsNewCardPresent()) {
    //Serial.println(F("Card 3 OK"));
    digitalWrite(OK_3, HIGH);
    board3.PICC_HaltA();
    board3.PCD_StopCrypto1();
    board3ok = 1;
  }
  digitalWrite(RST3_PIN, HIGH);
  if (board1ok && board2ok && board3ok) {
    //Serial.println(F("Unlocked!"));
    unlocked = 1;
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  if (unlocked && !opened) {
    open_door();
    opened = 1;
  }

  digitalWrite(OK_1, LOW);
  digitalWrite(OK_2, LOW);
  digitalWrite(OK_3, LOW);
  
  board1ok = 0;
  board2ok = 0;
  board3ok = 0;
  delay(100);
  
}

void open_door() {
  for (pos = 0; pos <= 120; pos +=1) {
    myServo.write(pos);
    delay(5);
  }
}
