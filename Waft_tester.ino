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
*   10            8                     SDA/SS
*   9             15                    RST
*   8             -                     To LED
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
#define LED_PIN         8
#define SERVO_PIN       7

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
Servo myServo;

int pos = 0;
bool unlocked = 0;
bool opened = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  myServo.attach(SERVO_PIN);
  swing_servo();
  myServo.write(10);
  Serial.println(F("Waft a card near the reader!"));
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    // Turn off the LED and end loop early if no card
    digitalWrite(LED_PIN, LOW);
    return;
  } else {
    // If we got a card flip on the LED and delay a bit for stability
    Serial.println(F("Card detected!"));
    digitalWrite(LED_PIN, HIGH);
    unlocked = 1;
    mfrc522.PICC_HaltA();
    delay(100);
  }
  if (unlocked && !opened) {
    swing_servo();
    opened = 1;
  }
}

void swing_servo() {
    for (pos = 0; pos <= 120; pos +=1) {
      myServo.write(pos);
      delay(5);
    }
}
