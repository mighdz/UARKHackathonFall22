#include "twilio.hpp"
#include <WiFi.h>
#include <LiquidCrystal.h>

using namespace std;

// DON'T push these to GitHub!
static const char *ssid = "kevin";
static const char *password = "helloooo";

// Values from Twilio
static const char *account_sid = "AC7ef9ce6074affdba028008197fecb24b";
static const char *auth_token = "77b1cd00a7c9302e9418b3246d4ddb02";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+15862819803";

// Phone number should start with "+<countrycode>"
static const char *to_number = "+14793061703";

int resval = 0;
int water_sensor_pin = 33;
const int rs = 13, en = 12, d4 = 25, d5 = 26, d6 = 27, d7 = 14;
Twilio *twilio;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network...");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(1000);
  }
  Serial.println("Connected!");

  twilio = new Twilio(account_sid, auth_token);

  lcd.begin(16,2);
  lcd.print("WATER LEVEL: ");
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(0,1);
  delay(2000);

  resval = analogRead(water_sensor_pin);

  if (resval >= 0 && resval <= 700) { // Low Water
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WATER LEVEL: ");
    lcd.setCursor(0,1);
    lcd.print("Low Level");
    Serial.print("Low level -> ");
    Serial.println(resval);
    sendLowText();
  } else if (resval > 700 && resval <= 950) { // Medium Water
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WATER LEVEL: ");
    lcd.setCursor(0,1);
    lcd.print("Medium Level");
    Serial.print("Medium level -> ");
    Serial.println(resval);
  } else if (resval > 950) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WATER LEVEL: ");
    lcd.setCursor(0,1);
    lcd.print("High Level");
    Serial.print("High level -> ");
    Serial.println(resval);
  }
}

void sendLowText() {
//  String response;
//  static const char *message = "Smart Bowl\n\nLow water level!";
//  bool success = twilio->send_message(to_number, from_number, message, response);
//  if (success) {
//    Serial.println("Sent message successfully!");
//  } else {
//    Serial.println(response);
//  }
//  delay(30000);
}
