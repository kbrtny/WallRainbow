#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ColorConverterLib.h>

Adafruit_PWMServoDriver pwm[] = {Adafruit_PWMServoDriver(0X40),Adafruit_PWMServoDriver(0X41)};


#define NUM_LEDS 1
struct RGB_LED { uint8_t pinR; uint8_t pinG; uint8_t pinB; uint16_t R; uint16_t G; uint16_t B;};
RGB_LED LEDS[5];


double hue = 0;
double saturation = .6;
double value = .1;

double red, green, blue;

void setup() {
  pwm[0].begin();
  pwm[0].setOscillatorFrequency(27000000);
  pwm[0].setPWMFreq(160);  // This is the maximum PWM frequency
  pwm[0].setOutputMode(0);
  for(int i=0;i<(NUM_LEDS + 1);i++){
    LEDS[i].pinR = 3*i;
    LEDS[i].pinG = 3*i+1;
    LEDS[i].pinB = 3*i+2;
  }
}

void loop() {
  hue += 0.01;
  if(hue > 1.0){
    hue = 0.0;
  }
  RGBConverter::HsvToRgb(hue, saturation, value, red, green, blue);
  for(int i=0;i<(NUM_LEDS + 1);i++){
    LEDS[i].R = 4096 - static_cast<uint16_t>(red * 0.7 * 4095);
    LEDS[i].G = 4096 - static_cast<uint16_t>(green * 4095);
    LEDS[i].B = 4096 - static_cast<uint16_t>(red * 0.75 * 4095);
  }
  
  for(int i=0;i<(NUM_LEDS + 1);i++){
    pwm[0].setPWM(LEDS[i].pinR, 0, LEDS[i].R ); 
    pwm[0].setPWM(LEDS[i].pinG, 0, LEDS[i].G ); 
    pwm[0].setPWM(LEDS[i].pinB, 0, LEDS[i].B ); 
  }
  delay(100);
}
