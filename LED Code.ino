#include <FastLED.h>
#define NUM_LEDS 144
#define DATA_PIN 9
#define RESET 6
#define STROBE 5
#define AUDIOPIN A0
int i = 0;
int col = 0;
int inputArray[7];
int led63hz = 0;
int downMillis();
unsigned long currentMicros = 0;
unsigned long previousMicros = 0;
unsigned long holdMicros = 0;
int downcount = 15;

//for IC data
int p1 = LOW;
int p2 = LOW;
int p3 = LOW;
int p4 = LOW;
int start = HIGH;

//Testing part veriables
int resetState = LOW;
unsigned long strobeLowMicros = 0;
bool readAnalog = false;
int j = 0;
int red = 200;
int green = 20;
int blue = 100;

int led160hz = 0;
int led400hz = 0;
int led1000hz = 0;
int led2500hz = 0;
int led6250hz = 0;
int led16khz = 0;

//Code for LED strip functionality
CRGBArray<NUM_LEDS> leds;



void setup() {
  // put your setup code here, to run once:

  //IC related pin setup
  pinMode(RESET, OUTPUT);
  pinMode(STROBE, OUTPUT);
  pinMode(AUDIOPIN, INPUT);
  digitalWrite(STROBE, HIGH);
  
  //LED related pin setup
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 700);
  FastLED.setBrightness(20);

  //Serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMicros = micros();
  //Function to read analog values from IC MSQEQ7
  audioRead();
  
  /*
  EVERY_N_MILLISECONDS(1000)
  {
    Serial.println(inputArray[0]);
    Serial.println(inputArray[1]);
    Serial.println(inputArray[2]);
    Serial.println(inputArray[3]);
    Serial.println(inputArray[4]);
    Serial.println(inputArray[5]);
    Serial.println(inputArray[6]);   
    Serial.println("\n\n\n");
  }
  */
  
  //Function(s) to control LEDs based on Frequency band
  mapFunction();
  lightUp();
  //63HzLightDown();

  //Color changer counter
  red++;
  green++;
  blue++;

  if(red == 255){red = 0;}
  if(green == 255){green = 0;}
  if(blue == 255){blue = 0;}

  //Testing code vvv
  /*if(downcount > 0)
  {
    leds[downcount].setRGB(0, 0, 0);
    FastLED.show();
    downcount--;
  }*/
  
  
  /*EVERY_N_MILLISECONDS(10)//if((currentMicros - previousMicros) > 500)
  {
    
    leds[downcount].setRGB(0, 0, 0);
   
    if (downcount < 0)
    {
      downcount = 15;
    }

    downcount--;
  }*/

  //FastLED.show();
} //Testing Code ^^^

//Function to Read Analog Values
void audioRead()
{
  /*Too linear, doesn't work
  digitalWrite(RESET, HIGH);
  digitalWrite(RESET, LOW);
  delayMicroseconds(75);
  //If 400usec has passed, start audio reads
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(STROBE, LOW);
    delayMicroseconds(40);

    inputArray[i] = analogRead(AUDIOPIN);
    //Serial.print("\nThis is box ");
    //Serial.print(i);
    //Serial.print(":");
    //Serial.print(inputArray[i]);
    // Serial.print("\n");
    digitalWrite(STROBE, HIGH);
    delayMicroseconds(40);
  }*/

  
  //If reset is high, dont do this part
  if (resetState == LOW)
  {
    digitalWrite(RESET, HIGH);
    delayMicroseconds(0.1);
    digitalWrite(RESET, LOW);
    delayMicroseconds(75);
    resetState = HIGH;
  }
  
  EVERY_N_MILLISECONDS(0.075)
  {
    digitalWrite(STROBE, LOW);
    strobeLowMicros = micros();
    //Analog read is now available
    readAnalog = true;

  }
  
  //If 40 microseconds have passed, read from analog pin
  if( (micros() - strobeLowMicros >= 0.040) && readAnalog == true)
  {
    //Array that holds our values for analog reads
    inputArray[i] = analogRead(AUDIOPIN);
    if(inputArray[i] <= 150)
    {
      inputArray[i] = 0;
    }
    digitalWrite(STROBE, HIGH);
    //Set analog read state to false so that we dont get re-read s in the conditional for the if statement
    readAnalog = false;
    i++;


    //if all 7 array boxes are filled, start at the beginning
    if(i == 7)
    {
      i = 0;
    }
    
  }
  
}

void mapFunction()
{

  //Or we could use a map
  led63hz = map(inputArray[0], 0, 1023, 0, 14);
  led160hz = map(inputArray[1], 0, 1023, 0, 14);
  led400hz = map(inputArray[2], 0, 1023, 0, 14);
  led1000hz = map(inputArray[3], 0, 1023, 0, 14);
  led2500hz = map(inputArray[4], 0, 1023, 0, 14);
  led6250hz = map(inputArray[5], 0, 1023, 0, 14);
  led16khz = map(inputArray[6], 0, 1023, 0, 14);
  downcount = led63hz;

}

void lightUp()
{
  //fill_solid(leds, led63hz, CRGB(0, 210, 100));
  
  leds(0,led63hz).fill_solid(CRGB(50, 210, 100));
  leds(15, led63hz).fill_solid(CRGB(0,0,0));
 
  leds(17,17+led160hz).fill_solid(CRGB(200, 10, 50));
  leds(32,17+led160hz).fill_solid(CRGB(0,0,0));

  leds(34,34+led400hz).fill_solid(CRGB(10, 50, 250));
  leds(47,34+led400hz).fill_solid(CRGB(0,0,0));

  leds(49,49+led1000hz).fill_solid(CRGB(100, 100, 100));
  leds(64,49+led1000hz).fill_solid(CRGB(0,0,0));

  leds(66,66+led2500hz).fill_solid(CRGB(100, 200, 69));
  leds(81,66+led2500hz).fill_solid(CRGB(0,0,0));

  leds(83,83+led6250hz).fill_solid(CRGB(150, 75, 30));
  leds(98,83+led6250hz).fill_solid(CRGB(0,0,0));

  leds(100,100+led16khz).fill_solid(CRGB(70, 250, 10));
  leds(115,100+led16khz).fill_solid(CRGB(0,0,0));
  
  FastLED.show();
}
