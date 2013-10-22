int recording[200];
int micLevel = 0;
int nomore = 0;
int ending = 0;
int LEDL = 0;
int LEDS = 0;
int avail[9];
int randy = 0;
int pin = 0;
int out = 0;
int fix = 0;
int ready = 1;
int readyornot = 0;
int resist = 0;

/* This program waits until a certian mic level is reached, record the levels of speech for
 * a maximum of 10 seconds, and then flash random LEDs at the same levels of the recording...
 * It's fixed now ;) This is my first real project, I guess. This should get me a fine art GCSE! Anyway:
 * Writer: terrabyte_aura
 * Project: Voice Your Opinion.
 */

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  randomSeed(analogRead(0));
  avail[0] = 1;
  avail[1] = 1;
  avail[2] = 1;
  avail[3] = 1;
  avail[4] = 1;
  avail[5] = 1;
  avail[6] = 1;
  avail[7] = 1;
  avail[8] = 1;
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(400);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop() {
  while(micLevel <= 360) { //waits for mic to be at a good level (<=360)
    micLevel = analogRead(1);
    resist = analogRead(2);
    if(resist > 1000) {
      micLevel = micLevel + 15;
    }
    Serial.print("Mic @ ");
    Serial.print(micLevel);
    Serial.println(" Not loud enough... (if last view of message, ignore)");
    delay(100);
  }
  for(int y = 0; y < 200; y++) {
    micLevel = analogRead(1);
    resist = analogRead(2);
    if(resist > 1000) {
      micLevel = micLevel + 15;
    }
    recording[y] = micLevel;  //records the level of the microphone in the array
    Serial.print(" MicLevel: ");
    Serial.println(micLevel);
    if(micLevel <= 360) {
      nomore = nomore + 1;
      Serial.print("nomore = ");
      Serial.print(nomore);
      if(nomore == 10) {
        fix = y;
        y = 200;  //if a low level is recorded for 2 seconds, it will terminate the recording
      }
    } 
    else {
      nomore = 0;
      Serial.print(" nomore = 0"); //resets the counter for low level...
    }
    delay(100);
    Serial.print(" Fix @ ");
    Serial.print(fix);
    if(fix > 0) {
      ending = fix;
      Serial.println(" Recording End Reached");
      fix = 0;
    }
  }
  Serial.println("FLASH!");
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(400);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  Serial.println("Playback...");
  for(int z = 0; z < ending; z++) {
    Serial.print(recording[z]);
    Serial.print(" ending:");
    Serial.print(ending);
    LEDL = recording[z];
    Serial.print(" Position:");
    Serial.println(z);
    if(LEDL <= 380) { //this takes the level at frame z and turns it into a number of LEDs
      LEDS = 1;
    }
    if(LEDL > 380 && LEDL <= 411) {
      LEDS = 2;
    }
    if(LEDL > 411 && LEDL <= 442) {
      LEDS = 3;
    }
    if(LEDL > 442 && LEDL <= 473) {
      LEDS = 4;
    }
    if(LEDL > 473 && LEDL <= 504) {
      LEDS = 5;
    }
    if(LEDL > 504 && LEDL <= 535) {
      LEDS = 6;
    }
    if(LEDL > 535 && LEDL <= 566) {
      LEDS = 7;
    }
    if(LEDL > 566 && LEDL <= 870) {
      LEDS = 8;
    }
    if(LEDL > 870) {
      LEDS = 9;
    }
    Serial.print(LEDS);
    Serial.println(" is the number of LEDS to be on...");
    while(readyornot == 0) {
      out = 0;
      randy = random(0, 10);
      Serial.print(randy); //this chooses which LEDs will NOT be turned on...
      Serial.println(" is the random number");
      out = 0;
      while(out < 1) {
        if(avail[randy] == 0) { //this checks to see if the number's already been chosen
          randy = random(0, 10);
          Serial.print("previous had already been chosen... new number: ");
          Serial.println(randy);
        } 
        else {
          avail[randy] = 0;
          Serial.print(randy);
          Serial.println(" activated");
          out = 1;
          ready = ready + 1;
          Serial.print("Ready: ");
          Serial.println(ready);
        }
        if(ready > LEDS) {
          Serial.println("READY");
          readyornot = 1;
        }
      }
    }
    ready = 1;
    readyornot = 0;
    out = 0;
    for(int p = 0; p < 9; p++) {
      pin = p + 2;
      if(avail[p] == 1) { //this writes to the LEDs
        digitalWrite(pin, LOW);
        Serial.print("LOW- ");
        Serial.println(pin);
      } 
      else {
        digitalWrite(pin, HIGH);
        Serial.print("HIGH- ");
        Serial.println(pin);
        avail[p] = 1;
      }
    }
    delay(100);  //this delays the whole script
    nomore = 0;
    Serial.println("nomore reset");
  }
  for(int q = 0; q < 9; q++) {
    pin = q + 2;
    digitalWrite(pin, LOW);
  }
  Serial.println("CLEAR");
}


