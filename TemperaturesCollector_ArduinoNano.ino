/*
 * 芯片选择Arduino Nano,ATmage328P Old Bootloader  AVRISP mkll
 * A0通道必须放在相变材料上
 * 
*/
/***********************************************************************
 * include 区域
************************************************************************/
#include  "string.h"
#include <MsTimer2.h>
#include <stdio.h>
#include "Arduino.h"



/***********************************************************************
 * include 区域
************************************************************************/
#define LEDPIN  13
#define	P_CTRL_PIN	2
#define	N_CTRL_PIN	3
#define	SET_MAX_TEMPERATURE_IN_BOX	1
#define	SET_MIN_TEMPERATURE_IN_BOX	-1
#define	PULL_MAGNIC_HANDSPIKE()		digitalWrite(P_CTRL_PIN, HIGH);digitalWrite(N_CTRL_PIN, LOW);
#define	PULL_MAGNIC_HANDSPIKE()		digitalWrite(P_CTRL_PIN, LOW);digitalWrite(N_CTRL_PIN, HIGH);
#define	DEFAULT_MAGNIC_HANDSPIKE()	digitalWrite(P_CTRL_PIN, LOW);digitalWrite(N_CTRL_PIN, LOW);

/***********************************************************************
 * 自定义数据类型 区域
************************************************************************/
enum enumStruct_TypeOfNTC
{
//  Res_2K_B3500K = 0,
//  Res_5K_B3700K ,
//  Res_10K_B3380K  ,
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

/***********************************************************************
 * 常量声明 区域
************************************************************************/
const  char  ServerCMD[]={"UPDATE THE DATA PLEASE"};

const  struct  CUNTIAN_NTC_TABLE NTC[]=
{
//temperature,Res_2K_B3500K,Res_5K_B3700K......
{-40, {  347.808}},
{-35, {  248.591}},
{-30, {  179.973}},
{-25, {  131.832 }},
{-20, {  97.679}},
{-15, {  73.119 }},
{-10, {  55.301}},
{-5,  {  42.257 }},
{0,   {  32.582 }},
{5,   {  25.324 }},
{10,  {  19.847 }},
{15,  {  15.679 }},
{20,  {  12.478}},
{25,  {  10.0   }},
{30,  {  8.068  }},
{35,  {  6.552   }},
{40,  {  5.353  }},
{45,  {  4.399  }},
{50,  {  3.635  }},
{55,  {  3.02  }},
{60,  {  2.521  }},
{65,  {  2.115  }},
{70,  {  1.783  }},
{75,  {  1.51  }},
{80,  {  1.284  }},
{85,  {  1.096  }},
{90,  {  0.939   }},
{95,  {  0.808   }},
{100, {  0.698   }},
{105, {  0.605  }},
{110, {  0.527  }},
{115, {  0.46  }},
{120, {  0.403 }},
{125, {  0.354}}
};
//

/***********************************************************************
 * global parameters 区域
************************************************************************/
int lenOfUartRev  = 0;
float temperatureBuff[8]={0.0};


/***********************************************************************
 * function blocks 区域
************************************************************************/

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



static int partition(float* sortArray, int low, int height)
{
  float key = sortArray[low];//

  while (low < height)
  {
    while (low < height && sortArray[height] >= key)
      height--;// 
    sortArray[low] = sortArray[height];// 
    while (low < height && sortArray[low] <= key)
      low++;// 
    sortArray[height] = sortArray[low];//
  }
  sortArray[low] = key;// 

  return low;
}
//




void quicksort(float* sortArray, int low, int height)
{
  if (low < height)
  {
    int result = partition(sortArray, low, height);

    quicksort(sortArray, low, result - 1);
    quicksort(sortArray, result + 1, height);
  }
  //
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


void magnicAction(char CMD)
{
	switch(CMD)
	{
		case	0:
		PULL_MAGNIC_HANDSPIKE();
		break;
		
		case	1:
		PUSH_MAGNIC_HANDSPIKE();
		break;
		
		default:
		DEFAULT_MAGNIC_HANDSPIKE();
		break;
	}
	//
}
//

void onTimer() 
{
  digitalWrite(LEDPIN, !digitalRead(LEDPIN));
}
//



void  setup(void)
{
	
	pinMode(P_CTRL_PIN,OUTPUT);
	pinMode(N_CTRL_PIN,OUTPUT);

	
	Serial.begin(115200);
	pinMode(LEDPIN, OUTPUT);
	
	MsTimer2::set(200, onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
	MsTimer2::start(); //开始计时
	
	Serial.print("Reboot\r\n");
}
//


//
void  loop()// run over and over
{
 

	/*硬件电阻值采集*/
	UpdateADCs();

	/*电阻值和温度值转换*/
	{
	  for(int channelIndex=0;channelIndex<8;channelIndex++)
	  {
		temperatureBuff[channelIndex] = GetTemperatureFromNTC(temperatureBuff[channelIndex],Res_10K_B3900K);
	  }
	  //

	}
	//

	/*收到上位机命令*/
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

	//对温度值进行排序
	quicksort(temperatureBuff,0,sizeof(temperatureBuff)/sizeof(float));
	
	
	//
	{
		#define		NO_PHASE_CHANGE_MATERIAL										0
		#define		NO_MIN_TEMPERATURE_IN_BOX_EXCEPT_PHASE_CHANGE_MATERIAL			1
		#define		NO_SECOND_MIN_TEMPERATURE_IN_BOX_EXCEPT_PHASE_CHANGE_MATERIAL	2
		#define		NO_SECOND_MAX_TEMPERATURE_IN_BOX_EXCEPT_PHASE_CHANGE_MATERIAL	6
		#define		NO_MIN_TEMPERATURE_IN_BOX_EXCEPT_PHASE_CHANGE_MATERIAL			7
		
		enum{Enum_Pull=0,Enum_Push,Enum_Default};
		
		
		float averageTemperatureInBox;
		char	commandForMagnet	=	Enum_Pull;
		
		static	char	preCommandForMagnet	=	Enum_Pull;
		
		averageTemperatureInBox	=	0;
		
		for(int i=1;i<8;i++)
		{
			averageTemperatureInBox	+=	temperatureBuff[i];
		}
		//
		
		averageTemperatureInBox	=	averageTemperatureInBox/7;
		
		
		
		if(averageTemperatureInBox>SET_MAX_TEMPERATURE_IN_BOX)
		{
			commandForMagnet	=	Enum_Pull;
		}
		//
		
		if(averageTemperatureInBox<SET_MIN_TEMPERATURE_IN_BOX)
		{
			commandForMagnet	=	Enum_Push;
		}
		//
		
		
		//磁铁动作
		{
			//计算得到的磁铁命令前后不一致，则说明磁铁的动作需要发生改变了。
			//如果前后一致，则释放磁铁控制线圈——磁铁是保持型的所以不必担心
			if(commandForMagnet^preCommandForMagnet)
			{
				magnicAction(commandForMagnet);
				preCommandForMagnet	=	commandForMagnet;
			}
			//
			else
			{
				magnicAction(Enum_Default);
			}
			//
			
		}
		//
		
	}
	//
	
	

  
	delay(300);
}
//




