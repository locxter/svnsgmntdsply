#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Pins
const int DISPLAY_GND_PIN = D0;
const int DISPLAY_PIN_9 = 1;
const int DISPLAY_PIN_10 = 3;
const int DISPLAY_PIN_12 = D8;
const int DISPLAY_PIN_13 = D7;
const int DISPLAY_PIN_15 = D6;
const int DISPLAY_PIN_16 = D5;
const int DISPLAY_PIN_17 = D4;
const int DISPLAY_PIN_18 = D3;
const int DISPLAY_PIN_19 = D2;
const int DISPLAY_PIN_20 = D1;
const int DISPLAY_PIN_21 = 10;

// CURRENT_PATHS[digit][segment][GND pin (0 = display pin 1; 1 = display pin 2) / VCC pin]
const int CURRENT_PATHS[3][7][2] = {
  {
    {1, DISPLAY_PIN_13},
    {1, DISPLAY_PIN_10},
    {1, DISPLAY_PIN_12},
    {0, DISPLAY_PIN_12},
    {0, DISPLAY_PIN_9},
    {0, DISPLAY_PIN_13},
    {0, DISPLAY_PIN_10}
  },
  {
    {0, DISPLAY_PIN_15},
    {0, DISPLAY_PIN_16},
    {0, DISPLAY_PIN_17},
    {1, DISPLAY_PIN_17},
    {1, DISPLAY_PIN_18},
    {1, DISPLAY_PIN_15},
    {1, DISPLAY_PIN_16}
  },
  {
    {1, DISPLAY_PIN_21},
    {1, DISPLAY_PIN_19},
    {1, DISPLAY_PIN_20},
    {0, DISPLAY_PIN_20},
    {0, DISPLAY_PIN_18},
    {0, DISPLAY_PIN_21},
    {0, DISPLAY_PIN_19}
  }
};

// NUMBER_CODES[number][segment]
const bool NUMBER_CODES[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}
};

// UPPERCASE_LETTER_CODES[uppercase letter][segment]
const bool UPPERCASE_LETTER_CODES[26][7] = {
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 1, 1},
    {0, 0, 0, 1, 1, 1, 0},
    {1, 1, 0, 1, 0, 1, 0},
    {1, 1, 1, 0, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 0},
    {1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 0, 1, 0},
    {1, 0, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 0, 0, 1},
    {0, 1, 0, 1, 0, 1, 1},
    {1, 1, 0, 1, 1, 0, 1}
};

// LOWERCASE_LETTER_CODES[lowercase letter][segment]
const bool LOWERCASE_LETTER_CODES[26][7] = {
  {0, 0, 1, 1, 0, 0, 1},
  {0, 0, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 0, 1},
  {0, 1, 1, 1, 1, 0, 1},
  {0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1},
  {1, 0, 0, 1, 1, 0, 1},
  {0, 0, 1, 0, 1, 1, 1},
  {1, 0, 0, 1, 1, 0, 0},
  {1, 0, 1, 1, 0, 0, 0},
  {1, 0, 0, 1, 0, 1, 1},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 1, 0, 1, 0, 1},
  {0, 0, 1, 0, 1, 0, 1},
  {0, 0, 1, 1, 1, 0, 1},
  {1, 1, 0, 0, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 1},
  {0, 0, 0, 0, 1, 0, 1},
  {0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 0, 0, 0},
  {0, 1, 0, 1, 0, 1, 0},
  {0, 0, 0, 1, 0, 0, 1},
  {0, 1, 1, 1, 0, 1, 1},
  {0, 0, 0, 1, 0, 0, 1},
};

// OTHER_CHARACTER_CODES[character][segment]
const bool OTHER_CHARACTER_CODES[9][7] = {
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1, 0},
  {1, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 0, 0},
  {1, 1, 0, 0, 1, 0, 1}
};

// WiFi and user authentication related constants
const char* SSID = "";
const char* WIFI_PASSWORD = "";
const char* HOSTNAME = "svnsgmntdsply";
const char* USERNAME = "svnsgmntdsply";
const char* PASSWORD = "svnsgmntdsply";

// Server object
ESP8266WebServer server(80);

// Other variables
String text = "";
int animationInterval = 1000;
bool isReceiving = false;
unsigned long currentMillis = 0;
unsigned long lastMillis = 0;
int textPosition = 0;
bool displayedCodes[3][7];

// Function to load the settings from storage into RAM
void loadSettings();

// Function to save the settings from RAM into storage
void saveSettings();

// Function to display a seven-segment code
void displayCode(int digit, bool code[]);

