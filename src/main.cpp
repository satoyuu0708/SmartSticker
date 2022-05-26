// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For red6x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.



#include <RGBmatrixPanel.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <BLEDevice.h>
#include <BLE2902.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <image.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
/*#include <cstdint>
#include <FS.h>
#include <Wire.h>
#include <SPI.h>
#include <SPIFFS.h>*/


#define mw 32
#define mh 32
#define NUMMATRIX (mw*mh)//電光掲示板の面積
#define setBrightness(x) fillScreen(15) // no-op, no brightness on this board
#define clear()          fillScreen(0)
#define show()           swapBuffers(true)
#define Color(x,y,z)     Color444(x/16,y/16,z/16)
#define LED_BLACK           0
#define BLE_LOCAL_NAME "Smart Sticker"
// BLEのサービスUUID。適当なUUID(ランダムで生成したものがよい)を設定して下さい。
#define BLE_SERVICE_UUID "133fe8d4-5197-4675-9d76-d9bbf2450bb4"
// BLEのCharacteristic UUID。適当なUUID(ランダムで生成したものがよい)を設定して下さい。
#define BLE_CHARACTERISTIC_UUID "0fc10cb8-0518-40dd-b5c3-c4637815de40"

//RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

  

void numberText(char number1,char number2,int16_t tx,int16_t ty,int16_t txx, int16_t tyy){
   matrix.drawChar(tx, ty, number1, WHITE, BLACK,2);
   matrix.drawChar(txx, tyy, number2, WHITE, BLACK,2);

};

void drawHP(uint16_t color,int16_t ipx, int16_t ipy,int16_t ipw,int16_t iph){

   matrix.drawRect(hpx,hpy,hpw,hph,color);
   matrix.drawRect(ipx,ipy,ipw,iph,color);
   //delay(10000);
};

void rdrawHP(uint16_t color,int16_t ipx, int16_t ipy,int16_t ipw,int16_t iph){
   matrix.drawRect(hpx,hpy,hpw,hph,color);
   for (ipy = 15; ipy > 13; ipy--){
   
   matrix.drawRect(ipx,ipy,ipw,ipy,color);
   delay(10);
   }
   
   
   delay(10000);
};



void heart_newmark(){
  matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
  matrix.drawRGBBitmap(0, 0, heartmark[0],9, 6);
  matrix.drawRGBBitmap(0, 9, heartmark[0],9, 6);
  matrix.drawRGBBitmap(23, 0, heartmark[0],9, 6);
  matrix.drawRGBBitmap(23, 10, heartmark[0],9, 6);


}

void animation_newmark1(){
int i = 0;
  while (1)
 {
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    delay(1500);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    delay(1500);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    delay(1500);
    matrix.clear();
    i++;

     if(i>1){
      //matrix.clear();
      break;
  }

   
  }
};

void animation_newmark2(){
  int i = 0;
 while (1)
 {
    
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    delay(1500);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    delay(800);

    matrix.clear();
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    delay(800);

    matrix.clear();
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    matrix.drawRGBBitmap(0, 8, watermark[0],5, 5);
    delay(800);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    matrix.drawRGBBitmap(0, 8, watermark[0],5, 5);
    matrix.drawRGBBitmap(6, 11, watermark[0],5, 5);
    delay(800);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    matrix.drawRGBBitmap(0, 8, watermark[0],5, 5);
    matrix.drawRGBBitmap(6, 11, watermark[0],5, 5);
    matrix.drawRGBBitmap(22, 11, watermark[0],5, 5);
    delay(800);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, watermark[0],5, 5);
    matrix.drawRGBBitmap(24, 6, watermark[0],5, 5);
    matrix.drawRGBBitmap(0, 8, watermark[0],5, 5);
    matrix.drawRGBBitmap(6, 11, watermark[0],5, 5);
    matrix.drawRGBBitmap(22, 11, watermark[0],5, 5);
    matrix.drawRGBBitmap(27, 0, watermark[0],5, 5);
    delay(800);
    matrix.clear();
    i++;

    if(i>1){
      //matrix.clear();
      break;
  }

  }
  
};

void animation_newmark_happy(){
   int i = 0;
 while (1)
 {
   
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    delay(1500);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    delay(1000);

    matrix.clear();
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    matrix.drawRGBBitmap(24, 6, note2[0],5, 5);
    delay(1000);

    matrix.clear();
    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    matrix.drawRGBBitmap(24, 6, note2[0],5, 5);
    matrix.drawRGBBitmap(0, 8, note1[0],5, 5);
    delay(1000);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    matrix.drawRGBBitmap(24, 6, note2[0],5, 5);
    matrix.drawRGBBitmap(0, 8, note1[0],5, 5);
    matrix.drawRGBBitmap(6, 11, note2[0],5, 5);
    delay(1000);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    matrix.drawRGBBitmap(24, 6, note2[0],5, 5);
    matrix.drawRGBBitmap(0, 8, note1[0],5, 5);
    matrix.drawRGBBitmap(6, 11, note1[0],5, 5);
    matrix.drawRGBBitmap(22, 11, note2[0],5, 5);
    delay(1000);
    matrix.clear();

    matrix.drawRGBBitmap(9, 0, newmark_v1[0],14,16);//初心者マーク
    matrix.drawRGBBitmap(4, 0, note1[0],5, 5);
    matrix.drawRGBBitmap(24, 6, note2[0],5, 5);
    matrix.drawRGBBitmap(0, 8, note1[0],5, 5);
    matrix.drawRGBBitmap(6, 11, note1[0],5, 5);
    matrix.drawRGBBitmap(22, 11, note2[0],5, 5);
    matrix.drawRGBBitmap(27, 0, note1[0],5, 5);
    delay(1000);
    matrix.clear();
    i++;

     if(i>1){
      //matrix.clear();
      break;
  }

  }

  
 

};

