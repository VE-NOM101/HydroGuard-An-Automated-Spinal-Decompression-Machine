#include <dht.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11  // Use DHT11 instead of dht11

dht DHT;

const int potPin = A0;
const int conPin = 3;                // Connect the fan to this pin
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address and dimensions

void setup() {
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);  // Set DHTPIN as input
  pinMode(conPin, OUTPUT);
  lcd.init();       // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("HydroGuard");
  lcd.setCursor(0, 1);
  lcd.print("Humidity Controll");
  delay(2000);
  lcd.clear();
}

void loop() {
  // int threshold = map(analogRead(potPin), 0, 1023, 20, 40);  // Map potentiometer value to temperature range
  
  int threshold = map(analogRead(potPin), 0, 1023, 20, 100);  // Map potentiometer value to temperature range

  DHT.read11(DHTPIN);  // Read data from DHT sensor

  float temperature = DHT.temperature;

  float humidity = DHT.humidity;

  if (isnan(humidity)) {
    lcd.clear();
    lcd.print("Failed to read from DHT sensor!");
    return;
  }

  // if (temperature > threshold) {
  //   digitalWrite(conPin, LOW); 

  // } else {
  //   digitalWrite(conPin, HIGH);  // Turn off the fan
  // }

  if (humidity > threshold) {
    digitalWrite(conPin, LOW); 
    Serial.println(humidity);
     Serial.println(threshold);

  } else {
    digitalWrite(conPin, HIGH);  // Turn off the fan
    
    Serial.println(humidity);
     Serial.println(threshold);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Threshold: ");
  lcd.print(threshold);
  lcd.print("%");

  delay(1000);
}
