#include <windows.h>
#include "escapi.h"

countCaptureDevicesProc countCaptureDevices;
initCaptureProc initCapture;
deinitCaptureProc deinitCapture;
doCaptureProc doCapture;
isCaptureDoneProc isCaptureDone;
getCaptureDeviceNameProc getCaptureDeviceName;
ESCAPIDLLVersionProc ESCAPIDLLVersion;

/* Internal: initialize COM */
typedef void (*initCOMProc)();
initCOMProc initCOM;

int setupESCAPI()
{
  /* Load DLL dynamically */
  char* wpurl = "escapi.dll";
  int len = strlen(wpurl)+1;

  wchar_t *wText = new wchar_t[len];
  if ( wText == 0 )
	return 0;
  memset(wText,0,len);
  ::MultiByteToWideChar(  CP_ACP, NULL,wpurl, -1, wText,len );

  //load the DLL
  HMODULE capdll = LoadLibrary(wText);
  
  // when finish using wText dont forget to delete it
  delete []wText;

  if (capdll == NULL)
    return 0;

  /* Fetch function entry points */
  countCaptureDevices = (countCaptureDevicesProc)GetProcAddress(capdll, "countCaptureDevices");
  initCapture = (initCaptureProc)GetProcAddress(capdll, "initCapture");
  deinitCapture = (deinitCaptureProc)GetProcAddress(capdll, "deinitCapture");
  doCapture = (doCaptureProc)GetProcAddress(capdll, "doCapture");
  isCaptureDone = (isCaptureDoneProc)GetProcAddress(capdll, "isCaptureDone");
  initCOM = (initCOMProc)GetProcAddress(capdll, "initCOM");
  getCaptureDeviceName = (getCaptureDeviceNameProc)GetProcAddress(capdll, "getCaptureDeviceName");
  ESCAPIDLLVersion = (ESCAPIDLLVersionProc)GetProcAddress(capdll, "ESCAPIDLLVersion");

  /* Check that we got all the entry points */
  if (initCOM == NULL ||
      ESCAPIDLLVersion == NULL ||
      getCaptureDeviceName == NULL ||
      countCaptureDevices == NULL ||
      initCapture == NULL ||
      deinitCapture == NULL ||
      doCapture == NULL ||
      isCaptureDone == NULL)
      return 0;

  /* Verify DLL version */
  if (ESCAPIDLLVersion() != 0x200)
    return 0;

  /* Initialize COM.. */
  initCOM();

  /* and return the number of capture devices found. */
  return countCaptureDevices();
}

