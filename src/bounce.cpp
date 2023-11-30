// #include <Arduino.h>

// bool stable;    // Guarda o último estado estável do botão;
// bool unstable;  // Guarda o último estado instável do botão;
// uint32_t bounce_timer;
// uint32_t button_pressed_time;  // Tempo que o botão está pressionado
// uint32_t pressed_time;
// uint8_t counter = 0;

// bool changed() {
//   bool now = digitalRead(8);   // Lê o estado atual do botão;
//   if (unstable != now) {       // Checa se houve mudança;
//     bounce_timer = millis();   // Atualiza timer;
//     unstable = now;            // Atualiza estado instável;
//   }
//   else if (millis() - bounce_timer > 10) {  // Checa se o tempo de trepidação acabou;
//     if (stable != now) {           // Checa se a mudança ainda persiste;
//       stable = now;                  // Atualiza estado estável;

//       if (stable == LOW) {  // Se o botão foi pressionado
//         button_pressed_time = millis();  // Armazena o tempo de início do pressionamento
//       } else {  // Se o botão foi liberado
//         // Calcula o tempo que o botão foi pressionado e faz algo com ele (por exemplo, imprimir no Serial)
//         Serial.print("Tempo pressionado: ");
//         Serial.print(millis() - button_pressed_time);
//         Serial.println(" ms");
//       }

//       return true;
//     }
//   }
//   return false;
// }

// void setup() {
//   Serial.begin(9600);        // Configura comunicação serial a uma taxa de 9600 bauds.
//   pinMode(8, INPUT_PULLUP);  // Configura pino 8 como entrada e habilita pull-up interno;
//   pinMode(9, OUTPUT);  // Configura pino 9 como saída para o LED
//   pinMode(10, OUTPUT);  // Configura pino 9 como saída para o LED
//   pinMode(11, OUTPUT);  // Configura pino 9 como saída para o LED
//   stable = digitalRead(8);
// }

// void loop() {
//   changed();
//   if (stable == LOW) {  // Se o botão foi pressionado
//     pressed_time = (millis() - button_pressed_time);
//     if ((pressed_time >= 1000) && (pressed_time < 3000)) {
//       digitalWrite(9, HIGH); //acende o led
//     }else if ((pressed_time >= 3000) && (pressed_time < 5000)) {
//       digitalWrite(10, HIGH); //acende o led
//     }else if ((pressed_time >= 5000)) {
//       digitalWrite(11, HIGH); //acende o led
//     }
//   } else {
//     digitalWrite(9, LOW); //APAGA O LED
//     digitalWrite(10, LOW); //APAGA O LED
//     digitalWrite(11, LOW); //APAGA O LED
//   }
// }
