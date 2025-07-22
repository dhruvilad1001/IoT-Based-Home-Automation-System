/* Read RFID Tag with RC522 RFID Reader
    Made by miliohm.com
*/

/*#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above
const int Lock = D1;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);
  pinMode(D1,OUTPUT);
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    if (tag == "1982424") {
      
      Serial.println("Access Granted!");
      digitalWrite(D1,HIGH);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);

    } else if (tag == "313317044") {
      Serial.println("Access Granted!");
      digitalWrite(D1,HIGH);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
    } else if (tag == "147814920") {
      Serial.println("Access Granted!");
      digitalWrite(D1,HIGH);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      delay(100);
    } else {
      Serial.println("Access Denied!");
      digitalWrite(D1,LOW);
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}*/




/****************with servo code**************/

/*#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN  = D4;
const int BUZZER_PIN = D8;
const int SERVO_PIN  = D2;

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID and Servo
MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

String tag = "";

// Valid RFID tag list
const String validTags[] = {
  "1982424",
  "313317044",
  "147814920"
};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  myServo.attach(SERVO_PIN);
  myServo.write(0);  // Door closed
  delay(500);
  myServo.detach();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" RFID DOOR LOCK ");
  lcd.setCursor(0, 1);
  lcd.print("  Ready to Scan ");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  tag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tag += String(rfid.uid.uidByte[i]);
  }

  Serial.println("Tag Scanned: " + tag);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Detected");
  lcd.setCursor(0, 1);
  lcd.print(tag.substring(0, 16));  // Display partial tag

  if (isValidTag(tag)) {
    Serial.println("Access Granted");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    buzzShort();
    openDoor();
  } else {
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    buzzLong();
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Ready to Scan ");

  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isValidTag(String scannedTag) {
  for (int i = 0; i < sizeof(validTags) / sizeof(validTags[0]); i++) {
    if (scannedTag == validTags[i]) return true;
  }
  return false;
}

void openDoor() {
  myServo.attach(SERVO_PIN);

  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(10);
  }

  delay(5000);  // Door stays open

  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }

  myServo.write(0);
  delay(500);
  myServo.detach();
}

void buzzShort() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void buzzLong() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2000);
  digitalWrite(BUZZER_PIN, LOW);
}*/



/*************************code*********************************************************************/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions (adjust as needed)
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN  = D4;
const int BUZZER_PIN = D8;
const int SERVO_PIN  = D2;  // Use a valid PWM pin, NOT D0

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID and Servo
MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

String tag = "";

// Valid RFID tag list
const String validTags[] = {
  "1982424",
  "313317044",
  "147814920"
};

// Corresponding names for valid tags
/*const String validNames[] = {
  "A",
  "B",
  "C"
};*/

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" RFID DOOR LOCK ");
  lcd.setCursor(0, 1);
  lcd.print("  Ready to Scan ");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  Serial.println("Card Present");

  if (!rfid.PICC_ReadCardSerial()) return;
  Serial.println("Card Read Successfully");

  tag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tag += String(rfid.uid.uidByte[i]);
  }

  Serial.println("Tag Scanned: " + tag);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Detected");
  lcd.setCursor(0, 1);
  lcd.print(tag.substring(0, 16));

  delay(1000);  // Delay to allow message visibility

  String userName = getUserName(tag);  // Get corresponding name for tag

  if (userName != "") {
    Serial.println("Access Granted");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Welcome " + userName);  // Display name
    buzzShort();
    //openDoor();  // Servo action disabled
  } else {
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    buzzLong();
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Ready to Scan ");

  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to get name based on tag ID
String getUserName(String scannedTag) {
  for (int i = 0; i < sizeof(validTags) / sizeof(validTags[0]); i++) {
    if (scannedTag == validTags[i]) {
      return validNames[i];  // Return corresponding name
    }
  }
  return "";  // Return empty string if tag is not valid
}

void openDoor() {
  myServo.attach(SERVO_PIN);

  // Rotate clockwise (e.g., open) for approx. 90 degrees
  myServo.write(0);       // Full speed CW
  delay(700);             // Adjust this for your servo’s speed

  myServo.write(90);      // Stop 
  delay(3000);            // Door open pause

  // Rotate counter-clockwise (e.g., close)
  myServo.write(180);     // Full speed CCW
  delay(700);             // Same as above

  myServo.write(90);      // Stop
  myServo.detach();
}



// Servo function commented out
/*void openDoor() {
  myServo.attach(SERVO_PIN);
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(10);
  }

  delay(3000);  // Keep door open
  for (int pos = 90; pos <=180; pos++) {
  //for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }
  //myServo.write(0);
  myServo.detach();
}*/


void buzzShort() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void buzzLong() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2000);
  digitalWrite(BUZZER_PIN, LOW);
}






