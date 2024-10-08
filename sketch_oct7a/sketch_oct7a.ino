// #include <Wire.h> // Código para pegar o endereço do LCD
// void setup()
// {
//   Wire.begin();
 
//   Serial.begin(9600);
//   while (!Serial);             
//   Serial.println("\nI2C Scanner");
// }
 
// void loop()
// {
//   byte error, address;
//   int nDevices;
//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if (error == 0)
//     {
//       Serial.print("Endereço I2C encontrado: 0x");
//       if (address<16)
//         Serial.print("0 ");
//       Serial.println(address,HEX);
 
//       nDevices++;
//     }
//     else if (error==4)
//     {
//       Serial.print("ERRO ");
//       if (address<16)
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0)
//     Serial.println("Nenhum endereço i2C encontrado ");
//   else
    
//     Serial.println(" Feito !");
 
//   delay(5000);         
// }

// **************************************************************************************************
// CODIGO PARA A BALANÇA SEM TELA LCD

// #include <HX711.h> //adiciona a biblioteca ao codigo

// //configuracao dos pinos para o modulo HX711
// const int PINO_DT = 3;
// const int PINO_SCK = 2;

// const int TEMPO_ESPERA = 1000; //declaracao da variavel de espera

// HX711 escala; //declaracao do objeto escala na classe HX711 da biblioteca

// float fator_calibracao = -45000; //pre-definicao da variavel de calibracao

// char comando; //declaracao da variavel que ira receber os comandos para alterar o fator de calibracao

// void setup ()
// {

//   //mensagens do monitor serial
//   Serial.begin(9600);
//   Serial.println("Celula de carga - Calibracao de Peso");
//   Serial.println("Posicione um peso conhecido sobre a celula ao comecar as leituras");

//   escala.begin (PINO_DT, PINO_SCK); //inicializacao e definicao dos pinos DT e SCK dentro do objeto ESCALA

//   //realiza uma media entre leituras com a celula sem carga 
//   float media_leitura = escala.read_average(); 
//   Serial.print("Media de leituras com Celula sem carga: ");
//   Serial.print(media_leitura);
//   Serial.println();

//   escala.tare(); //zera a escala
// }

// void loop ()
// {
//   escala.set_scale(fator_calibracao); //ajusta a escala para o fator de calibracao

//   //verifica se o modulo esta pronto para realizar leituras
//   if (escala.is_ready())
//   {
//     //mensagens de leitura no monitor serial
//     Serial.print("Leitura: ");
//     Serial.print(escala.get_units(), 1); //retorna a leitura da variavel escala com a unidade quilogramas
//     Serial.print(" kg");
//     Serial.print(" \t Fator de Calibracao = ");
//     Serial.print(fator_calibracao);
//     Serial.println();

//   //alteracao do fator de calibracao
//     if(Serial.available())
//       {
//         comando = Serial.read();
//         switch (comando)
//         {
//           case 'x':
//           fator_calibracao = fator_calibracao - 100;
//           break;
//           case 'c':
//           fator_calibracao = fator_calibracao + 100;
//           break;
//           case 'v':
//           fator_calibracao = fator_calibracao - 10;
//           break;
//           case 'b':
//           fator_calibracao = fator_calibracao + 10;
//           break;
//           case 'n':
//           fator_calibracao = fator_calibracao - 1;
//           break;
//           case 'm':
//           fator_calibracao = fator_calibracao + 1;
//           break;
//         }
//       }
//     }
//     else
//     {
//       Serial.print("HX-711 ocupado");
//     }
//   delay(TEMPO_ESPERA);
// }

// ***************************************** //

// CODIGO PARA BALANÇA COM TELA LCD

// #include <HX711.h> 
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>

// LiquidCrystal_I2C lcd(0x27,16,2); //endereçamento do LCD

// //configuracao dos pinos para o modulo HX711
// const int PINO_DT = 3;
// const int PINO_SCK = 2;

// //declaracao do intervalo de espera
// const int TEMPO_ESPERA = 500;

// HX711 escala; //declaracao do objeto ESCALA na classe HX711 da biblioteca

// const int FATOR_CALIBRACAO = -32010; //esse valor deve ser alterado para o valor de calibracao obtido com o outro codigo

// void setup ()
// {

