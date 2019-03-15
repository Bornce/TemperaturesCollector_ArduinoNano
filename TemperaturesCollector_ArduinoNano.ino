/*
 * 芯片选择Arduino Nano,ATmage328P Old Bootloader  AVRISP mkll
 * 
 * 
*/

#include  "string.h"
#include <MsTimer2.h>
#include <stdio.h>
#include "Arduino.h"


#define LEDPIN  13



const  char  ServerCMD[]={"UPDATE THE DATA PLEASE"};

enum enumStruct_TypeOfNTC
{
  Res_2K_B3500K = 0,
  Res_5K_B3700K ,
  Res_10K_B3380K  ,
  Res_10K_B3900K  ,
  TotalType_Res,
};
//


struct  CUNTIAN_NTC_TABLE
{
  float temperature;
  float Res[TotalType_Res];
  /*
    _2K_B3500K;
  float Res_5K_B3700K;
  float Res_10K_B3380K;
  float Res_10K_B3900K;
  float Res_20K_B4050K;
  float Res_30K_B4100K;
  float Res_50K_B4150K;
  float Res_100K_B4250K;
  */
};
//

const  struct  CUNTIAN_NTC_TABLE NTC[]=
{
//temperature,Res_2K_B3500K,Res_5K_B3700K......
{-40, {44.657,  123.484,  195.652,  347.808}},
{-35, {33.505,  92.295,   148.171,  248.591}},
{-30, {25.388,  69.614,   113.347,  179.973}},
{-25, {19.402,  52.86,    87.559,   131.832 }},
{-20, {14.961,  40.48,    68.237,   97.679}},
{-15, {11.644,  31.275,   53.65,    73.119 }},
{-10, {9.133,   24.339,   42.506,   55.301}},
{-5,  {7.198,   19.154,   33.892,   42.257 }},
{0,   {5.716,   15.148,   27.219,   32.582 }},
{5,   {4.571,   11.964,   22.021,   25.324 }},
{10,  {3.682,   9.52,     17.926,   19.847 }},
{15,  {2.987,   7.624,    14.674,   15.679 }},
{20,  {2.437,   6.16,     12.081,   12.478}},
{25,  {2.0,     5.0,      10.0,     10.0   }},
{30,  {1.651,   4.082,    8.315,    8.068  }},
{35,  {1.371,   3.354,    6.948,    6.552   }},
{40,  {1.143,   2.773,    5.834,    5.353  }},
{45,  {0.958,   2.299,    4.917,    4.399  }},
{50,  {0.807,   1.914,    4.161,    3.635  }},
{55,  {0.683,   1.607,    3.535,    3.02  }},
{60,  {0.582,   1.356,    3.014,    2.521  }},
{65,  {0.497,   1.149,    2.586,    2.115  }},
{70,  {0.426,   0.978,    2.228,    1.783  }},
{75,  {0.367,   0.834,    1.925,    1.51  }},
{80,  {0.318,   0.714,    1.669,    1.284  }},
{85,  {0.276,   0.612,    1.452,    1.096  }},
{90,  {0.24,    0.527,    1.268,    0.939   }},
{95,  {0.21,    0.456,    1.11,     0.808   }},
{100, {0.183,   0.396,    0.974,    0.698   }},
{105, {0.161,   0.345,    0.858,    0.605  }},
{110, {0.142,   0.302,    0.758,    0.527  }},
{115, {0.125,   0.264,    0.671,    0.46  }},
{120, {0.111,   0.232,    0.596,    0.403 }},
{125, {0.099,   0.205,    0.531,    0.354}}
};
//



float GetTemperatureFromNTC(float res,unsigned  char  TypeOfRes)
{
  unsigned  char  ucl_i;

  if(TypeOfRes>TotalType_Res)
  {
    return  0xFFFF;
  }
  //

  
  for(ucl_i=0;ucl_i<sizeof(NTC)/sizeof(struct CUNTIAN_NTC_TABLE);ucl_i++)
  {
    if(res>=NTC[ucl_i].Res[TypeOfRes])
    {
      break;
    }
    //
  }
  //
  
  if(ucl_i==0)
    {
      return  -40.0;
    }
  //
  if(ucl_i==sizeof(NTC)/sizeof(struct CUNTIAN_NTC_TABLE))
    {
      return  125.0;
    }
  //


  return  ((res-NTC[ucl_i-1].Res[TypeOfRes])*(NTC[ucl_i].temperature-NTC[ucl_i-1].temperature)/(NTC[ucl_i].Res[TypeOfRes]-NTC[ucl_i-1].Res[TypeOfRes]))+NTC[ucl_i-1].temperature;
  
}
//


//int serial_putc( char c, struct __file * )
//{
//  Serial.write( c );
//  return c;
//}
//void printf_begin(void)
//{
//  fdevopen( &serial_putc, 0 );
//}
////

int lenOfUartRev  = 0;
float temperatureBuff[8]={0.0};

void UpdateADCs();



void onTimer() 
{
  digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
//

void  setup(void)
{
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);

  MsTimer2::set(200, onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时

  Serial.print("Reboot\r\n");
}
//

void  loop()// run over and over
{
 

  
  UpdateADCs();

{
  for(int channelIndex=0;channelIndex<8;channelIndex++)
  {
    temperatureBuff[channelIndex] = GetTemperatureFromNTC(temperatureBuff[channelIndex],Res_10K_B3900K);
    

  }
  //

}
//


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
      for(int channelIndex=0;channelIndex<8;channelIndex++)
      {
        Serial.print(temperatureBuff[channelIndex],3);
        Serial.print(",");
      }
      //
      Serial.print("\r\n");
       
    }
    //
    
    memset(UartGet,0,sizeof(UartGet));
    
  }
  //


  
  delay(300);
}
//




void  UpdateADCs()
{
  #define micro_SampleTimes   10
  
  int channelIndex=0;
  int times=0;
  int sampleBuf[8]= {0};
  
  memset(sampleBuf,0,sizeof(sampleBuf));
  
  for(times=0;times<micro_SampleTimes;times++)
  {    
    for(channelIndex=0;channelIndex<8;channelIndex++)
    {
      switch(channelIndex)
      {
        case  0:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A0);  break;
        case  1:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A1);  break;
        case  2:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A2);  break;
        case  3:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A3);  break;
        case  4:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A4);  break;
        case  5:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A5);  break;
        case  6:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A6);  break;
        case  7:sampleBuf[channelIndex]  = sampleBuf[channelIndex]+analogRead(A7);  break;
      }
      //
      
    }
    //每个通道采集一次
  }
  //每个通道采集10次
  
  for(channelIndex=0;channelIndex<8;channelIndex++)
  {
    temperatureBuff[channelIndex]  = (float)sampleBuf[channelIndex]/10.0;
    temperatureBuff[channelIndex] = 5.1*temperatureBuff[channelIndex]/(float)(0x3FF-temperatureBuff[channelIndex]);//获得电阻阻值，单位KOhm  
  }



}
//
