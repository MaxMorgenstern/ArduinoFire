#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// LED
int led_count = 5*60;
int led_1_pin = 2;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(led_count, led_1_pin, NEO_GRB + NEO_KHZ800);

int brightness = 128;

uint32_t fire_color   = pixels.Color ( 80,  35,  00);
//uint32_t fire_color   = pixels.Color ( 20,  40,  190);
uint32_t off_color    = pixels.Color (  0,  0,  0);



void setup() {
  pixels.begin();
  //pixels.setBrightness(brightness);
  pixels.show();

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
}


void loop() {
  /*
  //  Regular (orange) flame:
  int r = 226, g = 121, b = 35;

  //  Purple flame:
  //  int r = 158, g = 8, b = 148;

  //  Green flame:
  //int r = 74, g = 150, b = 12;

  
  for(int i=0; i<pixels.numPixels(); i++) {
    int flicker = random(0,150);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    pixels.setPixelColor(i,r1,g1, b1);
  }
  pixels.show();

  //  Adjust the delay here, if you'd like.  Right now, it randomizes the 
  //  color switch delay to give a sense of realism
  delay(random(10,113));
  */
  Draw();
  delay(random(50,150));
}





void Draw()
{
//  Clear();
  for(int i=0;i<pixels.numPixels();i++)
    {
      pixels.setPixelColor(i,off_color);
    }
    
  for(int i=0;i<pixels.numPixels();i++)
    {
    AddColor(i, fire_color);
    int r = random(100);
    int r2 = random(100);
    int r3 = random(100);
    uint32_t diff_color = pixels.Color ( r, r/2, r/2);
    SubstractColor(i, diff_color);
    }
    
  pixels.show();
}

void AddColor(uint8_t position, uint32_t color)
{
uint32_t blended_color = Blend(pixels.getPixelColor(position), color);
pixels.setPixelColor(position, blended_color);
}

void SubstractColor(uint8_t position, uint32_t color)
{
uint32_t blended_color = Substract(pixels.getPixelColor(position), color);
pixels.setPixelColor(position, blended_color);
}

uint32_t Blend(uint32_t color1, uint32_t color2)
{
uint8_t r1,g1,b1;
uint8_t r2,g2,b2;
uint8_t r3,g3,b3;

r1 = (uint8_t)(color1 >> 16),
g1 = (uint8_t)(color1 >>  8),
b1 = (uint8_t)(color1 >>  0);

r2 = (uint8_t)(color2 >> 16),
g2 = (uint8_t)(color2 >>  8),
b2 = (uint8_t)(color2 >>  0);

return pixels.Color(constrain(r1+r2, 0, 255), constrain(g1+g2, 0, 255), constrain(b1+b2, 0, 255));
}

uint32_t Substract(uint32_t color1, uint32_t color2)
{
uint8_t r1,g1,b1;
uint8_t r2,g2,b2;
uint8_t r3,g3,b3;
int16_t r,g,b;

r1 = (uint8_t)(color1 >> 16),
g1 = (uint8_t)(color1 >>  8),
b1 = (uint8_t)(color1 >>  0);

r2 = (uint8_t)(color2 >> 16),
g2 = (uint8_t)(color2 >>  8),
b2 = (uint8_t)(color2 >>  0);

r=(int16_t)r1-(int16_t)r2;
g=(int16_t)g1-(int16_t)g2;
b=(int16_t)b1-(int16_t)b2;
if(r<0) r=0;
if(g<0) g=0;
if(b<0) b=0;

return pixels.Color(r, g, b);
}


