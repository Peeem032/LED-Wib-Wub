#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
const char* ssid = "Poonmy";
const char* password = "qwertyuiop12345";
const char* mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;

#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#define I2CADDR 0x21
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 0, 1, 2, 3 };
byte colPins[COLS] = { 4, 5, 6, 7 };
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574);

#define led1 12
#define led2 13
#define led3 14

#define led4 32
#define led5 33
#define led6 23

#define led7 18
#define led8 19
#define led9 4

// int level = 1;
int score = 0;
bool isOver = false;

int arr[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
}

void reconnect() {
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str()))
      Serial.println("Public emqx mqtt broker connected");
    else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
void refreshLed() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
}
void genLevel(int level) {
  for (int i = 0; i < level; i++) {
    arr[i] = random(1, 10);
  }
  for (int i = 0; i < level + 1; i++) {
    refreshLed();
    delay(300);
    if (arr[i] == 0) {
      break;
    } else if (arr[i] == 1) {
      digitalWrite(led1, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 2) {
      digitalWrite(led2, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 3) {
      digitalWrite(led3, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 4) {
      digitalWrite(led4, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 5) {
      digitalWrite(led5, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 6) {
      digitalWrite(led6, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 7) {
      digitalWrite(led7, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 8) {
      digitalWrite(led8, HIGH);
      Serial.println(arr[i]);
    } else if (arr[i] == 9) {
      digitalWrite(led9, HIGH);
      Serial.println(arr[i]);
    }
    delay(500);
  }
}

// void resetLevel() {
//   for (int i = 0; i < 2 + level; i++) {
//     arr[i] = 0;
//   }
// }

void checkLevel(int level) {
  for (int i = 0; i < level; i++) {
    if (isOver == true) {
      break;
    }
    while (true) {
      int key = keypad.getKey();
      key -= 48;
      if (key != -48) {
        if (key == 1) {
          digitalWrite(led1, HIGH);
          delay(300);
          digitalWrite(led1, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 2) {
          digitalWrite(led2, HIGH);
          delay(300);
          digitalWrite(led2, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 3) {
          digitalWrite(led3, HIGH);
          delay(300);
          digitalWrite(led3, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 4) {
          digitalWrite(led4, HIGH);
          delay(300);
          digitalWrite(led4, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 5) {
          digitalWrite(led5, HIGH);
          delay(300);
          digitalWrite(led5, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 6) {
          digitalWrite(led6, HIGH);
          delay(300);
          digitalWrite(led6, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 7) {
          digitalWrite(led7, HIGH);
          delay(300);
          digitalWrite(led7, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 8) {
          digitalWrite(led8, HIGH);
          delay(300);
          digitalWrite(led8, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else if (key == 9) {
          digitalWrite(led9, HIGH);
          delay(300);
          digitalWrite(led9, LOW);
          if (key != arr[i]) {
            Serial.println("Game Over!");
            isOver = true;
            break;
          } else {
            break;
          }
        } else {
          Serial.println("Game Over!");
          isOver = true;
          break;
        }
      }
    }
  }
  score++;
}

void setup() {

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  Wire.begin();
  keypad.begin(makeKeymap(keys));
  Serial.begin(115200);
  setup_wifi();
  reconnect();
}

void loop() {
  client.publish("ledwibwub/status", "0");
  while (1) {
    int key = keypad.getKey();
    if (key == '*')
      break;
  }
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);
  digitalWrite(led9, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
  delay(200);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);
  digitalWrite(led9, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
  delay(200);
  for (int i = 1; i < 12; i++) {
    char text[100];

    if (isOver == true) {
      isOver = false;
      memset(arr, 0, 10);
      sprintf(text, "%d", (i - 1) * -1);
      client.publish("ledwibwub/status", text);
      while (1) {
        int key = keypad.getKey();
        if (key == '#')
          break;
      }
      break;
    } else if (i == 11) {
      isOver = false;
      memset(arr, 0, 10);
      client.publish("ledwibwub/status", "100");
      while (1) {
        int key = keypad.getKey();
        if (key == '#')
          break;
      }
      break;
    }
    sprintf(text, "%d", i);
    client.publish("ledwibwub/status", text);
    genLevel(i);
    checkLevel(i);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, HIGH);
    digitalWrite(led9, HIGH);
    delay(400);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    digitalWrite(led9, LOW);
    Serial.println("===");
  }
}
