#include "StdAfx.h"
#include "P36GPIO.h"
//#include "Monitor.h"

CP36GPIO::CP36GPIO(void)
{
	GPIO_Open(_T("PIO1:"));

	//RESB_PIN引脚配置为输出
	GPIO_OutEnable(RESB_PIN);
	//CSON_PIN引脚配置为输出
	GPIO_OutEnable(CSON_PIN);
	//SCL_PIN引脚配置为输出
	GPIO_OutEnable(SCLK_PIN);
	//MOSI_PIN引脚配置为输出
	GPIO_OutEnable(MOSI_PIN);
	//MISO_PIN引脚配置为输入
	GPIO_OutDisable(MISO_PIN);

	//供电模式监视位
	GPIO_OutDisable(SUPPLYMODE_PIN);
	//音量加监视位
	GPIO_OutDisable(VOLUMEUP_PIN);
	//音量减监视位
	GPIO_OutDisable(VOLUMEDN_PIN);
	//外置PTT键
	GPIO_OutDisable(INPTT_PIN);
	//耳机PTT键
	GPIO_OutDisable(EARPHONEPTT_PIN);
	//扬声器模式位
	GPIO_OutDisable(SPEAKERMODE_PIN);
	//一键报警键
	GPIO_OutDisable(ALARM_PIN);
	//功放模式监视位
	GPIO_OutDisable(SOUNDMODE_PIN);
	
	//U/D控制位//CS控制位
	GPIO_OutSet(UPDN_PIN);
	GPIO_OutSet(CHIPSEL_PIN);
	GPIO_OutEnable(UPDN_PIN);
	GPIO_OutEnable(CHIPSEL_PIN);

	//VHF静音控制位
	GPIO_OutSet(VHFMUTE_PIN);
	GPIO_OutEnable(VHFMUTE_PIN);

	//功放模式控制位
	GPIO_OutSet(SPEAKERMODE_PIN);
	GPIO_OutClear(EARPHONEMODE_PIN);
	GPIO_OutEnable(SPEAKERMODE_PIN);
	GPIO_OutEnable(EARPHONEMODE_PIN);

	//初始化定时器事件
	m_hEvtIOVolume			= CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hEvtIOAlarm			= CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hEvtIOPTT				= CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hEvtIOSupplyMode		= CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hEvtIOSoundMode		= CreateEvent(NULL,TRUE,TRUE,NULL);
	m_hExitThreadEvent      = CreateEvent(NULL,TRUE,FALSE,NULL);

	m_hIOThread				= INVALID_HANDLE_VALUE;
	m_dwIOThread			= 0;
	m_IOInfo.dwIOLevel		= 0x0;
	m_IOInfo.dwIOLevel      |= ~SOUNDMODE_PIN;
}

CP36GPIO::~CP36GPIO(void)
{
}

/**************************************************************
480×800 TFT LCD延时函数
**************************************************************/
void CP36GPIO::mdelay(unsigned int i)
{
	volatile unsigned int j;
	for(;i != 0;--i)
		for(j = 1150;j != 0;--j);
}

//3线SPI指令时序
inline void CP36GPIO::TL2796_SpiWrite(unsigned int StartByte,unsigned int Data)
{
	GPIO_OutSet(CSON_PIN);
	GPIO_OutSet(SCLK_PIN);
	GPIO_OutClear(CSON_PIN);

	for(unsigned int i = 0x80;i != 0;i >>= 1)
	{
	    GPIO_OutClear(SCLK_PIN);

	    //设置当前位
		if((StartByte & i) == 0)
			GPIO_OutClear(MOSI_PIN);
		else
			GPIO_OutSet(MOSI_PIN);

        GPIO_OutSet(SCLK_PIN);
	}

	for(unsigned int i = 0x80;i != 0;i >>= 1)
	{
	    GPIO_OutClear(SCLK_PIN);

		if((Data & i) == 0)
			GPIO_OutClear(MOSI_PIN);
		else
			GPIO_OutSet(MOSI_PIN);

        GPIO_OutSet(SCLK_PIN);;
	}

	GPIO_OutSet(CSON_PIN);
}

inline void CP36GPIO::Write_Command(unsigned int Cmd)
{
	TL2796_SpiWrite(CMD,Cmd);
}

inline void CP36GPIO::Write_Data(unsigned int Data)
{
	TL2796_SpiWrite(DAT,Data);
}

void CP36GPIO::OLED_Init()
{
   mdelay(25);				// 上电后至少等待25ms

   GPIO_OutSet(RESB_PIN);	// AMOLED软复位
   GPIO_OutClear(RESB_PIN);	
   GPIO_OutSet(RESB_PIN);

   mdelay(25);
   InitTL2796Reg();
}

