#ifndef _LAMP_H
#define _LAMP_H

#include <Adafruit_NeoPixel.h>

#define _LAMP_PIN             4
#define _LAMP_NUMPIXELS       85 
#define _LAMP_REFRESH_TIME_MS 10


typedef enum _lampAnimationState_t{ lasIdle, lasTurnOn1_0, lasTurnOn1_1, lasTurnOn1_2, lasTurnOff1_0, lasTurnOff1_1, 
  lasWhiteNoise, lasColorNoise, lasFireplace, lasColorBars, lasWhiteBreathe1_0, 
  lasWhiteBreathe1_1, lasWhiteBreathe1_2, lasWhiteBreathe1_3 }lampAnimationState_t;


typedef struct _lampData_t
{
  unsigned long int     tick;
  lampAnimationState_t  animState;
  
  unsigned char         r[_LAMP_NUMPIXELS];
  unsigned char         g[_LAMP_NUMPIXELS];
  unsigned char         b[_LAMP_NUMPIXELS];
  
}lampData_t;



int lampInit( void );
int lampSetPixel( int idx, unsigned char r, unsigned char g, unsigned char b );
int lampSetPixelAlpha( int idx, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha );

int lampSetScene( int scene );
int lampMain( void );

#endif
