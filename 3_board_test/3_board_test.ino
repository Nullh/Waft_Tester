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
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST1_PIN         9          // Configurable, see typical pin layout above
#define SS1_PIN          10          // Configurable, see typical pin layout above
#define RST2_PIN        2
#define SS2_PIN         3
#define LED_PIN         4
#define RST3_PIN        5
#define SS3_PIN         6

bool board1ok = 0;
bool board2ok = 0;
bool board3ok = 0;

MFRC522 board1(SS1_PIN, RST1_PIN);  // Create MFRC522 instance
MFRC522 board2(SS2_PIN, RST2_PIN);
MFRC522 board3(SS3_PIN, RST3_PIN);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  board1.PCD_Init();   // Init MFRC522
  board2.PCD_Init();
  board3.PCD_Init();
  board1.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  board2.PCD_DumpVersionToSerial();
  board3.PCD_DumpVersionToSerial();
  Serial.println(F("Waft a card near the reader!"));
}

void loop() {
  if (board1.PICC_IsNewCardPresent()) {
    Serial.println(F("Card 1 OK"));
    board1.PICC_HaltA();
    board1ok = 1;
  }
  if (board2.PICC_IsNewCardPresent()) {
    Serial.println(F("Card 2 OK"));
    board2.PICC_HaltA();
    board2ok = 1;
  }
  if (board3.PICC_IsNewCardPresent()) {
    Serial.println(F("Card 3 OK"));
    board3.PICC_HaltA();
    board3ok = 1;
  }
  if (board1ok && board2ok && board3ok) {
    Serial.println(F("Unlocked!"));
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  board1ok = 0;
  board2ok = 0;
  board3ok = 0;
  delay(100);
  
}