void happy_baby(){
  matrix.drawRGBBitmap(0, 0, happy_babymark[0],16,15);
  matrix.drawRGBBitmap(16, 0, baby_hbottle_g[0],16,16);
  
};

void normal_baby(){
  matrix.drawRGBBitmap(0, 0, normal_babymark[0],16,15);
  matrix.drawRGBBitmap(16, 0, baby_bottle_o[0],16,16);
  
};

void cry_baby(){
  matrix.drawRGBBitmap(0, 0, cry_babymark[0],16,15);
  matrix.drawRGBBitmap(16, 0, baby_bottle_r[0],16,16);
  
};

void numberText(int16_t x, int16_t y, unsigned char c, uint8_t size){
  matrix.drawChar(x, y, c, WHITE, WHITE, size);
};



void Number_Human(int16_t x, int16_t y, unsigned char c, uint8_t size){//乗車人数の設定　y:y座標　c:乗車人数 size:文字の大きさ
  matrix.drawRGBBitmap(0, 0, human[0],15,32);
  matrix.drawRGBBitmap(16, 11, kakeru[0],7,7);
  numberText(x,y,c,size);
};
//Number_Human(22, 8, '2', 2);
//Number_Human(22, 8, '3', 2);
//Number_Human(22, 8, '4', 2);
//Number_Human(20, 4, '1', 3);

void step_break(int16_t x, int16_t y, int16_t w, int16_t h){
  matrix.writeFillRect(x,y,w,h,red);
};
/* delay(500);
     step_break(12,0,8,8);
  delay(500);
     step_break(8,8,16,8);
   delay(500);
     step_break(4,16,24,8);
   delay(500);
     step_break(0,24,32,8);
*/
 void Destination(){
   
 }
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("connect");
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      Serial.println("disconnect");
      deviceConnected = false;
    };
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic) {
    
    Serial.println("read");
    pCharacteristic->setValue("スマートステッカーと接続しました");
  };


  void onWrite(BLECharacteristic *pCharacteristic) {
    
    Serial.println("write");
    std::string value = pCharacteristic->getValue();
    int num = std::atoi(value.c_str());
  
    delay(60);

    if(num == 0){
      matrix.clear();
      happy_baby();
    }
    //Serial.println(value.c_str());
    else if(num == 1){
    
    matrix.clear();
    normal_baby();
    
      

    }

    else if(num == 2){
     matrix.clear(); 
     cry_baby();
     
     
    }
    
    else if(num == 3){
      //matrix.clear();
      //matrix.drawRGBBitmap(0, 0, oldermark1[0],mw, mh );//画像表示
      //drawHP(red,2,13,2,3);//限界
      //matrix.show();
    
      matrix.clear();
      matrix.drawRGBBitmap(0, 0, newmark[0],mw, mh );//画像表示
      


      
    }
    else if(num == 4){
     matrix.clear();
     animation_newmark1();
     

    }
    else if(num == 5){
     matrix.clear();
     animation_newmark2();

    }

    
    else if(num == 6){
    matrix.clear();
     animation_newmark_happy();
      

    }
    else if(num == 7){
       matrix.clear(); 
       matrix.drawRGBBitmap(0, 0, gdriver[0],mw, mh );//画像表示
       drawHP(matrix.Color333(0, 7, 0),2,0,2,16);//満タン
     
    }
    else if(num == 8){
     matrix.clear(); 
     matrix.drawRGBBitmap(0, 0, ydriver[0],mw, mh );//画像表示
     drawHP(orange,2,7,2,13);//半分
     
    }
    else if(num == 9){
      matrix.clear(); 
      matrix.drawRGBBitmap(0, 0, rdriver[0],mw, mh );//画像表示
      drawHP(red,2,13,2,15);//限界
      
    }
    else if(num == 10){
       matrix.clear();
    
    }
    else if(num == 11){
       matrix.clear();
       matrix.drawRGBBitmap(0, 0, oldermark1[0],mw, mh );//画像表示
    }
    else if(num == 12){
       /*matrix.clear();
     numberText('9','7',6,1,18,1);*/

     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','1',6,1,18,1);
    }
     else if(num == 13){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','2',6,1,18,1);
    }
    else if(num == 14){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','3',6,1,18,1);
      
    }
    else if(num == 16){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','4',6,1,18,1);
    }
    else if(num == 17){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','5',6,1,18,1);
    }
    else if(num == 18){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','6',6,1,18,1);
    }
    else if(num == 19){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','7',6,1,18,1);
    }
    else if(num == 20){
     matrix.clear();
     matrix.drawRGBBitmap(0, 0, human[0],mw, mh );//画像表示
     numberText('X','8',6,1,18,1);
    }
  }
};







/*void initBLEServise() {//ここが変
  BLEDevice::init(BLE_LOCAL_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         BLE_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY |
                                         BLECharacteristic::PROPERTY_INDICATE
                                        
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();  

}*/

//int ipy=0;
void setup() {
  matrix.begin();
  matrix.clear();
  Serial.begin(115200);
  Serial.print("call");
  Serial.print("test1");
  //initBLEServise();
  Serial.print("test2");
  //cry_baby();
 
}


void loop() {
 
}