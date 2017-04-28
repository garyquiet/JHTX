
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
//����Э��
#define PRCFG	L"$PRCFG"				//Ԥ����Ϣ����ָ��
#define IDCFG	L"$IDCFG"				//ָ�ӻ�վ����ָ��
#define SNCFG	L"$SNCFG"				//����������ָ��
#define MDCFG	L"$MDCFG"				//����ģʽ�л�ָ��
#define SAVE	L"$SAVE"					//�洢ָ��

#define ANY					L"-1"		//����ֵ

#define PRCFG_CfgID_QUERY	L"1"			//��ѯ��ǰ�豸Ԥ����Ϣ
#define PRCFG_CfgID_ADD		L"2"			//����һ��Ԥ����Ϣ
#define PRCFG_CfgID_MODIFY	L"3"			//����ĳ��Ԥ����Ϣ
#define PRCFG_CfgID_DELETE	L"4"			//ɾ��ĳ��Ԥ����Ϣ

#define IDCFG_CfgID_QUERY	L"1"			//��ѯ��ǰ���ĺ���
#define IDCFG_CfgID_SET		L"2"			//�������ĺ���

#define SNCFG_CfgID_QUERY	L"1"			//��ѯ��ǰ������
#define SNCFG_CfgID_SET		L"2"			//����������


#define MDCFG_CfgID_QUERY	L"1"			//��ѯ��ǰ�豸����ģʽ
#define MDCFG_CfgID_MODE1	L"2"			//�л�ģʽ����Ъ����ģʽ
#define MDCFG_CfgID_MODE2	L"3"			//�л�ģʽ����������ģʽ
#define MDCFG_CfgID_MODE3	L"4"			//�л�ģʽ���ͺĹ���ģʽ
#define MDCFG_CfgID_MODE4	L"5"			//�л�ģʽ����עģʽ
#define MDCFG_CfgID_MODE5	L"6"			//�л�ģʽ������ģʽ


#define SAVE_CfgID_1		L"1"			//�ָ���������
#define SAVE_CfgID_2		L"2"			//������ǰ�������ò�����
#define SAVE_CfgID_3		L"3"			//��ʼ��������ʾ
#define SAVE_CfgID_4		L"4"			//��ʼ��ͨ������
