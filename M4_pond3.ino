int botoes[5] = {17,5, 2, 4,35};
int leds[4] = {16, 33, 14, 18};
int sequencia[16] = {};
int rodada = 0;
int passo = 0;
bool perdeu = false;


void proxima_rodada() {
  int randomizar = random(4);
  sequencia[rodada] = randomizar;
  rodada = rodada + 1;
}

void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void espera_jogada() {
  int botao_pressionado = 0;
  for (int i = 0; i < rodada; i++) {
    bool jogada_efetuada = false;
    while (!jogada_efetuada) {
      for (int i = 0; i <= 3; i++) {
        if (digitalRead(botoes[i]) == HIGH) {
          botao_pressionado = i;
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          jogada_efetuada = true;
        }
      }
    }
    //ver se a jogada está certa
    if (sequencia[passo] != botao_pressionado) {//pisca 4 vezes indicando que perdeu
      for (int i = 0; i <= 3; i++) {
        delay(200);
        digitalWrite(16, HIGH);
        digitalWrite(33, HIGH);
        digitalWrite(14, HIGH);
        digitalWrite(18, HIGH);
        delay(100);
        digitalWrite(16, LOW);
        digitalWrite(33, LOW);
        digitalWrite(14, LOW);
        digitalWrite(18, LOW);
      }

      perdeu = true;
      break;
    }
    passo = passo + 1;
  }
  passo = 0;
}
void reset(){
    sequencia[16] = {};
    rodada = 0;
    passo = 0;
    perdeu = false;
}


void central(){
  proxima_rodada();
  reproduzirSequencia();
  espera_jogada();

  if (perdeu == true) {
    reset();// reinicia todas as variáveis
  }
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  // Botões
  pinMode(17, INPUT);
  pinMode(5, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(35, INPUT); //botao reset
  // Leds
  pinMode(16, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(18, OUTPUT);
}

void loop() {
  delay(2);
  central();
}