#ifndef _P36CmdMisc_h_
#define _P36CmdMisc_h_

/********************************************************/
//֡�������ֽ�����λ��
#define SOF_DEF_AT			0x00	//֡��ʼ�ֽ�λ��
#define LOF_DEF_AT			0x01	//֡�����ֽ�λ��
#define TOF_DEF_AT			0x02	//֡�����ֽ�λ��
#define COF_DEF_AT			0x03	//֡����Ĭ��λ��
#define POF_DEF_AT			0x03	//֡У��Ĭ��λ��

#define SOF_DEF_VAL			0x26	//Ĭ��֡ͷ�ֽ�0x26

//��Ϣ�����ֳ��ȶ���
#define COF_LEN_MAX			0xFB	//֡������󳤶�251�ֽ�
#define LOF_LEN_MAX			0xFF	//֡��󳤶�255�ֽ�
#define LOF_LEN_MIN			0x04	//֡��С����4�ֽ�
/********************************************************/

/********************************************************/
//�ն�������ʾλ�����ָ������
#define T2B_CMD_WSZL		0x01	//����ָ��
#define T2B_CMD_CSXX		0x03	//��ʼ��Ϣ
#define T2B_CMD_ZJZL		0x05	//�Լ�ָ��
#define T2B_CMD_DCJC		0x07	//��ؼ��
#define T2B_CMD_VHF_KBZL	0x0F	//����VHF״̬--�򿪻�ر�
#define T2B_CMD_VHF_PTT		0x13	//����VHF PTT--��������
#define T2B_CMD_VHF_SZPD	0x15	//����VHFƵ������
#define T2B_CMD_ZDSJ		0x17	//��ѯ��ǰʱ�䣨�ն�ϵͳʱ�䣩
#define T2B_CMD_WZXX		0x19	//��ѯ��ǰλ�ã��ն��˹����룩
#define T2B_CMD_ZHZL		0x1B	//ϵͳ�Ի�
#define T2B_CMD_BWZL		0x1D	//������Ϣ
#define T2B_CMD_DWZL		0x1F	//���Ƕ�λ   
#define T2B_CMD_BJZL		0x23	//����ϵͳ����
#define T2B_CMD_YXXZ		0x25	//�����������ʹ��ܴ���
#define T2B_CMD_SSZL		0x27	//������ʱָ��
#define T2B_CMD_BD1_GLCS	0x81	//����ͨ��ģ�鹦�ʲ���
#define T2B_CMD_BD1_WMCS	0x83	//����ͨ��ģ���������
#define T2B_CMD_VHF_XLJC	0x85	//DSC�������м��
#define T2B_CMD_DCSZ        0x93	//�����Ϣ����ָ��
#define T2B_CMD_GZMS        0x0B    //����ģʽ����ָ��

//����ʾλ�����ն˿���ָ������
#define B2T_CMD_ZJXX		0x06	//�豸�Լ����
#define B2T_CMD_DCXX	    0x08	//��ص�������
#define B2T_CMD_CXSJ        0x16	//��ѯ�ն˵�ǰʱ��
#define B2T_CMD_CXWZ	    0x18	//��ѯ��ǰλ��
#define B2T_CMD_ZHOK	    0x1C	//ϵͳ�Ի��ɹ�
#define B2T_CMD_BWOK	    0x1E	//������������ȷ��
#define B2T_CMD_BJOK	    0x24	//��������
#define B2T_BD1_GLZK	    0x30	//��������״��
#define B2T_BD1_TXXX	    0x32	//����ͨ����Ϣ
#define B2T_BD1_DWXX	    0x34	//����λ����Ϣ
#define B2T_BD1_SJXX	    0x36	//����ʱ����Ϣ
#define B2T_BD1_ICXX        0x38	//����IC��Ϣ
#define B2T_CMD_BD1_WMXX    0x84	//����ģ��������Խ��
#define B2T_CMD_ACK         0xA0	//�����ն�ָ����ȷ
#define B2T_CMD_NAK         0xA1	//�����ն�ָ�����
#define B2T_CMD_DWSQ_OK     0xB0	//���Ͷ�λ����ɹ�
#define B2T_CMD_DWSQ_FAIL   0xB1	//���Ͷ�λ����ʧ��
#define B2T_CMD_TXSQ_OK     0xB2	//����ͨ������ɹ�
#define B2T_CMD_TXSQ_FAIL   0xB3	//����ͨ������ʧ��
#define B2T_CMD_SJSC_OK     0xB4	//����ʱ������ɹ�
#define B2T_CMD_SJSC_FAIL   0xB5	//����ʱ�����ʧ��
#define B2T_CMD_TXSQ_BK     0xB6	//���跢�͵ı��ݱ�����Ϣ
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

//����֡��������
#define CMD_TRIGTYPE_AUTO	FALSE		//�Զ�����
#define CMD_TRIGTYPE_HAND	TRUE		//�ֶ�����

//����֡������Ϣ��ʾ
#define CMD_DISPTYPE_HIDE	FALSE		//��ʾ��Ϣ����
#define CMD_DISPTYPE_SHOW	TRUE		//��ʾ��Ϣ��ʾ

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
	CMD_STATE csWSZL;		//����ָ��
	CMD_STATE csCSXX;		//��ʼ��Ϣ
	CMD_STATE csZJZL;		//�Լ�ָ��
	CMD_STATE csDCJC;		//��ؼ��ָ��
	CMD_STATE csGZMS;		//�ŵ�����ģʽ
	CMD_STATE csBDKB;		//����ģ�鿪��ָ�� 
	CMD_STATE csVHFKB;		//VHFģ�鿪��ָ��
	CMD_STATE csVHFPTT;		//PTT����ָ��
	CMD_STATE csVHFSZPD;	//VHFƵ������ָ��
	CMD_STATE csZDSJ;		//�ն�ʱ��ָ��
	CMD_STATE csWZXX;		//�˹�λ����Ϣָ��
	CMD_STATE csZHZL;		//�Ի�ָ��
	CMD_STATE csBWZL;		//����ָ��
	CMD_STATE csDWZL;		//��λָ��
	CMD_STATE csBJZL;		//����ָ��
	CMD_STATE csYXXZ;		//������������ָ��
	CMD_STATE csSSZL;		//��ʱָ��
	CMD_STATE csGLCS;		//���ʲ���ָ��
	CMD_STATE csWMCS;		//�������ָ��
	CMD_STATE csXLJC;		//DSC���м��ָ��
	CMD_STATE csDCSZ;		//�����Ϣ����ָ��	
}BUOY_CMD;

#endif _P36CmdMisc_h_