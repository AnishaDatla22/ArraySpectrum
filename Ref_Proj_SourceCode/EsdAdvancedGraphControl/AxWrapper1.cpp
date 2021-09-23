// AxWrapper1.cpp : Implementation of CEsdAdvancedGraphControlApp and DLL registration.

#include "stdafx.h"
#include "AxWrapper1.h"
#include "TChart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CEsdAdvancedGraphControlApp theApp;

const GUID CDECL BASED_CODE _tlid =
{ 0x2947432F, 0x9C7, 0x4EEB, { 0xBD, 0x48, 0xA3, 0xD2, 0x59, 0x42, 0xBA, 0x77 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CEsdAdvancedGraphControlApp::InitInstance - DLL initialization

BOOL CEsdAdvancedGraphControlApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	AfxEnableControlContainer();
	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CEsdAdvancedGraphControlApp::ExitInstance - DLL termination

int CEsdAdvancedGraphControlApp::ExitInstance()
{
	// TODO: Add your own module termination code here.
#ifdef _TCHART_LOG
	WriteTChartLog("ExitInstance of Wrapper Control \n");
#endif

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