//   //mensagens do LCD
//   lcd.begin(16,2, 0x27); //inicializacao do display
//   lcd.backlight(); // ligacao do backlight do LCD
//   lcd.print("    ");
//   lcd.print("RoboCore");
//   delay(TEMPO_ESPERA);
//   lcd.clear();

//   escala.begin (PINO_DT, PINO_SCK); //inicializacao e definicao dos pinos DT e SCK dentro do objeto ESCALA
  
//   escala.tare(); //zera a escala

//   escala.set_scale(FATOR_CALIBRACAO); //ajusta a escala para o fator de calibracao
  
// }

// void loop ()
// {
//   //verifica se o modulo esta pronto para realizar leituras
//   if (escala.is_ready())
//   {
//   //mensagens de leitura no monitor serial
//     lcd.print(" Peso: ");
//     lcd.print(escala.get_units(), 1); //retorna a leitura da variavel escala com a unidade quilogramas
//     lcd.print(" kg");
  
//   }
//   else
//   {
//     lcd.print(" Aguarde  . . . ");
//   }
//   delay(TEMPO_ESPERA); //intervalo de espera para leitura
//   lcd.clear();
// }

// ********************************************************************* //


// CODIGO DO MOTOR DE PASSO !!!!!!!!!!!!!!!

// byte HOR[4] = {0x09,0x03,0x06,0x0C};    // Matriz dos bytes das Fases do Motor - sentido Horário Full Step
// byte AHO[4] = {0x0C,0x06,0x03,0x09};    // Matriz dos bytes das Fases do Motor - sentido Anti-Horário Full Step
// int atraso_fase = 2 ;                   // Intervalo de tempo entre as fases em milisegundos - min 2 para Full Step 
// int intervalo = 1000 ;                  // Intervalo de tempo entre os movimentos do motor em ms

// void Motor_AHO()                    // Movimento no sentido anti-horário 
// {
//   for(int i = 0; i < 512; i++)      // incrementa o contador i de 0 a 511 - uma volta
  
//     for(int j = 0; j < 4; j++)      // incrementa o contador j de 0 a 3 
//     {
//       PORTB = AHO[j];               // Carrega bytes da Matriz AHO na Porta B 
//       delay (atraso_fase);          // Atraso de tempo entre as fases em milisegundos
//     }    
// }

// void Motor_HOR()                    // Movimento no sentido horário 
// {
//   for(int i = 0; i < 512; i++)      // incrementa o contador i de 0 a 511 - uma volta
  
//     for(int j = 0; j < 4; j++)      // incrementa o contador j de 0 a 3 
//     {
//       PORTB = HOR[j];               // Carrega bytes da Matriz HOR na Porta B 
//       delay (atraso_fase);          // Atraso de tempo entre as fases em milisegundos
//     }
// }

// void setup()
// {
//   DDRB = 0x0F;           // Configura Portas D08,D09,D10 e D11 como saída 
//   PORTB = 0x00;          // Reset dos bits da Porta B (D08 a D15) 
// }

// void loop()
// {
//  Motor_HOR();           // Gira motor no sentido Horário 
//  delay (intervalo);     // Atraso em milisegundos 
//  Motor_AHO();           // Gira motor no sentido Anti-Horário 
//  delay (intervalo);     // Atraso em milisegundos 
// }

// const int buttonPin = 8; // Pino onde o botão está conectado
// bool counting = false; // Variável para controlar a contagem

// **************************************************************

// CODIGO DOS BOTOES !!!!!!!!!!!!!!!

// void setup() {
//   Serial.begin(9600); // Inicializa a comunicação serial
//   pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com resistor pull-up
// }

// void loop() {
//   // Lê o estado do botão (considera que o botão é pressionado quando está em LOW)
//   if (digitalRead(buttonPin) == LOW && !counting) {
//     counting = true; // Começa a contagem
//     Serial.println("Contagem iniciada!");

//     const unsigned long waitTime = 10; // 1 hora em segundos

//     for (unsigned long i = 0; i < waitTime; i++) {
//       Serial.print("Segundos: ");
//       Serial.println(i + 1); // Exibe o número de segundos
//       delay(1000); // Espera 1 segundo
//       if (digitalRead(buttonPin) == LOW && !counting) {
//         counting = true; // Começa a contagem
//         Serial.println("Contagem iniciada!");
//     }

//     Serial.println("Contagem finalizada!");
//     counting = false; // Reinicia a variável para permitir novas contagens
//   }
// }

