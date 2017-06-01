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
	/*�������ܣ���Gpio�ڣ�����ISA���������
	*��ڲ���:lpDevName:Gpio����
	*���ڲ�������
	*����ֵ������򿪳ɹ�����TRUE�����򷵻�FALSE*/
	BOOL GPIO_Open(LPCTSTR lpDevName);
	/******************************************************************************/

	/******************************************************************************/
	/*�������ܣ��ر�Gpio�ڣ��ر�ISA���������
	*��ڲ���:��
	*���ڲ�������
	*����ֵ������رճɹ�����TRUE�����򷵻�FALSE*/
    BOOL GPIO_Close();
	/******************************************************************************/

	/******************************************************************************/
	/*�������ܣ���Gpio������Ϊ�����
	*��ڲ���:dwEnBits:�������λ��Ϊ1
	*���ڲ�������
	*����ֵ��������óɹ�����TRUE�����򷵻�FALSE*/
    BOOL GPIO_OutEnable(unsigned int dwEnBits);
	/******************************************************************************

	/******************************************************************************
	/*�������ܣ���Gpio������Ϊ�����
	*��ڲ���:dwDisBits:�������λ��Ϊ1
	*���ڲ�������
	*����ֵ��������óɹ�����TRUE�����򷵻�FALSE*/
    BOOL GPIO_OutDisable(unsigned int dwDisBits);
	/******************************************************************************/

	/******************************************************************************/
	/*�������ܣ�����Gpio�������ƽΪ��
	*��ڲ���:dwSetBits:�����ƽλ��Ϊ1
	*���ڲ�������
	*����ֵ��������óɹ�����TRUE�����򷵻�FALSE*/
    BOOL GPIO_OutSet(unsigned int dwSetBits);
	/******************************************************************************/

	/******************************************************************************/
	/*�������ܣ�����Gpio�������ƽΪ��
	*��ڲ���:dwClearBits:�����ƽλ��Ϊ0
	*���ڲ�������
	*����ֵ��������óɹ�����TRUE�����򷵻�FALSE*/
    BOOL GPIO_OutClear(unsigned int dwClearBits);
	/******************************************************************************/

	/******************************************************************************/
	/*�������ܣ���ȡ����Gpio�ڵ�ƽ
	*���ڲ�����pPinState:����ֵָ��
	*����ֵ����ȡ�ĵ�ƽΪ�߷���TRUE�����򷵻�FALSE*/
    BOOL GPIO_PinState(unsigned int* pPinState);
	/******************************************************************************/

protected:
	
	HANDLE m_hGPIO;
};

#endif _CGIPO_h