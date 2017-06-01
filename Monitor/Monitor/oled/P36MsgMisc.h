#ifndef _P36MsgMisc_h_
#define _P36MsgMisc_h_

#define T9_INPUTTYPE_NUM				0				//T9��������ģʽ
#define T9_INPUTTYPE_ENG				1				//T9Ӣ������ģʽ
#define T9_INPUTTYPE_CHN				2				//T9��������ģʽ
#define T9_INPUTTYPE_BHZ				3				//T9�ʻ�����ģʽ
#define T9_CHARTYPE_CHN					FALSE			//T9ȫ������ģʽ
#define T9_CHARTYPE_ENG					TRUE			//T9�������ģʽ

//���������Ϣ
#define WM_SCOMM_RX						WM_USER + 1		//�յ����Դ���������Ϣ
#define WM_FRAME_RX						WM_USER + 2     //�յ����Դ�������֡��Ϣ 
#define WM_FRAME_TX						WM_USER + 3		//�յ���������ָ��֡��Ϣ

#define WM_HANDLE_OK                    WM_USER + 8
#define WM_HANDLE_FAILED                WM_USER + 9

//ˢ����Ϣ
#define WM_UPDATE_MSGERLIST				WM_USER + 21	//ˢ���ռ�����Ϣ
#define WM_UPDATE_SDMSGLIST				WM_USER + 22	//ˢ���Զ��屨����Ϣ
#define WM_UPDATE_SUPPLYMODE		    WM_USER + 23    //ˢ�¹�����ʾ��Ϣ
#define WM_UPDATE_SOUNDMODE             WM_USER + 24	//ˢ�¹���ģʽ��ʾ��Ϣ
#define WM_SAVE_MSGER    				WM_USER + 25	//�����ռ��������к���Ϣ
#define WM_ADD_MSG                      WM_USER + 26	//�����Զ��屨��������Ϣ
#define WM_UPDATE_MSGER                 WM_USER + 27
#define WM_UPDATE_ALARMRECORD           WM_USER + 28
#define WM_UPDATE_LOCATERECORD          WM_USER + 29
#define WM_UPDATE_RXMSGRECORD           WM_USER + 30
#define WM_UPDATE_TXMSGRECORD	        WM_USER + 31
#define WM_UPDATE_HISTORYRECORD		    WM_USER + 32

//���öԻ���
#define WM_DESTROY_DLG                  WM_USER + 49
#define WM_CREATE_CMDACKDLG				WM_USER + 50	//����ָ��ȷ�϶Ի�����Ϣ
#define WM_DESTROY_CMDACKDLG			WM_USER + 51	//����ָ��ȷ�϶Ի�����Ϣ
#define WM_CREATE_DELACKDLG			    WM_USER + 52	//����ȷ�϶Ի�����Ϣ
#define WM_DESTROY_DELACKDLG		    WM_USER + 53	//����ȷ�϶Ի�����Ϣ
#define WM_CREATE_PWDACKDLG			    WM_USER + 54	//��������Ի�����Ϣ
#define WM_DESTROY_PWDACKDLG			WM_USER + 55	//��������Ի�����Ϣ
#define WM_CMD_ACKED                    WM_USER + 56	//ָ��ȷ����Ϣ
#define WM_CMD_NACKED                   WM_USER + 57    //ָ��ȡ����Ϣ
#define WM_DEL_ACKED                    WM_USER + 58    //��Ϊȷ����Ϣ
#define WM_DEL_NACKED                   WM_USER + 59    //��Ϊȡ����Ϣ
#define WM_PWD_ACKED    		        WM_USER + 60    //����ȷ����Ϣ
#define WM_PWD_NACKED                   WM_USER + 61    //����ȡ����Ϣ
#define WM_CREATE_INFODLG				WM_USER + 62	//������������Ի�����Ϣ
#define WM_DESTROY_INFODLG				WM_USER + 63	//���ٴ�������Ի�����Ϣ
#define WM_CREATE_PWDSETDLG             WM_USER + 64   //�����������öԻ�����Ϣ
#define WM_DESTROY_PWDSETDLG            WM_USER + 65   //�����������öԻ�����Ϣ

