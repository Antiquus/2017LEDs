#include <Adafruit_NeoPixel.h>
//#include <Wire.h>

#define pinMain 6
#define auxPin 7

#define enabledPin 8
#define climbingPin 9
#define gearPin 10
#define shootingPin 11



Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, pinMain, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(9, auxPin, NEO_GRB + NEO_KHZ800);

int count = 0;
unsigned long previousMillis = 0;

boolean first = false;

void setup() {
  // put your setup code here, to run once:

//  Wire.begin(42);                // join i2c bus with address #42
//  Serial.begin(9600);   
  pinMode(enabledPin, INPUT); 
  pinMode(climbingPin, INPUT); 
  pinMode(gearPin, INPUT); 
  pinMode(shootingPin, INPUT); 
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'


  //Wire.onReceive(receiveEvent); // register event
}

int pixelNum = strip.numPixels();

uint32_t gold = strip.Color(255, 110, 0);
uint32_t blue = strip.Color(0, 0, 250);
uint32_t columBlue = strip.Color(0, 255, 230);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);

uint32_t off = strip.Color(0, 0, 0);

void loop() {


//initMode();
//climbingMode();
//collectingMode(); work on this
//gearCollectedMode();  
//shootingMode(red,100,5);
//teleMode();
pinLogic();
}

void pinLogic(){
  if(digitalRead(enabledPin) ==1 && digitalRead(climbingPin) ==1 && digitalRead(shootingPin) ==1 && digitalRead(gearPin) ==1)
  {
    
  }
  else if(digitalRead(enabledPin) ==1){
    if(digitalRead(climbingPin) ==1){
      climbingMode();
    }else if(digitalRead(shootingPin) ==1){
        shootingMode(red,100,5);
    }else if(digitalRead(gearPin) ==1){
        gearCollectedMode();
    }else{
    teleMode();
    }
  }
  else{
    initMode();
  }
}

void initMode() {
  int halfway = pixelNum / 2;
  setChunk(0, halfway, blue);
  setChunk(halfway + 1, pixelNum, gold);

}

void climbingMode() {
  setFull(blue);
  delay(67);
  setFull(gold);
  delay(66);
/*
  setFull(blue);
  delay(500);
  setFull(gold);
  delay(500);
  */
}

void collectingMode() {
  int a;
  if (first == true)//begin init
  {
    setFull(off);//reset display
    a = pixelNum;//reset a to top
    first == false;//finish init
  }
  setChunk(a,a,green);//set pixel
  a++;//incriment a
  if (a <= 0)//reached bottom
  {
    first = true;//run init next loop
  }
  delay(75);//delay for visual effect
}


void gearCollectedMode() {
  setFull(columBlue);
}

void shootingMode(uint32_t color, int cycles, int distance) {
  for (int j = 0; j < cycles; j++) { //do 10 cycles of chasing
    for (int q = 0; q < distance; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + distance) {
        strip.setPixelColor(i + q, color);  //turn every third pixel on
      }
      strip.show();

      delay(50);

      for (int i = 0; i < strip.numPixels(); i = i + distance) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}


void teleMode()
{
  int i;
  unsigned long currentMillis = millis();
  unsigned long interval = 100;
  if (currentMillis - previousMillis >= interval )
  {
    count++;
    previousMillis = currentMillis;
  }

  if ( count % 4 == 0 ) {
    for ( i = 0; i < 32; i += 4)
    {
      strip.setPixelColor(i, blue);
      strip.setPixelColor(i + 1, blue);
      strip.setPixelColor(i + 2, gold);
      strip.setPixelColor(i + 3, gold);
      strip.show();
    }
  }

  if ( count % 4 == 1) {
    for ( i = 0; i < 32; i += 4) {
      strip.setPixelColor(i, gold);
      strip.setPixelColor(i + 1, blue);
      strip.setPixelColor(i + 2, blue);
      strip.setPixelColor(i + 3, gold);
      strip.show();
    }
  }

  if ( count % 4 == 2) {
    for ( i = 0; i < 32; i += 4) {
      strip.setPixelColor(i, gold);
      strip.setPixelColor(i + 1, gold);
      strip.setPixelColor(i + 2, blue);
      strip.setPixelColor(i + 3, blue);
      strip.show();
    }
  }
  if ( count % 4 == 3) {
    for ( i = 0; i < 32; i += 4) {
      strip.setPixelColor(i, blue);
      strip.setPixelColor(i + 1, gold);
      strip.setPixelColor(i + 2, gold);
      strip.setPixelColor(i + 3, blue);
      strip.show();
    }
  }
}


void setChunk(int startingPixel, int endingPixel, uint32_t color)
{
  for (int i = startingPixel ; i <= endingPixel ; i++) {

    strip.setPixelColor(i, color);
    strip.show();
  }
}

void setChunkAlternatingColor(int startingPixel, int endingPixel, uint32_t color1, uint32_t color2)
{
  for (int i = startingPixel ; i <= endingPixel ; i++) {

    if (i % 2 == 0)
    {
      strip.setPixelColor(i, color1);
    }
    else
    {
      strip.setPixelColor(i, color2);
    }
    strip.show();
  }
}

void setFull(uint32_t color)
{
  for (int i = 0 ; i <= pixelNum ; i++) {

    strip.setPixelColor(i, color);
    strip.show();
  }
}
