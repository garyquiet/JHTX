#ifndef _P36MMTimer_h_
#define _P36MMTimer_h_

#include "Mmsystem.h"
#pragma comment(lib,"Mmtimer.lib")

class CP36MMTimer
{
public:
	CP36MMTimer();
	~CP36MMTimer();

	BOOL InitMMTimer(UINT uInterval,		//ʱ����
		             UINT uResolution,		//ʱ��ֱ���
					 LPTIMECALLBACK fptc,	//�ص�����ָ��
					 DWORD dwUser,			//�û��ص�����
					 UINT uEvent);			//��ʱ���¼�����

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
