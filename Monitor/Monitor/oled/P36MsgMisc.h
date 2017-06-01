#ifndef _P36MsgMisc_h_
#define _P36MsgMisc_h_

#define T9_INPUTTYPE_NUM				0				//T9数字输入模式
#define T9_INPUTTYPE_ENG				1				//T9英文输入模式
#define T9_INPUTTYPE_CHN				2				//T9汉字输入模式
#define T9_INPUTTYPE_BHZ				3				//T9笔画输入模式
#define T9_CHARTYPE_CHN					FALSE			//T9全角输入模式
#define T9_CHARTYPE_ENG					TRUE			//T9半角输入模式

//串口相关消息
#define WM_SCOMM_RX						WM_USER + 1		//收到来自串口数据消息
#define WM_FRAME_RX						WM_USER + 2     //收到来自串口数据帧消息 
#define WM_FRAME_TX						WM_USER + 3		//收到发往串口指令帧消息

#define WM_HANDLE_OK                    WM_USER + 8
#define WM_HANDLE_FAILED                WM_USER + 9

//刷新消息
#define WM_UPDATE_MSGERLIST				WM_USER + 21	//刷新收件人消息
#define WM_UPDATE_SDMSGLIST				WM_USER + 22	//刷新自定义报文消息
#define WM_UPDATE_SUPPLYMODE		    WM_USER + 23    //刷新供电显示消息
#define WM_UPDATE_SOUNDMODE             WM_USER + 24	//刷新功放模式显示消息
#define WM_SAVE_MSGER    				WM_USER + 25	//保存收件人索引行号消息
#define WM_ADD_MSG                      WM_USER + 26	//保存自定义报文索引消息
#define WM_UPDATE_MSGER                 WM_USER + 27
#define WM_UPDATE_ALARMRECORD           WM_USER + 28
#define WM_UPDATE_LOCATERECORD          WM_USER + 29
#define WM_UPDATE_RXMSGRECORD           WM_USER + 30
#define WM_UPDATE_TXMSGRECORD	        WM_USER + 31
#define WM_UPDATE_HISTORYRECORD		    WM_USER + 32

//公用对话框
#define WM_DESTROY_DLG                  WM_USER + 49
#define WM_CREATE_CMDACKDLG				WM_USER + 50	//创建指令确认对话框消息
#define WM_DESTROY_CMDACKDLG			WM_USER + 51	//销毁指令确认对话框消息
#define WM_CREATE_DELACKDLG			    WM_USER + 52	//创建确认对话框消息
#define WM_DESTROY_DELACKDLG		    WM_USER + 53	//销毁确认对话框消息
#define WM_CREATE_PWDACKDLG			    WM_USER + 54	//创建密码对话框消息
#define WM_DESTROY_PWDACKDLG			WM_USER + 55	//销毁密码对话框消息
#define WM_CMD_ACKED                    WM_USER + 56	//指令确认消息
#define WM_CMD_NACKED                   WM_USER + 57    //指令取消消息
#define WM_DEL_ACKED                    WM_USER + 58    //行为确认消息
#define WM_DEL_NACKED                   WM_USER + 59    //行为取消消息
#define WM_PWD_ACKED    		        WM_USER + 60    //密码确认消息
#define WM_PWD_NACKED                   WM_USER + 61    //密码取消消息
#define WM_CREATE_INFODLG				WM_USER + 62	//创建错误详情对话框消息
#define WM_DESTROY_INFODLG				WM_USER + 63	//销毁错误详情对话框消息
#define WM_CREATE_PWDSETDLG             WM_USER + 64   //创建密码设置对话框消息
#define WM_DESTROY_PWDSETDLG            WM_USER + 65   //销毁密码设置对话框消息

