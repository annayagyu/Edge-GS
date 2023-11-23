#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>
#include <WiFi.h>

// Configurações de WiFi
const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

// Configurações de MQTT
const char *BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char *ID_MQTT = "vitakids_mqtt";
const char *TOPIC_PUBLISH_MSG = "fiap/iot/vitakids";
const char *TOPIC_SUBSCRIBE_DISABLE = "fiap/iot/DESABLE";

WiFiClient espClient;
PubSubClient MQTT(espClient);

#define PIN_LCD 0x27
LiquidCrystal_I2C lcd(PIN_LCD, 16, 2);  // Ajuste para 16x2

const int temperaturaLimite = 375;
const int batimentosLimiteSuperior = 100;
const int batimentosLimiteInferior = 60;
const int acucarLimiteInferior = 70;
const int acucarLimiteSuperior = 180;
const int vitaminasLimite = 80;
const int gorduraLimiteSuperior = 30;
const int gorduraLimiteInferior = 10;

// Protótipos de funções
void initWiFi();
void initMQTT();
void callbackMQTT(char *topic, byte *payload, unsigned int length);
void reconnectMQTT();
void reconnectWiFi();
void checkWiFIAndMQTT();

void initWiFi() {
  Serial.print("Conectando com a rede: ");
  Serial.println(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso: ");
  Serial.println(SSID);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(callbackMQTT);
}

void callbackMQTT(char *topic, byte *payload, unsigned int length) {
}

void reconnectMQTT() {
while (!MQTT.connected()) {
    Serial.print("Tentando conectar ao Broker MQTT...");
    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPIC_SUBSCRIBE_DISABLE);
    } else {
      Serial.println("Falha na conexão com MQTT. Tentando novamente em 2 segundos.");
      delay(2000);
    }
  }
}

void checkWiFIAndMQTT() {
  if (WiFi.status() != WL_CONNECTED) reconnectWiFi();
  if (!MQTT.connected()) reconnectMQTT();
}

void reconnectWiFi(void) {
  if (WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Wifi conectado com sucesso");
  Serial.print(SSID);
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void exibirNotificacao(String mensagem) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mensagem);
  Serial.println(mensagem);  // Adiciona esta linha para exibir no Serial Monitor
  delay(2000);
  lcd.clear();

  // Adiciona o envio da mensagem MQTT
  MQTT.publish(TOPIC_PUBLISH_MSG, mensagem.c_str());
}

void atualizarTela(int temp, int bpm, int acucar, int vit, int gordura) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temp) + "C");  // Removido o formato de uma casa decimal
  lcd.setCursor(0, 1);
  lcd.print("BPM: " + String(bpm));
  lcd.setCursor(0, 2);
  lcd.print("A: " + String(acucar));
  lcd.setCursor(0, 3);
  lcd.print("V: " + String(vit) + " G: " + String(gordura));
}

int simularSensor(int minValue, int maxValue) {
  return random(minValue, maxValue + 1);
}

void setup() {
  initWiFi();
  initMQTT();
  Serial.begin(115200);
  lcd.begin(16, 2);  // Ajuste para 16x2
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("VitaKids Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  checkWiFIAndMQTT();
  MQTT.loop();
  int temperatura = simularSensor(35, 39);
  int batimentos = simularSensor(50, 150);
  int acucar = simularSensor(50, 200);
  int vitaminas = simularSensor(70, 90);
  int gordura = simularSensor(5, 35);

  if (temperatura > temperaturaLimite) {
    exibirNotificacao("Temp Alta!");
  }
  if (batimentos > batimentosLimiteSuperior || batimentos < batimentosLimiteInferior) {
    exibirNotificacao("BPM Irregulares!");
  }
  if (acucar < acucarLimiteInferior || acucar > acucarLimiteSuperior) {
    exibirNotificacao("Acucar Irregular!");
  }
  if (vitaminas < vitaminasLimite) {
    exibirNotificacao("Vitaminas Baixas!");
  }
  if (gordura > gorduraLimiteSuperior || gordura < gorduraLimiteInferior) {
    exibirNotificacao("Gordura Irregular!");
  }

  atualizarTela(temperatura, batimentos, acucar, vitaminas, gordura);

  delay(5000);  // Aguarda 5 segundos antes de simular o próximo ciclo
}





