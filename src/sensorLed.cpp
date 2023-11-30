// #include <Arduino.h>
 
// const int pinoLed = 10; //PINO DIGITAL UTILIZADO PELO LED
// const int pinoLDR = A5; //PINO ANALÓGICO UTILIZADO PELO LDR
  
// void setup(){  
//   Serial.begin(9600);
//   pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
//   pinMode(pinoLDR, INPUT); //DEFINE O PINO COMO ENTRADA
// }    
// void loop(){
//   //O VALOR 600 PODE SER AJUSTADO
//   Serial.println(analogRead(pinoLDR));
//   delay(300);
//   if(analogRead(pinoLDR) > 600){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
//     digitalWrite(pinoLed, HIGH); //ACENDE O LED
//   }  
//   else{ //SENÃO, FAZ
//     digitalWrite(pinoLed, LOW); //APAGA O LED
//   }  
// }