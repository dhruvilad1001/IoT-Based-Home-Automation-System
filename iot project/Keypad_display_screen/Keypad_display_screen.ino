/****************************key press display working code********************************/
/*#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Define keypad size
const byte ROWS = 4;
const byte COLS = 3;

// Define keypad row and column pin connections (NodeMCU example)
byte rowPins[ROWS] = {D1, D2, D3, D4};  // R1, R2, R3, R4
byte colPins[COLS] = {D5, D6, D7};      // C1, C2, C3

// Define key layout
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Initialize keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Initialize the LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();            // Correct initialization for I2C LCD
  lcd.backlight();       // Turn on backlight
  lcd.setCursor(0, 0);   // Set cursor at top left
  lcd.print("Press a key"); // Display message
}

void loop() {
  char key = keypad.getKey(); // Read keypad

  if (key) {
    lcd.clear();              // Clear display
    lcd.setCursor(0, 0);      // Reset cursor
    lcd.print("Pressed: ");   // Show label
    lcd.print(key);           // Show pressed key
    Serial.println(key);      // Print to Serial Monitor
  }
}*/



/******************buzzer code****************/
/*#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Keypad setup
const byte ROWS = 4;
const byte COLS = 3;

byte rowPins[ROWS] = {D1, D2, D3, D4};
byte colPins[COLS] = {D5, D6, D7};

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Buzzer pin setup
#define BUZZER_PIN D8  // Connect buzzer + to this pin, - to GND

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Press a key");

  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
  digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is off at start
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressed: ");
    lcd.print(key);
    Serial.println(key);

    // Turn on buzzer briefly
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);  // Buzzer on for 100 ms
    digitalWrite(BUZZER_PIN, LOW);
  }
}*/

/*******servo tested code******/
/*#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(D0); 
  Serial.begin(9600);
  Serial.println("Servo Test Start");
}

void loop() {
  myServo.write(0);     // Move to 0 degrees
  delay(1000);
  myServo.write(90);    // Move to 90 degrees
  delay(1000);
  myServo.write(180);   // Move to 180 degrees
  delay(1000);
}*/




/*************servo connected code*****************/
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {D1, D2, D3, D4};
byte colPins[COLS] = {D5, D6, D7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo and buzzer
Servo myServo;
#define SERVO_PIN D0     // Use a safe pin
#define BUZZER_PIN D8

String password = "1021";
String input = "";

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");

  myServo.attach(SERVO_PIN);
  myServo.write(0); // Stop servo initially

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input == password) {
        lcd.clear();
        lcd.print("Correct Password");
        Serial.println("Access Granted");
        buzz(1);
        openDoor();
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        Serial.println("Access Denied");
        buzz(3);
      }
      input = "";
      delay(2000);
      lcd.clear();
      lcd.print("Enter Password");
    } else if (key == '*') {
      input = "";
      lcd.clear();
      lcd.print("Enter Password");
    } else {
      if (input.length() < 16) {
        input += key;
        lcd.setCursor(0, 1);
        for (int i = 0; i < input.length(); i++) {
          lcd.print("*");
        }
      }
    }
  }
}

void buzz(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}


void openDoor() {
  // Smoothly open from 0 to 180 degrees
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(10);  // Adjust speed of opening
  }

  delay(5000);  // Keep door open for 5 seconds

  // Smoothly close from 180 to 0 degrees
  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(10);  // Adjust speed of closing
  }

  myServo.write(0);  // Ensure it's fully closed
}


/***********************************************************/

/*void openDoor() {
  myServo.write(0);     // Rotate servo (open)
  delay(500);           // Rotate briefly (adjust for desired turn)
 //myServo.write(90);    // Stop rotation
 //delay(500);         // Wait for 5 seconds
  myServo.write(180);   // Rotate in opposite direction (close)
  delay(500);   
   //myServo.write(360);   // Rotate in opposite direction (close)
  //delay(500);         // Rotate briefly
  myServo.write(0);    // Stop rotation again
}*/



/*void openDoor() {
  myServo.write(90);       // Rotate to 90 degrees (open position)
  delay(5000);             // Wait for 5 seconds with door open

  // Slowly return to 0 degrees (closed position)
  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);             // Controls speed; increase for slower movement
  }

  myServo.write(0);        // Ensure it's fully closed
}*/



/*void openDoor() {
  // Smoothly open to 90 degrees
  for (int pos = 0; pos <= 90; pos++) {
    myServo.write(pos);
    delay(15);
  }

  delay(5000);  // Wait while door remains open

  // Smoothly close to 0 degrees
  for (int pos = 90; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }

  myServo.write(0); // Ensure fully closed
}*/


