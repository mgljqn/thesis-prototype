#define BLYNK_TEMPLATE_ID "prototype1"
#define BLYNK_DEVICE_NAME "revised proto 1"
#define BLYNK_AUTH_TOKEN "Ann6QdNGdrkIHC1_LxdR-_bNmlx7QS6Q"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include<DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int sm_sensor=34;
int light_sensor=35;

 BLYNK_WRITE(V3)
{
  int pinvalue = param.asInt();
  digitalWrite(15,pinvalue);
}  

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "";  // wifi name
char pass[] = "";  // wifi password

BlynkTimer timer;

void sendSensor()
{
  //Reading temperature or humidity takes about 250 milliseconds
  // Sensor readings may also be up to 2 seconds old
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  int moisture_sensor= analogRead(sm_sensor);
  int light_intensity=analogRead(light_sensor);
  // Check if any reads failed and exit early (to try again).
   if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // send any value at any time.
  // don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, moisture_sensor);
    Blynk.virtualWrite(V4, light_intensity);
    delay(500);
}
void setup()
{   
  
   Serial.begin(9600);
   pinMode (15,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