//��������ضԻ��򴴽�
#define WM_CREATE_MODESELDLG            WM_USER + 100	//����ģʽѡ��Ի�����Ϣ
#define WM_DESTROY_MODESELDLG           WM_USER + 101	//����ģʽѡ��Ի�����Ϣ
#define WM_CREATE_STATEBARDLG           WM_USER + 102	//����״̬���Ի�����Ϣ
#define WM_DESTROY_STATEBARDLG          WM_USER + 103	//����״̬���Ի�����Ϣ
#define WM_CREATE_INFOBARDLG            WM_USER + 104	//������Ϣ��ʾ�Ի�����Ϣ
#define WM_DESTROY_INFOBARDLG           WM_USER + 105	//������Ϣ��ʾ�Ի�����Ϣ
#define WM_CREATE_T9DLG                 WM_USER + 106	//����T9���뷨�Ի�����Ϣ
#define WM_DESTROY_T9DLG                WM_USER + 107	//����T9���뷨�Ի�����Ϣ
#define WM_CREATE_MSGCOMMDLG			WM_USER + 108	//����ͨ�ŶԻ�����Ϣ
#define WM_DESTROY_MSGCOMMDLG			WM_USER + 109	//����ͨ�ŶԻ�����Ϣ
#define WM_CREATE_DETECTDLG				WM_USER + 110	//�������Ի�����Ϣ
#define WM_DESTROY_DETECTDLG			WM_USER + 111	//���ټ��Ի�����Ϣ
#define WM_CREATE_SETDLG				WM_USER + 112	//�������öԻ�����Ϣ
#define WM_DESTROY_SETDLG				WM_USER + 113	//�������öԻ�����Ϣ
#define WM_CREATE_HELPDLG				WM_USER + 114	//���������Ի�����Ϣ
#define WM_DESTROY_HELPDLG				WM_USER + 115	//���ٰ����Ի�����Ϣ
#define WM_CREATE_QUERYDLG				WM_USER + 116   //������ѯ�Ի�����Ϣ
#define WM_DESTROY_QUERYDLG				WM_USER + 117	//���ٲ�ѯ�Ի�����Ϣ
#define WM_CREATE_ALARMDLG				WM_USER + 118	//����һ�������Ի�����Ϣ
#define WM_DESTROY_ALARMDLG				WM_USER + 119	//����һ�������Ի�����Ϣ
#define WM_CREATE_VOLUMEDLG				WM_USER + 120	//���������Ի�����Ϣ
#define WM_DESTROY_VOLUMEDLG			WM_USER + 121	//���������Ի�����Ϣ
#define WM_CREATE_LOGODLG               WM_USER + 122
#define WM_DESTROY_LOGODLG              WM_USER + 123
#define WM_CREATE_BUGANALYSEDLG         WM_USER + 124
#define WM_DESTROY_BUGANALYSEDLG        WM_USER + 125
#define WM_CREATE_OPERATEDESCRIBEDLG    WM_USER + 126
#define WM_DESTROY_OPERATEDESCRIBEDLG   WM_USER + 127
#define WM_CREATE_SOFTVERSIONDLG	    WM_USER + 128
#define WM_DESTROY_SOFTVERSIONDLG	    WM_USER + 129

#define WM_CREATE_SELFDETECTDLG		    WM_USER + 130	//�����Լ�����Ի�����Ϣ
#define WM_DESTROY_SELFDETECTDLG        WM_USER + 131	//�����Լ�����Ի�����Ϣ
#define WM_CREATE_LOOPDETECTDLG 		WM_USER + 132	//�����Ի�����Ի�����Ϣ
#define WM_DESTROY_LOOPDETECTDLG		WM_USER + 133	//�����Ի�����Ի�����Ϣ
#define WM_CREATE_BATTDETECTDLG			WM_USER + 134	//���������Ϣ�Ի�����Ϣ
#define WM_DESTROY_BATTDETECTDLG		WM_USER + 135	//���ٵ����Ϣ�Ի�����Ϣ
#define WM_CREATE_LOCRECORDINFODLG		WM_USER + 136	//������λ��¼����Ի�����Ϣ
#define WM_DESTROY_LOCRECORDINFODLG		WM_USER + 137	//���ٶ�λ��¼����Ի�����Ϣ
#define WM_CREATE_ALMRECORDINFODLG		WM_USER + 138	//����������¼����Ի�����Ϣ
#define WM_DESTROY_ALMRECORDINFODLG		WM_USER + 139	//���ٱ�����¼����Ի�����Ϣ
#define WM_CREATE_RXMSGRECORDINFODLG	WM_USER + 140	//�������ձ��ļ�¼����Ի�����Ϣ
#define WM_DESTROY_RXMSGRECORDINFODLG	WM_USER + 141	//���ٽ��ձ��ļ�¼����Ի�����Ϣ
#define WM_CREATE_TXMSGRECORDINFODLG	WM_USER + 142	//�������ͱ��ļ�¼����Ի�����Ϣ
#define WM_DESTROY_TXMSGRECORDINFODLG	WM_USER + 143	//���ٷ��ͱ��ļ�¼����Ի�����Ϣ
#define WM_CREATE_TIMEDETECTDLG         WM_USER + 144	//����������ʱ����Ի�����Ϣ
#define WM_DESTROY_TIMEDETECTDLG        WM_USER + 145	//����������ʱ����Ի�����Ϣ
#define WM_CREATE_CODEDETECTDLG         WM_USER + 146	//��������������Ի�����Ϣ
#define WM_DESTROY_CODEDETECTDLG        WM_USER + 147   //��������������Ի�����Ϣ
#define WM_CREATE_WORKSETDLG            WM_USER + 148
#define WM_DESTROY_WORKSETDLG           WM_USER + 149
#define WM_CREATE_ALARMDETECTDLG        WM_USER + 150
#define WM_DESTROY_ALARMDETECTDLG       WM_USER + 151
#define WM_CREATE_LOCATEDETECTDLG       WM_USER + 152
#define WM_DESTROY_LOCATEDETECTDLG      WM_USER + 153

