#include "StdAfx.h"
#include "ProtocolPkg.h"
#include "Monitor.h"

CProtocolPkg::CProtocolPkg(void)
{
}

CProtocolPkg::~CProtocolPkg(void)
{
}

vector<CString> CProtocolPkg::SplitString(CString strSource, CString split)  
{  
	vector <CString> vecString;
	int iPos = 0;
	CString strTmp;
	strTmp = strSource.Tokenize(split,iPos);
	while(strTmp.Trim() != _T(""))
	{
		vecString.push_back(strTmp);
		strTmp = strSource.Tokenize(split,iPos);
	}
	return vecString;
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


//����Ԥ����Ϣ����
DWORD CProtocolPkg::SendPRCFGPacket(CString cmd, CString cfgID, CString msgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreatePRCFGPacket(cmd, cfgID, msgID, data);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//����ָ�ӻ�վ����
DWORD CProtocolPkg::SendIDCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateIDCFGPacket(cmd, cfgID, data);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���������ű���
DWORD CProtocolPkg::SendSNCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSNCFGPacket(cmd, cfgID, data);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���͹���ģʽ�л�ָ���
DWORD CProtocolPkg::SendMDCFGPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateMDCFGPacket(cmd, cfgID);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���ʹ洢ָ���
DWORD CProtocolPkg::SendSAVEPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSAVEPacket(cmd, cfgID);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}


//������ִ���
void CProtocolPkg::ParseANS(int type, CString content){
	
	switch (type)
	{
	case 1:
		/*
		{�����óɹ�!��}
		{������ʧ��!��}
		{������ɹ�!��}
		{����ʼ���ɹ�!��}
		{��Ԥ����Ϣ��!��}
		{����Ϣ��ʽ����!��}
		*/
		break;
	case 2:
		/*
		{���ϱ���վ��XXXXXXX��}
		*/
		break;
	case 3:
		/*
		{��01.(��1��Ԥ����Ϣ)��}
		{��02.(��2��Ԥ����Ϣ)��}
		*/
	default:
		break;
	}
}

//������ѯ���ص�Ԥ����Ϣ
map<CString,CString> CProtocolPkg::ParsePresetInfo(CString content){
	map<CString, CString> dic;
	vector<CString> vs = SplitString(content, L"\r\n");

	for(vector<CString>::iterator it = vs.begin(); it != vs.end(); ++it){
		int index = (*it).Find('.');
		CString no = (*it).Mid(index - 2, 2);

		int begin = (*it).Find('(');
		int end = (*it).Find(')');
		CString info = (*it).Mid(begin + 1, end - begin - 1);

		dic.insert(map<CString, CString>::value_type(no, info));
	}

	return dic;
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

//�ж��Ƿ�������
BOOL CProtocolPkg::isNumber(TCHAR ch){
	return isdigit(ch);
}

//�ж��Ƿ��Ǻ���
BOOL CProtocolPkg::isHanZi(TCHAR ch)
{
	return ch > 255;
}

//�ж��Ƿ�ȫ������
BOOL CProtocolPkg::isAllNumber(CString input){
	input = input.Trim();
	for (int i = 0; i < input.GetLength(); ++i)
	{
		if( false == isNumber(input.GetAt(i)))
			return FALSE;
	}
	return TRUE;
}

//�ж��Ƿ�ȫ�Ǻ���
BOOL CProtocolPkg::isAllHanZi(CString input){
	input = input.Trim();
	for (int i = 0; i < input.GetLength(); ++i)
	{
		if( false == isHanZi(input.GetAt(i)))
			return FALSE;
	}
	return TRUE;
}


//�޳��ַ����з����ֵ��ַ�
CString CProtocolPkg::eliminateNonNumber(CString input){
	input = input.Trim();

	CString str = L"";

	for (int i = 0; i < input.GetLength(); ++i)
	{
		TCHAR ch = input.GetAt(i);

		if( isNumber(ch))
		{
			str.AppendChar(ch);
		}
	}
	return str;
}

//�޳��ַ����зǺ��ֵ��ַ�
CString CProtocolPkg::eliminateNonHanZi(CString input){
	input = input.Trim();

	CString str = L"";

	for (int i = 0; i < input.GetLength(); ++i)
	{
		TCHAR ch = input.GetAt(i);

		if( isHanZi(ch))
		{
			str.AppendChar(ch);
		}
	}
	return str;
}