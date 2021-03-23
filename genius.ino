int led[4] = {11,10,9,6};
int botao[4] = {4,12,8,7};
int seq[100];
int rodada = 0;

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 4; i++) 
  {
  	pinMode(led[i], OUTPUT);
    pinMode(botao[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(A0));
}

void loop()
{
	NovaRodada();
  	EsperarJogador();
}

void NovaRodada() 
{
	seq[rodada] = random(0, 4);
  Serial.println(seq[rodada]);
  	PiscarSequencia();
	rodada++;
}

void PiscarSequencia() 
{
  for(int k = 0; k <= rodada; k++) {
  	digitalWrite(led[seq[k]], HIGH);
    delay(1000);
    digitalWrite(led[seq[k]], LOW);
    delay(1000);
  }
}

void EsperarJogador() 
{
  bool flag;
  int botaoPressionado;
  for(int k = 0; k < rodada; k++) {
     flag = true;
     while(flag) {
       if(digitalRead(botao[0]) == LOW) {
       	botaoPressionado = 0;
        flag = false;
        } else if(digitalRead(botao[1]) == LOW) {
          botaoPressionado = 1;
          flag = false;
        } else if(digitalRead(botao[2]) == LOW) {
          botaoPressionado = 2;
          flag = false;
        } else if(digitalRead(botao[3]) == LOW) {
          botaoPressionado = 3;
          flag = false;
        }
     }
     delay(250); //anti ghosting     
        if(botaoPressionado == seq[k]) {
       	Serial.println("Certo...");
        } else {
        	Serial.println("Errado!");
          	Serial.println("Reiniciando...");
           rodada = 0;
        }
      }
	}