#define WM_SHOW_T9						WM_USER + 160	//��ʾT9���뷨�Ի�����Ϣ
#define WM_HIDE_T9						WM_USER + 161	//����T9���뷨�Ի�����Ϣ
#define WM_SAVE_DLGINFO 				WM_USER + 162	//���洰�ھ����Ϣ
#define WM_CLEAR_DLGINFO				WM_USER + 163	//������ھ����Ϣ
#define WM_T9SWITCH_DOWN				WM_USER + 164	//T9���뷨�л���������Ϣ
#define WM_T9CHARTYPE_DOWN				WM_USER + 165	//T9���뷨ȫ/��ǰ���������Ϣ
#define WM_ENTER_ALARM                  WM_USER + 166   //��������ʱ������Ϣ
#define WM_CANCEL_ALARM                 WM_USER + 167   //��������ʱȡ����Ϣ

//����ͨ����ضԻ���
#define WM_CREATE_MSGERDLG				WM_USER + 200	//�����ռ��˶Ի�����Ϣ
#define WM_DESTROY_MSGERDLG				WM_USER + 201	//�����ռ��˶Ի�����Ϣ
#define WM_CREATE_NEWMSGDLG				WM_USER + 202	//�������ĶԻ�����Ϣ
#define WM_DESTROY_NEWMSGDLG			WM_USER + 203	//���ٱ��ĶԻ�����Ϣ
#define WM_CREATE_SDMSGDLG				WM_USER + 204	//�����Զ��屨�ĶԻ�����Ϣ
#define WM_DESTROY_SDMSGDLG				WM_USER + 205	//�����Զ��屨�ĶԻ�����Ϣ
#define WM_CREATE_PSMSGDLG				WM_USER + 206	//����Ԥ�ñ��ĶԻ�����Ϣ
#define WM_DESTROY_PSMSGDLG				WM_USER + 207	//����Ԥ�ñ��ĶԻ�����Ϣ

#define WM_CREATE_CREATEMSGERDLG		WM_USER + 215	//�����༭�ռ��˶Ի�����Ϣ
#define WM_DESTROY_CREATEMSGERDLG		WM_USER + 216	//���ٱ༭�ռ��˶Ի�����Ϣ
#define WM_CREATE_CHNMSGDLG				WM_USER + 230	//�������ֱ��ĶԻ�����Ϣ
#define WM_DESTROY_CHNMSGDLG			WM_USER + 231	//���ٺ��ֱ��ĶԻ�����Ϣ
#define WM_CREATE_NUMMSGDLG				WM_USER + 232	//�������ֱ��ĶԻ�����Ϣ
#define WM_DESTROY_NUMMSGDLG			WM_USER + 233	//�������ֱ��ĶԻ�����Ϣ
#define WM_CREATE_EDITSDMSGDLG			WM_USER + 245	//�����༭�Զ��屨�ĶԻ�����Ϣ
#define WM_DESTROY_EDITSDMSGDLG			WM_USER + 246	//���ٱ༭�Զ��屨�ĶԻ�����Ϣ
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

//�����ضԻ���
#define WM_CREATE_WORKDETECTDLG		    WM_USER + 300	//�����������Ի�����Ϣ
#define WM_DESTROY_WORKDETECTDLG		WM_USER + 301	//���ٹ������Ի�����Ϣ

