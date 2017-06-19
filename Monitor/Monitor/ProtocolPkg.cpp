#include "StdAfx.h"
#include "ProtocolPkg.h"
#include "Monitor.h"
#include <tlhelp32.h>
#include <winsock.h>

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

//�����ַ�
int CProtocolPkg::search(CString source, CString ch, int start){

	for (int i = start; i < source.GetLength(); ++i)
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
	pkg.Format(L"%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//���������ű���
CString CProtocolPkg::CreateSNCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//��������ģʽ�л�ָ���
CString CProtocolPkg::CreateMDCFGPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s\r\n", cmd, cfgID);
	return pkg;
}

//�����洢ָ���
CString CProtocolPkg::CreateSAVEPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s\r\n", cmd, cfgID);
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

			/*int begin = search(content, L"��");
			int end = search(content, L"��");
			CString info = content.Mid(begin + 1, end - begin - 1);
			str = info;*/
			str = content;
		}
		break;
	case 2: //���ĺ����ѯ��ִ
		/*
		{���ϱ���վ��XXXXXXX��}
		*/
		{
			
			/*int begin = search(content,L"��");
			int end = search(content, L"��");
			CString info = content.Mid(begin + 1, end - begin - 1);*/
			
			CString info = content;

			int index = search(info, L"��");
			if (index == -1)
			{
				index = search(info, L":");
				if (index != -1)
				{
					str = info.Right(info.GetLength() - index - 1);
				}
			}
			else
			{
				str = info.Right(info.GetLength() - index - 1);
			}
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
	/*
		{��01.(��1��Ԥ����Ϣ)��}
		{��02.(��2��Ԥ����Ϣ)��}
	*/

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
CString CProtocolPkg::ParseMOD(CString content){
	/*
	{����ǰģʽ:xxxx��}
	{���л���:xxxxxx��}
	*/


	CString str = L"";
	
	/*int begin = -1, end = -1;
	
	begin = search(content, L"��");
	if(begin == -1){
		begin = search(content, L"\"");
		end = search(content, L"\"", begin + 1);
	}
	else{
		end = search(content, L"��");
	}

	CString info = content.Mid(begin + 1, end - begin - 1);
	str = info;*/

	str =  content;

	return str;
}

//����ͬ������
CString CProtocolPkg::ParseOUT(CString content){
	/*
	{��>>>hh:mm:ss,RNSSδ��λ��}
	{��>>>hh:mm:ss,RNSS�Ѷ�λ��������:xx�š�}
	*/
	CString str = L"";
	return str;
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



//��������
BOOL CProtocolPkg::BootInputMethod(){
	char cmd[128];
	strcpy(cmd,"t9vs2008.exe");

	STARTUPINFO info;
	memset(&info,0,sizeof(info));
	info.cb=sizeof(info);
	PROCESS_INFORMATION pinfo;
	BOOL ret = CreateProcess((LPCWSTR) cmd, NULL, NULL,NULL,NULL,0,NULL,NULL,NULL,&pinfo);
	//BOOL ret = CreateProcess((LPCWSTR) cmd, L"t9vs2008.exe", NULL,NULL,NULL,0,NULL,NULL,NULL,&pinfo);
	//BOOL ret = CreateProcess(NULL,L"notepad.exe",NULL,NULL,FALSE,0,NULL,NULL,&info,&pinfo);
	return ret;
}

//�л����뷨
void CProtocolPkg::SwitchInputMethod(int type){
	int sockfd, port = 2014;
	struct sockaddr_in sin;
	int recv_size;
	char buf[16];

	memset(&sin,0 , sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(port);


	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return ;
	}

	if(connect(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		printf("continue, connect to %s:%d\n",inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
		closesocket(sockfd);
		//Sleep(100);
		//continue;
	}
	printf("success, connect to %s:%d\n",inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));

	struct timeval timeout={3,0};

	//if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, ( char * )&timeout, sizeof( timeout ) ) == -1)
	//{	
	//	printf("set socket option error ");
	//	net_close(sockfd);
	//}

	send(sockfd,(char*) &type, sizeof(type),0);
	closesocket(sockfd);
}

//�������뷨
void CProtocolPkg::HideInputMethd(){}

//ֹͣ���뷨
BOOL CProtocolPkg::KillInputMethod(){

	CString lpProcessName = _T("t9vs2008.exe");
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if(!Process32First(hSnapShot,&pe))
	{
		return FALSE;
	}
	CString strProcessName = lpProcessName;
	// strProcessName.MakeLower();
	while (Process32Next(hSnapShot,&pe))
	{
		CString scTmp = pe.szExeFile; 
		//  scTmp.MakeLower();
		if(scTmp==strProcessName)
		{
			DWORD dwProcessID = pe.th32ProcessID;
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);
			::TerminateProcess(hProcess,0);
			CloseHandle(hProcess);
			return TRUE;
		}
		// scTmp.ReleaseBuffer();
	}
	//strProcessName.ReleaseBuffer();
	return FALSE;
}