//主界面相关对话框创建
#define WM_CREATE_MODESELDLG            WM_USER + 100	//创建模式选择对话框消息
#define WM_DESTROY_MODESELDLG           WM_USER + 101	//销毁模式选择对话框消息
#define WM_CREATE_STATEBARDLG           WM_USER + 102	//创建状态栏对话框消息
#define WM_DESTROY_STATEBARDLG          WM_USER + 103	//销毁状态栏对话框消息
#define WM_CREATE_INFOBARDLG            WM_USER + 104	//创建消息提示对话框消息
#define WM_DESTROY_INFOBARDLG           WM_USER + 105	//销毁消息提示对话框消息
#define WM_CREATE_T9DLG                 WM_USER + 106	//创建T9输入法对话框消息
#define WM_DESTROY_T9DLG                WM_USER + 107	//销毁T9输入法对话框消息
#define WM_CREATE_MSGCOMMDLG			WM_USER + 108	//创建通信对话框消息
#define WM_DESTROY_MSGCOMMDLG			WM_USER + 109	//销毁通信对话框消息
#define WM_CREATE_DETECTDLG				WM_USER + 110	//创建检测对话框消息
#define WM_DESTROY_DETECTDLG			WM_USER + 111	//销毁检测对话框消息
#define WM_CREATE_SETDLG				WM_USER + 112	//创建设置对话框消息
#define WM_DESTROY_SETDLG				WM_USER + 113	//销毁设置对话框消息
#define WM_CREATE_HELPDLG				WM_USER + 114	//创建帮助对话框消息
#define WM_DESTROY_HELPDLG				WM_USER + 115	//销毁帮助对话框消息
#define WM_CREATE_QUERYDLG				WM_USER + 116   //创建查询对话框消息
#define WM_DESTROY_QUERYDLG				WM_USER + 117	//销毁查询对话框消息
#define WM_CREATE_ALARMDLG				WM_USER + 118	//创建一键报警对话框消息
#define WM_DESTROY_ALARMDLG				WM_USER + 119	//销毁一键报警对话框消息
#define WM_CREATE_VOLUMEDLG				WM_USER + 120	//创建音量对话框消息
#define WM_DESTROY_VOLUMEDLG			WM_USER + 121	//销毁音量对话框消息
#define WM_CREATE_LOGODLG               WM_USER + 122
#define WM_DESTROY_LOGODLG              WM_USER + 123
#define WM_CREATE_BUGANALYSEDLG         WM_USER + 124
#define WM_DESTROY_BUGANALYSEDLG        WM_USER + 125
#define WM_CREATE_OPERATEDESCRIBEDLG    WM_USER + 126
#define WM_DESTROY_OPERATEDESCRIBEDLG   WM_USER + 127
#define WM_CREATE_SOFTVERSIONDLG	    WM_USER + 128
#define WM_DESTROY_SOFTVERSIONDLG	    WM_USER + 129

#define WM_CREATE_SELFDETECTDLG		    WM_USER + 130	//创建自检详情对话框消息
#define WM_DESTROY_SELFDETECTDLG        WM_USER + 131	//销毁自检详情对话框消息
#define WM_CREATE_LOOPDETECTDLG 		WM_USER + 132	//创建自环详情对话框消息
#define WM_DESTROY_LOOPDETECTDLG		WM_USER + 133	//销毁自环详情对话框消息
#define WM_CREATE_BATTDETECTDLG			WM_USER + 134	//创建电池信息对话框消息
#define WM_DESTROY_BATTDETECTDLG		WM_USER + 135	//销毁电池信息对话框消息
#define WM_CREATE_LOCRECORDINFODLG		WM_USER + 136	//创建定位记录详情对话框消息
#define WM_DESTROY_LOCRECORDINFODLG		WM_USER + 137	//销毁定位记录详情对话框消息
#define WM_CREATE_ALMRECORDINFODLG		WM_USER + 138	//创建报警记录详情对话框消息
#define WM_DESTROY_ALMRECORDINFODLG		WM_USER + 139	//销毁报警记录详情对话框消息
#define WM_CREATE_RXMSGRECORDINFODLG	WM_USER + 140	//创建接收报文记录详情对话框消息
#define WM_DESTROY_RXMSGRECORDINFODLG	WM_USER + 141	//销毁接收报文记录详情对话框消息
#define WM_CREATE_TXMSGRECORDINFODLG	WM_USER + 142	//创建发送报文记录详情对话框消息
#define WM_DESTROY_TXMSGRECORDINFODLG	WM_USER + 143	//销毁发送报文记录详情对话框消息
#define WM_CREATE_TIMEDETECTDLG         WM_USER + 144	//创建卫星授时详情对话框消息
#define WM_DESTROY_TIMEDETECTDLG        WM_USER + 145	//销毁卫星授时详情对话框消息
#define WM_CREATE_CODEDETECTDLG         WM_USER + 146	//创建误码率详情对话框消息
#define WM_DESTROY_CODEDETECTDLG        WM_USER + 147   //销毁误码率详情对话框消息
#define WM_CREATE_WORKSETDLG            WM_USER + 148
#define WM_DESTROY_WORKSETDLG           WM_USER + 149
#define WM_CREATE_ALARMDETECTDLG        WM_USER + 150
#define WM_DESTROY_ALARMDETECTDLG       WM_USER + 151
#define WM_CREATE_LOCATEDETECTDLG       WM_USER + 152
#define WM_DESTROY_LOCATEDETECTDLG      WM_USER + 153