// **************************************************************************************

// CODIGO FINAL

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int button1 = 5; // Pino do botao 1
const int button2 = 6; // pino do botao 2
const int button3 = 7; // pino do botao3

LiquidCrystal_I2C lcd(0x27,16,2); //endereçamento do LCD
  
const int TEMPO_ESPERA = 1500; //declaracao do intervalo de espera

// declaraçao das minhas funçoes e variáveis
int setar_intervalo = 0;
bool intervalo_salvo = 0;
bool peso_salvo = 0;
unsigned long intervalo = 0;

void iniciarConfiguracao();
void configurarIntervalo();

void setup ()
{
//   //mensagens do LCD
  lcd.begin(16,2, 0x27); //inicializacao do display
  lcd.backlight(); // ligacao do backlight do LCD
  lcd.print("Comedouro Pets");
  delay(TEMPO_ESPERA);
  lcd.clear();

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  
}

void loop ()
{
  if (digitalRead(button1) == LOW){ // botao 1 primeira configuracao
    iniciarConfiguracao();
  }

  if (digitalRead(button2) == LOW){
    lcd.print("Botao 2");
    delay(TEMPO_ESPERA); //intervalo de espera para leitura
    lcd.clear();
  }
  if (digitalRead(button3) == LOW){
    lcd.print("Botao 3");
    delay(TEMPO_ESPERA); //intervalo de espera para leitura
    lcd.clear();
  }

  lcd.print("Comedouro Pets");
  delay(500); //intervalo de espera para leitura
  lcd.clear();
}

void iniciarConfiguracao(void) {
  while(1) {
      lcd.setCursor(0,0);
      lcd.print("Configuracao");
      lcd.setCursor(0, 1);  // Posiciona o cursor na segunda linha, coluna 0
      if (intervalo_salvo == 0)
      {
        lcd.print("Defina intervalo");
      }
      if (peso_salvo == 0 && intervalo_salvo == 1)
      {
        lcd.print("Defina Peso");
      }
      delay(500);
      lcd.clear();

      if (digitalRead(button2) == LOW && intervalo_salvo == 0) { // vai iniciar a configuração de intervalo
        configurarIntervalo();
      }
      if (digitalRead(button2) == LOW && intervalo_salvo == 0 && peso_salvo == 0) { // vai iniciar a configuração de peso
        configurarPeso();
      }

      if (digitalRead(button3) == LOW) { // Vai quitar das configurações sem salvar nada
        lcd.setCursor(0,0);
        lcd.print("Nao Salvo");
        delay(500);
        lcd.clear();
        intervalo_salvo = 0;
        peso_salvo = 0;
        break;
      }
    }
    lcd.setCursor(0,0);
    lcd.clear();
}

void configurarIntervalo() {
  lcd.setCursor(0,0);
  lcd.print("Intervalo");
  delay(500);
  lcd.clear();
  while(1) {
    lcd.setCursor(0,0);
    lcd.print("Intervalo");
    if (digitalRead(button2) == LOW)
    {
      setar_intervalo++;
      if (setar_intervalo == 3)
      {
        setar_intervalo = 0;
      }
    }
    lcd.setCursor(0, 1);  // Posiciona o cursor na segunda linha, coluna 0
    if (setar_intervalo == 0)
    {
      lcd.print("4 horas");
      intervalo = 4UL * 60 * 60 * 1000;
    }
    if (setar_intervalo == 1)
    {
        lcd.print("6 horas");
        intervalo = 6UL * 60 * 60 * 1000;
    }
    if (setar_intervalo == 2)
    {
        lcd.print("8 horas");
        intervalo = 8UL * 60 * 60 * 1000;
    }
    delay(250);
    lcd.clear();
    if (digitalRead(button1) == LOW) { // vai salvar a configuração de intervalo
      lcd.setCursor(0,0);
      lcd.print("Intervalo Salvo");
      delay(1000);
      lcd.clear();
      intervalo_salvo = 1;
      break;
    }
    if (digitalRead(button3) == LOW) { // vai quitar da configuração de intervalo
      lcd.setCursor(0,0);
      lcd.print("Nao Salvo");
      delay(1000);
      lcd.clear();
      intervalo_salvo = 0;
      break;
    } 
  }
  return ;
}

void configurarPeso()
{
  
}


