/* 
  Caminho Livre - Firmware Versão Prod

  Desenvolvido por A. OLIVEIRA (abliveira)

  Este firmware faz parte do projeto Caminho Livre, disponível em https://github.com/abliveira/Caminho-Livre

  Compatível com a placa customizada do projeto. Layout disponível no link.

  Licença de Uso
    A reprodução do projeto Caminho Livre deve ser feita somente seguindo a licença de uso 
    Creative Commons Attribution-ShareAlike 4.0 International License (https://creativecommons.org/licenses/by-sa/4.0/deed.pt_BR). 
    Os textos e imagens do repositório possuem direitos autorais protegidos por lei, 
    não abrangendo o conteúdo científico ou técnico (Lei nº 9.610, de 19 de fevereiro de 1998, 
    http://www.planalto.gov.br/ccivil_03/leis/l9610.htm).

  Changelog:
  - Comentários e renomeação de variáveis
  - Correção de bug de vibração quando no modo de alerta progressivo
  - Leitura de bateria no main loop
  - Tradução dos comentários originais

  To do:
  - Existe uma situação na qual o alerta da bateria pode não ser executado pois o alerta padrao estara rodando. Deveria tentar de novo, e se conseguir ser executado, aí sim espera mais 5min
  - Possivelmente é uma boa inverter no inicio a quantidade de pulsos (menos pulsos, melhor a bateria)
  - Atualizar biblioteca VL53
  - Colocar autorias
  - Incluir no cabeçalho instruções de configurações de compilação
  - Corrigir pinos para placa PCB

*/

// Bibliotecas

#include <Wire.h>   // Biblioteca I2C nativa do Arduino
#include <VL53L0X.h>    // Biblioteca de interface com o sensor VL53L0X, desenvolvida por Pololu. Disponível em: https://github.com/pololu/vl53l0x-arduino


// Variáveis auxiliares

boolean alert = 0;
boolean alert_bat = 0;
boolean last_alert_pulse = 0;
boolean last_bat_pulse = 0;
int alert_pulse_counter = 0;
int bat_pulse_counter = 0;
int battery_value;
int battery_voltage_mv;
int battery_status;
int max_distance;
int pwm_value = 0;
unsigned long previous_ms_alert_pulse = 0;  // Último pulso do alerta gerado em ms
unsigned long previous_ms_bat_pulse = 0;   // Último pulso do alerta da bateria gerado em ms
unsigned long previous_ms_bat_read = 0;  // Última leitura da bateria em ms


// Parâmetros

const int bat_pulses = 3;   // Quantidade de pulsos do alerta da bateria
const int bat_pulse_interval = 1000;    // Duração e intervalo de tempo dos pulsos do alerta da bateria
const unsigned long bat_read_interval = 30000;    // Intervalo de tempo entre a leitura de tensão da bateria
int alert_pulse_interval = 150;   // Duração e intervalo de tempo dos pulsos do alerta fixo
const int min_alert_pulse_interval = 70;    // Duração e intervalo de tempo mínimo entre os pulsos do alerta progressivo
const int max_alert_pulse_interval = 350;   // Duração e intervalo de tempo máximo entre os pulsos do alerta progressivo


// VL53L0X

VL53L0X sensor;

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


// Motor

// No modo de alerta progressivo, a frequência do padrão vibratório do alerta aumenta de acordo proximidade do obstáculo.
// Descomentar ativa o alerta progressivo:
//#define PROGRESSIVE_ALERT

const int min_alert_pulses = 2; // O mínimo de pulsos de vibração que serão gerados quando houver um alerta de obstáculo
const int motor_pin = 3;    // Saída PWM do motor ligada no pino 3 do microcontrolador
const int max_pwm = 230;    // Limite máximo da escala de PWM no motor (Max = 255): Mais baixo consome menos, mais alto é mais fácil perceber


// Função de leitura de tensão da bateria

void read_battery () {

  // Lê o valor da porta analógica ligada ao divisor de tensão do sinal da bateria
  battery_value = analogRead(A2);
  
  // O valor máximo da tensão da bateria lido pela porta analógica é aproximadamente 651:
  // Tensão máxima da bateria: 4,2 V. Após o divisor de tensão: 2,1 V. Valor de referência da porta analógica: 3,3 V. Range do ADC: 0  a 1023. Logo: 3,3/2,1*1023 = 651
  battery_voltage_mv = map(battery_value, 0, 651, 0, 4200); // Conversão do valor ADC para milivolts

  // Determina o status para o padrão de vibração para informar a tensão
  if (battery_voltage_mv > 3900)   // Cheia de 3,9 V a 4,2 V
    battery_status = 3;
  else if (battery_voltage_mv > 3600)    // Regular de 3,6 a 3,9 V
    battery_status = 2;
  else    // Fraca abaixo de 3,6 V
    battery_status = 1;
}


