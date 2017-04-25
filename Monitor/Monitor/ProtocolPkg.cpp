#include "StdAfx.h"
#include "ProtocolPkg.h"
#include "Monitor.h"

CProtocolPkg::CProtocolPkg(void)
{
}

CProtocolPkg::~CProtocolPkg(void)
{
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
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送指挥基站报文
DWORD CProtocolPkg::SendIDCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateIDCFGPacket(cmd, cfgID, data);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送特殊编号报文
DWORD CProtocolPkg::SendSNCFGPacket(CString cmd, CString cfgID, CString data){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSNCFGPacket(cmd, cfgID, data);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送工作模式切换指令报文
DWORD CProtocolPkg::SendMDCFGPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateMDCFGPacket(cmd, cfgID);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}

//发送存储指令报文
DWORD CProtocolPkg::SendSAVEPacket(CString cmd, CString cfgID){
	if (!theApp.m_Com.IsOpen())
		return -1;

	CString pkg = CreateSAVEPacket(cmd, cfgID);
	char buf[1024];
	buf[wcstombs(buf, pkg, 1023)] = 0;

	DWORD dwSend = theApp.m_Com.Write(buf);

	return dwSend;
}


//解析回执语句
void CProtocolPkg::ParseANS(CString content){
	/*
	{“设置成功!”}
	{“设置失败!”}
	{“保存成功!”}
	{“初始化成功!”}
	{“预置信息空!”}
	{“信息格式错误!”}

	*/

	/*
	{“上报基站：XXXXXXX”}
	{“01.(第1条预置信息)”}
	{“02.(第2条预置信息)”}

	*/
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