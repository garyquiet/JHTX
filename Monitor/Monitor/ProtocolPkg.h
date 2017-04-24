#pragma once

#include "const.h"

class CProtocolPkg
{
public:
	CProtocolPkg(void);
	~CProtocolPkg(void);

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


public:
	//������ִ���
	static void ParseANS(CString content);

	//����ģʽ����
	static void ParseMOD(CString content);

	//����ͬ������
	static void ParseOUT(CString content);
};
