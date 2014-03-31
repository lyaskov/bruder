#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "dht.h"

dht DHT1;
dht DHT2;

#define DHT11_PIN1  7
#define DHT11_PIN2  8

#define RELAY1 3
#define RELAY2 4

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

LiquidCrystal_I2C lcd(0x27, 10, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.backlight();

  lcd.home();
//pinMode(5, OUTPUT);

//  lcd.setCursor(2, 0);
//  lcd.print("Hello world...");
//  lcd.setCursor(0, 1);
//  lcd.print("dfrobot.com");
 pinMode(RELAY1, OUTPUT);       
 pinMode(RELAY2, OUTPUT);
}

//int backlightState = LOW;
long previousMillis = 0;
long interval = 2000;
//int i=0;
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    pinMode(5, OUTPUT);           // назначить выводу порт ввода
    digitalWrite(5, HIGH);       // включить подтягивающий резистор

    int chk1 = DHT1.read11(DHT11_PIN1);
    int chk2 = DHT2.read11(DHT11_PIN2);
//    switch (chk1)
//    {
//    case DHTLIB_OK:  
//		Serial.print("OK,\t"); 
//		break;
//    case DHTLIB_ERROR_CHECKSUM: 
//		Serial.print("Checksum error,\t"); 
//		break;
//    case DHTLIB_ERROR_TIMEOUT: 
//		Serial.print("Time out error,\t"); 
//		break;
//    default: 
//		Serial.print("Unknown error,\t"); 
//		break;
//    }
    if (DHT1.temperature < 25)
    {
      digitalWrite(RELAY1, HIGH);           // Turns ON Relays 1
    } else {
      digitalWrite(RELAY1, LOW);           // Turns OFF Relays 1
    }
    
    if (DHT2.temperature < 25)
    {
      digitalWrite(RELAY2, HIGH);           // Turns ON Relays 2
    } else {
      digitalWrite(RELAY2, LOW);           // Turns OFF Relays 1
    }
    lcd.clear();
    lcd.home();
    lcd.print("temp1 = "); lcd.print(DHT1.temperature);
    lcd.setCursor(0, 1);    
    lcd.print("temp2 = "); lcd.print(DHT2.temperature);
//    lcd.print("hum = "); 
//    lcd.print(DHT.humidity); lcd.setCursor(11, 1);

//  Serial.print(DHT.humidity, 1);
//  Serial.print(",\t");
//  Serial.println(DHT.temperature, 1);
  }
}
