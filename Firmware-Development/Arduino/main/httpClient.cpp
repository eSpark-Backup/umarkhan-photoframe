#include "httpClient.hpp"
#include <time.h>
#include <ArduinoJson.h>


NetworkClientSecure *client = new NetworkClientSecure;

 const char* rootCACertificate = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDejCCAmKgAwIBAgIQf+UwvzMTQ77dghYQST2KGzANBgkqhkiG9w0BAQsFADBX
MQswCQYDVQQGEwJCRTEZMBcGA1UEChMQR2xvYmFsU2lnbiBudi1zYTEQMA4GA1UE
CxMHUm9vdCBDQTEbMBkGA1UEAxMSR2xvYmFsU2lnbiBSb290IENBMB4XDTIzMTEx
NTAzNDMyMVoXDTI4MDEyODAwMDA0MlowRzELMAkGA1UEBhMCVVMxIjAgBgNVBAoT
GUdvb2dsZSBUcnVzdCBTZXJ2aWNlcyBMTEMxFDASBgNVBAMTC0dUUyBSb290IFI0
MHYwEAYHKoZIzj0CAQYFK4EEACIDYgAE83Rzp2iLYK5DuDXFgTB7S0md+8Fhzube
Rr1r1WEYNa5A3XP3iZEwWus87oV8okB2O6nGuEfYKueSkWpz6bFyOZ8pn6KY019e
WIZlD6GEZQbR3IvJx3PIjGov5cSr0R2Ko4H/MIH8MA4GA1UdDwEB/wQEAwIBhjAd
BgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDwYDVR0TAQH/BAUwAwEB/zAd
BgNVHQ4EFgQUgEzW63T/STaj1dj8tT7FavCUHYwwHwYDVR0jBBgwFoAUYHtmGkUN
l8qJUC99BM00qP/8/UswNgYIKwYBBQUHAQEEKjAoMCYGCCsGAQUFBzAChhpodHRw
Oi8vaS5wa2kuZ29vZy9nc3IxLmNydDAtBgNVHR8EJjAkMCKgIKAehhxodHRwOi8v
Yy5wa2kuZ29vZy9yL2dzcjEuY3JsMBMGA1UdIAQMMAowCAYGZ4EMAQIBMA0GCSqG
SIb3DQEBCwUAA4IBAQAYQrsPBtYDh5bjP2OBDwmkoWhIDDkic574y04tfzHpn+cJ
odI2D4SseesQ6bDrarZ7C30ddLibZatoKiws3UL9xnELz4ct92vID24FfVbiI1hY
+SW6FoVHkNeWIP0GCbaM4C6uVdF5dTUsMVs/ZbzNnIdCp5Gxmx5ejvEau8otR/Cs
kGN+hr/W5GvT1tMBjgWKZ1i4//emhA1JG1BbPzoLJQvyEotc03lXjTaCzv8mEbep
8RqZ7a2CPsgRbuvTPBwcOMBBmuFeU88+FSBX6+7iP0il8b4Z0QFqIwwMHfs/L6K1
vepuoxtGzi4CZ68zJpiq1UvSqTbFJjtbD4seiMHl
-----END CERTIFICATE-----
)EOF";

void begin() {
    setClock();
}

void setClock() {
    configTime(0, 0, "pool.ntp.org");

    Serial.print(F("Waiting for NTP time sync: "));
    time_t nowSecs = time(nullptr);
    while (nowSecs < 8 * 3600 * 2) {
        delay(500);
        Serial.print(F("."));
        yield();
        nowSecs = time(nullptr);
    }

    Serial.println();
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);
    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
}

void fetchSegmentsFromPayload(const String& payload) {
    const size_t capacity = 10 * 1024; // Adjust if needed
    DynamicJsonDocument doc(capacity);

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    JsonObject segments = doc["segments"];

    for (int i = 1; i <= 23; i++) {
        String segName = "seg" + String(i);

        if (segments.containsKey(segName)) {
            int percentageComplete = segments[segName]["percentageComplete"];
            bool isInverted = segments[segName]["isInverted"];

            Serial.printf("%s - percentageComplete: %d, isInverted: %s\n", 
                segName.c_str(), percentageComplete, isInverted ? "true" : "false");
              
        } else {
            Serial.printf("%s not found in segments.\n", segName.c_str());
        }
    }
}

void makeRequest(const char* url) {
    if (client) {
        client->setCACert(rootCACertificate);
        HTTPClient https;

        Serial.print("[HTTPS] begin...\n");
        if (https.begin(*client, url)) {
            Serial.print("[HTTPS] GET...\n");
            int httpCode = https.GET();

            if (httpCode > 0) {
                Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    String payload = https.getString();
                    Serial.println(payload);
                    fetchSegmentsFromPayload(payload);
                }
            } else {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            }

            https.end();
        } else {
            Serial.printf("[HTTPS] Unable to connect\n");
        }
    } else {
        Serial.println("Unable to create client");
    }
}