void CP36GPIO::InitTL2796Reg()
{
///////////////  OLED  Initial Sequence  //////////////////////

   //面板设置
   //SCTE设置
   Write_Command(0x31);	//
   Write_Data(0x08);

   //SCWE设置
   Write_Command(0x32);
   Write_Data(0x14);

   //显示行数、GTCON设置，根据实际显示行数设置
   Write_Command(0x30);	//DL1:DL0 00/800行 01/854行 10/864行 11/禁止设置
   Write_Data(0x02);

   //Display control4
   //显示区域的起始位置，根据实际显示行起始位置设置，当前设置从第一行起-00
   Write_Command(0x28);
   Write_Data(0x00);
   Write_Data(0x00);

   //显示区域的终止位置，根据实际显示行结束位置设置，当前设置以800行结束-800
   Write_Command(0x29);
   Write_Data(0x03);
   Write_Data(0x1F);

   //Display control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0       0       0       0       0      SOE		PCS
   //SOE:选择Pentile的起始类型。0/起始显示输入数据是R/G/B/G格式 1/起始显示输入数据是B/G/R/G格式
   //PCS:为PMOS类的AMOLED门信号选择供电顺序模式，每个PMOS类的门信号有两种供电顺序模式，门信号开启/关闭时序由这条命令改变
   //PCS:0/供电顺序模式1 1/供电顺序模式2
   Write_Command(0x27);
   Write_Data(0x01);

   //显示设置
   //Display control1,VSYNC后肩设置范围0-31，根据实际的同步时序设置，当前为8个行显时间
   Write_Command(0x12);
   Write_Data(0x08);

   //Display control1,VSYNC前肩设置范围0-31，根据实际的同步时序设置，当前为8个行显时间
   Write_Command(0x13);
   Write_Data(0x08);

   //Display control2,极性翻转，根据驱动厂家的实际有效电平进行设置
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0       0      SS      VSPL    HSPL    DPL     EPL
   //SS:选择源驱动的输出移位方向 0/S1->S960 1/S960->S1
   //VSPL:VSYNC信号有效极性 0/低有效 1/高有效
   //HSPL:HSYNC信号有效极性 0/低有效 1/高有效
   //DPL:DOCLK信号有效极性  0/数据在DOCLK上升沿同步读入 1/数据在DOCLK下降沿读入
   //EPL:选择使用RGB接口的数据使能信号极性 0/ENABLE=0数据有效，=1数据无效 1/ENABLE=1数据有效，=0数据无效
   Write_Command(0x15);
   Write_Data(0x01);

   //Display control2,极性翻转
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0      PT1		PT0		 0       0      CM1		CM0
   //PT1-0:设置非显示区的源输出
   //PT1	PT0		REV=0		REV=1
   // 0		 0      V0			V255
   // 0		 1		V255        V0
   // 1      0      V0          V255
   // 1		 1 禁止设置
   //CM1-0:颜色模式设置，根据实际RGB接口模式，此处为0x00
   //(1)0x00  24bit-16M   (2)0x01  18bit-262K   (3)0x10  16bit-65K	(4)0x11 3bit-8  
   Write_Command(0x16);
   Write_Data(0x00);       

   Write_Command(0xef);
   Write_Data(0xd0);
   Write_Data(0xe8);

//######################Gamma Setting##########################
   //Gamma设置选择,按默认方式设置
   Write_Command(0x39);
   Write_Data(0x44);	

   Write_Command(0x40);
   Write_Data(0x00);

   Write_Command(0x41);
   Write_Data(0x3f);

   Write_Command(0x42);
   Write_Data(0x2a);

   Write_Command(0x43);
   Write_Data(0x27);

   Write_Command(0x44);		   
   Write_Data(0x27);

   Write_Command(0x45);
   Write_Data(0x1f);

   Write_Command(0x46);
   Write_Data(0x44);

   Write_Command(0x50);	
   Write_Data(0x00);		

   Write_Command(0x51);
   Write_Data(0x00);

   Write_Command(0x52);
   Write_Data(0x17);

   Write_Command(0x53);
   Write_Data(0x24);

   Write_Command(0x54);
   Write_Data(0x26);

   Write_Command(0x55);
   Write_Data(0x1f);

   Write_Command(0x56);
   Write_Data(0x43);

   Write_Command(0x60);
   Write_Data(0x00);

   Write_Command(0x61);
   Write_Data(0x3f);

   Write_Command(0x62);
   Write_Data(0x2a);

   Write_Command(0x63);
   Write_Data(0x25);

   Write_Command(0x64);
   Write_Data(0x24);

   Write_Command(0x65);
   Write_Data(0x1b);

   Write_Command(0x66);
   Write_Data(0x5c);

/////////////////Power on setting sequence///////////////
   //模拟供电设置
   //Power Control1
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		DC12	DC11	DC10	 0		DC02	DC01	DC00
   //DC12-0:为高电压生成选择推进频率，如果推进频率高，推进电路的效率会改善，但功耗会增加
   //DC02-0:为中电压生成选择推进频率，如果推进频率高，推进电路的效率会改善，但功耗会增加
   Write_Command(0x17);
   Write_Data(0x22);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		SAP2	SAP1	SAP0	 0		AP2		AP1		AP0
   //SAP2-0：调节源驱动功放电流，电流大，AMOLED驱动力强，但耗电
   //AP2-0：调节AMOLED驱动功放的电流流动率，流动率大，显示效果增加功耗增加
   Write_Command(0x18);
   Write_Data(0x33);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		GAP2	GAP1	GAP0
   //GAP2-0:调节灰度功放电流流动率，流动率大，显示效果增加功耗增加
   Write_Command(0x19);
   Write_Data(0x03);

   //Power Control2
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		 0		BT1		BT0
   //BT1-0:控制DCDC转换电路的推进率
   Write_Command(0x1a);
   Write_Data(0x01);

   //Logic voltage control
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1      0       1       0       0      SVL2	SVL1	SVL0
   //SVL2-0:内部逻辑电压(VCCL)控制
   //推荐VCCL电压范围是1.75-1.9V,因此需根据实际的VCC设置SVL[2:0]
   Write_Command(0x22);
   Write_Data(0xa4);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		VC2		VC1		VC0
   Write_Command(0x23);
   Write_Data(0x00);

   //Display control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1		 0		 1		 0		 0		 0		DMD1	DMD0
   //DMD1-0:为LTPS信号生成选择参考时钟
   //00:使用DOTCLK作为LTPS时序时钟，LTPS时序时钟依赖于外部时钟频率，根据外部时钟频率，LTPS脉冲宽度可变
   //01:由内部晶振时钟自动侦测外部时钟频率，LTPS脉宽由SCWE寄存器值固定或由内部晶振时钟生成，而不考虑外部时钟频率
   Write_Command(0x26);
   Write_Data(0xA0);
   
   //Power Control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1		 0		 1		 0		 0		 0		 0		STB
   //STB: 1/IC进入待机模式，显示操作停止，命令对已处于待机模式模块无影响，只能通过离开待机模式指令离开待机模式
   Write_Command(0x1d);//Stand-by Off
   Write_Data(0xa0);
   
   //从待机模式发送离开待机模式指令后需等待200ms后可再次发送进入待机模式指令
   mdelay(250);
   
   //Display control2
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0	    REV		 0		 0		D1		D0
   //REV: 1/反转显示所有字符和图片
   //D1-0:00/01/10,源驱动输出级为V0，这种情况下AMOLED显示黑，11/源驱动输出256种灰度级
   Write_Command(0x14);//Display on
   Write_Data(0x03);
}

