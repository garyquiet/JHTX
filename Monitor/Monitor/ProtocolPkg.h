#pragma once

#include "const.h"


class CProtocolPkg
{
public:
	CProtocolPkg(void);
	~CProtocolPkg(void);

private:

	

public:
	//�ж��Ƿ�������
	static BOOL isNumber(TCHAR ch);

	//�ж��Ƿ��Ǻ���
	static BOOL isHanZi(TCHAR ch);

	//�ж��Ƿ�ȫ������
	static BOOL isAllNumber(CString input);

	//�ж��Ƿ�ȫ�Ǻ���
	static BOOL isAllHanZi(CString input);

	//�޳��ַ����з����ֵ��ַ�
	static CString eliminateNonNumber(CString input);

	//�޳��ַ����зǺ��ֵ��ַ�
	static CString eliminateNonHanZi(CString input);


	//�����ַ�
	static int search(CString source, CString ch); 

	//�����ַ�
	static int search(CString source, CString ch, int start);


	//�ָ��ַ���
	static vector<CString> SplitString(CString strSource, CString split);

public:
	//����Ԥ����Ϣ����
	static CString CreatePRCFGPacket(CString cmd, CString cfgID, CString msgID = ANY, CString data = ANY);

	//����ָ�ӻ�վ����
	static CString CreateIDCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//���������ű���
	static CString CreateSNCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//��������ģʽ�л�ָ���
	static CString CreateMDCFGPacket(CString cmd, CString cfgID);

	//�����洢ָ���
	static CString CreateSAVEPacket(CString cmd, CString cfgID);


	//����Ԥ����Ϣ����
	static DWORD SendPRCFGPacket(CString cmd, CString cfgID, CString msgID = ANY, CString data = ANY);

	//����ָ�ӻ�վ����
	static DWORD SendIDCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//���������ű���
	static DWORD SendSNCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//���͹���ģʽ�л�ָ���
	static DWORD SendMDCFGPacket(CString cmd, CString cfgID);

	//���ʹ洢ָ���
	static DWORD SendSAVEPacket(CString cmd, CString cfgID);


public:
	//������ִ���
	static CString ParseANS(int type, CString content);

	//����ģʽ����
	static CString ParseMOD(CString content);

	//����ͬ������
	static CString ParseOUT(CString content);

	//������ѯ���ص�Ԥ����Ϣ
	static map<CString,CString> ParsePresetInfo(CString content);


	//���뷨
public:

	//��������
	static BOOL BootInputMethod();

	//�л����뷨
	static void SwitchInputMethod(int type);

	//�������뷨
	static void HideInputMethd();

	//ֹͣ���뷨
	static BOOL KillInputMethod();
};
