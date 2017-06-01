#include "StdAfx.h"
#include "GPIO.h"
#include <windows.h>
#include <winioctl.h>

CGPIO::CGPIO(void)
{
	m_hGPIO = INVALID_HANDLE_VALUE;
}

CGPIO::~CGPIO(void)
{
}

BOOL CGPIO::GPIO_Open(LPCWSTR lpDevName)
{
    m_hGPIO = CreateFile(lpDevName,			                // name of device
                         GENERIC_READ|GENERIC_WRITE,		// desired access
                         FILE_SHARE_READ|FILE_SHARE_WRITE,	// sharing mode
                         NULL,								// security attributes (ignored)
                         OPEN_EXISTING,						// creation disposition
                         FILE_FLAG_RANDOM_ACCESS,			// flags/attributes
                         NULL);								// template file (ignored)

	if(m_hGPIO == INVALID_HANDLE_VALUE)
		return FALSE;
	else
		return TRUE;
}

BOOL CGPIO::GPIO_Close()
{
    if(m_hGPIO != INVALID_HANDLE_VALUE)
    {
        if (!CloseHandle(m_hGPIO))
            return FALSE;
    }
    return TRUE;
}

BOOL CGPIO::GPIO_OutEnable(unsigned int dwEnBits)
{
    if(!DeviceIoControl(m_hGPIO,		// file handle to the driver
       GPIO_IOCTL_OUT_ENABLE,			// I/O control code
       &dwEnBits,						// in buffer
       sizeof(unsigned int),  			// in buffer size
       NULL,							// out buffer
       0,								// out buffer size
       NULL,							// pointer to number of bytes returned
       NULL))							// ignored (=NULL)
    {
        return FALSE;
    }
   
    return TRUE;
}

BOOL CGPIO::GPIO_OutDisable(unsigned int dwDisBits)
{
    if(!DeviceIoControl(m_hGPIO,		// file handle to the driver
       GPIO_IOCTL_OUT_DISABLE,			// I/O control code
       &dwDisBits,						// in buffer
       sizeof(unsigned int),  			// in buffer size
       NULL,							// out buffer
       0,								// out buffer size
       NULL,							// pointer to number of bytes returned
       NULL))							// ignored (=NULL)
    {
        return FALSE;
    }
   
    return TRUE;
}

BOOL CGPIO::GPIO_OutSet(unsigned int dwSetBits)
{
    if (!DeviceIoControl(m_hGPIO,		// file handle to the driver
        GPIO_IOCTL_OUT_SET,				// I/O control code
        &dwSetBits,						// in buffer
        sizeof(unsigned int),  			// in buffer size
        NULL,							// out buffer
        0,								// out buffer size
        NULL,							// pointer to number of bytes returned
        NULL))							// ignored (=NULL)
    {
        return FALSE;
    }
   
    return TRUE;
}

BOOL CGPIO::GPIO_OutClear(unsigned int dwClearBits)
{
    if(!DeviceIoControl(m_hGPIO,		// file handle to the driver
       GPIO_IOCTL_OUT_CLEAR,			// I/O control code
       &dwClearBits,					// in buffer
       sizeof(unsigned int),  			// in buffer size
       NULL,							// out buffer
       0,								// out buffer size
       NULL,							// pointer to number of bytes returned
       NULL))							// ignored (=NULL)
    {
        return FALSE;
    }
   
    return TRUE;
}

BOOL CGPIO::GPIO_PinState(unsigned int* pPinState)
{
	UINT32	u32StateBits;
	UINT32	u32LastState;

	u32StateBits = *((UINT32*)pPinState);

    if(!DeviceIoControl(m_hGPIO,		// file handle to the driver
       GPIO_IOCTL_PIN_STATE,			// I/O control code
       &u32StateBits,					// in buffer
       sizeof(UINT32),				  	// in buffer size
       &u32LastState,					// out buffer
       sizeof(UINT32),				  	// out buffer size
       NULL,							// pointer to number of bytes returned
       NULL))							// ignored (=NULL)
    {
        return FALSE;
    }
   
	*pPinState = (unsigned int)u32LastState;
    return TRUE;
}