#define WM_SHOW_T9						WM_USER + 160	//显示T9输入法对话框消息
#define WM_HIDE_T9						WM_USER + 161	//隐藏T9输入法对话框消息
#define WM_SAVE_DLGINFO 				WM_USER + 162	//保存窗口句柄消息
#define WM_CLEAR_DLGINFO				WM_USER + 163	//清除窗口句柄消息
#define WM_T9SWITCH_DOWN				WM_USER + 164	//T9输入法切换键按下消息
#define WM_T9CHARTYPE_DOWN				WM_USER + 165	//T9输入法全/半角按键按下消息
#define WM_ENTER_ALARM                  WM_USER + 166   //报警倒计时启动消息
#define WM_CANCEL_ALARM                 WM_USER + 167   //报警倒计时取消消息

//报文通信相关对话框
#define WM_CREATE_MSGERDLG				WM_USER + 200	//创建收件人对话框消息
#define WM_DESTROY_MSGERDLG				WM_USER + 201	//销毁收件人对话框消息
#define WM_CREATE_NEWMSGDLG				WM_USER + 202	//创建报文对话框消息
#define WM_DESTROY_NEWMSGDLG			WM_USER + 203	//销毁报文对话框消息
#define WM_CREATE_SDMSGDLG				WM_USER + 204	//创建自定义报文对话框消息
#define WM_DESTROY_SDMSGDLG				WM_USER + 205	//销毁自定义报文对话框消息
#define WM_CREATE_PSMSGDLG				WM_USER + 206	//创建预置报文对话框消息
#define WM_DESTROY_PSMSGDLG				WM_USER + 207	//销毁预置报文对话框消息

#define WM_CREATE_CREATEMSGERDLG		WM_USER + 215	//创建编辑收件人对话框消息
#define WM_DESTROY_CREATEMSGERDLG		WM_USER + 216	//销毁编辑收件人对话框消息
#define WM_CREATE_CHNMSGDLG				WM_USER + 230	//创建汉字报文对话框消息
#define WM_DESTROY_CHNMSGDLG			WM_USER + 231	//销毁汉字报文对话框消息
#define WM_CREATE_NUMMSGDLG				WM_USER + 232	//创建数字报文对话框消息
#define WM_DESTROY_NUMMSGDLG			WM_USER + 233	//销毁数字报文对话框消息
#define WM_CREATE_EDITSDMSGDLG			WM_USER + 245	//创建编辑自定义报文对话框消息
#define WM_DESTROY_EDITSDMSGDLG			WM_USER + 246	//销毁编辑自定义报文对话框消息
#define WM_CREATE_MSGERLISTDLG          WM_USER + 247
#define WM_DESTROY_MSGERLISTDLG         WM_USER + 248
#define WM_CREATE_PSMSGLISTDLG          WM_USER + 249
#define WM_DESTROY_PSMSGLISTDLG         WM_USER + 250
#define WM_CREATE_CREATESDMSGDLG        WM_USER + 251
#define WM_DESTROY_CREATESDMSGDLG       WM_USER + 252
#define WM_CREATE_SDMSGLISTDLG          WM_USER + 253
#define WM_DESTROY_SDMSGLISTDLG         WM_USER + 254
#define WM_CREATE_ALARMRECORDDLG        WM_USER + 255
#define WM_DESTROY_ALARMRECORDDLG       WM_USER + 256
#define WM_CREATE_ALARMRECORDINFODLG    WM_USER + 257
#define WM_DESTROY_ALARMRECORDINFODLG   WM_USER + 258
#define WM_CREATE_LOCATERECORDDLG       WM_USER + 259
#define WM_DESTROY_LOCATERECORDDLG      WM_USER + 260
#define WM_CREATE_LOCATERECORDINFODLG   WM_USER + 261
#define WM_DESTROY_LOCATERECORDINFODLG  WM_USER + 262
#define WM_CREATE_HISTORYRECORDDLG      WM_USER + 263
#define WM_DESTROY_HISTORYRECORDDLG     WM_USER + 264
#define WM_CREATE_RXMSGINFODLG          WM_USER + 265
#define WM_DESTROY_RXMSGINFODLG         WM_USER + 266

//检测相关对话框
#define WM_CREATE_WORKDETECTDLG		    WM_USER + 300	//创建工厂检测对话框消息
#define WM_DESTROY_WORKDETECTDLG		WM_USER + 301	//销毁工厂检测对话框消息

