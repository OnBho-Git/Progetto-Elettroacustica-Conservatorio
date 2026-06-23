---
marp: true
theme: gaia
_class: lead
paginate: false
style: |
  section {
    font-family: 'Courier New', Courier, monospace;
    font-size: 30px
  }
  h1, h2, h3, h4 {
    font-weight: normal;
  }
  .twocol {
    display: grid;
    grid-template-columns: repeat(2, minmax(0, 1fr));
    gap: 20px;
  }
---
![w:350 Logo Conservatorio di Brescia](src/logo.png)
# Elettroacustica
### Danesi Gabriele (Matricola N. T-00053)
#### Creazione di un sistema di comunicazione Morse per Terminale
---

## Idea di Partenza

Poter creare un sistema che possa ricreare l'intro del brano *Glitter Freeze* di Gorillaz in modo veloce
<div class = twocol>
<div>
</div>
<div>

![w:350 https://open.spotify.com/intl-it/track/4EJFCpthcrP6oOUUXQZ22Z?si=c80f0fb1555943e3](src/PB.jpg)
</div>

---

## Componenti Elettronici Utilizzati

Oltre all'utilizzo di cavi jumper, di Arduino UNO Q R4 con caricato il codice e un computer con accesso a terminale che possa leggere ASCII sono stati utilizzati

<div class = twocol>
<div>

- Resistenza (100Ω) * 1
- Resistenza (220Ω) * 1
- Resistenza (1kΩ) * 1

</div>
<div>

- Led Bianco * 1
- Diffusore Acustico * 1
- Transistor NPN * 1

</div>

---

## Collegamenti Elettrici

Verrà scritto nel verso in cui si muove la corrente

DPin6-->Res(220Ω)-->AnodoLED-->CatodoLED-->GND
DPin9-->Res(1kΩ)-->Transistor(BASE)
5V-->Transistor(COLL.)
Transistor(EMETT.)-->Res(100Ω)-->Diffusore-->GND

---
<!---_backgroundColor: #ffffff--->
![bg w:85%](src/Project.jpg)

---

## Il codice: Global Value
Oltre alle inizializzazioni dei PIN è stata creato un array di stringhe, contenente dal valore array [0] a [25] la sequenza di punti e linee per le lettere dell'alfabeto, dal [26] al [35] quelle per i numeri, mentre il valore [36] e [37] (rispettivamente spazio e backspace) sono stati creati per facilitare la scrittura di testo in morse

---

## Il codice: void setup

Inizializzazione del Seriale e definizione dei PIN in valore di scrittura o lettura. Per evitare un suono che sia un'onda quadra, occorre sfruttare la funzione PWM dell'arduino, presente solo nei PIN con il simbolo ~

![ Arduino](src/Arduino.png)

---
## Il codice: void loop

La parte di loop è divisa in due sezioni: quella che legge dal terminale e invia all'esterno il testo tradotto in codice morse // e quella che trasforma il codice morse inviato dal bottone in testo stampato a schermo

![ Arduino](src/Arduino.png)

---

## Il codice: Le Funzioni Esterne

Le due funzioni esterne sono quelle richiamate rispettivamente per inviare il segnale di punti e linee di una lettera ai rispettivi pin (void) e per trasformare una stringa di punti e linee in un simbolo (char)

![ Arduino](src/Arduino.png)

---

## IA??

// Sì, è stata utilizzata l'IA nella fase 'grafica'. Il codice che crea i punti e le linee durante la fase di scrittura e poi la relativa cancellazione è stato fatto con l'aiuto di Gemini Pro 2.5

---
# Fine
Grazie per l'attenzione
