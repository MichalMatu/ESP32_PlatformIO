#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 14     // DHT22 data pin
#define DHTTYPE DHT22 // DHT22 sensor type

DHT dht(23, DHT22);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  dht.begin();     // Initialize the DHT22 sensor
}

void loop()
{
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity

  lcd.setCursor(0, 0);    // Set the cursor to the first column and first row
  lcd.print("Temp: ");    // Print the text "Temp: " on the LCD screen
  lcd.print(temperature); // Print the temperature value on the LCD screen
  lcd.print(" C");        // Print the text " C" on the LCD screen

  lcd.setCursor(0, 1);     // Set the cursor to the first column and second row
  lcd.print("Humidity: "); // Print the text "Humidity: " on the LCD screen
  lcd.print(humidity);     // Print the humidity value on the LCD screen
  lcd.print("%");          // Print the text "%" on the LCD screen

  delay(2000); // Wait for 2 seconds
}