void CP36GPIO::OLED_Off()
{
	Write_Command(0x14);//Display on
    Write_Data(0x00);

	mdelay(1);

	Write_Command(0x1d);//Stand-by Off
    Write_Data(0xa1);

	mdelay(250);
	GPIO_OutClear(CSON_PIN);
}

void CP36GPIO::OLED_On()
{
   InitTL2796Reg();
}

DWORD CP36GPIO::IOThread(LPVOID pParam)
{
	CP36GPIO* pGPIO = (CP36GPIO*)pParam;
	//unsigned int uPinState;

	while(1)
	{
		if(WaitForSingleObject(pGPIO->m_hExitThreadEvent,0) == WAIT_OBJECT_0)//关闭句柄有效则跳出线程函数
		{
			break;
		}

		////检测外置PTT引脚电平(INPTT_PIN引脚电平)				//低电平为有效电平
		//uPinState = INPTT_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOPTT,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & INPTT_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOPTT.InitMMTimer(100,10,TmrIOPTTProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOPTT.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOPTT);
		//	}
		//}
		//
		////检测耳机PTT引脚电平(EARPHONEPTT_PIN引脚电平)		//低电平为有效电平
		//uPinState = EARPHONEPTT_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOPTT,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & EARPHONEPTT_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOPTT.InitMMTimer(100,10,TmrIOPTTProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOPTT.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOPTT);
		//	}
		//}
		//
		////检测音量增引脚电平(VOLUMEUP_PIN引脚电平)			//低电平为有效电平			
		//uPinState = VOLUMEUP_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOVolume,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & VOLUMEUP_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOVolume.InitMMTimer(100,10,TmrIOVolumeProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOVolume.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOVolume);
		//	}
		//}

		////检测音量减引脚电平(VOLUMEDN_PIN引脚电平)			//低电平为有效电平			
		//uPinState = VOLUMEDN_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOVolume,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & VOLUMEDN_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOVolume.InitMMTimer(100,10,TmrIOVolumeProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOVolume.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOVolume);
		//	}
		//}

		////检测供电模式引脚电平(SUPPLYMODE_PIN引脚电平)			//低电平为潜艇供电，高电平为电池供电
		//uPinState = SUPPLYMODE_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOSupplyMode,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & SUPPLYMODE_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOSupplyMode.InitMMTimer(100,10,TmrIOSupplyModeProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOSupplyMode.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOSupplyMode);
		//	}
		//}

		////检测一键报警引脚电平(ALARM_PIN引脚电平)					//低电平为有效电平
		//uPinState = ALARM_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOAlarm,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & ALARM_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOAlarm.InitMMTimer(100,10,TmrIOAlarmProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOAlarm.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOAlarm);
		//	}
		//}

		////检测声音模式引脚电平(SOUNDMODE_PIN引脚电平)				//低电平为耳机内放，高电平为喇叭外放
		//uPinState = SOUNDMODE_PIN;
		//if(pGPIO->GPIO_PinState(&uPinState) && (WaitForSingleObject(pGPIO->m_hEvtIOSoundMode,0) == WAIT_OBJECT_0))
		//{
		//	if((pGPIO->m_IOInfo.dwIOLevel & SOUNDMODE_PIN) != uPinState)
		//	{
		//		pGPIO->m_TmrIOSoundMode.InitMMTimer(100,10,TmrIOSoundModeProc,(DWORD)pGPIO,TIME_CALLBACK_FUNCTION);
		//		if(pGPIO->m_TmrIOSoundMode.StartMMTimer())
		//			ResetEvent(pGPIO->m_hEvtIOSoundMode);
		//	}
		//}

		Sleep(0);
	}
	return 0;
}




