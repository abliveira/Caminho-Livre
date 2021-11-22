/* 
  
  Caminho Livre - Firmware Versão Dev

  Desenvolvido por A. OLIVEIRA (abliveira)

  Este firmware faz parte do projeto Caminho Livre, disponível em https://github.com/abliveira/Caminho-Livre

  Compatível com placas Arduino Pro Mini (5V), Arduino Nano e Arduino Uno. Esquema de montagem disponível no link.
  
  Licença de Uso
    A reprodução do projeto Caminho Livre deve ser feita somente seguindo a licença de uso 
    Creative Commons Attribution-ShareAlike 4.0 International License (https://creativecommons.org/licenses/by-sa/4.0/deed.pt_BR). 
    Os textos e imagens do repositório possuem direitos autorais protegidos por lei, 
    não abrangendo o conteúdo científico ou técnico (Lei nº 9.610, de 19 de fevereiro de 1998, 
    http://www.planalto.gov.br/ccivil_03/leis/l9610.htm).

*/


// Bibliotecas

#include <Wire.h>   // Biblioteca I2C nativa do Arduino
#include <VL53L0X.h>    // Biblioteca de interface com o sensor VL53L0X, desenvolvida por Pololu. Disponível em: https://github.com/pololu/vl53l0x-arduino
#include <U8glib.h>   // Biblioteca de interface com displays, desenvolvida por olikraus. Disponível em: https://github.com/olikraus/U8glib_Arduino


// VL53L0X

#define VL_ENABLE // Comentar desativa o sensor VL53L0X. Obs: Habilitar ambos sensores simultaneamente pode reduzir a velocidade de leitura

VL53L0X vl_sensor;

// É possível estender o alcance máximo do sensor de 1200mm para 2000mm através do modo long range.
// No entanto, é possível que ocorram imprecisões de leitura devido a reflexos de objetos.
// Funciona melhor em situação de baixa luz. Usar com cuidado.

// Descomentar ativa o modo long range:
//#define LONG_RANGE

// É possível alterar a velocidade do sensor através do tempo de amostragem. Há duas pré-definições:
//   HIGH_SPEED: alta velocidade, em troca de menor precisão
//   HIGH_ACCURACY: alta precisão, em troca de baixa velocidade
// Usar com cuidado.

// Descomentar uma linha de cada vez altera o tempo de amostragem. Se ambas estiverem comentadas, o tempo de amostragem segue o padrão de fábrica:
//#define HIGH_SPEED
//#define HIGH_ACCURACY

// Variáveis auxiliares
boolean vl_alert;
String VL_alert;
unsigned int vl_distance;
String VL_distance;
unsigned int vl_max_distance;
unsigned int vl_trig;
String VL_trig;


// HC-SR04

#define HC_ENABLE // Comentar desativa o sensor HC-SR04. Obs: Habilitar ambos sensores simultaneamente pode reduzir a velocidade de leitura

// Portas ligadas ao sensor HC-SR04
const int hc_trig_pin = 4;
const int hc_echo_pin = 2;

// Variáveis auxiliares
boolean hc_alert;
String HC_alert;
unsigned int hc_distance;
String HC_distance;
const int hc_max_distance = 400; // Determina a distância máxima do sensor HC-SR04
unsigned int hc_trig;
String HC_trig;


// Motores

// No modo de alerta progressivo, a frequência do padrão vibratório do alerta aumenta de acordo proximidade do obstáculo.
// Descomentar ativa o alerta progressivo:
//#define PROGRESSIVE_ALERT

const int min_alert_pulses = 2; // O mínimo de pulsos de vibração que serão gerados quando houver um alerta de obstáculo
const int motor1_pin = 3;    // Saída PWM do motor 1 ligada no pino 3 do microcontrolador
const int motor2_pin = 5;    // Saída PWM do motor 2 ligada no pino 5 do microcontrolador

const int min_pwm = 30;
const int max_pwm = 230;    // Limite máximo da escala de PWM no motor (Max = 255): Mais baixo consome menos, mais alto é mais fácil perceber



