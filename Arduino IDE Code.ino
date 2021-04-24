#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
DHT dht;
#define WS "E.D.I.T.H"
#define WP "qwertyas"
#define FH "mws01-799d4.firebaseio.com"
#define FA "hd3cNgXDUjlk8GY3WO5n4WECKiMxaiLgluGj3V0j"
#define pin D7;
#define pin D6;
#define pin D1;
#define pin D2;
unsigned long tim;
unsigned long ST;
unsigned long ET;
float HI = 0;
int count = 0;
int M = 1;
int P = 0;
float R = 0;
void setup() {
ST = millis();
Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(D7,INPUT);
WiFi.begin(WS,WP);
Serial.print("Connecting Boss");
while (WiFi.status()!=WL_CONNECTED) {
  Serial.print(".");
  delay (500);
}
Serial.println();
Serial.println("CONNECTION SUCCESFUL BOSS");
Serial.println(WiFi.localIP());// put your setup code here, to run once:
dht.setup(D6);
bmp.begin();
Firebase.begin(FH,FA);
Firebase.setFloat("T",0);
Firebase.setFloat("H",0);
}

void loop() {
if(WiFi.status()!=WL_CONNECTED) 
{
  digitalWrite(LED_BUILTIN,1);
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN,0);    // turn the LED off by making the voltage LOW
  delay(100);
}
else if(WiFi.status()==WL_CONNECTED) 
{
  digitalWrite(LED_BUILTIN,0);
}
HI = pulseIn(D7,HIGH);
if(HI < 2000 && HI > 0){
  count++;
  delay(500);}
  // put your main code here, to run repeatedly:
delay(2*dht.getMinimumSamplingPeriod());
float T = dht.getTemperature();
float H = dht.getHumidity();
P = bmp.readSealevelPressure();
ET = millis() - ST;
if (ET >= M*300000) {
  M++;
  tim++;
}
if(tim == 1){
  Firebase.setFloat("R",count*0.7/2500000);
  tim = 0;
  count = 0;
}
Firebase.setFloat("T",T);
Firebase.setFloat("H",H);
Firebase.setFloat("P",(P/100));
}
