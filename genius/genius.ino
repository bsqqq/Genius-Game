// # Para apenas 3 leds e para ESP32...

int Led[3] = {26,25,33};
int Botao[3] = {12,14,27};
int seq[100];
int rodada = 0;

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < 3; i++) 
  {
  	pinMode(Led[i], OUTPUT);
    pinMode(Botao[i], INPUT_PULLUP);
  }
  randomSeed(analogRead(34));
}

void loop()
{ 
	NovaRodada();
  EsperarJogador();
  delay(1000);
}

void NovaRodada() 
{
	seq[rodada] = random(0, 3);
  Serial.println(seq[rodada]);
  	PiscarSequencia();
	rodada++;
}

void PiscarSequencia() 
{
//  delay(1000);
  for(int k = 0; k <= rodada; k++) {
  	digitalWrite(Led[seq[k]], HIGH);
    delay(500);
    digitalWrite(Led[seq[k]], LOW);
    delay(500);
  }
}

void EsperarJogador() 
{
  bool flag;
  int BotaoPressionado;
  for(int k = 0; k < rodada; k++) {
     flag = true;
     while(flag) {
       if(digitalRead(Botao[0]) == LOW) {
        digitalWrite(Led[0], HIGH);
        delay(100);
        digitalWrite(Led[0], LOW);
       	BotaoPressionado = 0;
        flag = false;
        } else if(digitalRead(Botao[1]) == LOW) {
          digitalWrite(Led[1], HIGH);
          delay(100);
          digitalWrite(Led[1], LOW);
          BotaoPressionado = 1;
          flag = false;
        } else if(digitalRead(Botao[2]) == LOW) {
          digitalWrite(Led[2], HIGH);
          delay(100);
          digitalWrite(Led[2], LOW);
          BotaoPressionado = 2;
          flag = false;
        }
     }
     delay(250); //anti ghosting     
        if(BotaoPressionado == seq[k]) {
       	Serial.println("Certo...");
        } else {
        	Serial.println("Errado!");
          	Serial.println("Reiniciando...");
           rodada = 0;
        }
      }
	}
