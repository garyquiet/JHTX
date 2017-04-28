
#define BAUD_RATE	115200
#define	COM_PORT	3

#define RCV_BUFFER_SIZE			650
#define SND_BUFFER_SIZE			100

#define TIMER_EVENT_DATETIME	1
#define	TIMER_EVENT_POWER		2
#define	TIME_INTERVAL_SENCOND		1000
#define	TIME_INTERVAL_MINUTE		60000
#define TIME_INTERVAL_FALF_MINUTE	30000

/*Communication Protocol*/
//接收协议
#define PRCFG	L"$PRCFG"				//预置信息设置指令
#define IDCFG	L"$IDCFG"				//指挥基站设置指令
#define SNCFG	L"$SNCFG"				//特殊编号设置指令
#define MDCFG	L"$MDCFG"				//工作模式切换指令
#define SAVE	L"$SAVE"					//存储指令

#define ANY					L"-1"		//任意值

#define PRCFG_CfgID_QUERY	L"1"			//查询当前设备预置信息
#define PRCFG_CfgID_ADD		L"2"			//增加一条预置信息
#define PRCFG_CfgID_MODIFY	L"3"			//覆盖某条预置信息
#define PRCFG_CfgID_DELETE	L"4"			//删除某条预置信息

#define IDCFG_CfgID_QUERY	L"1"			//查询当前中心号码
#define IDCFG_CfgID_SET		L"2"			//设置中心号码

#define SNCFG_CfgID_QUERY	L"1"			//查询当前特殊编号
#define SNCFG_CfgID_SET		L"2"			//设置特殊编号


#define MDCFG_CfgID_QUERY	L"1"			//查询当前设备工作模式
#define MDCFG_CfgID_MODE1	L"2"			//切换模式至间歇工作模式
#define MDCFG_CfgID_MODE2	L"3"			//切换模式至持续工作模式
#define MDCFG_CfgID_MODE3	L"4"			//切换模式至低耗工作模式
#define MDCFG_CfgID_MODE4	L"5"			//切换模式至加注模式
#define MDCFG_CfgID_MODE5	L"6"			//切换模式至测试模式


#define SAVE_CfgID_1		L"1"			//恢复所有设置
#define SAVE_CfgID_2		L"2"			//保留当前所有设置并保存
#define SAVE_CfgID_3		L"3"			//初始化电量显示
#define SAVE_CfgID_4		L"4"			//初始化通信设置
