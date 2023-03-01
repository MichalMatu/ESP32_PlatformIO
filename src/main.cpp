#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 14     // DHT22 data pin
#define DHTTYPE DHT22 // DHT22 sensor type
#define ADKEYPIN 4    // ADKEY pin number

#define RELAYPIN 2 // Relay pin number

unsigned long previousMillis = 0; // Store the time of the previous update
const long interval = 1000;       // Update interval in milliseconds
// set float variables for temperature and humidity
float temperature;
float humidity;
// set default temperature and humidity
int set_temperature = 24;
int set_humidity = 50;
// set default menu state to false
bool menu = false;
// set default backlight state to true
bool backlightOn = true;
// DHT22 sensor type
DHT dht(23, DHTTYPE);
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();      // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  dht.begin();     // Initialize the DHT22 sensor

  pinMode(ADKEYPIN, INPUT);  // Set the ADKEY pin as an input
  pinMode(RELAYPIN, OUTPUT); // Set the relay pin as an output
}

void loop()
{
  unsigned long currentMillis = millis(); // Store the current time

  // Read value from ADKEY pin
  int adkeyValue = analogRead(ADKEYPIN);

  // If menu button is pressed
  if (adkeyValue > 2900 && adkeyValue < 3000)
  {
    menu = !menu; // Toggle the menu state
    delay(200);   // Wait for 200 milliseconds to avoid button bounce
    lcd.clear();  // Clear the LCD screen
  }

  // If menu is not active
  if (!menu)
  {
    // Update temperature and humidity every interval
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;      // Update the previous time
      temperature = dht.readTemperature(); // Read temperature in Celsius
      humidity = dht.readHumidity();       // Read humidity
    }

    // if adkeyValue > 370 && adkeyValue < 500 is pressed swich off backlight if is pressed again switch on backlight
    // Check if the button was pressed
    if (adkeyValue > 370 && adkeyValue < 500)
    {
      // Toggle the backlight state
      backlightOn = !backlightOn;

      // Turn the backlight on or off depending on the state
      if (backlightOn)
      {
        lcd.backlight();
      }
      else
      {
        lcd.noBacklight();
      }

      // Wait a short time to debounce the button
      delay(100);
    }

    // Display temperature and humidity
    lcd.setCursor(0, 0);    // Set the cursor to the first column and first row
    lcd.print("Tem: ");     // Print the text "Temp: " on the LCD screen
    lcd.print(temperature); // Print the temperature value on the LCD screen
    lcd.setCursor(9, 0);    // Set the cursor to the 10th column and first row
    lcd.print(" ");         // Print the text " " on the LCD screen
    lcd.print("C");         // Print the text " C" on the LCD screen

    lcd.setCursor(0, 1); // Set the cursor to the first column and second row
    lcd.print("Hum: ");  // Print the text "Humidity: " on the LCD screen
    lcd.print(humidity); // Print the humidity value on the LCD screen
    lcd.setCursor(9, 1); // Set the cursor to the 10th column and second row
    lcd.print(" ");      // Print the text " " on the LCD screen
    lcd.print("%");      // Print the text "%" on the LCD screen
  }
  // If menu is active
  else
  {
    lcd.setCursor(0, 0);        // Set the cursor to the first column and first row
    lcd.print("Set Tem:");      // Print the text "Menu" on the LCD screen
    lcd.setCursor(9, 0);        // Set the cursor to the 11th column and first row
    lcd.print(set_temperature); // Print the ADKEY value on the LCD screen
    lcd.setCursor(11, 0);       // Set the cursor to the 15th column and first row
    lcd.print(" C");            // Print the text "C" on the LCD screen

    if (adkeyValue > 370 && adkeyValue < 500 && set_temperature < 100)
    {
      set_temperature = set_temperature + 1;
      delay(100);
    }

    if (adkeyValue > 1000 && adkeyValue < 1100 && set_temperature > -40)
    {
      set_temperature = set_temperature - 1;
      delay(100);
    }

    lcd.setCursor(0, 1);     // Set the cursor to the first column and second row
    lcd.print("Set Hum:");   // Print the text "Menu" on the LCD screen
    lcd.setCursor(9, 1);     // Set the cursor to the 11th column and second row
    lcd.print(set_humidity); // Print the humidity value on the LCD screen
    lcd.setCursor(11, 1);    // Set the cursor to the 15th column and second row
    lcd.print(" %");         // Print the text "%" on the LCD screen

    if (adkeyValue > 1790 && adkeyValue < 1850 && set_humidity < 100)
    {
      set_humidity = set_humidity + 1;
      delay(100);
    }

    if (adkeyValue < 110 && set_humidity > 0)
    {
      set_humidity = set_humidity - 1;
      delay(100);
    }
  }

  // If temperature is higher than set temperature
  if (temperature > set_temperature)
  {
    digitalWrite(RELAYPIN, LOW); // Turn on the relay
    lcd.setCursor(15, 0);        // Set the cursor to the 15th column and first row
    lcd.print("0");              // Print the text "ON" on the LCD screen
  }
  // If temperature is lower than set temperature
  else
  {
    digitalWrite(RELAYPIN, HIGH); // Turn off the relay
    lcd.setCursor(15, 0);         // Set the cursor to the 15th column and first row
    lcd.print("1");               // Print the text "ON" on the LCD screen
  }

  // If humidity is higher than set humidity
  if (humidity > set_humidity)
  {
    digitalWrite(RELAYPIN, LOW); // Turn off the relay
    lcd.setCursor(15, 1);        // Set the cursor to the 15th column and second row
    lcd.print("0");              // Print the text "ON" on the LCD screen
  }
  // If humidity is lower than set humidity
  else
  {
    digitalWrite(RELAYPIN, HIGH); // Turn on the relay
    lcd.setCursor(15, 1);         // Set the cursor to the 15th column and second row
    lcd.print("1");               // Print the text "ON" on the LCD screen
  }
}
