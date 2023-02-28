#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 14     // DHT22 data pin
#define DHTTYPE DHT22 // DHT22 sensor type

#define ADKEYPIN 4 // ADKEY pin number

DHT dht(23, DHTTYPE); // DHT22 sensor type

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  dht.begin();     // Initialize the DHT22 sensor

  pinMode(ADKEYPIN, INPUT); // Set the ADKEY pin as an input
}

void loop()

{

  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity

  // Read value from ADKEY pin and print to console
  int adkeyValue = analogRead(ADKEYPIN);

  if (adkeyValue == 4095)
  {
    lcd.setCursor(0, 0);    // Set the cursor to the first column and first row
    lcd.print("T: ");       // Print the text "Temp: " on the LCD screen
    lcd.print(temperature); // Print the temperature value on the LCD screen
    lcd.print(" C");        // Print the text " C" on the LCD screen

    lcd.setCursor(0, 1); // Set the cursor to the first column and second row
    lcd.print("H: ");    // Print the text "Humidity: " on the LCD screen
    lcd.print(humidity); // Print the humidity value on the LCD screen
    lcd.print("%");      // Print the text "%" on the LCD screen

    lcd.setCursor(12, 0);  // Set the cursor to the 13th column and second row
    lcd.print(adkeyValue); // Print the ADKEY value on the LCD screen

    delay(1000); // Wait for 1 seconds
  }

  if (adkeyValue > 2900 && adkeyValue < 3000)
  {
    // Menu btn
    lcd.clear();         // Clear the LCD screen
    lcd.setCursor(0, 0); // Set the cursor to the first column and first row
    lcd.print("Menu");   // Print the text "Menu" on the LCD screen

    delay(1000); // Wait for 1 seconds
  }

  if (adkeyValue > 4000)
  {
    // Up btn
    lcd.clear(); // Clear the LCD screen
  }
  if (adkeyValue > 900 && adkeyValue < 1200)
  {
    // Down btn
    lcd.clear(); // Clear the LCD screen
  }

  if (adkeyValue > 0 && adkeyValue < 200)
  {
    // Left btn
    lcd.clear(); // Clear the LCD screen
  }

  if (adkeyValue > 1500 && adkeyValue < 2000)
  {
    // Right btn
    lcd.clear(); // Clear the LCD screen
  }
}