/**********************without servo connected**************************************/
/*#include <SPI.h>
#include <MFRC522.h>
// #include <Servo.h>  // Servo is disabled
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN  = D4;
const int BUZZER_PIN = D8;
//const int SERVO_PIN  = D2;

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID
MFRC522 rfid(SS_PIN, RST_PIN);
// Servo myServo;  // Servo object is disabled

String tag = "";

// Valid RFID tag list
const String validTags[] = {
  "1982424",
  "313317044",
  "147814920"
};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // myServo.attach(SERVO_PIN);
  // myServo.write(0);  // Door closed
  // delay(500);
  // myServo.detach();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" RFID DOOR LOCK ");
  lcd.setCursor(0, 1);
  lcd.print("  Ready to Scan ");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  tag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tag += String(rfid.uid.uidByte[i]);
  }

  Serial.println("Tag Scanned: " + tag);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Detected");
  lcd.setCursor(0, 1);
  lcd.print(tag.substring(0, 16));  // Display partial tag

  if (isValidTag(tag)) {
    Serial.println("Access Granted");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    buzzShort();
    // openDoor();  // Door control is disabled
  } else {
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    buzzLong();
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Ready to Scan ");

  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isValidTag(String scannedTag) {
  for (int i = 0; i < sizeof(validTags) / sizeof(validTags[0]); i++) {
    if (scannedTag == validTags[i]) return true;
  }
  return false;
}

// void openDoor() {
//   myServo.attach(SERVO_PIN);
//   for (int pos = 0; pos <= 180; pos++) {
//     myServo.write(pos);
//     delay(10);
//   }
//   delay(5000);
//   for (int pos = 180; pos >= 0; pos--) {
//     myServo.write(pos);
//     delay(10);
//   }
//   myServo.write(0);
//   delay(500);
//   myServo.detach();
// }

void buzzShort() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void buzzLong() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2000);
  digitalWrite(BUZZER_PIN, LOW);
}*/


/******************************************CONNECT TO THE BLYNK APPLICATION************************************************************************/

/*#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>  // Add this line for Blynk

// Pin definitions (adjust as needed)
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN  = D4;
const int BUZZER_PIN = D8;
const int SERVO_PIN  = D2;  // Use a valid PWM pin, NOT D0

// Blynk Auth Token
char auth[] = "qdNIwc3qR4JM43h0SuVne8c6I-O4DYzK";  // Replace with your Blynk Auth Token

// Wi-Fi credentials
char ssid[] = "Galaxy A14 5G AA96";     // Your Wi-Fi SSID
char pass[] = "dhruvilad@21";           // Your Wi-Fi password

// I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// RFID and Servo
MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;

String tag = "";

// Valid RFID tag list
const String validTags[] = {
  "1982424",
  "313317044",
  "147814920"
};

// Corresponding names for valid tags
const String validNames[] = {
  "A",
  "B",
  "C"
};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" RFID DOOR LOCK ");
  lcd.setCursor(0, 1);
  lcd.print("  Ready to Scan ");

  // Start Blynk
  Blynk.begin(auth, ssid, pass);  // Use your Wi-Fi credentials
}

void loop() {
  Blynk.run();  // Keep Blynk running

  if (!rfid.PICC_IsNewCardPresent()) return;
  Serial.println("Card Present");

  if (!rfid.PICC_ReadCardSerial()) return;
  Serial.println("Card Read Successfully");

  tag = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tag += String(rfid.uid.uidByte[i]);
  }

  Serial.println("Tag Scanned: " + tag);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag Detected");
  lcd.setCursor(0, 1);
  lcd.print(tag.substring(0, 16));

  delay(1000);  // Delay to allow message visibility

  String userName = getUserName(tag);  // Get corresponding name for tag

  if (userName != "") {
    Serial.println("Access Granted");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Welcome " + userName);  // Display name
    buzzShort();
    // openDoor();  // Servo action disabled
    Blynk.virtualWrite(V0, "Access Granted: " + userName);  // Send message to Blynk app on virtual pin V0
  } else {
    Serial.println("Access Denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    buzzLong();
    Blynk.virtualWrite(V0, "Access Denied");  // Send message to Blynk app on virtual pin V0
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Ready to Scan ");

  tag = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to get name based on tag ID
String getUserName(String scannedTag) {
  for (int i = 0; i < sizeof(validTags) / sizeof(validTags[0]); i++) {
    if (scannedTag == validTags[i]) {
      return validNames[i];  // Return corresponding name
    }
  }
  return "";  // Return empty string if tag is not valid
}*/

/*
// Servo function commented out
void openDoor() {
  myServo.attach(SERVO_PIN);
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(10);
  }

  delay(3000);  // Keep door open

  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);
  }

  myServo.detach();
}
*/

/*void buzzShort() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void buzzLong() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(2000);
  digitalWrite(BUZZER_PIN, LOW);
}*/