//设置相关对话框
#define WM_CREATE_INITSETDLG			WM_USER + 400	//创建用户设置对话框消息
#define WM_DESTROY_INITSETDLG			WM_USER + 401	//销毁用户设置对话框消息
#define WM_CREATE_WORKSSETDLG			WM_USER + 402	//创建工厂设置对话框消息
#define WM_DESTROY_WORKSSETDLG			WM_USER + 403	//销毁工厂设置对话框消息
#define WM_CREATE_TIMESETDLG			WM_USER + 404	//创建时间设置对话框消息
#define WM_DESTROY_TIMESETDLG			WM_USER + 405	//销毁时间设置对话框消息
#define WM_CREATE_VHFSETDLG				WM_USER + 406   //创建VHF设置对话框消息
#define WM_DESTROY_VHFSETDLG			WM_USER + 407	//销毁VHF设置对话框消息
#define WM_CREATE_TUDESETDLG			WM_USER + 408   //创建经纬度设置对话框消息
#define WM_DESTROY_TUDESETDLG			WM_USER + 409	//销毁经纬度设置对话框消息
#define WM_CREATE_INFOMANAGEDLG			WM_USER + 415	//创建管信对话框消息
#define WM_DESTROY_INFOMANAGEDLG		WM_USER + 416	//销毁管信对话框消息
#define WM_CREATE_BATTSETDLG			WM_USER + 417	//创建电池设置对话框消息
#define WM_DESTROY_BATTSETDLG			WM_USER + 418	//销毁电池设置对话框消息
#define WM_CREATE_CODESETDLG			WM_USER + 419	//创建电池设置对话框消息
#define WM_DESTROY_CODESETDLG			WM_USER + 420	//销毁电池设置对话框消息

//帮助相关对话框
#define WM_CREATE_DEBUGDLG				WM_USER + 500	//创建故障分析对话框消息
#define WM_DESTROY_DEBUGDLG				WM_USER + 501	//销毁故障分析对话框消息
#define WM_CREATE_OPERSPECDLG			WM_USER + 502	//创建操作说明对话框消息
#define WM_DESTROY_OPERSPECDLG			WM_USER + 503	//销毁操作说明对话框消息
#define WM_CREATE_VERSIONDLG			WM_USER + 504	//创建软件版本对话框消息
#define WM_DESTROY_VERSIONDLG			WM_USER + 505	//销毁软件版本对话框消息

//查询相关对话框
#define WM_CREATE_ALMRECORDDLG			WM_USER + 600	//创建报警记录对话框消息
#define WM_DESTROY_ALMRECORDDLG			WM_USER + 601	//销毁报警记录对话框消息
#define WM_CREATE_LOCRECORDDLG			WM_USER + 602	//创建定位记录对话框消息
#define WM_DESTROY_LOCRECORDDLG			WM_USER + 603	//销毁定位记录对话框消息
#define WM_CREATE_TXMSGRECORDDLG		WM_USER + 604	//创建发送报文记录对话框消息
#define WM_DESTROY_TXMSGRECORDDLG		WM_USER + 605	//销毁发送报文记录对话框消息
#define WM_CREATE_RXMSGRECORDDLG		WM_USER + 606	//创建接收报文记录对话框消息
#define WM_DESTROY_RXMSGRECORDDLG		WM_USER + 607	//销毁接收报文记录对话框消息

#define WM_SHOW_T9						WM_USER + 160	//显示T9输入法对话框消息
#define WM_HIDE_T9						WM_USER + 161	//隐藏T9输入法对话框消息
#define WM_SAVE_DLGINFO 				WM_USER + 162	//保存窗口句柄消息
#define WM_CLEAR_DLGINFO				WM_USER + 163	//清除窗口句柄消息
#define WM_T9SWITCH_DOWN				WM_USER + 164	//T9输入法切换键按下消息
#define WM_T9CHARTYPE_DOWN				WM_USER + 165	//T9输入法全/半角按键按下消息
#define WM_ENTER_ALARM                  WM_USER + 166   //报警倒计时启动消息
#define WM_CANCEL_ALARM                 WM_USER + 167   //报警倒计时取消消息

#define WM_LISTBOX_SELECTED             WM_USER + 168

#define WM_PREPARE_TXCMDPTT				WM_USER + 1000
#define WM_PREPARE_RXCMDPTT             WM_USER + 1001
#define WM_INCREASE_VOLUME              WM_USER + 1002
#define WM_DECREASE_VOLUME              WM_USER + 1003
#define WM_PREPARE_CMDALARM				WM_USER + 1004
#define WM_SUPPLYMODE_OUT               WM_USER + 1005
#define WM_SUPPLYMODE_BAT               WM_USER + 1006
#define WM_SOUNDMODE_SPEAKER            WM_USER + 1007
#define WM_SOUNDMODE_EARPHONE           WM_USER + 1008

#endif _P36MsgMisc_h_