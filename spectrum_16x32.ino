#include<MegunoLink.h>
#include<Filter.h>

#include "ESP32-RGBMatrixPanel-GRAB.h"
RGB64x32MatrixPanel_I2S_DMA matrix(32, 16);

#define NOISE 550 // 550
#define MIC_PIN 34





int lvl = 0; // tweak the min and max as needed
ExponentialFilter<long> ADCFilter(5,0);

void setup() {
  // put your setup code here, to run once:
  //
  //Serial.begin(115200);
  //pinMode(Red, OUTPUT);
  
  matrix.begin();
  matrix.fillScreen(0);
  matrix.setPanelBrightness(20);
    
//  ledcSetup(ledChannelR, freq, resolution);
//  ledcSetup(ledChannelG, freq, resolution);
//  ledcSetup(ledChannelB, freq, resolution);
//  
//  // attach the channel to the GPIO to be controlled
//  ledcAttachPin(Red, ledChannelR);ledcAttachPin(Green, ledChannelG);
//  ledcAttachPin(Blue, ledChannelB);

  for(int k =31; k>= 0 ;k--) {
      for(int h = 15; h >= 0 ;h--) {
        matrix.drawPixel(k,h,LED_RED_HIGH);
        
      }
    }
    delay(1000);
    matrix.fillScreen(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int n, heightx;
  n = analogRead(MIC_PIN);
  // remove the MX9614 bias of 1.25VDC
  n = abs(1023 - n); //1023
  // hard limit noise/hum
  n = (n <= NOISE) ? 0 : abs(n - NOISE);
  // apply the exponential filter to smooth the raw signal
  ADCFilter.Filter(n);
  lvl = ADCFilter.Current();
//  delay(10);
//  Serial.println(lvl);

  int ySpec = map(lvl,0,140,0,15);
//  int xSpec = map(lvl,0,30,0,31);
//    Serial.println(ySpec);

//   for(int k = 15; k >= 0 ;k--) {
//        if(k <= ySpec){
//          matrix.fillScreen(0);
//        }
//        else{
//          
//          matrix.drawPixel(0,k,LED_RED_HIGH);
//          matrix.drawPixel(1,k,LED_RED_HIGH);
//          matrix.drawPixel(2,k,LED_RED_HIGH);
//          matrix.drawPixel(3,k,LED_RED_HIGH);
//          matrix.drawPixel(4,k,LED_RED_HIGH);
//          matrix.drawPixel(5,k,LED_RED_HIGH);
//          matrix.drawPixel(6,k,LED_RED_HIGH);
//          matrix.drawPixel(7,k,LED_RED_HIGH);
//          matrix.drawPixel(8,k,LED_RED_HIGH);
//          matrix.drawPixel(9,k,LED_RED_HIGH);
//          matrix.drawPixel(10,k,LED_RED_HIGH);
//
//          matrix.drawPixel(11,k,LED_RED_HIGH);
//          matrix.drawPixel(12,k,LED_RED_HIGH);
//          matrix.drawPixel(13,k,LED_RED_HIGH);
//          matrix.drawPixel(14,k,LED_RED_HIGH);
//          matrix.drawPixel(15,k,LED_BLUE_HIGH);
//          matrix.drawPixel(16,k,LED_BLUE_HIGH);
//          matrix.drawPixel(17,k,LED_BLUE_HIGH);
//          matrix.drawPixel(18,k,LED_RED_HIGH);
//          matrix.drawPixel(19,k,LED_RED_HIGH);
//          matrix.drawPixel(20,k,LED_RED_HIGH);
//          matrix.drawPixel(21,k,LED_RED_HIGH);
//
//          matrix.drawPixel(22,k,LED_RED_HIGH);
//          matrix.drawPixel(23,k,LED_RED_HIGH);
//          matrix.drawPixel(24,k,LED_RED_HIGH);
//          matrix.drawPixel(25,k,LED_RED_HIGH);
//          matrix.drawPixel(26,k,LED_RED_HIGH);
//          matrix.drawPixel(27,k,LED_RED_HIGH);
//          matrix.drawPixel(28,k,LED_RED_HIGH);
//          matrix.drawPixel(29,k,LED_RED_HIGH);
//          matrix.drawPixel(30,k,LED_RED_HIGH);
//          matrix.drawPixel(31,k,LED_RED_HIGH);
//          
//          
//        }
//        
//      } 
//  delay(5);
  
  
// *************** LED MATRIX *******************

        int led31 = random(ySpec);
        lightcolumns(31, ySpec+ led31);
        lightcolumns(30, ySpec+ led31);
        lightcolumns(29, 0);

        int led28 = random(ySpec);
        lightcolumns(28, ySpec+ led28);
        lightcolumns(27, ySpec+ led28);
        lightcolumns(26, 0);


        int led25 = random(ySpec);
        lightcolumns(25, ySpec + led25);
        lightcolumns(24, ySpec+ led25);
        lightcolumns(23, 0);

        int led22 = random(ySpec);
        lightcolumns(22, ySpec+ led22);
        lightcolumns(21, ySpec+ led22);
        lightcolumns(20, 0);

        int led19 = random(ySpec);
        lightcolumns(19, ySpec+ led19);
        lightcolumns(18, ySpec+ led19);
        lightcolumns(17, 0);

        int led16 = random(ySpec);
        lightcolumns(16, ySpec+ led16);
        lightcolumns(15, ySpec+ led16);
        lightcolumns(14, 0);

        int led13 = random(ySpec);
        lightcolumns(13, ySpec+ led13);
        lightcolumns(12, ySpec+ led13);
        lightcolumns(11, 0);

        int led10 = random(ySpec);
        lightcolumns(10, ySpec+ led10);
        lightcolumns(9, ySpec+ led10);
        lightcolumns(8, 0);

        int led7 = random(ySpec);
        lightcolumns(7, ySpec+ led7);
        lightcolumns(6, ySpec+ led7);
        lightcolumns(5, 0);

        int led4 = random(ySpec);
        lightcolumns(4, ySpec+ led4);
        lightcolumns(3, ySpec+ led4);
        lightcolumns(2, 0);

        int led1 = random(ySpec);
        lightcolumns(1, ySpec+ led1);
        lightcolumns(0, ySpec+ led1);
      //delay(10);
}

void lightcolumns(int rownum, int amplitude)
{
  if(amplitude >=12)  // <-O-> set the threshold for the band to turn red
  {
      for( int y = 0; y < 2; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 7));     // red-green
      }
      for( int y = 2; y <= 12; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 5, 0));     // red-green
      }
      
      
      for(int y = amplitude; y <16; y++)
      {
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 0));  
      }
      //matrix.drawPixel(rownum, amplitude+2, matrix.Color333(7, 7, 7));
  }
  
  else if(amplitude>9 && amplitude < 12 ) // <-O-> set the threshold for the band to turn yellow
  {
      for( int y = 0; y < 2; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 7));     // red-green
      }
      for( int y = 2; y < amplitude; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 5, 0));     // red-green
      }
      
      for(int y = amplitude; y < 16; y++)
      {
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 0));  
      }
      //matrix.drawPixel(rownum, amplitude+2, matrix.Color333(7, 7, 7));
  }
  
  else if(amplitude>2 && amplitude < 9) // <-O-> set the threshold for the band to turn green
  {
      for( int y = 0; y < 2; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 7));     // red-green
      }
      for( int y = 2; y < amplitude; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 5, 0));
      }
      for(int y = amplitude; y < 16; y++)
      {
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 0));  
      }
      //matrix.drawPixel(rownum, amplitude+2, matrix.Color333(7, 7, 7));
  } 
  
  else if(amplitude != 0)
  {
      for( int y = 0; y < 2; y++){
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 7));     // red-green
      }
      for(int y = amplitude; y < 16; y++)
      {
        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 0));  
      }
  } 

  if(amplitude >0 & amplitude < 16){
    matrix.drawPixel(rownum, amplitude+2, matrix.Color333(7, 7, 7));
//    for(int y = amplitude; y < 16; y++)
//      {
//        matrix.drawPixel(rownum, y, matrix.Color333(0, 0, 0));  
//      }
    delay(2);
  }
  
  
}
