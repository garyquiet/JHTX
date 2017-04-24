#include "StdAfx.h"
#include "ProtocolPkg.h"

CProtocolPkg::CProtocolPkg(void)
{
}

CProtocolPkg::~CProtocolPkg(void)
{
}


//����Ԥ����Ϣ����
CString CProtocolPkg::CreatePRCFGPacket(CString cmd, CString cfgID, CString msgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, msgID, data);
	return pkg;
}


//����ָ�ӻ�վ����
CString CProtocolPkg::CreateIDCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//���������ű���
CString CProtocolPkg::CreateSNCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//��������ģʽ�л�ָ���
CString CProtocolPkg::CreateMDCFGPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID);
	return pkg;
}

//�����洢ָ���
CString CProtocolPkg::CreateSAVEPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID);
	return pkg;
}


//������ִ���
void CProtocolPkg::ParseANS(CString content){
	/*
	{�����óɹ�!��}
	{������ʧ��!��}
	{������ɹ�!��}
	{����ʼ���ɹ�!��}
	{��Ԥ����Ϣ��!��}
	{����Ϣ��ʽ����!��}

	*/

	/*
	{���ϱ���վ��XXXXXXX��}
	{��01.(��1��Ԥ����Ϣ)��}
	{��02.(��2��Ԥ����Ϣ)��}

	*/
}

//����ģʽ����
void CProtocolPkg::ParseMOD(CString content){
	/*
	{����ǰģʽ:xxxx��}
	{���л���:xxxxxx��}

	*/
}

//����ͬ������
void CProtocolPkg::ParseOUT(CString content){
	/*
	{��>>>hh:mm:ss,RNSSδ��λ��}
	{��>>>hh:mm:ss,RNSS�Ѷ�λ��������:xx�š�}
	*/
}