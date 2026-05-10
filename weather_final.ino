#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

/* ---------------- WIFI ---------------- */
const char* ssid     = "AI LAB";
const char* password = "11223344";
const char* hostName = "weatherstation";

/* ---------------- DHT11 ---------------- */
#define DHTPIN  D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* ---------------- OLED ---------------- */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ---------------- SERVER ---------------- */
ESP8266WebServer server(80);

/* ---------------- DATA ---------------- */
float temp = 0;
float hum = 0;
float heatIndexVal = 0;
float minTemp = 999;
float maxTemp = -999;
float lastTemp = 0;

unsigned long lastRead = 0;
unsigned long lastPage = 0;

int page = 0;

/* ===================================================== */
/* ---------------- HELPER FUNCTIONS ------------------- */
/* ===================================================== */

String comfortStatus(float t, float h) {
  if (t > 32) return "Hot";
  if (h > 75) return "Humid";
  if (t < 18) return "Cold";
  if (h < 30) return "Dry";
  return "Comfort";
}

String trendStatus() {
  if (temp > lastTemp) return "Rising";
  if (temp < lastTemp) return "Falling";
  return "Stable";
}

/* ===================================================== */
/* ---------------- WEB PAGE --------------------------- */
/* ===================================================== */

void handleRoot() {

  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Mini Weather Station</title>
<meta name='viewport' content='width=device-width, initial-scale=1'>
<meta http-equiv='refresh' content='5'>
<style>
body{
  font-family:Arial;
  background:#111;
  color:white;
  text-align:center;
  margin:0;
  padding:20px;
}
h1{
  color:#00ffcc;
}
.card{
  background:#222;
  padding:15px;
  margin:10px auto;
  border-radius:15px;
  max-width:350px;
  font-size:22px;
}
.small{
  color:#aaa;
  font-size:16px;
}
</style>
</head>
<body>
<h1>Mini Weather Station</h1>
)rawliteral";

  html += "<div class='card'>Temperature: " + String(temp,1) + " C</div>";
  html += "<div class='card'>Humidity: " + String(hum,1) + " %</div>";
  html += "<div class='card'>Feels Like: " + String(heatIndexVal,1) + " C</div>";
  html += "<div class='card'>Current Condition: " + comfortStatus(temp, hum) + "</div>";
  html += "<div class='card'>Min Temp: " + String(minTemp,1) + " C</div>";
  html += "<div class='card'>Max Temp: " + String(maxTemp,1) + " C</div>";
  html += "<div class='card'>Trend: " + trendStatus() + "</div>";
  html += "<div class='small'>Auto refresh every 5 sec</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

/* ===================================================== */
/* ---------------- OLED DISPLAY ---------------------- */
/* ===================================================== */

void showOLED() {

  display.clearDisplay();
  display.setTextColor(WHITE);

  if (page == 0) {
    display.setTextSize(1);
    display.setCursor(20, 0);
    display.println("Weather Data");

    display.setTextSize(1.5);
    display.setCursor(0, 18);
    display.print("Temp :");
    
    display.setTextSize(2);
    display.setCursor(45, 14);
    display.print(temp, 1);
    display.print("C");
    
    display.setTextSize(1.5);
    display.setCursor(0, 46);
    display.print("Hum  :");
    
    display.setTextSize(2);
    display.setCursor(45, 42);
    display.print(hum, 0);
    display.print("%");
  }
  else if (page == 1) {
    display.setTextSize(1);
    display.setCursor(28, 0);
    display.println("Condition");
  
    display.setTextSize(2);
    display.setCursor(0, 28);
    display.println(comfortStatus(temp, hum));
  }
  else if (page == 2) {
    display.setTextSize(1);
    display.setCursor(45, 0);
    display.println("Stats");

    display.setCursor(0, 22);
    display.print("Min: ");
    display.print(minTemp, 1);

    display.setCursor(0, 42);
    display.print("Max: ");
    display.print(maxTemp, 1);
  }

  else if (page == 3) {
    display.setTextSize(1);
    display.setCursor(45, 0);
    display.println("Trend");

    display.setTextSize(2);
    display.setCursor(0, 28);
    display.println(trendStatus());
  }

  display.display();
}

/* ===================================================== */
/* ---------------- SENSOR READ ----------------------- */
/* ===================================================== */

void readSensor() {

  lastTemp = temp;

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("DHT Sensor Error");
    return;
  }

  temp = t;
  hum = h;

  heatIndexVal = dht.computeHeatIndex(temp, hum, false);

  if (temp < minTemp) minTemp = temp;
  if (temp > maxTemp) maxTemp = temp;

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C   Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
}

/* ===================================================== */
/* ---------------- WIFI CONNECT ---------------------- */
/* ===================================================== */

void connectWiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostName);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println("Connecting WiFi...");

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.println("Connecting WiFi");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(hostName)) {
    Serial.println("mDNS Started");
    Serial.println("Open: http://weatherstation.local");
  }
}

/* ===================================================== */
/* ---------------- SETUP ----------------------------- */
/* ===================================================== */

void setup() {

  Serial.begin(115200);

  dht.begin();
  Wire.begin(D2, D1);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Startup Page 1
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10,18);
  display.println("Weather");
  display.setCursor(18,42);
  display.println("Station");
  display.display();
  delay(2000);

  connectWiFi();

  server.on("/", handleRoot);
  server.begin();

  // Startup Page 2
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15,18);
  display.println("Open Browser");
  display.setCursor(0,40);
  display.println("weatherstation.local");
  display.display();
  delay(2000);

  lastPage = millis();
}

/* ===================================================== */
/* ---------------- LOOP ------------------------------ */
/* ===================================================== */

void loop() {

  server.handleClient();
  MDNS.update();

  if (millis() - lastRead > 3000) {
    readSensor();
    lastRead = millis();
  }

  if (millis() - lastPage > 3000) {
    page++;
    if (page > 3) page = 0;

    showOLED();
    lastPage = millis();
  }
}
