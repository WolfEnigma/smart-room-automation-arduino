#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

/* -------- LCD Configuration -------- */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* -------- Keypad Configuration -------- */
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {A0, A1, A2, A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* -------- Door Lock Configuration -------- */
const int relayPin = 10;
String correctPassword = "1234";
String enteredPassword = "";

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("SMART DOOR LOCK");
  delay(2000);
  lcd.clear();
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      verifyPassword();
    } 
    else if (key == '*') {
      resetInput();
    } 
    else {
      enteredPassword += key;
      lcd.setCursor(0, 1);
      lcd.print(enteredPassword);
    }
  }
}

void verifyPassword() {
  lcd.clear();

  if (enteredPassword == correctPassword) {
    lcd.print("Access Granted");
    digitalWrite(relayPin, HIGH);   // Unlock door
    delay(3000);
    digitalWrite(relayPin, LOW);    // Lock door
  } else {
    lcd.print("Access Denied");
    delay(2000);
  }

  resetInput();
}

void resetInput() {
  enteredPassword = "";
  lcd.clear();
  lcd.print("Enter Password:");
}
