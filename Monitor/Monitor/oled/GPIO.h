#ifndef _GPIO_h_
#define _GPIO_h_

#define	GPIO0		(1 <<  0)
#define	GPIO1		(1 <<  1)
#define	GPIO2		(1 <<  2)
#define	GPIO3		(1 <<  3)
#define	GPIO4		(1 <<  4)
#define	GPIO5		(1 <<  5)
#define	GPIO6		(1 <<  6)
#define	GPIO7		(1 <<  7)
#define	GPIO8		(1 <<  8)
#define	GPIO9		(1 <<  9)
#define	GPIO10		(1 << 10)
#define	GPIO11		(1 << 11)
#define	GPIO12		(1 << 12)
#define	GPIO13		(1 << 13)
#define	GPIO14		(1 << 14)
#define	GPIO15		(1 << 15)
#define	GPIO16		(1 << 16)
#define	GPIO17		(1 << 17)
#define	GPIO18		(1 << 18)
#define	GPIO19		(1 << 19)
#define	GPIO20		(1 << 20)
#define	GPIO21		(1 << 21)
#define	GPIO22		(1 << 22)
#define	GPIO23		(1 << 23)
#define	GPIO24		(1 << 24)
#define	GPIO25		(1 << 25)
#define	GPIO26		(1 << 26)
#define	GPIO27		(1 << 27)
#define	GPIO28		(1 << 28)
#define	GPIO29		(1 << 29)
#define	GPIO30		(1 << 30)
#define	GPIO31		(1 << 31)

// Gpio IO Control Codes
#define GPIO_IOCTL_OUT_ENABLE			CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3900, METHOD_BUFFERED, FILE_ANY_ACCESS)  
#define GPIO_IOCTL_OUT_DISABLE			CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3901, METHOD_BUFFERED, FILE_ANY_ACCESS)  
#define GPIO_IOCTL_OUT_SET			    CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3902, METHOD_BUFFERED, FILE_ANY_ACCESS)  
#define GPIO_IOCTL_OUT_CLEAR			CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3903, METHOD_BUFFERED, FILE_ANY_ACCESS)  
#define GPIO_IOCTL_PIN_STATE			CTL_CODE(FILE_DEVICE_BUS_EXTENDER, 3904, METHOD_BUFFERED, FILE_ANY_ACCESS)  

class CGPIO
{
public:
	CGPIO(void);
	~CGPIO(void);

	/******************************************************************************/
	/*函数介绍：打开Gpio口，创建ISA流驱动句柄
	*入口参数:lpDevName:Gpio别名
	*出口参数：无
	*返回值：如果打开成功返回TRUE，否则返回FALSE*/
	BOOL GPIO_Open(LPCTSTR lpDevName);
	/******************************************************************************/

	/******************************************************************************/
	/*函数介绍：关闭Gpio口，关闭ISA流驱动句柄
	*入口参数:无
	*出口参数：无
	*返回值：如果关闭成功返回TRUE，否则返回FALSE*/
    BOOL GPIO_Close();
	/******************************************************************************/

	/******************************************************************************/
	/*函数介绍：将Gpio口设置为输出口
	*入口参数:dwEnBits:输出控制位设为1
	*出口参数：无
	*返回值：如果设置成功返回TRUE，否则返回FALSE*/
    BOOL GPIO_OutEnable(unsigned int dwEnBits);
	/******************************************************************************

	/******************************************************************************
	/*函数介绍：将Gpio口设置为输入口
	*入口参数:dwDisBits:输入控制位设为1
	*出口参数：无
	*返回值：如果设置成功返回TRUE，否则返回FALSE*/
    BOOL GPIO_OutDisable(unsigned int dwDisBits);
	/******************************************************************************/

	/******************************************************************************/
	/*函数介绍：设置Gpio口输出电平为高
	*入口参数:dwSetBits:输出电平位设为1
	*出口参数：无
	*返回值：如果设置成功返回TRUE，否则返回FALSE*/
    BOOL GPIO_OutSet(unsigned int dwSetBits);
	/******************************************************************************/

	/******************************************************************************/
	/*函数介绍：设置Gpio口输出电平为低
	*入口参数:dwClearBits:输出电平位设为0
	*出口参数：无
	*返回值：如果设置成功返回TRUE，否则返回FALSE*/
    BOOL GPIO_OutClear(unsigned int dwClearBits);
	/******************************************************************************/

	/******************************************************************************/
	/*函数介绍：读取输入Gpio口电平
	*出口参数：pPinState:返回值指针
	*返回值：读取的电平为高返回TRUE，否则返回FALSE*/
    BOOL GPIO_PinState(unsigned int* pPinState);
	/******************************************************************************/

protected:
	
	HANDLE m_hGPIO;
};

#endif _CGIPO_h