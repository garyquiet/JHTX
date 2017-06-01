#ifndef _P36Misc_h_
#define _P36Misc_h_

#include "P36MsgMisc.h"
#include "P36CmdMisc.h"

#define CMD	    0x70
#define DAT     0x72

BYTE    BoatCode(BYTE* pbyDest, const BYTE* pbySrc, int nCharLen);

#define TIMER_DATE_TIME_STATEBARDLG  	1
#define TIMER_SEC_COUNT_ALARMDLG		2
#define TIMER_SEC_COUNT_MODESELDLG      3
#define TIMER_SEC_COUNT_VOLUMEDLG       4
#define TIMER_HSEC_COUNT_MAINDLG        5
#define TIMER_SEC_COUNT_INFODLG         6

#define INFO_TYPE_FAIL					0
#define INFO_TYPE_SUCCESS				1 
#define INFO_TYPE_WARN					2

#define DLG_INVALID_PTR					0
#define DLG_CREATE_OK					1
#define DLG_ALREADY_EXIST				2

#define LISTITEM_NUM10					10		//列表行数10
#define LISTITEM_NUM13					13      //列表行数13
#define RECORD_NUM50                    50      //数据库表记录数50
#define RECORD_NUM100                   100     //数据库表记录数100

typedef enum
{
	BUOY_MCU = 0x03
}SCOMM_NO;

//串口数据块结构体
typedef struct tagSCOMMDATA
{
	SCOMM_NO	nSCommNo;
	DWORD		dwSCommData;
	BYTE*		pbySCommData;
}SCOMM_DATA;

//通信状态结构体
typedef enum
{
	SCOMM_HANDSHAKE,
	SCOMM_SHAKENEXT,
	SCOMM_ENTERNORM
}SCOMM_STATE;

//日期结构体
typedef struct tagP36DATE
{
	BYTE byYearHI;
	BYTE byYearLO;
	BYTE byMonth;
	BYTE byDay;
}P36DATE;

//时间结构体
typedef struct tagP36TIME
{
	BYTE byHour;
	BYTE byMinute;
	BYTE bySecond;
	BYTE byMSecond;
}P36TIME;

//经/纬度结构体
typedef struct tagP36TUDE
{
	BYTE byDegree;
	BYTE byMinute;
	BYTE bySecond;
	BYTE byMSecond;
}P36TUDE;

typedef struct tagP36HEIG
{
	BYTE byHSign;
	BYTE byHData;
	BYTE byHESign;
	BYTE byHEData;
}P36HEIG;

//电池信息结构体
typedef struct tagBATT_INFO						
{
	P36DATE Date;
	BYTE	byCharge;
}BATT_INFO;

//北斗场强信息结构体
typedef struct tagBD_INFO						
{
	BYTE byBDPower1;
	BYTE byBDPower2;
	BYTE byBDPower3;
	BYTE byBDPower4;
	BYTE byBDPower5;
	BYTE byBDPower6;
}BD_INFO;

//VHF模块信息结构体
typedef struct tagVHF_INFO						
{
	BOOL bVHFState;								//VHF模块状态：TRUE/故障或关闭；FALSE/打开
	BOOL bPTTState;								//VHFPTT状态：FALSE/发射 TRUE/接收；
	BYTE byVHFChannel;							//VHF当前频道
	BYTE byVolume;								//当前音量等级
}VHF_INFO;

//IO信息结构体
typedef struct tagIO_INFO						
{
	DWORD dwIOLevel;
}IO_INFO;

//卫星授时信息结构体
typedef struct tagSATE_TIME						
{
	P36DATE Date;
	P36TIME Time;
}SATE_TIME;

//卫星定位信息结构体
typedef struct tagSATE_TUDE						
{
	P36TIME Time;
	P36TUDE Lgt;
	P36TUDE Lat;
	P36HEIG Heig;
}SATE_TUDE;

//北斗IC卡级别
typedef struct tagIC_INFO
{
	DWORD dwCommFreq;
	DWORD dwChnLevel;
	DWORD dwNumLevel;
	DWORD dwLocalId;
	DWORD dwBaseId;
}IC_INFO;

