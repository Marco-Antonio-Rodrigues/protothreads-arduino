#include <Arduino.h>
#include "pt-sem.h"
#include "utils.h"

#define BUFSIZE 4

static uint8_t buffer[BUFSIZE];
static uint8_t bufptr;
static struct pt_sem full, empty, bounce_sem,ldr_sem;

Button *button_producer = (Button*)malloc(sizeof(Button));
Button *button_consumer = (Button*)malloc(sizeof(Button));
Button *button_bounce = (Button*)malloc(sizeof(Button));

const int pinoLed = 13; //PINO DIGITAL UTILIZADO PELO LED
const int pinoLDR = A0; //PINO ANALÓGICO UTILIZADO PELO LDR

static int produce_item(void){
  static int item = 1;
  Serial.print("Item ");
  Serial.print(item);
  Serial.println(" produced");
  return item++;
}

static void add_to_buffer(int item){
  if(bufptr < BUFSIZE){
    digitalWrite(8,LOW);
    switch (bufptr){
      case 0:
        digitalWrite(4,HIGH);
        break;
      case 1:
        digitalWrite(5,HIGH);  
        break;
      case 2:
        digitalWrite(6,HIGH);
        break;
      case 3:
        digitalWrite(7,HIGH);
        break;
    }
    Serial.print("Item ");  
    Serial.print(item);  
    Serial.print(" added to buffer at place ");  
    Serial.println(bufptr);
    buffer[bufptr] = item;
    bufptr++;
  }else{
    Serial.print("Item ");  
    Serial.print(item);  
    Serial.println(" lost when adding to in-place buffer");  
    digitalWrite(8,HIGH);
  }
}

static int get_from_buffer(void){
  int item;
  if(bufptr-1 >= 0){
      bufptr--;
      item = buffer[bufptr];
      digitalWrite(8,LOW);
      switch (bufptr){
        case 0:
          digitalWrite(4,LOW);
          break;
        case 1:
          digitalWrite(5,LOW);  
          break;
        case 2:
          digitalWrite(6,LOW);
          break;
        case 3:
          digitalWrite(7,LOW);
          break;
      }
    Serial.print("Item ");
    Serial.print(item);
    Serial.print(" retrieved from buffer at place ");
    Serial.println(bufptr);
  }else{
    digitalWrite(8,HIGH);
    Serial.println("there is nothing to consume");  
    item = 0; 
  }
  return item;
}

static void consume_item(int item){
  if(item){
    Serial.print("Item ");
    Serial.print(item);
    Serial.println(" consumed");
  }
}
 
static PT_THREAD(producer(struct pt *pt)){  
  PT_BEGIN(pt);
    
  PT_SEM_WAIT(pt, &full);
    if(changed(button_producer)){
      if (button_producer->stable == LOW){  // Se o botão foi pressionado
        add_to_buffer(produce_item());
      }
    }    
  PT_SEM_SIGNAL(pt, &empty);

  PT_END(pt);
}
 
static PT_THREAD(consumer(struct pt *pt)){
  PT_BEGIN(pt);

  PT_SEM_WAIT(pt, &empty);
    if(changed(button_consumer)){
      if (button_consumer->stable == LOW){  // Se o botão foi pressionado
        consume_item(get_from_buffer());   
      }
    }    
  PT_SEM_SIGNAL(pt, &full);
 
  PT_END(pt);
}
 
static PT_THREAD(bounce(struct pt *pt)){
  PT_BEGIN(pt);

  PT_SEM_WAIT(pt, &bounce_sem);
    changed(button_bounce);
    if (button_bounce->stable == LOW) {  // Se o botão foi pressionado
      button_bounce->pressed_time = (millis() - button_bounce->button_pressed_time);
      if ((button_bounce->pressed_time >= 1000) && (button_bounce->pressed_time < 3000)) {
        digitalWrite(9, HIGH); //acende o led
      }else if ((button_bounce->pressed_time >= 3000) && (button_bounce->pressed_time < 5000)) {
        digitalWrite(10, HIGH); //acende o led
      }else if ((button_bounce->pressed_time >= 5000)) {
        digitalWrite(11, HIGH); //acende o led
      }
    } else {
      digitalWrite(9, LOW); //APAGA O LED
      digitalWrite(10, LOW); //APAGA O LED
      digitalWrite(11, LOW); //APAGA O LED
    }
  PT_SEM_SIGNAL(pt, &full);
 
  PT_END(pt);
}

static PT_THREAD(ldr(struct pt *pt)){
  PT_BEGIN(pt);

  PT_SEM_WAIT(pt, &ldr_sem);

  Serial.println(analogRead(pinoLDR));
  if(analogRead(pinoLDR) > 600){ //SE O VALOR LIDO FOR MAIOR QUE 600, FAZ
    digitalWrite(pinoLed, HIGH); //ACENDE O LED
  }  
  else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //APAGA O LED
  } 

  PT_SEM_SIGNAL(pt, &full);
 
  PT_END(pt);
}

static PT_THREAD(driver_thread(struct pt *pt)){
  static struct pt pt_producer, pt_consumer, pt_bounce, pt_ldr;
 
  PT_BEGIN(pt);
  
  PT_SEM_INIT(&empty, 0);
  PT_SEM_INIT(&full, BUFSIZE);
  PT_SEM_INIT(&bounce_sem, 1);
  PT_SEM_INIT(&ldr_sem, 1);
 
  PT_INIT(&pt_producer);
  PT_INIT(&pt_consumer);
  PT_INIT(&pt_bounce);
  PT_INIT(&pt_ldr);
 
  PT_WAIT_THREAD(pt,ldr(&pt_ldr) & bounce(&pt_bounce) & producer(&pt_producer) & consumer(&pt_consumer));
 
  PT_END(pt);
}

void setup(){

  button_consumer->port = 2;
  button_producer->port = 3;
  button_bounce->port = 12;

  Serial.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(button_consumer->port, INPUT_PULLUP);
  pinMode(button_producer->port, INPUT_PULLUP);
  pinMode(button_bounce->port, INPUT_PULLUP);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoLDR, INPUT);

  button_consumer->stable = digitalRead(button_consumer->port);
  button_producer->stable = digitalRead(button_producer->port);
  button_bounce->stable = digitalRead(button_bounce->port);
}

void loop(){
  struct pt driver_pt;

  PT_INIT(&driver_pt);

  PT_SCHEDULE(driver_thread(&driver_pt));

}

