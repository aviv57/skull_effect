#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>

#define PIN_RED_1    4 // D2
#define PIN_GREEN_1  0 // D3
#define PIN_BLUE_1   2 // D4

#define PIN_RED_2    15 // D8
#define PIN_GREEN_2  1  // TX
#define PIN_BLUE_2   3  // RX

#define FADE_TIME_MS 350

// Define some colors as arrays of R, G, B values
#define RED {255, 0, 0}
#define GREEN {0, 255, 0}
#define BLUE {0, 0, 255}
#define YELLOW {255, 255, 0}
#define CYAN {0, 255, 255}
#define MAGENTA {255, 0, 255}
#define WHITE {255, 255, 255}
#define BLACK {0, 0, 0}

int black[] = BLACK;
int red[] = RED;
int yellow[] = YELLOW;
int green[] = GREEN;
int cyan[] = CYAN;
int blue[] = BLUE;
int magenta[] = MAGENTA;
int white[] = WHITE;

// Define a variable to store the current color
int current_color[3] = BLACK;

byte should_run_effect = 0;

// should be replaced
const char* ssid     = "SSID";
const char* password = "PASSWORD";
const String wait_for_event_url = "URL";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long lastTime = 0; 

unsigned long timerDelay = 15000;

// Define a function to set the color of the RGB LED
void setColor(int color[3]) {
  // Set the PWM duty cycle for each pin
  analogWrite(PIN_RED_1, color[0]);
  analogWrite(PIN_RED_2, color[0]);
  analogWrite(PIN_GREEN_1, color[1]);
  analogWrite(PIN_GREEN_2, color[1]);
  analogWrite(PIN_BLUE_1, color[2]);
  analogWrite(PIN_BLUE_2, color[2]);
  
  // Update the current color variable
  current_color[0] = color[0];
  current_color[1] = color[1];
  current_color[2] = color[2];
}

// Define a function to fade from one color to another in a given time
void fadeColor(int from_color[3], int to_color[3], int time) {
  // Calculate the difference between the colors
  int delta_red = to_color[0] - from_color[0];
  int delta_green = to_color[1] - from_color[1];
  int delta_blue = to_color[2] - from_color[2];
  
  // Calculate the number of steps to fade
  int steps = time / 10; // Assume each step is 10 ms
  
  // Calculate the increment for each color per step
  float increment_red = (float)delta_red / steps;
  float increment_green = (float)delta_green / steps;
  float increment_blue = (float)delta_blue / steps;
  
  // Loop through the steps
  for (int i = 0; i < steps; i++) {
    // Calculate the intermediate color
    int intermediate_red = from_color[0] + (int)(increment_red * i);
    int intermediate_green = from_color[1] + (int)(increment_green * i);
    int intermediate_blue = from_color[2] + (int)(increment_blue * i);
    
    // Set the intermediate color
    int intermediate_color[3] = {intermediate_red, intermediate_green, intermediate_blue};
    setColor(intermediate_color);
    
    // Wait for 10 ms
    delay(10);
  }
  
  // Set the final color
  setColor(to_color);
}

void skull_eyes_effect_loop_bing_gpt() {
   Serial.println("skull_eyes_effect_loop_bing_gpt called");

   fadeColor(black, red, FADE_TIME_MS);
   fadeColor(red, yellow, FADE_TIME_MS);
   fadeColor(yellow, green, FADE_TIME_MS);
   fadeColor(green, cyan, FADE_TIME_MS);   
   fadeColor(cyan, blue, FADE_TIME_MS);
   fadeColor(blue, magenta, FADE_TIME_MS);
   fadeColor(magenta, white, FADE_TIME_MS);
   fadeColor(white, black, FADE_TIME_MS);   
}

void pause(unsigned long pause_time) {
  setColor(black);
  delay(pause_time);
}

void setup() {
  pinMode(PIN_RED_1,   OUTPUT);
  pinMode(PIN_RED_1,   OUTPUT);
  pinMode(PIN_GREEN_1, OUTPUT);
  pinMode(PIN_GREEN_2, OUTPUT);
  pinMode(PIN_BLUE_1,  OUTPUT);  
  pinMode(PIN_BLUE_2,  OUTPUT);
  Serial.begin(115200);
  skull_eyes_effect_loop_bing_gpt();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void wait_for_event_loop(){
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED)
    {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    
    //create an HTTPClient instance
    HTTPClient https;
      
      // Your Domain name with URL path or IP address with path
      https.begin(*client, wait_for_event_url.c_str());
      https.setTimeout(20000);
        
      // Send HTTP GET request
      lastTime = millis();
      int httpResponseCode = https.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = https.getString();
        should_run_effect = (payload.indexOf("true") >= 15);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      https.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }

  if (should_run_effect)
    {
     should_run_effect = 0;
     skull_eyes_effect_loop_bing_gpt();
     pause(1);
     lastTime -= timerDelay;
    }    
  }
}

void loop(){
  wait_for_event_loop();
}