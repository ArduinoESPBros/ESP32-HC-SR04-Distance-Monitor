#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Most 16x2 I2C LCDs use 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // ESP32 I2C pins
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Distance Meter");
  delay(1500);

  lcd.clear();
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No object");

  } else {

    float distance = duration * 0.0343 / 2;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Distance:");

    lcd.setCursor(0, 1);
    lcd.print(distance, 1);
    lcd.print(" cm");

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
