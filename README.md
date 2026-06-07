# 🕐 Relógio Inteligente com Arduino

Projeto desenvolvido para a disciplina de **Projetos de Hardware e Software** do curso de **Engenharia da Computação**.

---

## 📋 Descrição

Relógio inteligente que exibe hora em tempo real, data, dia da semana em português, temperatura e umidade em um display OLED de 0,96". Conta com tela de inicialização animada com barra de carregamento, logo da equipe em bitmap e ajuste de hora/minuto por botões físicos.

---

## ⚙️ Funcionalidades

- ✅ Exibição de hora em tempo real (HH:MM:SS)
- ✅ Exibição de data e dia da semana em português (DOM, SEG, TER...)
- ✅ Leitura de temperatura (°C) via DHT11
- ✅ Leitura de umidade relativa (%) via DHT11
- ✅ Tela de inicialização animada com barra de carregamento
- ✅ Logo da equipe em bitmap no display OLED
- ✅ Ajuste de hora e minuto por botões físicos (pressionamento longo)
- ✅ Leitura do DHT com intervalo de 2 segundos para estabilidade

---

## 🔌 Componentes

| Componente         | Descrição                                       |
|--------------------|-------------------------------------------------|
| Arduino            | Microcontrolador principal                      |
| RTC DS3231         | Módulo de relógio em tempo real de alta precisão|
| DHT11              | Sensor de temperatura e umidade                 |
| OLED SSD1306       | Display gráfico 0,96" 128x64 via I2C            |
| Protoboard         | Montagem do circuito                            |
| 2x Botão           | Ajuste de hora e minuto                         |
| Jumpers            | Conexões entre componentes                      |

---

## 🔧 Mapeamento de Pinos

| Pino Arduino | Função              |
|--------------|---------------------|
| A4 (SDA)     | OLED SDA / RTC SDA  |
| A5 (SCL)     | OLED SCL / RTC SCL  |
| 7            | DHT11 Data          |
| 3            | Botão Hora          |
| 4            | Botão Minuto        |

---

## 📚 Bibliotecas utilizadas

- `DS3231.h` — Controle do RTC DS3231
- `Wire.h` — Comunicação I2C
- `Adafruit_GFX.h` — Gráficos para display
- `Adafruit_SSD1306.h` — Driver do display OLED
- `DHT.h` — Leitura do sensor de temperatura/umidade

---

## 📸 Fotos do Projeto

### Tela de Inicialização
> <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/44fd814c-5413-47b8-ac54-30dcff0640a6" />



### Display em funcionamento
> <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/f746d61b-2c7a-4237-9268-4d4b62d2ac1e" />

---

## 🚀 Como usar

1. Instale as bibliotecas acima na Arduino IDE
2. Faça o upload do código para o Arduino
3. Na primeira execução, configure a data/hora no RTC via código
4. Conecte os componentes conforme o mapeamento de pinos acima
5. Alimente o circuito e aguarde a animação de boot

### Ajuste de hora pelos botões
- **Segurar BTN_HORA (pino 3) por 3 segundos** → incrementa a hora
- **Pressionar BTN_MINUTO (pino 4)** → incrementa o minuto

---

## 🛠️ Tecnologias utilizadas

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

---

## 👤 Autor

**Matheus Barbosa**  
Estudante de Engenharia da Computação | Técnico em Eletroeletrônica (SENAI)

[![GitHub](https://img.shields.io/badge/GitHub-MatheusBarbosaEng-181717?style=flat&logo=github)](https://github.com/MatheusBarbosaEng)
