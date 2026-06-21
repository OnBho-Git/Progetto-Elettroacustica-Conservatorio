const int ledPin = 6;
const int speakerPin = 9;
const int buttonPin = 2;
const int tempoTrasmissione = 80; //Durata del valore più piccolo (punto) in trasmissione
const int tempoRicezione = 150; //Durata del valore più piccolo in ricezione

// Array: 0-25 lettere A-Z, 26-35 numeri 0-9
const String morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
  "..-", "...-", ".--", "-..-", "-.--", "--..", // A-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", // 0-9
  "----", // Spazio
  "......" //Backspace
};

unsigned long tempoPressione = 0;
unsigned long tempoRilascio = 0;
String sequenzaRicevuta = "";
bool bottonePremuto = false;
bool letteraTradotta = true;
bool spazioTradotto = true;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() 
{
  //Codice per la Scrittura
  if (Serial.available() > 0) {
    String testo = Serial.readStringUntil('\n');
    Serial.println("Trasmissione in Corso...");
    testo.toUpperCase();

    for (int i = 0; i < testo.length(); i++) 
    {
      char c = testo[i];
      
      if (c >= 'A' && c <= 'Z') 
      {
        eseguiMorse(morseCode[c - 'A']);
        delay(tempoTrasmissione * 2); // Pausa tra lettere
      } 
      else if (c >= '0' && c <= '9') 
      {
        eseguiMorse(morseCode[c - '0' + 26]);
        delay(tempoTrasmissione * 2);
      } 
      else if (c == ' ') delay(tempoTrasmissione * 2); // Pausa tra parole
    }
    Serial.println("Trasmissione completata");
  }

  //Fine Codice Scrittura. Inizio Codice Traduzione

  int statoBottone = digitalRead(buttonPin);

  if (statoBottone == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 880);
  } 
  else
  {
    digitalWrite(ledPin, LOW);
    noTone(speakerPin);
  }

  // Gestione Pressione
  if (statoBottone == HIGH && !bottonePremuto)
  {
    tempoPressione = millis();
    bottonePremuto = true;
    letteraTradotta = false;
    spazioTradotto = false;
  } 

  // Gestione Rilascio
  else if (statoBottone == LOW && bottonePremuto) 
  {
    unsigned long durataPressione = millis() - tempoPressione;
    bottonePremuto = false;
    tempoRilascio = millis();

    if (durataPressione > 40) 
    { 
      if (durataPressione < (tempoRicezione * 1.5)) 
      {
        sequenzaRicevuta += ".";
        Serial.print(".");
      }
      else 
      {
        sequenzaRicevuta += "-";
        Serial.print("-");
      }
    }
  }

  if (!bottonePremuto)
  {
    unsigned long durataPausa = millis() - tempoRilascio;

    // Fine lettera
    if (durataPausa >= (tempoRicezione * 3) && !letteraTradotta && sequenzaRicevuta.length() > 0)
    {
      if (sequenzaRicevuta == "........")
      {
        letteraTradotta = true;
        Serial.print("\33[2K\r");
        sequenzaRicevuta = "";
      } 
      // Altrimenti, se è una sequenza normale, traduci la lettera
      else 
      {
        char carattereTradotto = traduciMorse(sequenzaRicevuta);
        if (carattereTradotto != '\0') 
        {
          Serial.print(carattereTradotto);
        }
        sequenzaRicevuta = ""; 
        letteraTradotta = true;
      }
    }
  }
}

//Funzione di traduzione da stringa di simbolo a suono e luce
void eseguiMorse(String sequenza) {
  for (int i = 0; i < sequenza.length(); i++) 
  {
    digitalWrite(ledPin, HIGH);
    tone(speakerPin, 880);
    
    if (sequenza[i] == '.') delay(tempoTrasmissione);
    else delay(tempoTrasmissione * 3); // Linea = 3 volte il punto
    
    digitalWrite(ledPin, LOW);
    noTone(speakerPin);
    delay(tempoTrasmissione);
  }
}

//Funzione di traduzione da stringa di punti linea a simbolo in formato ASCII
char traduciMorse(String sequenza) 
{
  for (int i = 0; i < sequenza.length(); i++) Serial.print("\b \b");

  for (int i = 0; i < 38; i++) 
  {
    if (morseCode[i] == sequenza) 
    {
      if (i < 26) return (char)('A' + i);      // A-Z
      if (i >= 26 && i < 36) return (char)('0' + (i - 26)); // 0-9
      if (i == 36) return ' ';                 // Spazio
      if (i == 37) 
      {
        Serial.print("\b \b");                 // Cancella il carattere precedente
        return '\0';                           // Ritorna null
      }
    }
  }
  return '?'; // Se non trovato
}