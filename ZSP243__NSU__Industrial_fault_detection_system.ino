#include <LCD.h>
  #include <Wire.h>
    #include <LiquidCrystal_I2C.h>
      LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
      //LiquidCrystal_I2C lcd(0x3F , 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
         #define BLYNK_PRINT Serial
           #include <ESP8266WiFi.h>
             #include <BlynkSimpleEsp8266.h>
               #include <DHT.h>



int gas = D0;
  int fire = D3;
    int buzzar = D5;
      int load = D6;
        int load1 = D7;
          int load2 = D8;

char auth[] = "KRpy1da_ozGbXHxHzbN3ZCNyEI1CqCCy";


char ssid[] = "abcde";//abcde//ZerOne BD
char pass[] = "12345678";//12345678//zeronebd2017

#define DHTPIN 2          // What digital pin we're connected to


//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  if(t >34){
  Blynk.notify("Temperature In Danger Zone");
       digitalWrite(D6,HIGH);
       digitalWrite(D5,HIGH);
                lcd.clear();
                  lcd.print(".Temperature In.");
                    lcd.setCursor(0,1);
                      lcd.print("..Danger Zone..");
  delay(3000);
      digitalWrite(D6,LOW);
      digitalWrite(D5,LOW);
                lcd.clear();
                  lcd.print("Industrial Fault");
                    lcd.setCursor(0,1);
                      lcd.print("Dtection System");
  }
}

void setup()
{
 Serial.begin(9600); 
 lcd.begin(16,2);
         lcd.clear();
           lcd.print("Industrial Fault");
             lcd.setCursor(0,1);
               lcd.print("Dtection System");
 delay(2000);

pinMode(D0,INPUT);
  pinMode(D3,INPUT);
    pinMode(D5,OUTPUT);
      pinMode(D6,OUTPUT);
        pinMode(D7,OUTPUT);
          pinMode(D8,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

  int gas1 = digitalRead(D0);
    int fire1 = digitalRead(D3);

 if(gas1 == LOW){
 Blynk.notify("Gas Leakaged in your Industry");
     digitalWrite(D7,HIGH);
     digitalWrite(D5,HIGH);
             lcd.clear();
               lcd.print(".Gas Leakaged in.");
                 lcd.setCursor(0,1);
                   lcd.print("..your Industry..");
 delay(3000);
      digitalWrite(D7,LOW);
      digitalWrite(D5,LOW);
             lcd.clear();
               lcd.print("Industrial Fault");
                 lcd.setCursor(0,1);
                   lcd.print("Dtection System");
  }

 if(fire1 == LOW ){
 Blynk.notify("Fire Detected in your Industry");
      digitalWrite(D8,HIGH);
      digitalWrite(D5,HIGH);
             lcd.clear();
               lcd.print("Fire Detected in");
                 lcd.setCursor(0,1);
                   lcd.print("your Industry");
 delay(3000);
      digitalWrite(D8,LOW);
      digitalWrite(D5,LOW);
             lcd.clear();
               lcd.print("Industrial Fault");
                 lcd.setCursor(0,1);
                   lcd.print("..Dtection System..");
  }
}
