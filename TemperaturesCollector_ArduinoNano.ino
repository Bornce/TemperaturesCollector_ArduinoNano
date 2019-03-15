/*
 * 芯片选择Arduino Nano,ATmage328P Old Bootloader  AVRISP mkll
 * 
 * 
*/

#include  "string.h"
#include <MsTimer2.h>
#include <stdio.h>



#define LEDPIN  13



const  char  ServerCMD[]={"UPDATE THE DATA PLEASE"};

enum enumStruct_TypeOfNTC
{
  Res_2K_B3500K = 0,
  Res_5K_B3700K ,
  Res_10K_B3380K  ,
  Res_10K_B3900K  ,
  Res_20K_B4050K  ,
  Res_30K_B4100K  ,
  Res_50K_B4150K  ,
  Res_100K_B4250K ,
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
{-40, {44.657,  123.484,  195.652,  347.808,  733.007,  1149.5,   1948.575, 4256.752}},
{-35, {33.505,  92.295,   148.171,  248.591,  524.831,  819.651,  1387.289, 3005.888}},
{-30, {25.388,  69.614,   113.347,  179.973,  380.184,  591.391,  999.456,  2148.514}},
{-25, {19.402,  52.86,    87.559,   131.832,  277.845,  430.529,  728.895,  1555.02 }},
{-20, {14.961,  40.48,    68.237,   97.679,   205.26,   316.87,   537.039,  1137.312}},
{-15, {11.644,  31.275,   53.65,    73.119,   153.642,  236.337,  399.167,  839.314 }},
{-10, {9.133,   24.339,   42.506,   55.301,   116.016,  177.842,  299.469,  625.338 }},
{-5,  {7.198,   19.154,   33.892,   42.257,   88.125,   134.63,   226.186,  469.127 }},
{0,   {5.716,   15.148,   27.219,   32.582,   67.522,   102.816,  172.393,  355.224 }},
{5,   {4.571,   11.964,   22.021,   25.324,   52.168,   79.183,   132.857,  272.045 }},
{10,  {3.682,   9.52,     17.926,   19.847,   40.617,   61.46,    103.089,  209.803 }},
{15,  {2.987,   7.624,    14.674,   15.679,   31.847,   48.045,   80.43,    162.713 }},
{20,  {2.437,   6.16,     12.081,   12.478,   25.151,   37.834,   63.201,   127.117 }},
{25,  {2.0,     5.0,      10.0,     10.0,     20.0,     30.0,     50.0,     100.0   }},
{30,  {1.651,   4.082,    8.315,    8.068,    16.014,   23.955,   39.825,   79.215  }},
{35,  {1.371,   3.354,    6.948,    6.552,    12.902,   19.249,   31.918,   63.15   }},
{40,  {1.143,   2.773,    5.834,    5.353,    10.457,   15.56,    25.733,   50.649  }},
{45,  {0.958,   2.299,    4.917,    4.399,    8.527,    12.657,   20.877,   40.885  }},
{50,  {0.807,   1.914,    4.161,    3.635,    6.993,    10.354,   17.034,   33.195  }},
{55,  {0.683,   1.607,    3.535,    3.02,     5.771,    8.525,    13.929,   27.014  }},
{60,  {0.582,   1.356,    3.014,    2.521,    4.789,    7.058,    11.439,   22.079  }},
{65,  {0.497,   1.149,    2.586,    2.115,    3.992,    5.869,    9.485,    18.226  }},
{70,  {0.426,   0.978,    2.228,    1.783,    3.343,    4.905,    7.906,    15.124  }},
{75,  {0.367,   0.834,    1.925,    1.51,     2.809,    4.113,    6.614,    2.598   }},
{80,  {0.318,   0.714,    1.669,    1.284,    2.371,    3.463,    5.558,    10.542  }},
{85,  {0.276,   0.612,    1.452,    1.096,    2.02,     2.945,    4.686,    8.852   }},
{90,  {0.24,    0.527,    1.268,    0.939,    1.729,    2.516,    3.967,    7.463   }},
{95,  {0.21,    0.456,    1.11,     0.808,    1.476,    2.143,    3.373,    6.321   }},
{100, {0.183,   0.396,    0.974,    0.698,    1.264,    1.832,    2.878,    5.374   }},
{105, {0.161,   0.345,    0.858,    0.605,    1.085,    1.571,    2.465,    4.585   }},
{110, {0.142,   0.302,    0.758,    0.527,    0.935,    1.35,     2.118,    3.925   }},
{115, {0.125,   0.264,    0.671,    0.46,     0.812,    1.171,    1.828,    3.376   }},
{120, {0.111,   0.232,    0.596,    0.403,    0.708,    1.019,    1.583,    2.913   }},
{125, {0.099,   0.205,    0.531,    0.354,    0.617,    0.886,    1.374,    2.52    }}
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

int lenOfUartRev  = 0;
float temperatureBuff[8]={0.0};

void UpdateADCs();
void UpdateADC();



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
      char SendBuf[100]={0};
      char loopi;

    Serial.print(UartGet);
      
        sprintf(SendBuf,"%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",\
        temperatureBuff[0],temperatureBuff[1],temperatureBuff[2],temperatureBuff[3],\
        temperatureBuff[4],temperatureBuff[5],temperatureBuff[6],temperatureBuff[7]);
        #if false
      for(loopi=0;loopi<8;loopi++)
      {

        

      }
      //
      #endif
        Serial.print(SendBuf[0]);
        Serial.print(',');      
	  Serial.println("");
    }
    //
    
    memset(UartGet,0,sizeof(UartGet));
    
  }
  //
  
  UpdateADCs();
  
  delay(1000);
}
//

void UpdateADC()
{
        int sensorValueA0 = analogRead(A0);
        int sensorValueA1 = analogRead(A1);
        int sensorValueA2 = analogRead(A2);
        int sensorValueA3 = analogRead(A3);
        int sensorValueA4 = analogRead(A4);
        int sensorValueA5 = analogRead(A5);
        int sensorValueA6 = analogRead(A6);
        int sensorValueA7 = analogRead(A7);  


        Serial.print(sensorValueA0);
        Serial.print(',');
        Serial.print(sensorValueA1);
        Serial.print(',');
                        Serial.print(sensorValueA2);
        Serial.print(',');
                Serial.print(sensorValueA3);
        Serial.print(',');
                Serial.print(sensorValueA4);
        Serial.print(',');
                Serial.print(sensorValueA5);
        Serial.print(',');
                Serial.print(sensorValueA6);
        Serial.print(',');
                Serial.println(sensorValueA7);
        
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
    
    temperatureBuff[channelIndex] = 5.1*(float)(temperatureBuff[channelIndex])/(float)(0x3FF-temp);//获得电阻阻值，单位KOhm
    //查表获取数据

    temperatureBuff[channelIndex] = GetTemperatureFromNTC(temperatureBuff[channelIndex],Res_10K_B3900K);
Serial.print(temperatureBuff[channelIndex]);Serial.print(',');
  }
  //
  

  
  return  ;

}
//