// Configuração Inicial

void setup() {

  // Inicialização do Serial
  Serial.begin(115200); // Obs: Reduzir o baud-rate pode reduzir a velocidade leitura do sensor
  Serial.println("\nIniciando...");

  // Sinaliza a inicialização da placa com um padrão de vibração
  analogWrite(motor_pin, max_pwm);
  delay(500);
  analogWrite(motor_pin, LOW);
  delay(500);

  // Inicialização do Sensor
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  Serial.println("Sensor inicializado.");

  // Sinaliza a inicialização do sensor com um padrão de vibração
  analogWrite(motor_pin, max_pwm);
  delay(200);
  analogWrite(motor_pin, LOW);
  delay(150);
  analogWrite(motor_pin, max_pwm);
  delay(200);
  analogWrite(motor_pin, LOW);
  delay(150);

  // Configura o sensor de acordo com os modos escolhidos. Aqui, os modos podem ser customizados (Alterar os valores com cuidado)
#if defined LONG_RANGE
  // Controla o limite da taxa do sinal de retorno (padrão é 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // Controlam os períodos de pulso do laser (padrão é 14 e 10 PCLKs, respectivamente)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // Determina a distância máxima no modo LONG RANGE
  max_distance = 2200;
#else
  max_distance = 1300;
#endif

#if defined HIGH_SPEED
  // Reduz o tempo de amostragem para 20 ms (O padrão de fábrica é 33 ms. Aqui, um valor rápido demais pode gerar falsos positivos e perturbar o usuário)
  sensor.setMeasurementTimingBudget(20000);

#elif defined HIGH_ACCURACY
  // Aumenta o tempo de amostragem para 100 ms (O padrão de fábrica é 33 ms. Aqui, um valor lento demais pode comprometer a segurança do usuário)
  sensor.setMeasurementTimingBudget(100000);
#endif

  delay(1500);

  // Checa a tensão da bateria
  read_battery();

  // Log via Serial
  Serial.print("Tensão da Bateria (ADC): ");
  Serial.print(battery_value);
  Serial.print("\tTensão da Bateria: ");;
  Serial.print(battery_voltage_mv);
  Serial.print(" mV");
  if (battery_status == 3) // Cheia de 3,9 V a 4,2 V
    Serial.println(". Tensão ok.\t Nível 3/3\n");
  else if (battery_status == 2)    // Regular de 3,6 a 3,9 V
    Serial.println(". Tensão regular.\t Nível 2/3\n");
  else    // Fraca abaixo de 3,6 V
    Serial.println(". Tensão fraca.\t Nível 1/3\n");

  // Gera o padrão de vibração para informar a tensão
  for (int i = 0; i < battery_status; i++) {
    analogWrite(motor_pin, max_pwm);
    delay(1000);
    analogWrite(motor_pin, LOW);
    delay(500);
  }

  delay(500);
}


// Loop Principal

