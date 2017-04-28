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

//�����ַ�
int CProtocolPkg::search(CString source, CString ch){

	for (int i = 0; i < source.GetLength(); ++i)
	{
		TCHAR tc = source.GetAt(i);
		CString tmp = L"";
		tmp.Format(L"%c", tc);

		if( ch == tmp ){
			return i;
		}
	}

	return -1;
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
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//����ָ�ӻ�վ����
DWORD CProtocolPkg::SendIDCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateIDCFGPacket(cmd, cfgID, data);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���������ű���
DWORD CProtocolPkg::SendSNCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSNCFGPacket(cmd, cfgID, data);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���͹���ģʽ�л�ָ���
DWORD CProtocolPkg::SendMDCFGPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateMDCFGPacket(cmd, cfgID);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//���ʹ洢ָ���
DWORD CProtocolPkg::SendSAVEPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSAVEPacket(cmd, cfgID);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}


//������ִ���
CString CProtocolPkg::ParseANS(int type, CString content){
	CString str = L"";
	
	switch (type)
	{
	case 1://һ����Ϣ��ִ
		/*
		{�����óɹ�!��}
		{������ʧ��!��}
		{������ɹ�!��}
		{����ʼ���ɹ�!��}
		{��Ԥ����Ϣ��!��}
		{����Ϣ��ʽ����!��}
		*/
		{
			//int begin = content.Find("��");
			//int end = content.Find('��');
			int begin = search(content, L"��");
			int end = search(content, L"��");
			CString info = content.Mid(begin + 1, end - begin - 1);
			str = info;
		}
		break;
	case 2: //���ĺ����ѯ��ִ
		/*
		{���ϱ���վ��XXXXXXX��}
		*/
		{
			/*int begin = content.Find('��');
			int end = content.Find('��');*/
			int begin = search(content,L"��");
			int end = search(content, L"��");
			CString info = content.Mid(begin + 1, end - begin - 1);

			//int index = info.Find('��');
			int index = search(info, L"��");
			str = info.Right(info.GetLength() - index - 1);
		}
		
		break;
	case 3:
		/*
		{��01.(��1��Ԥ����Ϣ)��}
		{��02.(��2��Ԥ����Ϣ)��}
		*/
		{

		}
		break;
	default:
		break;
	}

	return str;
}

//������ѯ���ص�Ԥ����Ϣ
map<CString,CString> CProtocolPkg::ParsePresetInfo(CString content){
	map<CString, CString> dic;
	vector<CString> vs = SplitString(content, L"\r\n");

	for(vector<CString>::iterator it = vs.begin(); it != vs.end(); ++it){
		//int index = (*it).Find('.');
		int index = search((*it), L".");
		CString no = (*it).Mid(index - 2, 2);

		/*int begin = (*it).Find('(');
		int end = (*it).Find(')');*/
		int begin = search((*it), L"(");
		int end = search((*it), L")");
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