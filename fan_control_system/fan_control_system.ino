#include <DHT.h>

// pins setup
int dhtPin = 2;
int motorPin = 3;
float triggerTemp = 27.0; // threshold temp

DHT dht(dhtPin, DHT11);

// timers for the internet telemetry
unsigned long previousSensorTime = 0;
const unsigned long sensorDelay = 2000; // 2s between DHT reads

unsigned long previousHttpTime = 0;
const unsigned long postDelay = 30000;  // 30s between HTTP posts

void setup() {
  Serial.begin(9600); // for the terminal
  Serial1.begin(9600); // pins 18/19 for the SIM module
  
  pinMode(motorPin, OUTPUT);
  dht.begin();
  
  // initial dht wake up
  delay(2000);
  
  // setting up the GPRS conenction
  Serial1.println("AT");
  delay(100);
  Serial1.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(100);
  Serial1.println("AT+SAPBR=3,1,\"APN\",\"safaricom\""); // safaricom apn
  delay(100);
  Serial1.println("AT+SAPBR=1,1");
  delay(2000);
  
  Serial.println("System is ready.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // 1. Non-blocking Sensor & Motor Logic
  if (currentMillis - previousSensorTime >= sensorDelay) {
    previousSensorTime = currentMillis;
    
    float currentTemp = dht.readTemperature();
    
    if (isnan(currentTemp)) {
      Serial.println("Sensor error: check wiring");
    } else {
      // Motor control
      if (currentTemp >= triggerTemp) {
        digitalWrite(motorPin, HIGH);
        Serial.print("Temp: ");
        Serial.print(currentTemp);
        Serial.println(" °C | Fan: ON");
      } else {
        digitalWrite(motorPin, LOW);
        Serial.print("Temp: ");
        Serial.print(currentTemp);
        Serial.println(" °C | Fan: OFF");
      }
    }
  }
  
  // 2. HTTP Post Logic
  if (currentMillis - previousHttpTime >= postDelay) {
    previousHttpTime = currentMillis;
    // pass the last known temperature
    postToServer((int)dht.readTemperature()); 
  }
}

// BONUS TASK
void postToServer(int temp) {
  if (isnan(temp)) return;

  Serial.println("Initiating HTTPS POST command...");
  
  // making the json string in the proposed fomart
  String myJson = "{\"t\":" + String(temp) + "}";

  Serial1.println("AT+HTTPSSL=1"); //enables ssl for the https endpoint
  delay(500);
  
  Serial1.println("AT+HTTPINIT");
  delay(500);
  Serial1.println("AT+HTTPPARA=\"CID\",1");
  delay(500);
  Serial1.println("AT+HTTPPARA=\"URL\",\"https://michael.alwaysdata.net/mk/message/8CQFEA-87E1AC-87E1AC\"");
  delay(500);
  Serial1.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(500);
  
  Serial1.print("AT+HTTPDATA=");
  Serial1.print(myJson.length());
  Serial1.println(",5000");
  delay(500);
  
  Serial1.println(myJson);
  delay(500);
  
  Serial1.println("AT+HTTPACTION=1"); //post request 
  delay(3000); // give server time to reply
  
  Serial1.println("AT+HTTPTERM");
  
  Serial.println("Data sent!");
}