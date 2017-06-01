#ifndef _P36CmdMisc_h_
#define _P36CmdMisc_h_

/********************************************************/
//帧各部分字节索引位置
#define SOF_DEF_AT			0x00	//帧起始字节位置
#define LOF_DEF_AT			0x01	//帧长度字节位置
#define TOF_DEF_AT			0x02	//帧类型字节位置
#define COF_DEF_AT			0x03	//帧内容默认位置
#define POF_DEF_AT			0x03	//帧校验默认位置

#define SOF_DEF_VAL			0x26	//默认帧头字节0x26

//消息各部分长度定义
#define COF_LEN_MAX			0xFB	//帧内容最大长度251字节
#define LOF_LEN_MAX			0xFF	//帧最大长度255字节
#define LOF_LEN_MIN			0x04	//帧最小长度4字节
/********************************************************/

/********************************************************/
//终端至卫星示位标控制指令类型
#define T2B_CMD_WSZL		0x01	//握手指令
#define T2B_CMD_CSXX		0x03	//初始信息
#define T2B_CMD_ZJZL		0x05	//自检指令
#define T2B_CMD_DCJC		0x07	//电池检测
#define T2B_CMD_VHF_KBZL	0x0F	//设置VHF状态--打开或关闭
#define T2B_CMD_VHF_PTT		0x13	//设置VHF PTT--发射或接收
#define T2B_CMD_VHF_SZPD	0x15	//设置VHF频道号码
#define T2B_CMD_ZDSJ		0x17	//查询当前时间（终端系统时间）
#define T2B_CMD_WZXX		0x19	//查询当前位置（终端人工输入）
#define T2B_CMD_ZHZL		0x1B	//系统自环
#define T2B_CMD_BWZL		0x1D	//报文信息
#define T2B_CMD_DWZL		0x1F	//卫星定位   
#define T2B_CMD_BJZL		0x23	//启动系统报警
#define T2B_CMD_YXXZ		0x25	//设置遇险性质功能代码
#define T2B_CMD_SSZL		0x27	//卫星授时指令
#define T2B_CMD_BD1_GLCS	0x81	//卫星通信模块功率测试
#define T2B_CMD_BD1_WMCS	0x83	//卫星通信模块误码测试
#define T2B_CMD_VHF_XLJC	0x85	//DSC呼叫序列检测
#define T2B_CMD_DCSZ        0x93	//电池信息设置指令
#define T2B_CMD_GZMS        0x0B    //工作模式设置指令

//卫星示位标至终端控制指令类型
#define B2T_CMD_ZJXX		0x06	//设备自检情况
#define B2T_CMD_DCXX	    0x08	//电池电量数据
#define B2T_CMD_CXSJ        0x16	//查询终端当前时间
#define B2T_CMD_CXWZ	    0x18	//查询当前位置
#define B2T_CMD_ZHOK	    0x1C	//系统自环成功
#define B2T_CMD_BWOK	    0x1E	//岸基报文收妥确认
#define B2T_CMD_BJOK	    0x24	//岸基报警
#define B2T_BD1_GLZK	    0x30	//北斗功率状况
#define B2T_BD1_TXXX	    0x32	//北斗通信信息
#define B2T_BD1_DWXX	    0x34	//北斗位置信息
#define B2T_BD1_SJXX	    0x36	//北斗时间信息
#define B2T_BD1_ICXX        0x38	//北斗IC信息
#define B2T_CMD_BD1_WMXX    0x84	//卫星模块误码测试结果
#define B2T_CMD_ACK         0xA0	//接收终端指令正确
#define B2T_CMD_NAK         0xA1	//接收终端指令错误
#define B2T_CMD_DWSQ_OK     0xB0	//发送定位申请成功
#define B2T_CMD_DWSQ_FAIL   0xB1	//发送定位申请失败
#define B2T_CMD_TXSQ_OK     0xB2	//发送通信申请成功
#define B2T_CMD_TXSQ_FAIL   0xB3	//发送通信申请失败
#define B2T_CMD_SJSC_OK     0xB4	//发送时间输出成功
#define B2T_CMD_SJSC_FAIL   0xB5	//发送时间输出失败
#define B2T_CMD_TXSQ_BK     0xB6	//外设发送的备份报文信息
/********************************************************/

#define RX_MSGTYPE_CHN		0x40
#define RX_MSGTYPE_NUM		0x60
#define TX_MSGTYPE_CHN		0x44
#define TX_MSGTYPE_NUM		0x46

typedef enum
{
	FRAME_INVALID_PTR = 0x00,
	FRAME_INVALID_LOF = 0x01,
	FRAME_INVALID_TOF = 0x02,
	FRAME_INVALID_COF = 0x03,
	FRAME_HANDLE_OK   = 0x04,
	FRAME_HANDLE_FAIL = 0x05
}FRAME_STATE;

//发送帧触发类型
#define CMD_TRIGTYPE_AUTO	FALSE		//自动触发
#define CMD_TRIGTYPE_HAND	TRUE		//手动触发

//发送帧调试信息提示
#define CMD_DISPTYPE_HIDE	FALSE		//提示信息隐藏
#define CMD_DISPTYPE_SHOW	TRUE		//提示信息显示

typedef struct tagFRAME
{
	BYTE  bySOF;
	BYTE  byLOF;
	BYTE  byTOF;
	BYTE  abyCOF[COF_LEN_MAX];
	BYTE  byPOF;
}FRAME;

typedef enum
{
	CMD_IN_IDLE,
	CMD_WAIT_TOSEND,
	CMD_WAIT_TOACK,
	CMD_WAIT_RESULT,
}CMD_STATE;

typedef struct tagBUOY_CMD
{
	CMD_STATE csWSZL;		//握手指令
	CMD_STATE csCSXX;		//初始信息
	CMD_STATE csZJZL;		//自检指令
	CMD_STATE csDCJC;		//电池检测指令
	CMD_STATE csGZMS;		//信道工作模式
	CMD_STATE csBDKB;		//北斗模块开闭指令 
	CMD_STATE csVHFKB;		//VHF模块开闭指令
	CMD_STATE csVHFPTT;		//PTT设置指令
	CMD_STATE csVHFSZPD;	//VHF频道设置指令
	CMD_STATE csZDSJ;		//终端时间指令
	CMD_STATE csWZXX;		//人工位置信息指令
	CMD_STATE csZHZL;		//自环指令
	CMD_STATE csBWZL;		//报文指令
	CMD_STATE csDWZL;		//定位指令
	CMD_STATE csBJZL;		//报警指令
	CMD_STATE csYXXZ;		//遇险性质设置指令
	CMD_STATE csSSZL;		//授时指令
	CMD_STATE csGLCS;		//功率测试指令
	CMD_STATE csWMCS;		//误码测试指令
	CMD_STATE csXLJC;		//DSC序列检测指令
	CMD_STATE csDCSZ;		//电池信息设置指令	
}BUOY_CMD;

#endif _P36CmdMisc_h_