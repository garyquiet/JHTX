#ifndef _P36GPIO_h_
#define _P36GPIO_h_ 

#include "GPIO.h"
#include "P36MMTimer.h"
#include "P36Misc.h"

#define CMD	    0x70
#define DAT     0x72

#define CSON_PIN        GPIO15
#define SCLK_PIN        GPIO14
#define MOSI_PIN        GPIO13
#define MISO_PIN        GPIO12
#define RESB_PIN        GPIO27

#define EARPHONEMODE_PIN	GPIO11
#define SPEAKERMODE_PIN		GPIO10
#define VHFMUTE_PIN			GPIO9
#define CHIPSEL_PIN			GPIO8
#define UPDN_PIN			GPIO7
#define ALARM_PIN			GPIO6
#define SOUNDMODE_PIN		GPIO5           
#define SUPPLYMODE_PIN		GPIO4
#define VOLUMEUP_PIN		GPIO3
#define VOLUMEDN_PIN		GPIO2
#define INPTT_PIN			GPIO1
#define EARPHONEPTT_PIN		GPIO0

class CP36GPIO : public CGPIO
{
public:

	CP36GPIO(void);
	~CP36GPIO(void);

	void OLED_Init();
	void OLED_Off();
	void OLED_On();

	void VolumeDn();
	void VolumeUp();
	BOOL MonitorIO();
	void CloseThread();
	void CloseGPIO();

protected:

	CP36MMTimer m_TmrIOPTT;
	CP36MMTimer m_TmrIOAlarm;
	CP36MMTimer m_TmrIOSupplyMode;
	CP36MMTimer m_TmrIOVolume;
	CP36MMTimer m_TmrIOSoundMode;

	HANDLE      m_hEvtIOPTT;
	HANDLE      m_hEvtIOAlarm;
	HANDLE      m_hEvtIOSupplyMode;
	HANDLE      m_hEvtIOVolume;
	HANDLE      m_hEvtIOSoundMode;

	HANDLE      m_hIOThread;
	HANDLE		m_hExitThreadEvent;//退出线程事件句柄
	DWORD       m_dwIOThread;

	void InitTL2796Reg();
	IO_INFO m_IOInfo;

	void Delay(UINT uDelay);
	void mdelay(unsigned int i);
	inline void TL2796_SpiWrite(unsigned int StartByte,unsigned int Data); 
	inline void Write_Command(unsigned int Cmd);
	inline void Write_Data(unsigned int Data);

	static DWORD WINAPI IOThread(LPVOID pParam);

};

#endif _P36GPIO_h_