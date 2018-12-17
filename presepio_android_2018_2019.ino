#include <Adafruit_NeoPixel.h>


#define FIREPIN 2 
#define FIREN 5

#define LAMPPIN 3 //lampada retro grotta
#define LAMPN 3 //nr pin lampada grotta

#define WATPIN 4 //lampada acqua
#define WATN 2 //nr pin lampada acqua

#define SUNPIN 5  //mattina 
#define SUNN 21

#define HOMEPIN 12
#define HOMEN 10 

#define COMETPIN 6  //led normale

#define STAR1PIN 10  //led normale vibrante
#define STAR2PIN 11  //led normale vibrante
#define STAR3PIN 9  //led normale vibrante

#define BACKPIN 7  //sfondo montagne
#define BACKN 3


#define MAXTIME 115000 //tempo del ciclo totale 1 minuto
#define DAYDELAY 100
#define NIGHTDELAY 100
#define SKYDELAY 100
#define STAR1DELAY 400
#define STAR2DELAY 400
#define COMETDELAY 400
#define BGDELAY 100

//SWITCH TEMPO
#define DAYSWITCH 27000
#define SKYUPSWITCH 56000
#define SKYDOWNSWITCH 85000
#define HOMEBRIGHT 50

//inizializza led RGB
Adafruit_NeoPixel fireleds = Adafruit_NeoPixel(FIREN, FIREPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel lampleds = Adafruit_NeoPixel(LAMPN, LAMPPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel watleds = Adafruit_NeoPixel(WATN, WATPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel sunleds = Adafruit_NeoPixel(SUNN, SUNPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel homeleds = Adafruit_NeoPixel(HOMEN, HOMEPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel backleds = Adafruit_NeoPixel(BACKN, BACKPIN, NEO_GRB + NEO_KHZ800);

//timing for fire
unsigned long previousMillis = 0; //riferimento per fire
unsigned long previousLampMillis = 0; //riferimento per fire
unsigned long previousWatMillis = 0; //riferimento per fire
unsigned long previousStar1Millis = 0; //riferimento per fire
unsigned long previousStar1DwnMillis = 0;
unsigned long previousStar2Millis = 0; //riferimento per fire
unsigned long previousStar2DwnMillis = 0;
unsigned long previousCometMillis = 0; //riferimento per fire
unsigned long previousCometDwnMillis = 0;
unsigned long tm = 0; //time generale si resetta dopo fine ciclo MAXTIME
unsigned long prevMillis = 0; //riferimento per time generale
unsigned long previousDayMillis = 0;
unsigned long previousNightMillis = 0;
unsigned long previousSkyMillis = 0;
unsigned long previousSkydownMillis = 0;
unsigned long previousbgupMillis = 0;
unsigned long previousbgdownMillis = 0;

int daybr=0;
int bgbr=0;

int is=0;
int stp=0;
int strstp=10;

int is2=0;
int stp2=0;
int strstp2=10;

int isc=0;
int stpc=0;
int strstpc=10;
void setup()
{
  Serial.begin(9600);
  fireleds.begin();
  sunleds.begin();
  homeleds.begin();
  lampleds.begin();
  watleds.begin();
  backleds.begin();
  clearLEDs();   // This function, defined below, turns all LEDs off...  
  fireleds.show();  
  sunleds.show();
  lampleds.show(); 
  watleds.show();  
  backleds.show();
  homeleds.show();

  // declare pin 9 to be an output:
  pinMode(STAR1PIN, OUTPUT);
  pinMode(STAR2PIN, OUTPUT);
  pinMode(STAR3PIN, OUTPUT);
  pinMode(COMETPIN, OUTPUT);


}
void loop()
{ 
  calctime();
  if (tm >= 0 && tm < DAYSWITCH && daybr <= 255)  {
     day();
     Serial.println("day ");
  }
  if (tm > DAYSWITCH && tm < SKYUPSWITCH && daybr >= 0) {
     night(); 
     star1up();
     star2up();
     Serial.println("night ");
  }
  if (tm > SKYUPSWITCH && tm < SKYDOWNSWITCH && daybr <= 255) {
     skyup();
     star1up();
     star2up();
     bgup();
     Serial.println("skyup ");
  } 
  if (tm > SKYDOWNSWITCH && daybr >= 0) {
     skydown(); 
     star1down();
     star2down();
     bgdown();
     Serial.println("skydown ");
  } 
  fire();
  lamp();
  wat();
}
void calctime() {
  unsigned long nowMillis = millis();
  tm+=(nowMillis-prevMillis);
  prevMillis = nowMillis;
  if(tm >= MAXTIME) {
  tm=0;
  }
}
void day() {
  unsigned long dayMillis = tm;
  if (dayMillis - previousDayMillis >= DAYDELAY) {
     previousDayMillis = dayMillis;
     for (int ip=0; ip<SUNN; ip++)
        {
          sunleds.setPixelColor(ip,225,80,50);
          sunleds.setBrightness(daybr);
        }
     sunleds.show();
    Serial.print("day ");Serial.print(daybr);Serial.print("-");Serial.print(tm);Serial.print("\n");
     if (daybr < 255) {
       daybr++;
    };
    if (daybr > 50 && daybr < 75) {
     }
    if (daybr > 75 && daybr < 100) {
       homeleds.setPixelColor(6,0,0,0);
       homeleds.setPixelColor(7,0,0,0);
       homeleds.show();
    }
    if (daybr > 100 && daybr < 125) {
       homeleds.setPixelColor(2,0,0,0);
       homeleds.setPixelColor(3,0,0,0);
       homeleds.show();
    }
    if (daybr > 125 && daybr < 150) {
       homeleds.setPixelColor(0,0,0,0);
       homeleds.setPixelColor(1,0,0,0);
       homeleds.show();
    }
    if (daybr > 150 && daybr < 175) {
       homeleds.setPixelColor(4,0,0,0);
       homeleds.setPixelColor(5,0,0,0);
       homeleds.setPixelColor(8,0,0,0);
       homeleds.setPixelColor(9,0,0,0);
       homeleds.show();
    }
  }
}
void night() {
    unsigned long nightMillis = tm;
    if (nightMillis - previousNightMillis >= NIGHTDELAY) {
      previousNightMillis = nightMillis;
    for (int ip=0; ip<SUNN; ip++)
    {
    sunleds.setPixelColor(ip,225,80,50);
    sunleds.setBrightness(daybr);
    }
    sunleds.show();
   //Serial.print("night ");Serial.print(daybr);Serial.print("-");Serial.print(tm);Serial.print("\n");
    if (daybr > 0) {
    daybr--;
    }
    if (daybr > 75 && daybr < 100) {
       homeleds.setPixelColor(6,255,100,0);
       homeleds.setPixelColor(7,255,100,0);
       homeleds.show();
    }
    if (daybr > 50 && daybr < 75) {
       homeleds.setPixelColor(2,255,100,0);
       homeleds.setPixelColor(3,255,100,0);
       homeleds.show();
    }
    if (daybr > 25 && daybr < 50) {
       homeleds.setPixelColor(0,255,100,0);
       homeleds.setPixelColor(1,255,100,0);
       homeleds.show();
    }
    if (daybr > 0 && daybr < 25) {
       homeleds.setPixelColor(4,255,100,0);
       homeleds.setPixelColor(5,255,100,0);
       homeleds.setPixelColor(8,255,100,0);
       homeleds.setPixelColor(9,255,100,0);
       homeleds.show();
    }
  }
}
void skyup() {
    unsigned long skyMillis = tm;
    if (skyMillis - previousSkyMillis >= SKYDELAY) {
      previousSkyMillis = skyMillis;
    for (int ip=0; ip<SUNN; ip++)
    {
    sunleds.setPixelColor(ip,0,0,40);
    sunleds.setBrightness(daybr);
    }
    sunleds.show();
    cometup();
   //Serial.print("night ");Serial.print(daybr);Serial.print("-");Serial.print(tm);Serial.print("\n");
   if (daybr > 50 && daybr < 75) {
       homeleds.setPixelColor(2,0,0,0);       homeleds.setPixelColor(3,0,0,0);
       homeleds.show();
    }
    if (daybr > 25 && daybr < 50) {
       homeleds.setPixelColor(6,0,0,0);       homeleds.setPixelColor(7,0,0,0);                              
       homeleds.show();
    }
    if (daybr > 0 && daybr < 25) {
       homeleds.setPixelColor(0,0,0,0);       homeleds.setPixelColor(1,0,0,0);
       homeleds.show();
    }
    if (daybr<255) {
    daybr++;
    }
  }
}
void cometup() {
    unsigned long cometMillis = tm;

    if (cometMillis - previousCometMillis >= COMETDELAY) {
       previousCometMillis = cometMillis;
       analogWrite(COMETPIN, isc);
       if (isc <= 32) {
        isc++;
        }
        else {
       
       if ( isc >= (255-strstpc)) {
         stpc=-strstpc;
       }  
       if ( isc <= 145) {
         stpc=strstpc;
       }  
       isc=isc+stpc;      
        }    
       Serial.print("comet-");Serial.print(stpc);Serial.print("-");Serial.print(isc);Serial.print("\n");
    }
}
void star1up() {
    unsigned long star1Millis = tm;
    if (star1Millis - previousStar1Millis >= STAR1DELAY) {
       previousStar1Millis = star1Millis;
       analogWrite(STAR1PIN, is);
       analogWrite(STAR3PIN, is);
       if (is <= 32) {
        is++;
        }
        else {
       
       if ( is >= (255-strstp)) {
         stp=-strstp;
       }  
       if ( is <= 145) {
         stp=strstp;
       }  
       is=is+stp;
        }
       Serial.print("star1-");Serial.print(stp);Serial.print("-");Serial.print(is);Serial.print("\n");
    }
}
void star2up() {
    unsigned long star2Millis = tm;
    if (star2Millis - previousStar2Millis >= STAR2DELAY) {
       previousStar2Millis = star2Millis;
       analogWrite(STAR2PIN, is2);
       if (is2 <= 32) {
        is2++;
        }
        else {
       if ( is2 >= (255-strstp2)) {
         stp2=-strstp2;
       }
       if ( is2 <= 127) {
         stp2=strstp2;
       }
       is2=is2+stp2;
        }
        Serial.print("star2-");Serial.print(stp2);Serial.print("-");Serial.print(is2);Serial.print("\n");
    }
}
void cometdown() {
    unsigned long cometDwnMillis = tm;
    if (cometDwnMillis - previousCometDwnMillis >= COMETDELAY) {
       previousCometDwnMillis = cometDwnMillis;
       if ( isc > 0) {
       isc=isc-5;
       if (isc < 0) {
        isc = 0;
        }
       analogWrite(COMETPIN, is);
       }
    }
}
void star1down() {
    unsigned long star1DwnMillis = tm;
    if (star1DwnMillis - previousStar1DwnMillis >= STAR1DELAY) {
       previousStar1DwnMillis = star1DwnMillis;
       if ( is > 0) {
       is=is-5;
       if (is < 0) {
        is = 0;
        }
       analogWrite(STAR1PIN, is);
       analogWrite(STAR3PIN, is);
       }
    }
}
void star2down() {
    unsigned long star2DwnMillis = tm;
    if (star2DwnMillis - previousStar2DwnMillis >= STAR2DELAY) {
       previousStar2DwnMillis = star2DwnMillis;
       if ( is2 > 0) {
       is2=is2-5;
       if (is2 < 0) {
        is2 = 0;
        }
       analogWrite(STAR2PIN, is2);
       }
    }
}
void skydown() {
    unsigned long skydownMillis = tm;
    if (skydownMillis - previousSkydownMillis >= SKYDELAY) {
      previousSkydownMillis = skydownMillis;
    for (int ip=0; ip<SUNN; ip++)
    {
    sunleds.setPixelColor(ip,0,0,40);
    sunleds.setBrightness(daybr);
    }
    sunleds.show();
    cometdown();
   //Serial.print("night ");Serial.print(daybr);Serial.print("-");Serial.print(tm);Serial.print("\n");
   if (daybr > 50 && daybr < 75) {
       homeleds.setPixelColor(2,255,100,0);
       homeleds.setPixelColor(3,255,100,0);
       homeleds.show();
    }
    if (daybr > 25 && daybr < 50) {
       homeleds.setPixelColor(0,255,100,0);
       homeleds.setPixelColor(1,255,100,0);
       homeleds.show();
    }
    if (daybr > 0 && daybr < 25) {
       homeleds.setPixelColor(6,255,100,0);
       homeleds.setPixelColor(7,255,100,0);
       homeleds.show();
    }
   if (daybr >0) {
    daybr--;
   }
  }
}
void fire() {
   unsigned long currentMillis = millis();
   int r = 255;
   int g = 100;
   int b = 0;
   if (currentMillis - previousMillis >= random(80,200)) {
   previousMillis = currentMillis;
   fireleds.setBrightness(random(5,45));
   for(int x=0; x<FIREN; x++)
      {
         int flicker = random(0,90); //aumentando aumenta il rosso, diminuendo fa più giallo
         int r1 = r;
         int g1 = g-flicker;
         int b1 =0;
         if(g1<0) {g1=0;}
         if(r1<0) {r1=0;};
         if(b1<0) {b1=0;};
         fireleds.setPixelColor(x,r1,g1, b1);
      }
   fireleds.show();
   }
}
void lamp() {
   unsigned long currentMillis = millis();
   int r = 255;
   int g = 100;
   int b = 0;
   if (currentMillis - previousLampMillis >= random(100,300)) {
   previousLampMillis = currentMillis;   lampleds.setBrightness(random(5,25));
   for(int x=0; x<LAMPN; x++)
      {
         int flicker = random(0,70); //aumentando aumenta il rosso, diminuendo fa più giallo
         int r1 = r;
         int g1 = g-flicker;
         int b1 =0;
         if(g1<0) {g1=0;}
         if(r1<0) {r1=0;};
         if(b1<0) {b1=0;};
         lampleds.setPixelColor(x,r1,g1,b1);
      }
   lampleds.show();
   }
}
void wat() {
   unsigned long currentMillis = millis();
   int r = 0;
   int g = 90;
   int b = 255;
   if (currentMillis - previousWatMillis >= random(100,300)) {
   previousWatMillis = currentMillis;
   watleds.setBrightness(random(5,25));
   for(int x=0; x<WATN; x++)
      {
         int flicker = random(0,90); //effetto blu celeste
         int r1 = r;
         int g1 = g+flicker;
         int b1 =b;      watleds.setPixelColor(x,r1,g1,b1);
      }
   watleds.show();
   }
}
void bgup(){
    unsigned long bgupMillis = tm;
    if (bgupMillis - previousbgupMillis >= BGDELAY) {
      previousbgupMillis = bgupMillis;
      for (int ip=0; ip<BACKN; ip++)
        {
           int r = 150;
           int g = 50;
           int b = 0;
           backleds.setPixelColor(ip,r,g,b);
           backleds.setBrightness(bgbr);
        }
    backleds.show();
    if (bgbr < 255) {
      bgbr++;
    }
}
void bgdown(){
    unsigned long bgdownMillis = tm;
    if (bgdownMillis - previousbgdownMillis >= BGDELAY) {
      previousbgdownMillis = bgdownMillis;
      for (int ip=0; ip<BACKN; ip++)
        {
           int r = 150;
           int g = 40;
           int b = 0;
           backleds.setPixelColor(ip,r,g,b);
           backleds.setBrightness(bgbr);
        }
    backleds.show();
    if (bgbr > 0) {
      bgbr--;
    }
}
void clearLEDs(){
  for (int i=0; i<FIREN; i++)
  {
    fireleds.setPixelColor(i, 0);
  }
  for (int i=0; i<SUNN; i++)
  {
    sunleds.setPixelColor(i, 0);
  }  
  for (int i=0; i<HOMEN; i++)
  {
    homeleds.setPixelColor(i, 0);
  } 
    for (int i=0; i<LAMPN; i++)
  {
    lampleds.setPixelColor(i, 0);
  }
  for (int i=0; i<WATN; i++)
  {
    watleds.setPixelColor(i, 0);
  }
  for (int i=0; i<BACKN; i++)
  {
    backleds.setPixelColor(i, 0);
  }
}
