#include <RGBmatrixPanel.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>


#define CLK  15
#define OE   13
#define LAT  19
#define A   12
#define B   16
#define C   17
#define D   18
#define mw 32
#define mh 32
#define NUMMATRIX (mw*mh)//電光掲示板の面積
#define setBrightness(x) fillScreen(15) // no-op, no brightness on this board
//#define clear()          fillScreen(0)
#define show()           swapBuffers(true)
#define Color(x,y,z)     Color444(x/16,y/16,z/16)
#define LED_BLACK           0
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

  int16_t  hpx = 1;
  int16_t  hpy = 0;
  int16_t  hpw = 4;
  int16_t  hph = 16;
  uint16_t WHITE = 0xffffff;
  uint16_t BLACK = 0x000000;
  uint16_t red = 0xfff000;//限界
  uint16_t green = matrix.Color333(0, 7, 0);//満タン
  uint16_t yellow = 0xffff00;//半分*/
  uint16_t blue = 0x0000ff;
  uint16_t orange = 0xffa00;
  uint16_t rightgreen =matrix.Color333(3, 3, 0);//満タン
  int16_t tx = 0;
  int16_t ty = 0;
static const uint16_t PROGMEM
 ddriver[16][32]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0 ,0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, WHITE, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE,WHITE , 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
 };

 static const uint16_t PROGMEM
 bdriver[16][32]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, blue, blue, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0 ,0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, blue, blue, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, blue, blue, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, 0, 0, 0, 0, 0, WHITE, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, blue, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue,blue , 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, blue, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, blue, blue, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
 };

static const uint16_t PROGMEM
 rdriver[16][32]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, red, red, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0 ,0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, red, red, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, red, red, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, 0, 0, 0, 0, 0, WHITE, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, red, red, red, red, red, red, red, red, red, red, red, red, red, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, red, red, red, red, red, red, red, red, red, red, red, red, red, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, red, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red,red , 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, red, red, red, red, red, red, red, red, red, red, red, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, red, red, red, red, red, red, red, red, red, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, red, red, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
 };

 static const uint16_t PROGMEM
 ydriver[16][32]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0 ,0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, 0, 0, 0, 0, 0, WHITE, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow,yellow , 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, yellow, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, yellow, yellow, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
 };

 static const uint16_t PROGMEM
 gdriver[16][32]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, green, green, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0 ,0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, green, green, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, green, green, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, 0, 0, 0, 0, 0, WHITE, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, green, green, green, green, green, green, green, green, green, green, green, green, green, 0, 0, 0, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, green, green, green, green, green, green, green, green, green, green, green, green, green, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, green, 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green,green , 0, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, green, green, green, green, green, green, green, green, green, green, green, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, green, green, green, green, green, green, green, green, green, 0, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, green, green, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0},
 };


