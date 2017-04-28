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


//创建预置信息报文
CString CProtocolPkg::CreatePRCFGPacket(CString cmd, CString cfgID, CString msgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, msgID, data);
	return pkg;
}


//创建指挥基站报文
CString CProtocolPkg::CreateIDCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//创建特殊编号报文
CString CProtocolPkg::CreateSNCFGPacket(CString cmd, CString cfgID, CString data){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID, data);
	return pkg;
}

//创建工作模式切换指令报文
CString CProtocolPkg::CreateMDCFGPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID);
	return pkg;
}

//创建存储指令报文
CString CProtocolPkg::CreateSAVEPacket(CString cmd, CString cfgID){
	CString pkg = L"";
	pkg.Format(L"%s,%s,%s,%s\r\n", cmd, cfgID);
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
			int begin = search(content, L"“");
			int end = search(content, L"”");
			CString info = content.Mid(begin + 1, end - begin - 1);
			str = info;
		}
		break;
	case 2: //中心号码查询回执
		/*
		{“上报基站：XXXXXXX”}
		*/
		{
			/*int begin = content.Find('“');
			int end = content.Find('”');*/
			int begin = search(content,L"“");
			int end = search(content, L"”");
			CString info = content.Mid(begin + 1, end - begin - 1);

			//int index = info.Find('：');
			int index = search(info, L"：");
			str = info.Right(info.GetLength() - index - 1);
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
void CProtocolPkg::ParseMOD(CString content){
	/*
	{“当前模式:xxxx”}
	{“切换至:xxxxxx”}

	*/
}

//解析同步报文
void CProtocolPkg::ParseOUT(CString content){
	/*
	{“>>>hh:mm:ss,RNSS未定位”}
	{“>>>hh:mm:ss,RNSS已定位，卫星数:xx颗”}
	*/
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