//状态信息结构体
typedef struct tagSTATEINFO						
{
	IC_INFO   ICInfo;		//IC信息
	BD_INFO   BDInfo;		//北斗功率
	VHF_INFO  VHFInfo;		//VHF信息
	SATE_TUDE SateTude;		//定位信息
	SATE_TIME SateTime;		//授时信息
	BATT_INFO BattInfo;		//当前电池电量
	IO_INFO   IOInfo;       //IO电平
	
	BOOL bWorkDetecting;	//工厂检测 FALSE/当前不在工厂检测 TRUE/当前处于工厂检测
	BOOL bSupplyMode;		//供电指示 FALSE/电池供电  TRUE/外部供电
	BOOL bAlarming;			//是否处于报警状态
	BYTE byAlarmAck;		//岸基报警回执
	BOOL bSateTime_En;      //是否允许自动授时
	BOOL bSateTimed;		//卫星是否已触发授时
	BOOL bSateTuded;		//卫星是否已定位
	BOOL bCharged;			//是否等待触发电池电量
	BOOL bHandShaked;		//握手是否成功
	BYTE byOLEDState;		//OLED最近一次屏幕状态
	BOOL bRxSComData;       //是否收到串口数据
}STATE_INFO;

//保存菜单的所有有关信息


//页信息结构体
typedef struct tagPAGE										
{
	int  nStart;			//页在UNICODE串中的起始位置
	int  nStop;				//页在UNICODE串中的结束位置
	BOOL bInit;				//页信息结构体是否已被初始化
}PAGE;

class CP36StateBarDlg;
class CP36InfoBarDlg;
class CP36T9Dlg;
class CP36MsgCommDlg;
class CP36DetectDlg;
class CP36SetDlg;
class CP36QueryDlg;
class CP36HelpDlg;
class CP36CmdAckDlg;
class CP36VolumeDlg;
class CP36InfoDlg;
class CP36Database;
class CP36DetectInfoDlg;
class CP36PwdAckDlg;
class CP36WorkDetectDlg;
class CP36InitSetDlg;
class CP36TimeSetDlg;
class CP36TudeSetDlg;
class CP36PwdSetDlg;
class CP36ModeSelDlg;
class CP36AlarmDlg;
class CP36VhfSetDlg;
class CP36CodeSetDlg;
class CP36MsgerDlg;
class CP36CreateMsgerDlg;
class CP36DelAckDlg;
class CP36ChnMsgDlg;
class CP36MsgerListDlg;
class CP36PSMsgDlg;
class CP36PSMsgListDlg;
class CP36NumMsgDlg;
class CP36NewMsgDlg;
class CP36SDMsgDlg;
class CP36CreateSDMsgDlg;
class CP36SDMsgListDlg;
class CP36AlarmRecordDlg;
class CP36AlarmRecordInfoDlg;
class CP36LocateRecordDlg;
class CP36LocateRecordInfoDlg;
class CP36RxMsgRecordDlg;
class CP36RxMsgRecordInfoDlg;
class CP36TxMsgRecordDlg;
class CP36TxMsgRecordInfoDlg;
class CP36HistoryRecordDlg;
class CP36Database;
class CP36LogoDlg;
class CP36BugAnalyseDlg;
class CP36OperateDescribeDlg;
class CP36SoftVersionDlg;
class CP36WorkSetDlg;
class CP36BattSetDlg;
class CP36CmdState;
class CP36TxAssemble;
class CP36RxMsgInfoDlg;

