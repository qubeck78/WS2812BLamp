#include "lamp.h"

//https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

lampData_t lampData;

Adafruit_NeoPixel led( _LAMP_NUMPIXELS, _LAMP_PIN, NEO_GRB + NEO_KHZ800 );

int lampInit( void )
{
  int i;
  
  led.begin(); 
  led.setBrightness( 255 );
  led.clear();
  led.show();

  for( i = 0; i < _LAMP_NUMPIXELS; i++ )
  {
    lampData.r[ i ] = 0;
    lampData.g[ i ] = 0;
    lampData.b[ i ] = 0;
  }

  lampData.animState  = lasIdle;
  lampData.tick       = 0;
  
  return 0;
  
}

int lampSetPixel( int idx, unsigned char r, unsigned char g, unsigned char b )
{
  if( idx < 0 )
  {
    return 1;
  }
  if( idx >= _LAMP_NUMPIXELS )
  {
    return 1;
  }

  lampData.r[ idx ] = r;
  lampData.g[ idx ] = g;
  lampData.b[ idx ] = b;
  
  return 0;
}

int lampSetPixelAlpha( int idx, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha )
{
  int arp, agp, abp;
  int arb, agb, abb;
  
  if( idx < 0 )
  {
    return 1;
  }
  
  if( idx >= _LAMP_NUMPIXELS )
  {
    return 1;
  }

  arb = lampData.r[ idx ] * ( 255 - alpha );
  agb = lampData.g[ idx ] * ( 255 - alpha );
  abb = lampData.b[ idx ] * ( 255 - alpha );

  arp = ( r * alpha ) + arb;
  agp = ( g * alpha ) + agb;
  abp = ( b * alpha ) + abb;

  arp /= 256;
  agp /= 256;
  abp /= 256;

  if( arp > 255 )
  {
    arp = 255;
  }
  if( arp < 0 )
  {
    arp = 0;
  }
  if( agp > 255 )
  {
    agp = 255;
  }
  if( agp < 0 )
  {
    agp = 0;
  }
  if( abp > 255 )
  {
    abp = 255;
  }
  if( abp < 0 )
  {
    abp = 0;
  }

  lampData.r[ idx ] = arp;
  lampData.g[ idx ] = agp;
  lampData.b[ idx ] = abp;
  
  return 0;
}


int lampSetScene( int scene )
{
  
  switch( scene )
  {
    case 0:

      lampData.animState = lasTurnOff1_0;

      break;

    case 1:
      
      lampData.animState = lasTurnOn1_0;

      break;

    case 2:
      
      lampData.animState = lasWhiteNoise;

      break;

    case 3:
      
      lampData.animState = lasColorNoise;

      break;
      
    case 4:
      
      lampData.animState = lasFireplace;

      break;

    case 5:
      
      lampData.animState = lasColorBars;

      break;

    case 6:

      lampData.animState = lasWhiteBreathe1_0;
      break;
  }
 

  return 0;
}


