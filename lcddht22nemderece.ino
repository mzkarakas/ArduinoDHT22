#include <DHT.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);  //LCD adresi 0x27 16 karaketer 2 satir olacak sekilde ayarlaniyor

#define DHTPIN 2 // belirlenen sensor data pini
#define DHTTYPE DHT22 // sensor tipi DHT22 olacak
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Baslatiliyor...");

  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Baslatiliyor...");

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float c = dht.readTemperature();  // Derece
  float f = dht.readTemperature(true);  // Fahrenheit bu kullanilmayacagi icin yorum satirina cevirdik

  if (isnan(h) || isnan(c) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0, 0); //Ledde cursorun baslangic yeri ayarlandi
  lcd.print("SICAKLIK: ");
  lcd.print(c, 1);  // print only one decimal digit due to limited space
  lcd.print("C | ");
  //lcd.print(f, 1);  // print only one decimal digit due to limited space
  //lcd.print("F"); bu kullanilmayacagi icin yorum satirina cevirdik

  lcd.setCursor(0, 1);
  lcd.print("NEM     : ");
  lcd.print(h);
  lcd.print("%");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(c);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");

  delay(2000);
}


