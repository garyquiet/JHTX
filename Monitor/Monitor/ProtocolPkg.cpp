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

//查找字符
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

//查找字符
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



//创建预置信息报文
CString CProtocolPkg::CreatePRCFGPacket(CString cmd, CString cfgID, CString msgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, msgID, data);
	return pkg;
}


//创建指挥基站报文
CString CProtocolPkg::CreateIDCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//创建特殊编号报文
CString CProtocolPkg::CreateSNCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//创建工作模式切换指令报文
CString CProtocolPkg::CreateMDCFGPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s\r\n", cmd, cfgID);
	return pkg;
}

//创建存储指令报文
CString CProtocolPkg::CreateSAVEPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s\r\n", cmd, cfgID);
	return pkg;
}


//发送预置信息报文
DWORD CProtocolPkg::SendPRCFGPacket(CString cmd, CString cfgID, CString msgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreatePRCFGPacket(cmd, cfgID, msgID, data);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送指挥基站报文
DWORD CProtocolPkg::SendIDCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateIDCFGPacket(cmd, cfgID, data);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送特殊编号报文
DWORD CProtocolPkg::SendSNCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSNCFGPacket(cmd, cfgID, data);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送工作模式切换指令报文
DWORD CProtocolPkg::SendMDCFGPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateMDCFGPacket(cmd, cfgID);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送存储指令报文
DWORD CProtocolPkg::SendSAVEPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSAVEPacket(cmd, cfgID);
	char buf[SND_BUFFER_SIZE];
	buf[wcstombs(buf, pkg, SND_BUFFER_SIZE - 1)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}


//解析回执语句
CString CProtocolPkg::ParseANS(int type, CString content){
	CString str = L"";
	
	switch (type)
	{
	case 1://一般信息回执
		/*
		{“设置成功!”}
		{“设置失败!”}
		{“保存成功!”}
		{“初始化成功!”}
		{“预置信息空!”}
		{“信息格式错误!”}
		*/
		{
			//int begin = content.Find("第");
			//int end = content.Find('”');

			/*int begin = search(content, L"“");
			int end = search(content, L"”");
			CString info = content.Mid(begin + 1, end - begin - 1);
			str = info;*/
			str = content;
		}
		break;
	case 2: //中心号码查询回执
		/*
		{“上报基站：XXXXXXX”}
		*/
		{
			
			/*int begin = search(content,L"“");
			int end = search(content, L"”");
			CString info = content.Mid(begin + 1, end - begin - 1);*/
			
			CString info = content;

			int index = search(info, L"：");
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
		{“01.(第1条预置信息)”}
		{“02.(第2条预置信息)”}
		*/
		{

		}
		break;
	default:
		break;
	}

	return str;
}

//解析查询返回的预置信息
map<CString,CString> CProtocolPkg::ParsePresetInfo(CString content){
	/*
		{“01.(第1条预置信息)”}
		{“02.(第2条预置信息)”}
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

//解析模式报告
CString CProtocolPkg::ParseMOD(CString content){
	/*
	{“当前模式:xxxx”}
	{“切换至:xxxxxx”}
	*/


	CString str = L"";
	
	/*int begin = -1, end = -1;
	
	begin = search(content, L"“");
	if(begin == -1){
		begin = search(content, L"\"");
		end = search(content, L"\"", begin + 1);
	}
	else{
		end = search(content, L"”");
	}

	CString info = content.Mid(begin + 1, end - begin - 1);
	str = info;*/

	str =  content;

	return str;
}

//解析同步报文
CString CProtocolPkg::ParseOUT(CString content){
	/*
	{“>>>hh:mm:ss,RNSS未定位”}
	{“>>>hh:mm:ss,RNSS已定位，卫星数:xx颗”}
	*/
	CString str = L"";
	return str;
}

//判断是否是数字
BOOL CProtocolPkg::isNumber(TCHAR ch){
	return isdigit(ch);
}

//判断是否是汉字
BOOL CProtocolPkg::isHanZi(TCHAR ch)
{
	return ch > 255;
}

//判断是否全是数字
BOOL CProtocolPkg::isAllNumber(CString input){
	input = input.Trim();
	for (int i = 0; i < input.GetLength(); ++i)
	{
		if( false == isNumber(input.GetAt(i)))
			return FALSE;
	}
	return TRUE;
}

//判断是否全是汉字
BOOL CProtocolPkg::isAllHanZi(CString input){
	input = input.Trim();
	for (int i = 0; i < input.GetLength(); ++i)
	{
		if( false == isHanZi(input.GetAt(i)))
			return FALSE;
	}
	return TRUE;
}


//剔除字符串中非数字的字符
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

//剔除字符串中非汉字的字符
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



//启动输入
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

//切换输入法
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

//隐藏输入法
void CProtocolPkg::HideInputMethd(){}

//停止输入法
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