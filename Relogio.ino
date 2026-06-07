// ============================================================
//  Relógio Inteligente com Arduino
//  Disciplina: Projetos de Hardware e Software
//  Curso: Engenharia da Computação
//  Autor: Matheus Barbosa
// ============================================================

#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ================= DISPLAY =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DS3231 rtc(SDA, SCL);

// ================= SENSOR DHT11 =================
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ================= BOTÕES =================
#define BTN_HORA 3
#define BTN_MINUTO 4
#define TEMPO_SEGURAR 3000  // tempo em ms para considerar pressionamento longo

unsigned long tempoHora = 0;
unsigned long tempoMinuto = 0;
bool segurouHora = false;
bool segurouMinuto = false;
bool ultimoHora = HIGH;
bool ultimoMinuto = HIGH;

// ================= VARIÁVEIS DHT =================
float temperatura = 0;
float umidade = 0;
unsigned long ultimaLeituraDHT = 0;
#define INTERVALO_DHT 2000  // leitura a cada 2 segundos para estabilidade

// ================= LOGO DA EQUIPE (bitmap 16x16) =================
const unsigned char logoEquipe[] PROGMEM = {
  0xFF, 0xFF, 0xE0, 0x07, 0x70, 0x0E, 0x38, 0x1C,
  0x1C, 0x38, 0x0E, 0x70, 0x07, 0xE0, 0x03, 0xC0,
  0x03, 0xC0, 0x07, 0xE0, 0x0E, 0x70, 0x1C, 0x38,
  0x38, 0x1C, 0x70, 0x0E, 0xE0, 0x07, 0xFF, 0xFF
};

// ================= DIA DA SEMANA EM PT-BR =================
void traduzirDia() {
  String d = rtc.getDOWStr(FORMAT_SHORT);

  if (d == "Sun") display.print("DOM");
  else if (d == "Mon") display.print("SEG");
  else if (d == "Tue") display.print("TER");
  else if (d == "Wed") display.print("QUA");
  else if (d == "Thu") display.print("QUI");
  else if (d == "Fri") display.print("SEX");
  else if (d == "Sat") display.print("SAB");
}

// ================= ANIMAÇÃO DE BOOT =================
void bootAnimado() {

  for (int i = 0; i <= 100; i += 5) {

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);

    display.setCursor(30, 18);
    display.print("RELOGIO");

    // barra de carregamento
    int barW = 100;
    int barX = 14;
    int barY = 45;

    display.drawRect(barX, barY, barW, 8, WHITE);

    int fill = (i * barW) / 100;
    display.fillRect(barX, barY, fill, 8, WHITE);

    display.display();
    delay(25);
  }

  display.clearDisplay();
}

// ================= SETUP =================
void setup() {

  pinMode(BTN_HORA, INPUT_PULLUP);
  pinMode(BTN_MINUTO, INPUT_PULLUP);

  rtc.begin();
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  bootAnimado();
}

// ================= LOOP PRINCIPAL =================
void loop() {

  // --- Leitura dos botões ---
  bool leituraHora = digitalRead(BTN_HORA);
  bool leituraMinuto = digitalRead(BTN_MINUTO);

  // Botão hora: pressionamento longo de 3s para incrementar
  if (leituraHora == LOW && ultimoHora == HIGH) {
    tempoHora = millis();
    segurouHora = false;
  }
  if (leituraHora == LOW && !segurouHora) {
    if (millis() - tempoHora >= TEMPO_SEGURAR) {
      segurouHora = true;
      delay(250);
    }
  }
  ultimoHora = leituraHora;

  // Botão minuto: incrementa ao pressionar
  if (leituraMinuto == LOW && ultimoMinuto == HIGH) {
    tempoMinuto = millis();
    segurouMinuto = false;
  }
  if (leituraMinuto == LOW && !segurouMinuto) {
    segurouMinuto = true;
    delay(250);
  }
  ultimoMinuto = leituraMinuto;

  // --- Leitura do DHT11 com intervalo ---
  if (millis() - ultimaLeituraDHT >= INTERVALO_DHT) {
    ultimaLeituraDHT = millis();
    float t = dht.readTemperature();
    float u = dht.readHumidity();
    if (!isnan(t)) temperatura = t;
    if (!isnan(u)) umidade = u;
  }

  // ================= INTERFACE GRÁFICA =================
  display.clearDisplay();

  // Logo da equipe (canto superior esquerdo)
  display.drawBitmap(0, 0, logoEquipe, 16, 16, WHITE);

  // Hora em destaque
  display.setTextSize(2);
  display.setCursor(20, 0);
  display.print(rtc.getTimeStr());

  // Linha separadora superior
  display.drawLine(0, 17, 128, 17, WHITE);

  // Dia da semana + data centralizados
  display.setTextSize(1);

  String dia = rtc.getDOWStr(FORMAT_SHORT);
  String data = rtc.getDateStr();

  String linha = "";

  if (dia == "Sun") linha += "DOM ";
  else if (dia == "Mon") linha += "SEG ";
  else if (dia == "Tue") linha += "TER ";
  else if (dia == "Wed") linha += "QUA ";
  else if (dia == "Thu") linha += "QUI ";
  else if (dia == "Fri") linha += "SEX ";
  else if (dia == "Sat") linha += "SAB ";

  linha += data;

  // Centralização automática do texto
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(linha, 0, 0, &x1, &y1, &w, &h);

  display.setCursor((128 - w) / 2, 24);
  display.print(linha);

  // Linha separadora inferior
  display.drawLine(0, 40, 128, 40, WHITE);

  // Temperatura e umidade
  display.setCursor(0, 48);
  display.print("T:");
  display.print(temperatura, 1);
  display.print("C");

  display.setCursor(70, 48);
  display.print("U:");
  display.print(umidade, 0);
  display.print("%");

  display.display();
  delay(100);
}