//������ضԻ���
#define WM_CREATE_INITSETDLG			WM_USER + 400	//�����û����öԻ�����Ϣ
#define WM_DESTROY_INITSETDLG			WM_USER + 401	//�����û����öԻ�����Ϣ
#define WM_CREATE_WORKSSETDLG			WM_USER + 402	//�����������öԻ�����Ϣ
#define WM_DESTROY_WORKSSETDLG			WM_USER + 403	//���ٹ������öԻ�����Ϣ
#define WM_CREATE_TIMESETDLG			WM_USER + 404	//����ʱ�����öԻ�����Ϣ
#define WM_DESTROY_TIMESETDLG			WM_USER + 405	//����ʱ�����öԻ�����Ϣ
#define WM_CREATE_VHFSETDLG				WM_USER + 406   //����VHF���öԻ�����Ϣ
#define WM_DESTROY_VHFSETDLG			WM_USER + 407	//����VHF���öԻ�����Ϣ
#define WM_CREATE_TUDESETDLG			WM_USER + 408   //������γ�����öԻ�����Ϣ
#define WM_DESTROY_TUDESETDLG			WM_USER + 409	//���پ�γ�����öԻ�����Ϣ
#define WM_CREATE_INFOMANAGEDLG			WM_USER + 415	//�������ŶԻ�����Ϣ
#define WM_DESTROY_INFOMANAGEDLG		WM_USER + 416	//���ٹ��ŶԻ�����Ϣ
#define WM_CREATE_BATTSETDLG			WM_USER + 417	//����������öԻ�����Ϣ
#define WM_DESTROY_BATTSETDLG			WM_USER + 418	//���ٵ�����öԻ�����Ϣ
#define WM_CREATE_CODESETDLG			WM_USER + 419	//����������öԻ�����Ϣ
#define WM_DESTROY_CODESETDLG			WM_USER + 420	//���ٵ�����öԻ�����Ϣ

//������ضԻ���
#define WM_CREATE_DEBUGDLG				WM_USER + 500	//�������Ϸ����Ի�����Ϣ
#define WM_DESTROY_DEBUGDLG				WM_USER + 501	//���ٹ��Ϸ����Ի�����Ϣ
#define WM_CREATE_OPERSPECDLG			WM_USER + 502	//��������˵���Ի�����Ϣ
#define WM_DESTROY_OPERSPECDLG			WM_USER + 503	//���ٲ���˵���Ի�����Ϣ
#define WM_CREATE_VERSIONDLG			WM_USER + 504	//��������汾�Ի�����Ϣ
#define WM_DESTROY_VERSIONDLG			WM_USER + 505	//��������汾�Ի�����Ϣ

//��ѯ��ضԻ���
#define WM_CREATE_ALMRECORDDLG			WM_USER + 600	//����������¼�Ի�����Ϣ
#define WM_DESTROY_ALMRECORDDLG			WM_USER + 601	//���ٱ�����¼�Ի�����Ϣ
#define WM_CREATE_LOCRECORDDLG			WM_USER + 602	//������λ��¼�Ի�����Ϣ
#define WM_DESTROY_LOCRECORDDLG			WM_USER + 603	//���ٶ�λ��¼�Ի�����Ϣ
#define WM_CREATE_TXMSGRECORDDLG		WM_USER + 604	//�������ͱ��ļ�¼�Ի�����Ϣ
#define WM_DESTROY_TXMSGRECORDDLG		WM_USER + 605	//���ٷ��ͱ��ļ�¼�Ի�����Ϣ
#define WM_CREATE_RXMSGRECORDDLG		WM_USER + 606	//�������ձ��ļ�¼�Ի�����Ϣ
#define WM_DESTROY_RXMSGRECORDDLG		WM_USER + 607	//���ٽ��ձ��ļ�¼�Ի�����Ϣ

#define WM_SHOW_T9						WM_USER + 160	//��ʾT9���뷨�Ի�����Ϣ
#define WM_HIDE_T9						WM_USER + 161	//����T9���뷨�Ի�����Ϣ
#define WM_SAVE_DLGINFO 				WM_USER + 162	//���洰�ھ����Ϣ
#define WM_CLEAR_DLGINFO				WM_USER + 163	//������ھ����Ϣ
#define WM_T9SWITCH_DOWN				WM_USER + 164	//T9���뷨�л���������Ϣ
#define WM_T9CHARTYPE_DOWN				WM_USER + 165	//T9���뷨ȫ/��ǰ���������Ϣ
#define WM_ENTER_ALARM                  WM_USER + 166   //��������ʱ������Ϣ
#define WM_CANCEL_ALARM                 WM_USER + 167   //��������ʱȡ����Ϣ

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