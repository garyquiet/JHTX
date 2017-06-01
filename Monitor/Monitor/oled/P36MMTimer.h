#ifndef _P36MMTimer_h_
#define _P36MMTimer_h_

#include "Mmsystem.h"
#pragma comment(lib,"Mmtimer.lib")

class CP36MMTimer
{
public:
	CP36MMTimer();
	~CP36MMTimer();

	BOOL InitMMTimer(UINT uInterval,		//时间间隔
		             UINT uResolution,		//时间分辨率
					 LPTIMECALLBACK fptc,	//回调函数指针
					 DWORD dwUser,			//用户回调参数
					 UINT uEvent);			//定时器事件类型

	UINT StartMMTimer();
	UINT KillMMTimer();
	UINT GetTimerID();
	
protected:
	UINT			m_uInterval;
	UINT			m_uResolution;
	LPTIMECALLBACK	m_fptc;
	DWORD			m_dwUser;
	UINT			m_uEvent;
	UINT			m_uTimerID;
};

#endif _P36MMTimer_h_;
