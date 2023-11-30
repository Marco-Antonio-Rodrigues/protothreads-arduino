#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>

#ifndef UTILS_H
#define UTILS_H

struct Button{
  bool stable; 
  bool unstable; 
  uint8_t port;
  uint32_t bounce_timer;
  uint32_t button_pressed_time;
  uint32_t pressed_time;
};

bool changed(Button *button) {
  bool now = digitalRead(button->port);   // Lê o estado atual do botão;
  if (button->unstable != now) {       // Checa se houve mudança;
    button->bounce_timer = millis();   // Atualiza timer;
    button->unstable = now;            // Atualiza estado instável;
  }
  else if (millis() - button->bounce_timer > 10) {  // Checa se o tempo de trepidação acabou;
    if (button->stable != now) {           // Checa se a mudança ainda persiste;
      button->stable = now;                  // Atualiza estado estável;

      if (button->stable == LOW) {  // Se o botão foi pressionado
        button->button_pressed_time = millis();  // Armazena o tempo de início do pressionamento
      } else {  // Se o botão foi liberado
        // Calcula o tempo que o botão foi pressionado e faz algo com ele (por exemplo, imprimir no Serial)
        Serial.print("Tempo pressionado: ");
        Serial.print(millis() - button->button_pressed_time);
        Serial.println(" ms");
      }
      return true;
    }
  }
  return false;
}

#endif