BOOL CP36GPIO::MonitorIO()
{
	BOOL bResult;

	m_hIOThread = CreateThread(NULL,0,IOThread,this,CREATE_SUSPENDED,&m_dwIOThread);//创建IO监视线程
	if(!m_hIOThread)
		bResult = FALSE;
	else
	{
		ResumeThread(m_hIOThread);
		bResult = TRUE;
	}
	
	return bResult;
}

/*****************************************************************************************/
/*函数介绍：VolumeDn()
  函数作用：控制GPIO电平，降低音量
*入口参数：无
*出口参数：无
*返回值：无*/
/****************************************************************************************/
void CP36GPIO::VolumeDn()
{
	GPIO_OutClear(CHIPSEL_PIN);
	Delay(20);					
	for(int i = 0;i < 7;++i)
	{
		GPIO_OutClear(UPDN_PIN);
		Delay(20);
		GPIO_OutSet(UPDN_PIN);
		Delay(20);			
	}
	GPIO_OutSet(CHIPSEL_PIN);
}

/*****************************************************************************************/
/*函数介绍：VolumeUp()
  函数作用：控制GPIO电平，增加音量
*入口参数：无
*出口参数：无
*返回值：无*/
/****************************************************************************************/
void CP36GPIO::VolumeUp()
{
	GPIO_OutClear(UPDN_PIN);
	Delay(20);
	GPIO_OutClear(CHIPSEL_PIN);
	for(int i = 0;i < 7;++i)
	{
		GPIO_OutClear(UPDN_PIN);
		Delay(20);
		GPIO_OutSet(UPDN_PIN);
		Delay(20);
	}
	GPIO_OutSet(CHIPSEL_PIN);
}

void CP36GPIO::Delay(UINT uDelay)
{
	while(uDelay--);
}

void CP36GPIO::CloseThread()
{
	SetEvent(m_hExitThreadEvent);//置退出串口线程事件为有信号
	if(WaitForSingleObject(m_hIOThread,1000) == WAIT_TIMEOUT)//等待线程句柄关闭超时
	{
		TerminateThread(m_hIOThread,0);
	}
	m_hIOThread = NULL; 
}

void CP36GPIO::CloseGPIO()
{
	CloseThread();//关闭线程
	CloseHandle(m_hExitThreadEvent);//关闭退出串口线程事件句柄
	m_hExitThreadEvent = NULL;
	CloseHandle(m_hIOThread);//关闭串口文件句柄
    m_hIOThread = INVALID_HANDLE_VALUE;//置串口文件句柄无效  
	CloseHandle(m_hEvtIOPTT);
	m_hEvtIOPTT = NULL;
	CloseHandle(m_hEvtIOAlarm);
	m_hEvtIOAlarm = NULL;
	CloseHandle(m_hEvtIOSupplyMode);
	m_hEvtIOSupplyMode = NULL;
	CloseHandle(m_hEvtIOVolume);
	m_hEvtIOVolume = NULL;
	CloseHandle(m_hEvtIOSoundMode);
	m_hEvtIOSoundMode = NULL;
	GPIO_Close();
}