extern CP36StateBarDlg*			g_pStateBarDlg;
extern CP36InfoBarDlg*			g_pInfoBarDlg;
extern CP36T9Dlg*               g_pT9Dlg;
extern CP36MsgCommDlg*			g_pMsgCommDlg;
extern CP36DetectDlg*			g_pDetectDlg;
extern CP36SetDlg*				g_pSetDlg;
extern CP36QueryDlg*			g_pQueryDlg;
extern CP36HelpDlg*				g_pHelpDlg;
extern CP36CmdAckDlg*			g_pCmdAckDlg;
extern CP36VolumeDlg*			g_pVolumeDlg;
extern CP36InfoDlg*				g_pInfoDlg;
extern CP36DetectInfoDlg*		g_pSelfDetectDlg;
extern CP36DetectInfoDlg*		g_pLoopDetectDlg;
extern CP36DetectInfoDlg*		g_pBattDetectDlg;
extern CP36DetectInfoDlg*		g_pCodeDetectDlg;
extern CP36DetectInfoDlg*       g_pAlarmDetectDlg;
extern CP36DetectInfoDlg*       g_pLocateDetectDlg;
extern CP36DetectInfoDlg*       g_pTimeDetectDlg;
extern CP36WorkDetectDlg*		g_pWorkDetectDlg;
extern CP36PwdAckDlg*			g_pPwdAckDlg;
extern CP36InitSetDlg*			g_pInitSetDlg;
extern CP36TimeSetDlg*			g_pTimeSetDlg;
extern CP36TudeSetDlg*			g_pTudeSetDlg;
extern CP36PwdSetDlg*			g_pPwdSetDlg;
extern CP36ModeSelDlg*			g_pModeSelDlg;
extern CP36AlarmDlg*			g_pAlarmDlg;
extern CP36VhfSetDlg*			g_pVhfSetDlg;
extern CP36CodeSetDlg*			g_pCodeSetDlg;
extern CP36MsgerDlg*			g_pMsgerDlg;
extern CP36CreateMsgerDlg*		g_pCreateMsgerDlg;
extern CP36DelAckDlg*			g_pDelAckDlg;
extern CP36ChnMsgDlg*			g_pChnMsgDlg;
extern CP36MsgerListDlg*		g_pMsgerListDlg;
extern CP36PSMsgDlg*			g_pPSMsgDlg;
extern CP36PSMsgListDlg*		g_pPSMsgListDlg;
extern CP36NumMsgDlg*			g_pNumMsgDlg;
extern CP36NewMsgDlg*			g_pNewMsgDlg;
extern CP36SDMsgDlg*			g_pSDMsgDlg;
extern CP36CreateSDMsgDlg*		g_pCreateSDMsgDlg;
extern CP36SDMsgListDlg*		g_pSDMsgListDlg;
extern CP36AlarmRecordDlg*		g_pAlarmRecordDlg;
extern CP36AlarmRecordInfoDlg*	g_pAlarmRecordInfoDlg;
extern CP36LocateRecordDlg*		g_pLocateRecordDlg;
extern CP36LocateRecordInfoDlg*	g_pLocateRecordInfoDlg;
extern CP36RxMsgRecordDlg*		g_pRxMsgRecordDlg;
extern CP36RxMsgRecordInfoDlg*	g_pRxMsgRecordInfoDlg;
extern CP36TxMsgRecordDlg*		g_pTxMsgRecordDlg;
extern CP36TxMsgRecordInfoDlg*	g_pTxMsgRecordInfoDlg;
extern CP36HistoryRecordDlg*	g_pHistoryRecordDlg;
extern CP36LogoDlg*             g_pLogoDlg;
extern CP36BugAnalyseDlg*       g_pBugAnalyseDlg;
extern CP36OperateDescribeDlg*  g_pOperateDescribeDlg;
extern CP36SoftVersionDlg*		g_pSoftVersionDlg;
extern CP36WorkSetDlg*          g_pWorkSetDlg;
extern CP36BattSetDlg*          g_pBattSetDlg;
extern CP36CmdState*			g_pCmdState;
extern CP36TxAssemble*			g_pTxAssemble;
extern CP36RxMsgInfoDlg*        g_pRxMsgInfoDlg;
extern STATE_INFO				g_StateInfo;
extern CP36Database				g_Database;

#define COLOR_WHITE  RGB(255,255,255)
#define COLOR_BLACK  RGB(0,0,0)
#define COLOR_ORANGE RGB(255,128,0)
#define COLOR_RED    RGB(255,0,0)
#define COLOR_GREEN  RGB(0,255,0)
#define COLOR_SBLUE  RGB(175,225,225)
#define COLOR_GRAY   RGB(192,192,192)

#endif _P36Misc_h_