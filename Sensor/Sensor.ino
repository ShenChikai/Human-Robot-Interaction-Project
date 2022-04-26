#include <ESP8266WiFi.h>          // Include the Wi-Fi library

const char* ssid     = "XXX";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "XXX";     // The password of the Wi-Fi network
const int pingPin = D4;                // PING))) Ultrasonic
WiFiClient client;                 // Initialize the Ethernet client object
char get_request[200];
char server[] = "XXXX";

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, distance;
  char distance_str[20];

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  distance = microsecondsToCentimeters(duration);

  Serial.print("detect");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  // React to distance:
  itoa(distance, distance_str, 10);
//  sprintf(get_request,"POST /?distance=%s HTTP/1.1\r\nHost: XXX:XXX\r\nConnection: close\r\n\r\n", distance_str);
//  client.print(get_request);
  
  if (client.connect(server, 7000)) {
    // Serial.println("Connected to server");
    // Make a HTTP request
    client.print("POST /?distance=");
    client.print(distance_str);
    client.println(" HTTP/1.1");
    client.println("Host: arduino.cc");
    client.println("Connection: close");
    client.println();
    Serial.println("sent");
  }
  
  delay(500);
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  delay(1000);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  return microseconds / 29 / 2;
}
