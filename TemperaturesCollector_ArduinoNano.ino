/*
 * 芯片选择Arduino Nano,ATmage328P Old Bootloader  AVRISP mkll
 * 
 * 
*/

#include  "string.h"
#include <stdio.h>

const  char  ServerCMD[]={"UPDATE THE DATA PLEASE"};


int lenOfUartRev  = 0;
float temperatureBuff[8]={0.0};

void  setup(void)
{
  Serial.begin(115200);
}
//

void  loop()// run over and over
{
  
  if(Serial.available())
  {
    int index = 0;
    char  UartGet[512]={0};
    
    //
    index = 0;
    lenOfUartRev  = 0;
    lenOfUartRev = Serial.available();


    while(lenOfUartRev--) 
    {
      UartGet[index] = Serial.read();
      index ++;
    }
    //
    
    
    if(memcmp(UartGet,ServerCMD,sizeof(ServerCMD)-1) == 0)
    {
      char loopi;

      for(loopi=0;loopi<8;loopi++)
      {
        Serial.print(temperatureBuff[loopi]);
        Serial.print(',');
      }
      //
	  Serial.println("");
    }
    //
    
    memset(UartGet,0,sizeof(UartGet));
    
  }
  //
  
  UpdateADCs();
  
  delay(100);
}
//

void  UpdateADCs()
{
  #define micro_SampleTimes   10
  
  int channelIndex=0;
  int times=0;
  int sampleBuf[8][micro_SampleTimes] = {0};
  
  
  
  for(times=0;times<micro_SampleTimes;times++)
  {
    channelIndex  = 0;
    
    for(channelIndex=0;channelIndex<8;channelIndex++)
    {
      switch(channelIndex)
      {
        case  0:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A0);  break;
        case  1:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A1);  break;
        case  2:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A2);  break;
        case  3:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A3);  break;
        case  4:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A4);  break;
        case  5:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A5);  break;
        case  6:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A6);  break;
        case  7:sampleBuf[channelIndex][times]  = sampleBuf[channelIndex][times]+analogRead(A7);  break;
      }
      //
    }
    //
    
  }
  //
  


  for(channelIndex=0;channelIndex<8;channelIndex++)
  {
    int temp  = 0;

    
    temperatureBuff[channelIndex]=  sampleBuf[channelIndex][micro_SampleTimes-1]/micro_SampleTimes;
    temp  = temperatureBuff[channelIndex];
    
    temperatureBuff[channelIndex] = 5.6*(float)(temperatureBuff[channelIndex])/(float)(0xFFFF-temp);//获得电阻阻值，单位KOhm
    //查表获取数据



    
    
  }
  //
  

  
  return  ;

}
//
