#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 setup
#define DHTPIN 11      // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11 // DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
  delay(1000); // Optional delay for display setup
}

void loop() {
  // Reading temperature and humidity values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 30);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");

  display.display();
  delay(2000); // Update every 2 seconds
}
