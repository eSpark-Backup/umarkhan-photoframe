#include "WebServerHandler.hpp"
#include "SPIFFHandler.hpp"
#include <Preferences.h>
#include <WiFi.h>
#include <time.h>
#include <sys/time.h>

// const int LED_PIN = 2;  // Built-in LED pin

WebServer server(80);
Preferences preferences;
time_t updatedTime ; // Actual definition and initialization

bool ledState = false;

struct Schedule {
      int onHour;
      int onMinute;
      int offHour;
      int offMinute;
};
Schedule ledSchedule = {0, 0, 0, 0};



// ---- Web Handlers ----

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
        vTaskDelay(pdMS_TO_TICKS(WIFI_ATTEMPTS_DURATION));

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
        server.send(400, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=failed';</script>");
      }
}

void handleSyncTime() { // Although the time is synced automatically the user can do it manually to
       currentDateTime = server.arg("datetime"); // Format: "2025-04-17T14:30"
         esp_sntp_stop();
      Serial.println("Received Time Sync Request:");
      Serial.println("Current DateTime: " + currentDateTime);
      String responseMessage;
      if (currentDateTime.length() > 0) {
        struct tm tm;
        if (strptime(currentDateTime.c_str(), "%Y-%m-%dT%H:%M", &tm)) {
          updatedTime = mktime(&tm); 
          struct timeval now = { .tv_sec = updatedTime };
          settimeofday(&now, NULL);  
          Serial.println("System time updated successfully.");
          responseMessage = "<h2>System time updated successfully!</h2>";
          server.send(200, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=timesync_success';</script>");
        } else {
          Serial.println("Failed to parse DateTime.");
          responseMessage = "<h2>System time updat Failed!</h2>";
          server.send(400, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=timesync_failed';</script>");
        }
      } else {
        responseMessage = "<h2> No DateTime Provided !</h2>";
        server.send(400, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=No timesync';</script>");
      }
}

void handleUploadSchedule() {
      String onTime = server.arg("onTime");   // Format: "06:00"
      String offTime = server.arg("offTime"); // Format: "22:30"
      String responseMessage;
      Serial.println("Received Schedule Update:");
      Serial.println("ON Time: " + onTime);
      Serial.println("OFF Time: " + offTime);

      if (onTime.length() > 0 && offTime.length() > 0) {
        ledSchedule.onHour = onTime.substring(0, 2).toInt();
        ledSchedule.onMinute = onTime.substring(3, 5).toInt();
        ledSchedule.offHour = offTime.substring(0, 2).toInt();
        ledSchedule.offMinute = offTime.substring(3, 5).toInt();
        // server.send(200, "text/html", "<h2>Schedule Updated!</h2>");
        responseMessage = "<h2>Schedule Updated!!</h2>";
        server.send(200, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=schedule_success';</script>");
      } else {
        // server.send(400, "text/html", "<h2>Invalid Schedule Provided</h2>");
        responseMessage = "<h2>Invalid Schedule Provided!</h2>";
        server.send(400, "text/html", htmlForm + responseMessage + "<script>window.location.href = '/?status=schedule_failed';</script>");
      }
}

// ---- LED Schedule Checker ----

void WebServerHandler::checkLEDStatus() {
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
      }
      // Serial.print("[WebServerHandler checkLEDStatus] time:"); Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

      int currentHour = timeinfo.tm_hour;
      int currentMinute = timeinfo.tm_min;


      if (currentHour == ledSchedule.onHour && currentMinute == ledSchedule.onMinute && !ledState) {
        ledState = true;
        Serial.println("LED Turned ON (Scheduled)");
      }

      if (currentHour == ledSchedule.offHour && currentMinute == ledSchedule.offMinute && ledState) {
        ledState = false;
        Serial.println("LED Turned OFF (Scheduled)");
      }
}

// ---- WiFi Setup ----

void WebServerHandler::startAccessPoint() {
      WiFi.mode(WIFI_AP_STA);
      WiFi.softAP(ESP_AP_ID, ESP_AP_PWD);
      Serial.println("Access Point Started");
      Serial.print("Access Point IP Address: ");
      Serial.println(WiFi.softAPIP());
}

void WebServerHandler::setupWiFi() {
      preferences.begin("wifi", true);
      String savedSSID = preferences.getString("ssid", "");
      String savedPassword = preferences.getString("password", "");

      startAccessPoint();

      if (savedSSID != "" && savedPassword != "") {
        Serial.println("Connecting to saved Wi-Fi credentials...");
        WiFi.begin(savedSSID.c_str(), savedPassword.c_str());

        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < WIFI_ATTEMPTS) {

          vTaskDelay(pdMS_TO_TICKS(WIFI_ATTEMPTS_DURATION));

          Serial.print(".");
          attempts++;
        }

        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("\nConnected to Wi-Fi!");
        } else {
          Serial.println("\nWi-Fi connection failed");
        }
      } else {
        Serial.println("\nWiFi credentials not found, using AP mode.");
      }
}

// ---- Web Server Setup ----

void WebServerHandler::setupWebServer() {
      server.on("/", HTTP_GET, handleRoot);
      server.on("/connect", HTTP_POST, handleConnect);
      server.on("/sync_time", HTTP_POST, handleSyncTime);
      server.on("/upload_schedule", HTTP_POST, handleUploadSchedule);
      server.begin();
      Serial.println("HTTP server started");
}

void WebServerHandler::init(){
    setupWiFi();
    setupWebServer();
}

void WebServerHandler::loop(){
      checkLEDStatus();
      server.handleClient();
      
}





