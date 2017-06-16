#pragma once

#include "const.h"


class CProtocolPkg
{
public:
	CProtocolPkg(void);
	~CProtocolPkg(void);

private:

	

public:
	//判断是否是数字
	static BOOL isNumber(TCHAR ch);

	//判断是否是汉字
	static BOOL isHanZi(TCHAR ch);

	//判断是否全是数字
	static BOOL isAllNumber(CString input);

	//判断是否全是汉字
	static BOOL isAllHanZi(CString input);

	//剔除字符串中非数字的字符
	static CString eliminateNonNumber(CString input);

	//剔除字符串中非汉字的字符
	static CString eliminateNonHanZi(CString input);


	//查找字符
	static int search(CString source, CString ch); 

	//查找字符
	static int search(CString source, CString ch, int start);


	//分割字符串
	static vector<CString> SplitString(CString strSource, CString split);

public:
	//创建预置信息报文
	static CString CreatePRCFGPacket(CString cmd, CString cfgID, CString msgID = ANY, CString data = ANY);

	//创建指挥基站报文
	static CString CreateIDCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//创建特殊编号报文
	static CString CreateSNCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//创建工作模式切换指令报文
	static CString CreateMDCFGPacket(CString cmd, CString cfgID);

	//创建存储指令报文
	static CString CreateSAVEPacket(CString cmd, CString cfgID);


	//发送预置信息报文
	static DWORD SendPRCFGPacket(CString cmd, CString cfgID, CString msgID = ANY, CString data = ANY);

	//发送指挥基站报文
	static DWORD SendIDCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//发送特殊编号报文
	static DWORD SendSNCFGPacket(CString cmd, CString cfgID, CString data = ANY);

	//发送工作模式切换指令报文
	static DWORD SendMDCFGPacket(CString cmd, CString cfgID);

	//发送存储指令报文
	static DWORD SendSAVEPacket(CString cmd, CString cfgID);


public:
	//解析回执语句
	static CString ParseANS(int type, CString content);

	//解析模式报告
	static CString ParseMOD(CString content);

	//解析同步报文
	static CString ParseOUT(CString content);

	//解析查询返回的预置信息
	static map<CString,CString> ParsePresetInfo(CString content);


	//输入法
public:

	//启动输入
	static BOOL BootInputMethod();

	//切换输入法
	static void SwitchInputMethod(int type);

	//隐藏输入法
	static void HideInputMethd();

	//停止输入法
	static BOOL KillInputMethod();
};
