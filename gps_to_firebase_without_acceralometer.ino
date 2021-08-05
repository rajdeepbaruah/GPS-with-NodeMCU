#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <arduino-geohash.h>
GeoHash hasher(15);
TinyGPSPlus gps;
SoftwareSerial ss(14, 12);
#define FIREBASE_HOST "nodemcu-73345.firebaseio.com"
#define FIREBASE_AUTH "rRVPvlLyJQyPHymAztUehkVmFWf8jCZXZuAieqin"
#define WIFI_SSID "jai bhabani"
#define WIFI_PASSWORD "237237237237"
float latitude;
float longitude;
String lat_str , lng_str;
int limitswitch = 13;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(limitswitch,INPUT);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
  
void loop() {

  while(ss.available() > 0) {gps.encode(ss.read());}
 
    if (gps.location.isUpdated())
    {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      String lat_str = String(latitude, 15);
      String lng_str = String(longitude, 15);
    const char* geohash = hasher.encode(latitude, longitude);
  
      if (digitalRead(limitswitch) == HIGH){
      Firebase.setString("GEOHASH", geohash);
      Firebase.setString("LATITUTE", lat_str);
      Firebase.setString("LONGITUDE", lng_str);

      Serial.print("GEOHASH=");Serial.println(geohash);
      Serial.print("LATITUTE="); Serial.println(latitude, 15);
      Serial.print("LONGITUDE="); Serial.println(longitude, 15);
   }
   }}
