#include "WebServerHandler.hpp"
#include "SPIFFHandler.hpp"

const int LED_PIN = 2;

unsigned long ledInterval = 0;  
bool ledBlinking = false;
unsigned long previousMillis = 0;
bool ledState = false;

WebServer server(80);
Preferences preferences;

void webServerTask(void* pvParameters);


void handleRoot() {
  server.send(200, "text/html", htmlForm);
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  Serial.print("Connecting to Wi-Fi with SSID: ");
  Serial.println(ssid);

  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();

  WiFi.begin(ssid.c_str(), password.c_str());

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < WIFI_ATTEMPTS) {
    delay(WIFI_ATTEMPTS_DURATION);
    Serial.print(".");
    attempts++;
  }

  String responseMessage;
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to Wi-Fi!");
    responseMessage = "<h2>Wi-Fi Connected Successfully!</h2><p>IP Address: " + WiFi.localIP().toString() + "</p>";
    server.send(200, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=connected';</script>");
  } else {
    responseMessage = "<h2>Connection Failed. Please try again.</h2>";
    server.send(200, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=failed';</script>");
  }
}

void handleLEDControl() {
  String ledStateParam = server.arg("state");
  String timePeriodParam = server.arg("timePeriod");

  if (ledStateParam == "start" && timePeriodParam.length() > 0) {
    ledInterval = timePeriodParam.toInt() * 1000;  // Convert seconds to milliseconds
    ledBlinking = true;
    Serial.println("\nLED Blinking Started");

    if (ledBlinking) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= ledInterval) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        Serial.println(ledState ? "LED ON" : "LED OFF");
      }
    }

  } else if (ledStateParam == "stop") {
    ledBlinking = false;
    digitalWrite(LED_PIN, LOW);
    Serial.println("\nLED Stopped");
  }
  server.send(200, "text/html", htmlForm + "<h2>LED Control: " + ledStateParam + "</h2>");
}

void startAccessPoint() {
#if WIFI_DEBUG
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ESP_AP_ID, ESP_AP_PWD);
  Serial.println("Access Point Started");
  Serial.print("Access Poin IP Address: ");
  Serial.println(WiFi.softAPIP());

#endif
}

// Initialize Wi-Fi and AP mode
void setupWiFi() {
  preferences.begin("wifi", true);
  String savedSSID = preferences.getString("ssid", "");
  String savedPassword = preferences.getString("password", "");

  startAccessPoint();

  if (savedSSID != "" && savedPassword != "") {
    Serial.println("Connecting to saved Wi-Fi credentials...");
    WiFi.begin(savedSSID.c_str(), savedPassword.c_str());

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < WIFI_ATTEMPTS) {
      delay(WIFI_ATTEMPTS_DURATION);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to Wi-Fi!");
    } else {
      Serial.println("\nWi-Fi connection failed");
    }
  } else {
    Serial.println("\nWiFi credentials isn't available in Memory, Starting AP mode.");
  }
}

void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/led", HTTP_GET, handleLEDControl);
  server.begin();
  Serial.println("HTTP server started");
}

void createTask() {
  xTaskCreate(webServerTask, "webServerTask", 4096, NULL, 0, NULL);
}

void webServerTask(void* pvParameters) {

  setupWebServer();

  while (1) {
    server.handleClient();
    vTaskDelay(10 / portTICK_PERIOD_MS);  // delay 10 ms
  }
}
