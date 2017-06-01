#include "StdAfx.h"
#include "P36MMTimer.h"

CP36MMTimer::CP36MMTimer()
{
	m_uTimerID		= 0;
	m_dwUser		= 0;
	m_fptc			= NULL;
	m_uInterval		= 3000;
	m_uResolution	= 30;
	m_uEvent        = TIME_CALLBACK_FUNCTION;
}

CP36MMTimer::~CP36MMTimer()
{
	KillMMTimer();
}

BOOL CP36MMTimer::InitMMTimer(UINT uInterval,UINT uResolution,LPTIMECALLBACK fptc,DWORD dwUser,UINT uEvent)
{
	TIMECAPS tc;
	if(timeGetDevCaps(&tc,sizeof(TIMECAPS)) == TIMERR_NOERROR)
	{
		if(uResolution != min(max(tc.wPeriodMin,uResolution),tc.wPeriodMax))//是否在可设定分辨率范围内
			return FALSE;
	}

	if((uEvent == TIME_CALLBACK_EVENT_SET) || (uEvent == TIME_CALLBACK_EVENT_PULSE) || (uEvent == TIME_ONESHOT) || (uEvent == TIME_PERIODIC) || (uEvent == TIME_CALLBACK_FUNCTION))
	{
		if(fptc == NULL)
			return FALSE;
		else
		{
			m_uInterval		= uInterval;
			m_uResolution	= uResolution;
			m_fptc			= fptc;
			m_dwUser        = dwUser;
			m_uEvent        = uEvent;
			return TRUE;
		}
	}
	return TRUE;
}

UINT CP36MMTimer::StartMMTimer()
{
	m_uTimerID = NULL;

	if(timeBeginPeriod(m_uResolution) == TIMERR_NOERROR)
	{
		m_uTimerID = timeSetEvent(m_uInterval,m_uResolution,m_fptc,m_dwUser,m_uEvent);
	}
	return m_uTimerID;
}

UINT CP36MMTimer::KillMMTimer()
{
	if(m_uTimerID)
	{
		timeKillEvent(m_uTimerID);
		timeEndPeriod(m_uResolution);
		m_uTimerID = 0;
	}
	return m_uTimerID;
}

UINT CP36MMTimer::GetTimerID()
{
	return m_uTimerID;
}