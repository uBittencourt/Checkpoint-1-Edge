// Declarando as variáveis e os pinos do arduino
int ledGreen = 10; // LED verde no pino 10
int ledYellow = 9; // LED amarelo no pino 9
int ledRed = 8;    // LED vermelho no pino 8
int LDR = A0;      // Resistor LDR no pino A0
int valueLDR;      // Iniciando variável do valor do LDR
int buzzer = 11;   // Buzzer no pino 11
int valueLight;    // Declarando variável do valor da luz em %
int readings[5];   // Array para armazenar as últimas 5 leituras do LDR
int index = 0;     // Índice atual do array

void setup()
{
  // Função para iniciar a conexão entre o arduino e o computador
  Serial.begin(9600);
  
  // Fazendo a saída dos pinos
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LDR, INPUT); // Saída INPUT pois aqui recebemos o valor LDR
}

void loop()
{ 
  // Lendo valores do LDR e armazenando no array
  readings[index] = analogRead(LDR);
  index = (index + 1) % 5; // Atualiza o índice circularmente

  // Calculando a média das últimas 5 leituras
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += readings[i];
  }
  valueLDR = sum / 5;

  // Transformando valores da medição do LDR em porcentagem
  valueLight = map(valueLDR, 54, 960, 0, 100);
  Serial.println(valueLight); // Apresendo  valor da luz em % na tela
  
  // Estrutura condicional para acender os LEDs e tocar o buzzer
  if(valueLight <= 65){
    
    // Iluminação abaixo de 65%, LED verde ligado
    digitalWrite(ledGreen, HIGH);
    
  } else if(valueLight > 65 && valueLight <= 90){
    
    // Iluminação entre 65% e 90%, LED amarelo ligado
    digitalWrite(ledYellow, HIGH);
    
    for(int x=1; x <= 3; x++){
      // Laço de repetição para dar pequenos toques com buzzer
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    
  } else{
    
    // Iluminação acima de 90%, LED vermelho ligado
    digitalWrite(ledRed, HIGH);
    
    // Buzzer tocando iinterruptamente por 3 segundos
    digitalWrite(buzzer, HIGH);
    delay(3000);
  }
  
  // Apagando LEDs e o Buzzer, antes do próximo laço de repetição
  digitalWrite(buzzer, LOW);
  delay(300);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
}