int lampAnimation()
{
  int i;
  int j;
  int r;
  int g;
  int b;
  
  switch( lampData.animState )
  {
    case lasIdle:

      break;


    case lasTurnOn1_0:

      lampData.tick = 0;
      lampData.animState = lasTurnOn1_1;
      
      break;


    case lasTurnOn1_1:

      lampData.tick++;

      if( lampData.tick <= _LAMP_NUMPIXELS + 255 )
      {

        for( i = 0 ; i <= _LAMP_NUMPIXELS / 2; i++ )
        {
        
          if( i < lampData.tick )
          {
            r = lampData.tick - i;
            if( r < 0 )
            {
              r = 0;
            }
            if( r > 255 )
            {
              r = 255;
            }
            
            lampSetPixel( _LAMP_NUMPIXELS / 2 + i, r, r, r );
            lampSetPixel( _LAMP_NUMPIXELS / 2 - i, r, r, r );          
          }
        }
      }
      else
      {
        lampData.animState = lasTurnOn1_2;
      }

      break;


      case lasTurnOn1_2:

        for( i = 0; i < _LAMP_NUMPIXELS; i++ )
        {
          lampSetPixel( i, 255, 255, 255 );
        }

        lampData.animState = lasIdle;
        
        break;

     case lasTurnOff1_0:
        
        lampData.tick = 0;
        
        for( i = 0; i < _LAMP_NUMPIXELS; i++ )
        {
          lampSetPixelAlpha( i, 0, 0, 0, 1 );
        }

        lampData.animState = lasTurnOff1_1;

        break;

     case lasTurnOff1_1:


        if( lampData.tick < 300 )
        {
          lampData.tick++;
          for( i = 0; i < _LAMP_NUMPIXELS; i++ )
          {
            lampSetPixelAlpha( i, 0, 0, 0, 1 );
          }  
        }
        else
        {
          for( i = 0; i < _LAMP_NUMPIXELS; i++ )
          {
            lampSetPixel( i, 0, 0, 0 );
          }
          lampData.animState = lasIdle; //idle
        }

        break;
        
     case lasWhiteNoise:

      for( i = 0; i < _LAMP_NUMPIXELS; i++)
      {
        if( random(1000) > 970 )
        {
          lampSetPixel( i, 255, 255, 255 );
        }
        else
        {
          lampSetPixelAlpha( i, 0, 0, 0, 7 );
        }
      }
      break;

    case lasColorNoise:

      for( i = 0; i < _LAMP_NUMPIXELS; i++)
      {
        if( random(1000) > 970 )
        {
          lampSetPixel( i, random( 255 ), random( 255 ), random( 255 ) );
        }
        else
        {
          lampSetPixelAlpha( i, 0, 0, 0, 7 );
        }
      }
      break;

     case lasFireplace:

      for( i = 0; i < _LAMP_NUMPIXELS; i++)
      {
        if( random(1000) > 970 )
        {
          lampSetPixel( i, 255, 55, 0 ); //fire :)
        }
        else
        {
          lampSetPixelAlpha( i, 0, 0, 0, 7 );
        }
      }
      break;

   case lasColorBars:

      lampData.tick++;
      
      if( lampData.tick % 10 == 0 )
      {
        for( i = 0; i < _LAMP_NUMPIXELS; i++)
        {
          if( random(1000) > 995 )
          {
            r = random( 255 );
            g = random( 255 );
            b = random( 255 );

            for( j = 0; j < 5; j++ )
            {
              if(( j == 0 ) || ( j == 4 ) )
              {
                lampSetPixelAlpha( i + j, r, g, b, 128 );
              }
              else
              {
                lampSetPixel( i + j, r, g, b );              
              }
            }
            i += 4;
          }
          else
          {
            lampSetPixelAlpha( i, 0, 0, 0, 7 );
          }
        }
      }
      break;

    case lasWhiteBreathe1_0:

      lampData.tick = 0;
      
      lampData.animState = lasWhiteBreathe1_1;
      
      break;

    case lasWhiteBreathe1_1:

      if( lampData.tick < 64 )
      {
        for( i = 0; i < _LAMP_NUMPIXELS; i++ )
        {
           lampSetPixelAlpha( i, 128, 128, 128, lampData.tick );
        }

        lampData.tick++;
        
      }
      else
      {      
        lampData.tick = 0;
        lampData.animState = lasWhiteBreathe1_2;        
      }
      break;

    case lasWhiteBreathe1_2:

      if( lampData.tick < 128 )
      {
        
        for( i = 0; i < _LAMP_NUMPIXELS; i++ )
        {
           r = 128 + lampData.tick;

           if( r > 255 )
           {
              r = 255;
           }
           lampSetPixel( i, r, r, r );
        }

        lampData.tick++;
        

      }
      else
      {
        lampData.tick = 0;
        lampData.animState = lasWhiteBreathe1_3;
      }
      break;

    case lasWhiteBreathe1_3:

      if( lampData.tick < 512 )
      {

        for( i = 0; i < _LAMP_NUMPIXELS; i++ )
        {
           r = 255 - ( lampData.tick / 4 );

           if( r > 255 )
           {
              r = 255;
           }
           
           lampSetPixel( i, r, r, r );
        }

        lampData.tick++;
      }
      else
      {
        lampData.tick = 0;
        lampData.animState = lasWhiteBreathe1_2;
      }
      break;
      
  }


/*  for( i = 0; i < _LAMP_NUMPIXELS; i++ )
  {
    lampData.r[ i ] = 16;
    lampData.g[ i ] = 16;
    lampData.b[ i ] = 16;
    
  }*/
    return 0;
}

int lampMain()
{
  static unsigned long int lastRefreshMs = 0;
  int i;

  if( millis() >= ( lastRefreshMs + _LAMP_REFRESH_TIME_MS ) )
  {
    lastRefreshMs = millis();

    //do animation step
    lampAnimation();

    //refresh led strip
    for( i = 0; i < _LAMP_NUMPIXELS; i++ )
    {
       led.setPixelColor( i, led.Color( lampData.r[i], lampData.g[i], lampData.b[i] ) );
    }
    led.show();
  }

}