void loop() {

  // Lê o valor calculado pelo sensor em milímetros
  int distance_mm_value = sensor.readRangeSingleMillimeters();

  // Lê o valor configurado no trimpot
  int pot_value = analogRead(A3);

  // Determina a faixa de disparo do sensor de acordo com valor do trimpot e com a distância máxima do sensor
  int trig_value = map(pot_value, 0, 1023, 0, max_distance);

  // Determina se deve ser gerado um alerta para o usuário
  if (distance_mm_value > max_distance) // Se for maior que a distância máxima possível, ignora (erro)
    alert = 0;
  else if (distance_mm_value >= trig_value) // Se for maior ou igual que o configurado no trimpot, não é gerado um alerta
    alert = 0;
  else if (distance_mm_value < trig_value) // Se for menor que o configurado no trimpot, gera um alerta
    alert = 1;

#ifdef PROGRESSIVE_ALERT   // Calcula o intervalo de tempo entre os pulsos se o alerta estiver no modo progressivo
  
  if (alert) {
    
    // A distância lida é transformada em intervalo entre os pulsos
    alert_pulse_interval = map(distance_mm_value, 200, trig_value, min_alert_pulse_interval, max_alert_pulse_interval); 
    
    // Se a distância lida for muito pequena, é utilizado um intervalo mínimo
    if (distance_mm_value < 200) {
      alert_pulse_interval = min_alert_pulse_interval;
    }
    // Se a distância lida for maior que máximo (erro de leitura), é utilizado um intervalo máximo
    else if (distance_mm_value > max_distance) { 
      alert_pulse_interval = max_alert_pulse_interval;
    }
  }
#endif

  // Carrega o tempo atual de execução
  unsigned long current_ms = millis();

  // Gera os pulsos de vibração enquanto houver o alerta ou até dar uma quantidade mínima de pulsos
  if (alert || last_alert_pulse) {

    // Muda o estado atual do pulso somente se o intervalo de tempo desde o último pulso foi decorrido
    if (current_ms - previous_ms_alert_pulse >= alert_pulse_interval ) {

      // Determina o tempo no qual esta condição foi executada
      previous_ms_alert_pulse = current_ms;

      if (pwm_value == LOW) { // Se o pulso do padrão de vibração não estiver sendo gerado
        pwm_value = max_pwm; // Seta o valor para gerar o pulso
        if (alert_pulse_counter < min_alert_pulses)
          alert_pulse_counter++;  // Conta o pulso dado
      }
      else { // Se o pulso do padrão de vibração estiver sendo gerado
        pwm_value = LOW;  // Seta o valor para interromper o pulso
      }

      // Permite esta condição rodar uma última vez para finalizar um pulso mesmo após o alert zerar
      if (pwm_value != LOW || alert_pulse_counter < min_alert_pulses)
        last_alert_pulse = 1;
      else
        last_alert_pulse = 0;
    }
  }
  // Se o alerta for concluído, zera os pulsos contados
  else {
    alert_pulse_counter = 0;
  }

  // Lê a tensão da bateria somente se o intervalo de tempo desde a última leitura foi decorrido
  if (current_ms - previous_ms_bat_read >= bat_read_interval ) {

    // Determina o tempo no qual esta condição foi executada
    previous_ms_bat_read = current_ms;

    // Lê a tensão da bateria
    read_battery();
    
    // Se a tensão for baixa, prepara o alerta da bateria
    if (battery_status == 1)
      alert_bat = 1;
  }

  // Se o alerta de obstáculos estiver ativo, inibe o acionamento do alerta de bateria
  if (alert) {
    bat_pulse_counter = 0;
    alert_bat = 0;
  }
  
  // Se todos os pulsos do alerta da bateria foram gerados, reinicia o ciclo
  if (bat_pulse_counter >= bat_pulses) {
    previous_ms_bat_read = current_ms;
    bat_pulse_counter = 0;
    alert_bat = 0;
  }

  // Gera os pulsos de vibração enquanto houver o alerta ou até dar uma quantidade mínima de pulsos
  if (alert_bat || last_bat_pulse) {
    
    // Muda o estado atual do pulso somente se o intervalo de tempo desde o último pulso foi decorrido
    if (current_ms - previous_ms_bat_pulse >= bat_pulse_interval ) {

      // Determina o tempo no qual esta condição foi executada
      previous_ms_bat_pulse = current_ms;

      if (pwm_value == LOW) { // Se o pulso do padrão de vibração não estiver sendo gerado
        pwm_value = max_pwm; // Seta o valor para gerar o pulso
        bat_pulse_counter++;  // Conta o pulso dado
      }
      else { // Se o pulso do padrão de vibração estiver sendo gerado
        pwm_value = LOW;  // Seta o valor para interromper o pulso
      }

      // Permite esta condição rodar uma última vez para finalizar um pulso mesmo após o alert zerar
      if (pwm_value != LOW)
        last_bat_pulse = 1;
      else
        last_bat_pulse = 0;
    }
  }

  // Atualiza o valor da porta PWM
  analogWrite(motor_pin, pwm_value);
  
  // Log via serial
  Serial.print("Distância: ");
  Serial.print(distance_mm_value);
  Serial.print(" mm\t");
  if (distance_mm_value > max_distance)
    Serial.print("(Fora de alcance)\t");
  Serial.print("Trigger: ");
  Serial.print(trig_value);
  Serial.print(" mm\t");
  Serial.print("Tensão da Bateria (ADC): ");
  Serial.print(battery_value);
  Serial.print("\tTensão da Bateria: ");
  Serial.print(battery_voltage_mv);
  Serial.print(" mV");
  Serial.print("\tStatus da Bateria: ");
  Serial.println(battery_status);
}