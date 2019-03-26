#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// SSID parameters
const char* ssid = "AXESIDE";
const char* password = "darkside1247";

const int port = 80; // Port
ESP8266WebServer server(port);

// Motors pins
static const uint8_t a = D0;//1
static const uint8_t b = D1;//2
static const uint8_t c = D2;//3
static const uint8_t d = D3;//4

// Motor speed = [0-1024]
int motor_speed = 1024;
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // Declaration of motors
  pinMode(a, OUTPUT); // PMW A
  pinMode(b, OUTPUT); // PMW B
  pinMode(c, OUTPUT); // DIR A
  pinMode(d, OUTPUT); // DIR B

  // Setup STA
  Serial.print("Connecting to : ");
  Serial.println(ssid);

  WiFi.persistent(false);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    pinMode(LED_BUILTIN, LOW);
    delay(250);
    pinMode(LED_BUILTIN, HIGH);
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connection established!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Start Server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}


void loop() {
  server.handleClient();
}


void handleRoot() {
  if (server.hasArg("State")) {
    String command = server.arg("State");
    if (command.equals("F")) {
      
      forward();
      server.send(200, "text / plain", "Forward");
    }
    else  if (command.equals("B")) {
      backward();
      server.send(200, "text / plain", "Backward");
    }
    else  if (command.equals("L")) {
      turn_left();
      server.send(200, "text / plain", "Turn Left");
    }
    else  if (command.equals("R")) {
      turn_right();
      server.send(200, "text / plain", "Turn Right");
    }
    else  if (command.equals("S")) {
    
      stop_motors();
      server.send(200, "text / plain", "Stop");
    }
  }
}

void stop_motors() {
   digitalWrite(a, LOW);
  digitalWrite(b, LOW);
   digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}

void backward() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
}

void forward() {
 digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}

void turn_left() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
}

void turn_right() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
}
