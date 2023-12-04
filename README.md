# Referências
https://dunkels.com/adam/pt/index.html

https://www.youtube.com/watch?v=kNs2KyIlUUE&ab_channel=GustavoDenardin

## O que foi imprementado?
  Nesse projeto utilizei a biblioteca protothreads para rodar 3 protothreads em paralelo.
  ### 1º- Produtor/Consumidor
  Nessa protothread, foi aplica o problema do produtor/consumidor aonde um botão faz o papel do produtor e outro do consumidor, quando um deles tentar fazer uma
  operação inválida(tentar consumir com o buffer vazio/testar produzir com o buffer cheio) o led vermelho é acionado indicando bloqueio.

  ### 2º- Duração do tempo pressionado
  Nessa protothread foi aplicado um cronômetro para medir a duração do tempo em que o botão permanceu pressionado, com o passar do tempo ele começa a ligar os leds 1 a 1.

  ### 3º- Sensor de luz
  Nessa protothread foi aplicado um photoresistor que vai funcionar como um sensor de luz nesse projeto, quando ele recebe pouca luz ou nada o led liga e 
  quando volta a receber luz o led apaga.
