#pragma once

#include "const.h"

class CProtocolPkg
{
public:
	CProtocolPkg(void);
	~CProtocolPkg(void);

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


public:
	//解析回执语句
	static void ParseANS(CString content);

	//解析模式报告
	static void ParseMOD(CString content);

	//解析同步报文
	static void ParseOUT(CString content);
};