// Setup function
void setup() {
    // Initialize filesystem
    LittleFS.begin();
    loadSettings();
    // Initialize display and WiFi connection
    pinMode(DISPLAY_GND_PIN, OUTPUT);
    digitalWrite(DISPLAY_GND_PIN, LOW);
    pinMode(DISPLAY_PIN_9, OUTPUT);
    digitalWrite(DISPLAY_PIN_9, LOW);
    pinMode(DISPLAY_PIN_10, OUTPUT);
    digitalWrite(DISPLAY_PIN_10, LOW);
    pinMode(DISPLAY_PIN_12, OUTPUT);
    digitalWrite(DISPLAY_PIN_12, LOW);
    pinMode(DISPLAY_PIN_13, OUTPUT);
    digitalWrite(DISPLAY_PIN_13, LOW);
    pinMode(DISPLAY_PIN_15, OUTPUT);
    digitalWrite(DISPLAY_PIN_15, LOW);
    pinMode(DISPLAY_PIN_16, OUTPUT);
    digitalWrite(DISPLAY_PIN_16, LOW);
    pinMode(DISPLAY_PIN_17, OUTPUT);
    digitalWrite(DISPLAY_PIN_17, LOW);
    pinMode(DISPLAY_PIN_18, OUTPUT);
    digitalWrite(DISPLAY_PIN_18, LOW);
    pinMode(DISPLAY_PIN_19, OUTPUT);
    digitalWrite(DISPLAY_PIN_19, LOW);
    pinMode(DISPLAY_PIN_20, OUTPUT);
    digitalWrite(DISPLAY_PIN_20, LOW);
    pinMode(DISPLAY_PIN_21, OUTPUT);
    digitalWrite(DISPLAY_PIN_21, LOW);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    // Initialize mDNS
    MDNS.begin(HOSTNAME);
    // Initialize server
    server.on("/", [&]() {
        if (!server.authenticate(USERNAME, PASSWORD)) {
            server.requestAuthentication();
        } else {
            File file;
            String content;
            if (server.method() == HTTP_POST && server.hasArg("text") && server.hasArg("animation-interval")) {
                isReceiving = true;
                text = server.arg("text") + " ";
                animationInterval = server.arg("animation-interval").toInt();
                saveSettings();
                lastMillis = currentMillis - animationInterval;
                textPosition = 0;
                isReceiving = false;
            }
            file = LittleFS.open("/index.html", "r");
            while (file.available()) {
                content += (char) file.read();
            }
            file.close();
            server.send(200, "text/html", content);
        }
    });
    server.serveStatic("/data/settings.csv", LittleFS, "/data/settings.csv");
    server.serveStatic("/styles/dark.min.css", LittleFS, "/styles/dark.min.css");
    server.onNotFound([&]() {
        server.send(404, "text/plain", "Resource not found");
    });
    server.begin();
    lastMillis = millis() - animationInterval;
}

// Main function
void loop() {
    if (!isReceiving) {
        currentMillis = millis();
        if (currentMillis - lastMillis > animationInterval) {
            // Select characters to display and convert them from ASCII into seven-segment codes
            for (int i = 0; i < 3; i++) {
                int character = (int) text.charAt((textPosition + i) % text.length());
                if (character >= '0' && character <= '9') {
                    for (int j = 0; j < 7; j++) {
                        displayedCodes[i][j] = NUMBER_CODES[character - '0'][j];
                    }
                } else if (character >= 'A' && character <= 'Z') {
                    for (int j = 0; j < 7; j++) {
                        displayedCodes[i][j] = UPPERCASE_LETTER_CODES[character - 'A'][j];
                    }
                } else if (character >= 'a' && character <= 'z') {
                    for (int j = 0; j < 7; j++) {
                        displayedCodes[i][j] = LOWERCASE_LETTER_CODES[character - 'a'][j];
                    }
                } else {
                    switch (character) {
                        case ' ':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[0][j];
                            }
                            break;
                        case '_':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[1][j];
                            }
                            break;
                        case '-':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[2][j];
                            }
                            break;
                        case '=':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[3][j];
                            }
                            break;
                        case '"':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[4][j];
                            }
                            break;
                        case '\'':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[5][j];
                            }
                            break;
                        case '(':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[6][j];
                            }
                            break;
                        case ')':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[7][j];
                            }
                            break;
                        case '?':
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[8][j];
                            }
                            break;
                        default:
                            for (int j = 0; j < 7; j++) {
                                displayedCodes[i][j] = OTHER_CHARACTER_CODES[0][j];
                            }
                            break;
                    }
                }
            }
            textPosition = (textPosition + 1) % text.length();
            lastMillis = currentMillis;
        }
        // Display seven-segment codes of selected characters
        for (int i = 0; i < 3; i++) {
            displayCode(i, displayedCodes[i]);
        }
    }
    server.handleClient();
    MDNS.update();
}

// Function to load the settings from storage into RAM
void loadSettings() {
    File file = LittleFS.open("/data/settings.csv", "r");
    while (file.available()) {
        String line = file.readStringUntil('\n');
        String key = line.substring(0, line.indexOf(','));
        line.remove(0, line.indexOf(',') + 2);
        if (key == "text") {
            text = line;
        } else if (key == "animation-interval") {
            animationInterval = line.toInt();;
        }
    }
    file.close();
}

// Function to save the settings from RAM into storage
void saveSettings() {
    File file = LittleFS.open("/data/settings.csv", "w");
    file.print("Key:, Value:\n");
    file.print("text, " + text + "\n");
    file.print("animation-interval, " + String(animationInterval) + "\n");
    file.close();
}

// Function to display a seven-segment code
void displayCode(int digit, bool code[]) {
    digitalWrite(DISPLAY_GND_PIN, LOW);
    digitalWrite(DISPLAY_PIN_9, LOW);
    digitalWrite(DISPLAY_PIN_10, LOW);
    digitalWrite(DISPLAY_PIN_12, LOW);
    digitalWrite(DISPLAY_PIN_13, LOW);
    digitalWrite(DISPLAY_PIN_15, LOW);
    digitalWrite(DISPLAY_PIN_16, LOW);
    digitalWrite(DISPLAY_PIN_17, LOW);
    digitalWrite(DISPLAY_PIN_18, LOW);
    digitalWrite(DISPLAY_PIN_19, LOW);
    digitalWrite(DISPLAY_PIN_20, LOW);
    digitalWrite(DISPLAY_PIN_21, LOW);
    for (int i = 0; i < 7; i++) {
        if (i > 0) {
            digitalWrite(CURRENT_PATHS[digit][i - 1][1], LOW);
        }
        digitalWrite(DISPLAY_GND_PIN, CURRENT_PATHS[digit][i][0]);
        digitalWrite(CURRENT_PATHS[digit][i][1], code[i]);
        delayMicroseconds(1000);
    }
}