static const uint16_t PROGMEM
  newmark[16][32]={
 	  {0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,WHITE,0,0,0,0,0,0,0,0,WHITE,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,WHITE,0,0,0,0,0,0,WHITE,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,WHITE,0,0,0,0,WHITE,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,WHITE,0,0,WHITE,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };

  static const uint16_t PROGMEM
  newmark1[16][32]={
 	  {0,0,0,0,0,0,blue,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,blue,blue,blue,0,WHITE,yellow,WHITE,0,0,0,0,0,0,0,0,WHITE,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,blue,blue,blue,blue,blue,WHITE,yellow,yellow,WHITE,0,0,0,0,0,0,WHITE,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,blue,blue,blue,blue,blue,WHITE,yellow,yellow,yellow,WHITE,0,0,0,0,WHITE,green,green,green,WHITE,0,0,blue,0,0,0,0,0,0},
    {0,0,0,0,0,blue,blue,blue,0,WHITE,yellow,yellow,yellow,yellow,WHITE,0,0,WHITE,green,green,green,green,WHITE,0,blue,blue,blue,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,green,green,green,green,green,WHITE,blue,blue,blue,blue,blue,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,blue,blue,blue,blue,blue,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,blue,blue,blue,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,green,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,green,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };

  static const uint16_t PROGMEM
  newmark2[16][32]={
 	  {0,0,0,0,0,0,blue,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,blue,blue,blue,0,WHITE,yellow,WHITE,0,0,0,0,0,0,0,0,WHITE,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,blue,blue,blue,blue,blue,WHITE,yellow,yellow,WHITE,0,0,0,0,0,0,WHITE,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,blue,blue,blue,blue,blue,WHITE,yellow,yellow,yellow,WHITE,0,0,0,0,WHITE,green,green,green,WHITE,0,0,blue,0,0,0,0,0,0},
    {0,0,0,0,0,blue,blue,blue,0,WHITE,yellow,yellow,yellow,yellow,WHITE,0,0,WHITE,green,green,green,green,WHITE,0,blue,blue,blue,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,green,green,green,green,green,WHITE,blue,blue,blue,blue,blue,0,0,0,0},
    {0,0,blue,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,blue,blue,blue,blue,blue,0,0,0,0},
    {0,blue,blue,blue,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,blue,blue,blue,0,0,0,0,0},
    {blue,blue,blue,blue,blue,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {blue,blue,blue,blue,blue,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
    {0,blue,blue,blue,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,blue,0,0,WHITE,yellow,yellow,yellow,yellow,green,green,green,green,WHITE,0,0,0,0,blue,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,blue,blue,blue,0,0,WHITE,yellow,yellow,yellow,green,green,green,WHITE,0,0,0,0,blue,blue,blue,0,0,0,0,0},
    {0,0,0,0,0,0,blue,blue,blue,blue,blue,0,0,WHITE,yellow,yellow,green,green,WHITE,0,0,0,0,blue,blue,blue,blue,blue,0,0,0,0},
    {0,0,0,0,0,0,blue,blue,blue,blue,blue,0,0,0,WHITE,yellow,green,WHITE,0,0,0,0,0,blue,blue,blue,blue,blue,0,0,0,0},
    {0,0,0,0,0,0,0,blue,blue,blue,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,blue,blue,blue,0,0,0,0,0},
  };

  static const uint16_t PROGMEM
   oldermark1[16][32]{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,WHITE,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,WHITE,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,WHITE,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,WHITE,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,WHITE,orange,orange,WHITE,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,WHITE,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,WHITE,orange,orange,orange,orange,WHITE,rightgreen,rightgreen,rightgreen,rightgreen,rightgreen,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,WHITE,orange,orange,orange,orange,WHITE,WHITE,rightgreen,rightgreen,rightgreen,WHITE,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,WHITE,orange,orange,orange,orange,orange,WHITE,WHITE,WHITE,green,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,WHITE,orange,orange,orange,orange,orange,orange,WHITE,WHITE,WHITE,green,green,green,green,green,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,WHITE,orange,orange,orange,WHITE,yellow,yellow,yellow,WHITE,WHITE,green,green,green,green,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,yellow,yellow,yellow,yellow,yellow,WHITE,green,green,green,WHITE,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,WHITE,green,green,WHITE,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,WHITE,yellow,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,yellow,yellow,yellow,yellow,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

   };
  
  
  static const uint16_t PROGMEM
   happy_babymark[15][16]{
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,WHITE,0,0,0,0},
{0,0,0,WHITE,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0,0},
{0,WHITE,0,0,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0},
{WHITE,0,0,0,0,0,0,WHITE,0,0,0,0,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{0,WHITE,red,red,0,0,0,0,0,0,0,0,red,red,WHITE,0},
{0,0,WHITE,0,0,WHITE,0,0,0,0,WHITE,0,0,WHITE,0,0},
{0,0,WHITE,0,0,0,WHITE,0,0,WHITE,0,0,0,WHITE,0,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,WHITE,0,0},
{0,0,0,WHITE,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0},
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
   };



static const uint16_t PROGMEM
   normal_babymark[15][16]{
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,WHITE,0,0,0,0},
{0,0,0,WHITE,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0,0},
{0,WHITE,0,0,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0},
{WHITE,0,0,0,0,0,0,WHITE,0,0,0,0,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{0,WHITE,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,0},
{0,0,WHITE,0,0,0,0,0,0,0,0,0,0,WHITE,0,0},
{0,0,WHITE,0,0,0,WHITE,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0},
{0,0,0,WHITE,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,WHITE,0,0},
{0,0,0,WHITE,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0},
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
   };


static const uint16_t PROGMEM
   cry_babymark[15][16]{
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,WHITE,0,0,0,0},
{0,0,0,WHITE,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0,0},
{0,WHITE,0,0,0,0,WHITE,0,WHITE,0,0,0,0,0,WHITE,0},
{WHITE,0,0,0,0,0,0,WHITE,0,0,0,0,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{WHITE,0,0,0,WHITE,WHITE,0,0,0,0,WHITE,WHITE,0,0,0,WHITE},
{0,WHITE,0,0,blue,0,0,WHITE,WHITE,0,0,blue,0,0,WHITE,0},
{0,0,WHITE,0,blue,0,WHITE,WHITE,WHITE,WHITE,0,blue,0,WHITE,0,0},
{0,0,WHITE,0,0,WHITE,WHITE,0,0,WHITE,WHITE,0,0,WHITE,0,0},
{0,0,0,WHITE,0,0,0,0,0,0,0,0,WHITE,0,0,0},
{0,0,WHITE,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,WHITE,0,0},
{0,0,0,WHITE,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0},
{0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
   };

static const uint16_t PROGMEM
   baby_bottle[16][16]{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,0,WHITE,0,0,0,0,WHITE,WHITE,0,0,0},
{WHITE,WHITE,0,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,0,0,WHITE,0,0,0,0,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };



static const uint16_t PROGMEM
   baby_hbottle_g[16][16]{
{red,red,0,red,red,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{red,red,red,red,red,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{0,red,red,red,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,red,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,green,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,green,green,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,green,green,WHITE,green,green,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,green,green,green,WHITE,green,green,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,green,green,WHITE,green,green,green,green,green,green,WHITE,0,0,0},
{0,WHITE,WHITE,green,green,green,WHITE,green,green,green,green,WHITE,WHITE,0,0,0},
{WHITE,WHITE,green,WHITE,green,green,green,green,green,green,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,green,green,WHITE,green,green,green,green,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,green,green,green,green,green,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,green,green,green,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };

static const uint16_t PROGMEM
   baby_hbottle_o[16][16]{
{red,red,0,red,red,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{red,red,red,red,red,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{0,red,red,red,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,red,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,orange,orange,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,WHITE,WHITE,orange,orange,orange,WHITE,0,0,0,0,WHITE,WHITE,0,0,0},
{WHITE,WHITE,orange,WHITE,orange,orange,orange,orange,0,0,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,orange,orange,WHITE,orange,orange,orange,orange,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,orange,orange,orange,orange,orange,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,orange,orange,orange,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };

static const uint16_t PROGMEM
   baby_bottle_o[16][16]{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{0,0,0,0,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,orange,orange,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,WHITE,WHITE,orange,orange,orange,WHITE,0,0,0,0,WHITE,WHITE,0,0,0},
{WHITE,WHITE,orange,WHITE,orange,orange,orange,orange,0,0,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,orange,orange,WHITE,orange,orange,orange,orange,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,orange,orange,orange,orange,orange,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,orange,orange,orange,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };

static const uint16_t PROGMEM
   baby_bottle_r[16][16]{
{0,0,blue,0,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{0,blue,blue,blue,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{blue,blue,blue,blue,blue,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{blue,blue,blue,blue,blue,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,blue,blue,blue,WHITE,WHITE,WHITE,0,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,0,WHITE,0,0,0,0,WHITE,WHITE,0,0,0},
{WHITE,WHITE,red,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,red,red,WHITE,0,0,0,0,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,red,red,red,0,0,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,red,red,red,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };


static const uint16_t PROGMEM
   baby_hbottle[16][16]{
{red,red,0,red,red,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
{red,red,red,red,red,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
{0,red,red,red,0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,red,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,0,0,WHITE,WHITE,WHITE,0},
{0,0,0,0,WHITE,WHITE,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,WHITE,0},
{0,0,0,WHITE,WHITE,0,0,WHITE,0,0,WHITE,WHITE,0,WHITE,WHITE,0},
{0,0,WHITE,WHITE,WHITE,0,0,0,WHITE,0,0,WHITE,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,WHITE,0,0,0,0,0,0,WHITE,0,0,0},
{0,WHITE,WHITE,0,0,0,WHITE,0,0,0,0,WHITE,WHITE,0,0,0},
{WHITE,WHITE,0,WHITE,0,0,0,0,0,0,WHITE,WHITE,0,0,0,0},
{WHITE,WHITE,0,0,WHITE,0,0,0,0,WHITE,WHITE,WHITE,0,0,0,0},
{0,WHITE,WHITE,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0},
{0,0,WHITE,WHITE,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0},
{0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0,0,0,0},
{0,0,0,0,WHITE,WHITE,0,0,0,0,0,0,0,0,0,0},
   };



static const uint16_t PROGMEM
  newmark_v1[16][14]={
 	  {WHITE,WHITE,0,0,0,0,0,0,0,0,0,0,WHITE,WHITE},
    {WHITE,yellow,WHITE,0,0,0,0,0,0,0,0,WHITE,green,WHITE},
    {WHITE,yellow,yellow,WHITE,0,0,0,0,0,0,WHITE,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,WHITE,0,0,0,0,WHITE,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,WHITE,0,0,WHITE,green,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,yellow,WHITE,WHITE,green,green,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE},
    {WHITE,yellow,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,green,WHITE},
    {0,WHITE,yellow,yellow,yellow,yellow,yellow,green,green,green,green,green,WHITE,0},
    {0,0,WHITE,yellow,yellow,yellow,yellow,green,green,green,green,WHITE,0,0},
    {0,0,0,WHITE,yellow,yellow,yellow,green,green,green,WHITE,0,0,0},
    {0,0,0,0,WHITE,yellow,yellow,green,green,WHITE,0,0,0,0},
    {0,0,0,0,0,WHITE,yellow,green,WHITE,0,0,0,0,0},
    {0,0,0,0,0,0,WHITE,WHITE,0,0,0,0,0,0},
  };


static const uint16_t PROGMEM
  watermark[5][5]{
    {0,0,blue,0,0},
    {0,blue,blue,blue,0},
    {blue,blue,blue,blue,blue},
    {blue,blue,blue,blue,blue},
    {0,blue,blue,blue,0},
  };

static const uint16_t PROGMEM
  note1[5][5]{
    {0,0,red,red,0},
    {0,0,red,0,red},
    {0,0,red,0,red},
    {red,red,red,0,0},
    {red,red,red,0,0},
  };

static const uint16_t PROGMEM
  note2[5][5]{
    {0,red,red,red,red},
    {0,red,0,0,red},
    {0,red,0,0,red},
    {red,red,0,red,red},
    {red,red,0,red,red},
  };

static const uint16_t PROGMEM
  heartmark[6][9]{
    {0,0,red,0,0,0,0,red,0},
    {0,red,red,red,0,0,red,red,red},
    {0,red,red,red,red,red,red,red,red,},
    {0,0,red,red,red,red,red,red,0,},
    {0,0,0,red,red,red,red,0,0},
    {0,0,0,0,red,red,0,0,0},
  };

static const uint16_t PROGMEM
  heartmark_s[4][5]{
    {red,red,0,red,red},
    {red,red,red,red,red},
    {0,red,red,red,0},
    {0,0,red,0,0},
   
  };

static const uint16_t PROGMEM
   kakeru[7][7]{
      {WHITE,0,0,0,0,0,WHITE},
      {0,WHITE,0,0,0,WHITE,0},
      {0,0,WHITE,0,WHITE,0,0},
      {0,0,0,WHITE,0,0,0},
      {0,0,WHITE,0,WHITE,0,0},
      {0,WHITE,0,0,0,WHITE,0},
      {WHITE,0,0,0,0,0,WHITE},
   };


static const uint16_t PROGMEM
   human[32][15]{
      {0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0,0},
      {0,0,0,0,0,0,WHITE,WHITE,WHITE,0,0,0,0,0,0},
      {0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0},
      {0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0},
      {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE},
      {0,WHITE,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,WHITE,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},
      {0,0,0,0,WHITE,WHITE,WHITE,0,WHITE,WHITE,WHITE,0,0,0,0},


   };


static const uint16_t PROGMEM
   Sapporo[26][12]{
      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1},
      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1},
      {0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1},
      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
      {0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,1,1,1,1,1,1},
      {0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,0,0,0,1},
      {0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0},
      {0,1,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1},
      {0,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,1,1,0,0},
      {0,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,0,1,1,0,0},
      {0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,1,0,0,1,1,0,1},
      {0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1},

   };



 