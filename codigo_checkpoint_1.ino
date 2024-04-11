// Declarando as variáveis e os pinos do arduino
int ledGreen = 10; // LED verde no pino 10
int ledYellow = 9; // LED amarelo no pino 9
int ledRed = 8;    // LED vermelho no pino 8
int LDR = A0;      // Resistor LDR no pino A0
int valueLDR;      // Iniciando variável do valor do LDR
int buzzer = 11;   // Buzzer no pino 11
int valueLight;    // Declarando variável do valor da luz em %

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
  valueLDR = analogRead(LDR); // Lendo valores do LDR
  valueLight = map(valueLDR, 182, 969, 0, 100); // Transformando valores da medição do LDR em pocentagem
  Serial.println(valueLight); // Apresendo  valor da luz em % na tela
  
  // Estrutura condicional para acender os LEDs e tocar o buzzer
  if(valueLight >= 50){
    
    // Iluminação com até 50% do recomendado, LED verde ligado
  	digitalWrite(ledGreen, HIGH);
    
  } else if(valueLight < 50 && valueLight >= 10){
    
    // Iluminação entre 50% e 10% do recomendado, LED amarelo ligado
  	digitalWrite(ledYellow, HIGH);
    
    for(int x=1; x <= 3; x++){
      // Laço de repetição para dar pequenos toques com buzzer
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    
  } else{
    
    // Iluminação abaixo de 10% do recomendado, LED vermelho ligado
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