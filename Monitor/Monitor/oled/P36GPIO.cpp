#include "StdAfx.h"
#include "P36GPIO.h"
//#include "Monitor.h"

CP36GPIO::CP36GPIO(void)
{
	GPIO_Open(_T("PIO1:"));

	//RESB_PIN��������Ϊ���
	GPIO_OutEnable(RESB_PIN);
	//CSON_PIN��������Ϊ���
	GPIO_OutEnable(CSON_PIN);
	//SCL_PIN��������Ϊ���
	GPIO_OutEnable(SCLK_PIN);
	//MOSI_PIN��������Ϊ���
	GPIO_OutEnable(MOSI_PIN);
	//MISO_PIN��������Ϊ����
	GPIO_OutDisable(MISO_PIN);

	//����ģʽ����λ
	GPIO_OutDisable(SUPPLYMODE_PIN);
	//�����Ӽ���λ
	GPIO_OutDisable(VOLUMEUP_PIN);
	//����������λ
	GPIO_OutDisable(VOLUMEDN_PIN);
	//����PTT��
	GPIO_OutDisable(INPTT_PIN);
	//����PTT��
	GPIO_OutDisable(EARPHONEPTT_PIN);
	//������ģʽλ
	GPIO_OutDisable(SPEAKERMODE_PIN);
	//һ��������
	GPIO_OutDisable(ALARM_PIN);
	//����ģʽ����λ
	GPIO_OutDisable(SOUNDMODE_PIN);
	
	//U/D����λ//CS����λ
	GPIO_OutSet(UPDN_PIN);
	GPIO_OutSet(CHIPSEL_PIN);
	GPIO_OutEnable(UPDN_PIN);
	GPIO_OutEnable(CHIPSEL_PIN);

	//VHF��������λ
	GPIO_OutSet(VHFMUTE_PIN);
	GPIO_OutEnable(VHFMUTE_PIN);

	//����ģʽ����λ
	GPIO_OutSet(SPEAKERMODE_PIN);
	GPIO_OutClear(EARPHONEMODE_PIN);
	GPIO_OutEnable(SPEAKERMODE_PIN);
	GPIO_OutEnable(EARPHONEMODE_PIN);

	//��ʼ����ʱ���¼�
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
480��800 TFT LCD��ʱ����
**************************************************************/
void CP36GPIO::mdelay(unsigned int i)
{
	volatile unsigned int j;
	for(;i != 0;--i)
		for(j = 1150;j != 0;--j);
}

//3��SPIָ��ʱ��
inline void CP36GPIO::TL2796_SpiWrite(unsigned int StartByte,unsigned int Data)
{
	GPIO_OutSet(CSON_PIN);
	GPIO_OutSet(SCLK_PIN);
	GPIO_OutClear(CSON_PIN);

	for(unsigned int i = 0x80;i != 0;i >>= 1)
	{
	    GPIO_OutClear(SCLK_PIN);

	    //���õ�ǰλ
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
   mdelay(25);				// �ϵ�����ٵȴ�25ms

   GPIO_OutSet(RESB_PIN);	// AMOLED��λ
   GPIO_OutClear(RESB_PIN);	
   GPIO_OutSet(RESB_PIN);

   mdelay(25);
   InitTL2796Reg();
}

void CP36GPIO::InitTL2796Reg()
{
///////////////  OLED  Initial Sequence  //////////////////////

   //�������
   //SCTE����
   Write_Command(0x31);	//
   Write_Data(0x08);

   //SCWE����
   Write_Command(0x32);
   Write_Data(0x14);

   //��ʾ������GTCON���ã�����ʵ����ʾ��������
   Write_Command(0x30);	//DL1:DL0 00/800�� 01/854�� 10/864�� 11/��ֹ����
   Write_Data(0x02);

   //Display control4
   //��ʾ�������ʼλ�ã�����ʵ����ʾ����ʼλ�����ã���ǰ���ôӵ�һ����-00
   Write_Command(0x28);
   Write_Data(0x00);
   Write_Data(0x00);

   //��ʾ�������ֹλ�ã�����ʵ����ʾ�н���λ�����ã���ǰ������800�н���-800
   Write_Command(0x29);
   Write_Data(0x03);
   Write_Data(0x1F);

   //Display control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0       0       0       0       0      SOE		PCS
   //SOE:ѡ��Pentile����ʼ���͡�0/��ʼ��ʾ����������R/G/B/G��ʽ 1/��ʼ��ʾ����������B/G/R/G��ʽ
   //PCS:ΪPMOS���AMOLED���ź�ѡ�񹩵�˳��ģʽ��ÿ��PMOS������ź������ֹ���˳��ģʽ�����źſ���/�ر�ʱ������������ı�
   //PCS:0/����˳��ģʽ1 1/����˳��ģʽ2
   Write_Command(0x27);
   Write_Data(0x01);

   //��ʾ����
   //Display control1,VSYNC������÷�Χ0-31������ʵ�ʵ�ͬ��ʱ�����ã���ǰΪ8������ʱ��
   Write_Command(0x12);
   Write_Data(0x08);

   //Display control1,VSYNCǰ�����÷�Χ0-31������ʵ�ʵ�ͬ��ʱ�����ã���ǰΪ8������ʱ��
   Write_Command(0x13);
   Write_Data(0x08);

   //Display control2,���Է�ת�������������ҵ�ʵ����Ч��ƽ��������
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0       0      SS      VSPL    HSPL    DPL     EPL
   //SS:ѡ��Դ�����������λ���� 0/S1->S960 1/S960->S1
   //VSPL:VSYNC�ź���Ч���� 0/����Ч 1/����Ч
   //HSPL:HSYNC�ź���Ч���� 0/����Ч 1/����Ч
   //DPL:DOCLK�ź���Ч����  0/������DOCLK������ͬ������ 1/������DOCLK�½��ض���
   //EPL:ѡ��ʹ��RGB�ӿڵ�����ʹ���źż��� 0/ENABLE=0������Ч��=1������Ч 1/ENABLE=1������Ч��=0������Ч
   Write_Command(0x15);
   Write_Data(0x01);

   //Display control2,���Է�ת
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0      0      PT1		PT0		 0       0      CM1		CM0
   //PT1-0:���÷���ʾ����Դ���
   //PT1	PT0		REV=0		REV=1
   // 0		 0      V0			V255
   // 0		 1		V255        V0
   // 1      0      V0          V255
   // 1		 1 ��ֹ����
   //CM1-0:��ɫģʽ���ã�����ʵ��RGB�ӿ�ģʽ���˴�Ϊ0x00
   //(1)0x00  24bit-16M   (2)0x01  18bit-262K   (3)0x10  16bit-65K	(4)0x11 3bit-8  
   Write_Command(0x16);
   Write_Data(0x00);       

   Write_Command(0xef);
   Write_Data(0xd0);
   Write_Data(0xe8);

//######################Gamma Setting##########################
   //Gamma����ѡ��,��Ĭ�Ϸ�ʽ����
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
   //ģ�⹩������
   //Power Control1
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		DC12	DC11	DC10	 0		DC02	DC01	DC00
   //DC12-0:Ϊ�ߵ�ѹ����ѡ���ƽ�Ƶ�ʣ�����ƽ�Ƶ�ʸߣ��ƽ���·��Ч�ʻ���ƣ������Ļ�����
   //DC02-0:Ϊ�е�ѹ����ѡ���ƽ�Ƶ�ʣ�����ƽ�Ƶ�ʸߣ��ƽ���·��Ч�ʻ���ƣ������Ļ�����
   Write_Command(0x17);
   Write_Data(0x22);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		SAP2	SAP1	SAP0	 0		AP2		AP1		AP0
   //SAP2-0������Դ�������ŵ�����������AMOLED������ǿ�����ĵ�
   //AP2-0������AMOLED�������ŵĵ��������ʣ������ʴ���ʾЧ�����ӹ�������
   Write_Command(0x18);
   Write_Data(0x33);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		GAP2	GAP1	GAP0
   //GAP2-0:���ڻҶȹ��ŵ��������ʣ������ʴ���ʾЧ�����ӹ�������
   Write_Command(0x19);
   Write_Data(0x03);

   //Power Control2
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		 0		BT1		BT0
   //BT1-0:����DCDCת����·���ƽ���
   Write_Command(0x1a);
   Write_Data(0x01);

   //Logic voltage control
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1      0       1       0       0      SVL2	SVL1	SVL0
   //SVL2-0:�ڲ��߼���ѹ(VCCL)����
   //�Ƽ�VCCL��ѹ��Χ��1.75-1.9V,��������ʵ�ʵ�VCC����SVL[2:0]
   Write_Command(0x22);
   Write_Data(0xa4);

   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0		 0		 0		VC2		VC1		VC0
   Write_Command(0x23);
   Write_Data(0x00);

   //Display control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1		 0		 1		 0		 0		 0		DMD1	DMD0
   //DMD1-0:ΪLTPS�ź�����ѡ��ο�ʱ��
   //00:ʹ��DOTCLK��ΪLTPSʱ��ʱ�ӣ�LTPSʱ��ʱ���������ⲿʱ��Ƶ�ʣ������ⲿʱ��Ƶ�ʣ�LTPS�����ȿɱ�
   //01:���ڲ�����ʱ���Զ�����ⲿʱ��Ƶ�ʣ�LTPS������SCWE�Ĵ���ֵ�̶������ڲ�����ʱ�����ɣ����������ⲿʱ��Ƶ��
   Write_Command(0x26);
   Write_Data(0xA0);
   
   //Power Control3
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 1		 0		 1		 0		 0		 0		 0		STB
   //STB: 1/IC�������ģʽ����ʾ����ֹͣ��������Ѵ��ڴ���ģʽģ����Ӱ�죬ֻ��ͨ���뿪����ģʽָ���뿪����ģʽ
   Write_Command(0x1d);//Stand-by Off
   Write_Data(0xa0);
   
   //�Ӵ���ģʽ�����뿪����ģʽָ�����ȴ�200ms����ٴη��ͽ������ģʽָ��
   mdelay(250);
   
   //Display control2
   //IB7	IB6		IB5		IB4		IB3		IB2		IB1		IB0
   // 0		 0		 0	    REV		 0		 0		D1		D0
   //REV: 1/��ת��ʾ�����ַ���ͼƬ
   //D1-0:00/01/10,Դ���������ΪV0�����������AMOLED��ʾ�ڣ�11/Դ�������256�ֻҶȼ�
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
		if(WaitForSingleObject(pGPIO->m_hExitThreadEvent,0) == WAIT_OBJECT_0)//�رվ����Ч�������̺߳���
		{
			break;
		}

		////�������PTT���ŵ�ƽ(INPTT_PIN���ŵ�ƽ)				//�͵�ƽΪ��Ч��ƽ
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
		////������PTT���ŵ�ƽ(EARPHONEPTT_PIN���ŵ�ƽ)		//�͵�ƽΪ��Ч��ƽ
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
		////������������ŵ�ƽ(VOLUMEUP_PIN���ŵ�ƽ)			//�͵�ƽΪ��Ч��ƽ			
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

		////������������ŵ�ƽ(VOLUMEDN_PIN���ŵ�ƽ)			//�͵�ƽΪ��Ч��ƽ			
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

		////��⹩��ģʽ���ŵ�ƽ(SUPPLYMODE_PIN���ŵ�ƽ)			//�͵�ƽΪǱͧ���磬�ߵ�ƽΪ��ع���
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

		////���һ���������ŵ�ƽ(ALARM_PIN���ŵ�ƽ)					//�͵�ƽΪ��Ч��ƽ
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

		////�������ģʽ���ŵ�ƽ(SOUNDMODE_PIN���ŵ�ƽ)				//�͵�ƽΪ�����ڷţ��ߵ�ƽΪ�������
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

	m_hIOThread = CreateThread(NULL,0,IOThread,this,CREATE_SUSPENDED,&m_dwIOThread);//����IO�����߳�
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
/*�������ܣ�VolumeDn()
  �������ã�����GPIO��ƽ����������
*��ڲ�������
*���ڲ�������
*����ֵ����*/
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
/*�������ܣ�VolumeUp()
  �������ã�����GPIO��ƽ����������
*��ڲ�������
*���ڲ�������
*����ֵ����*/
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
	SetEvent(m_hExitThreadEvent);//���˳������߳��¼�Ϊ���ź�
	if(WaitForSingleObject(m_hIOThread,1000) == WAIT_TIMEOUT)//�ȴ��߳̾���رճ�ʱ
	{
		TerminateThread(m_hIOThread,0);
	}
	m_hIOThread = NULL; 
}

void CP36GPIO::CloseGPIO()
{
	CloseThread();//�ر��߳�
	CloseHandle(m_hExitThreadEvent);//�ر��˳������߳��¼����
	m_hExitThreadEvent = NULL;
	CloseHandle(m_hIOThread);//�رմ����ļ����
    m_hIOThread = INVALID_HANDLE_VALUE;//�ô����ļ������Ч  
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