// Display

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);   // Definição do modelo de display utilizado (Ver referência da biblioteca U8glib)


// Função de leitura da distância do sensor HC-SR04. Dispensa o uso de biblioteca

int HC_getDistance (void) {

  // Reseta o pino Trig e aguarda 2 uS (Pode ser até 5uS)
  digitalWrite(hc_trig_pin, LOW);
  delayMicroseconds(2); 

  // Aciona o sensor mantendo o pino Trig alto por 10 uS
  digitalWrite(hc_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(hc_trig_pin, LOW);

  // Lê a duração do pulso enviado pelo echoPin. 
  // A função pulseIn() aguarda o pino ir de baixo para alto, e cronometra o tempo até o pino voltar para baixo
  long duration = pulseIn(hc_echo_pin, HIGH);

  // Se der timeout, pode ser que o sensor travou
  // Para destravar, muda o pino Echo para saída para dar um pulso, e volta para entrada
  if (duration == 0) { 
    pinMode(hc_echo_pin, OUTPUT);
    digitalWrite(hc_echo_pin, LOW);
    delayMicroseconds(200);
    pinMode(hc_echo_pin, INPUT);
  }

  // Calcula a distância através da duração do pulso
  int distance_cm = duration * 0.034 / 2;

  return distance_cm;
}


// Função de desenho no display

void draw(void) {

#ifdef VL_ENABLE
  // Formatação de strings do sensor VL53L0X para o display OLED
  if (vl_distance < vl_max_distance)
    VL_distance = "VL Dist: " + String (vl_distance) + " mm";
  else
    VL_distance = "VL Dist: ?";
  VL_trig = "VL Trig: <" + String (vl_trig) + " mm";
  VL_alert = "VL Alert: " + String (vl_alert);

  // Comandos de escrita no display OLED
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(0, 10);
  u8g.print(VL_distance);
  u8g.setPrintPos(0, 20);
  u8g.print(VL_trig);
  u8g.setPrintPos(0, 30);
  u8g.print(VL_alert);
  u8g.setPrintPos(0, 40);

  // Repetição de dados do OLED no Serial
  Serial.print(VL_distance);
  Serial.print("\t");
  Serial.print(VL_trig);
  Serial.print("\t");
  Serial.print(VL_alert);
  Serial.print("\t");
#endif

#ifdef HC_ENABLE
  // Formatação de strings do sensor HC-SR04 para o display OLED
  if (hc_distance < hc_max_distance)
    HC_distance = "HC Dist: " + String (hc_distance) + " cm";
  else
    HC_distance = "HC Dist: ?";
  HC_trig = "HC Trig: <" + String (hc_trig) + " cm";
  HC_alert = "HC Alert: " + String (hc_alert);

  // Comandos de escrita no display OLED
  u8g.setFont(u8g_font_6x12);
  u8g.print(HC_distance);
  u8g.setPrintPos(0, 50);
  u8g.print(HC_trig);
  u8g.setPrintPos(0, 60);
  u8g.print(HC_alert);

  // Repetição de dados do OLED no Serial
  Serial.print(HC_distance);
  Serial.print("\t");
  Serial.print(HC_trig);
  Serial.print("\t");
  Serial.println(HC_alert);
#endif
}


// Configuração Inicial

void setup() {

  // Inicialização do Serial
  Serial.begin(115200); // Obs: Reduzir o baud-rate pode reduzir a velocidade leitura dos sensores
  Serial.println("\nIniciando...");

  // Configuração de porta do LED embutido
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Configuração de portas ligadas ao sensor HC-SR04
  pinMode(hc_trig_pin, OUTPUT);   // Define a porta Trig como saída
  pinMode(hc_echo_pin, INPUT);    // Define a porta Echo como entrada

  // Configuração do display
  u8g.setRot180();   // Rotaciona o display. Comentar se não for necessário
  // Define a cor de acordo com o modelo de display utilizado
  if (u8g.getMode() == U8G_MODE_R3G3B2)
    u8g.setColorIndex(255);     // white
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
    u8g.setColorIndex(3);         // max intensity
  else if (u8g.getMode() == U8G_MODE_BW)
    u8g.setColorIndex(1);         // pixel on
  else if (u8g.getMode() == U8G_MODE_HICOLOR)
    u8g.setHiColorByRGB(255, 255, 255);

  // Inicialização do Sensor VL53L0X
  Wire.begin();
  vl_sensor.init();
  vl_sensor.setTimeout(500);
  //  Serial.println("Sensor inicializado.");

  // Configura o sensor VL53L0X de acordo com os modos escolhidos. Aqui, os modos podem ser customizados (Alterar os valores com cuidado)
#if defined LONG_RANGE
  // Controla o limite da taxa do sinal de retorno (padrão é 0.25 MCPS)
  vl_sensor.setSignalRateLimit(0.1);
  // Controlam os períodos de pulso do laser (padrão é 14 e 10 PCLKs, respectivamente)
  vl_sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  vl_sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // Determina a distância máxima no modo LONG RANGE
  vl_max_distance = 2200;
#else
  vl_max_distance = 1300;
#endif

#if defined HIGH_SPEED
  // Reduz o tempo de amostragem para 20 ms (O padrão de fábrica é 33 ms. Aqui, um valor rápido demais pode gerar falsos positivos e perturbar o usuário)
  vl_sensor.setMeasurementTimingBudget(20000);

#elif defined HIGH_ACCURACY
  // Aumenta o tempo de amostragem para 100 ms (O padrão de fábrica é 33 ms. Aqui, um valor lento demais pode comprometer a segurança do usuário)
  vl_sensor.setMeasurementTimingBudget(100000);
#endif
}


// Loop Principal

void loop() {

#ifdef VL_ENABLE

  // Lê o valor calculado pelo sensor VL530X em milímetros
  vl_distance = vl_sensor.readRangeSingleMillimeters();

  // Lê o valor configurado no potenciômetro
  int pot1 = analogRead(A2);

  // Determina a faixa de disparo do sensor de acordo com valor do trimpot e com a distância máxima do sensor
  vl_trig = map(pot1, 0, 1023, 0, vl_max_distance);

  // Determina se deve ser gerado um alerta para o usuário
  if (vl_distance > vl_max_distance) { // Se for maior que a distância máxima possível, ignora (erro)
    vl_alert = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (vl_distance >= vl_trig) { // Se for maior ou igual que o configurado no trimpot, não é gerado um alerta
    vl_alert = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (vl_distance < vl_trig) { // Se for menor que o configurado no trimpot, gera um alerta
    vl_alert = 1;
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (vl_alert) {
    int pwm_value = map(vl_distance, 0, vl_trig, max_pwm, min_pwm);
    analogWrite(motor1_pin, pwm_value);
  }
  else {
    analogWrite(motor1_pin, LOW);
  }
#endif

#ifdef HC_ENABLE

  // Calculating the distance
  hc_distance = HC_getDistance();

  // Lê o valor configurado no potenciômetro
  int pot2 = analogRead(A3);

  // Determina a faixa de disparo do sensor de acordo com valor do trimpot e com a distância máxima do sensor
  hc_trig = map(pot2, 0, 1023, 0, hc_max_distance);

  // Determina se deve ser gerado um alerta para o usuário
  if (hc_distance > hc_max_distance) { // Se for maior que a distância máxima possível, ignora (erro)
    hc_alert = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (hc_distance >= hc_trig) { // Se for maior ou igual que o configurado no trimpot, não é gerado um alerta
    hc_alert = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (hc_distance < hc_trig) { // Se for menor que o configurado no trimpot, gera um alerta
    hc_alert = 1;
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (hc_alert) {
    int pwm_value = map(hc_distance, 0, hc_trig, max_pwm, min_pwm);
    analogWrite(motor2_pin, pwm_value);
  }
  else {
    analogWrite(motor2_pin, LOW);
  }
#endif

  // Log via display e serial
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}
