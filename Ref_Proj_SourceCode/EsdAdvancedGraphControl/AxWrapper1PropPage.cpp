// AxWrapper1PropPage.cpp : Implementation of the CEsdAdvancedGraphControlPropPage property page class.

#include "stdafx.h"
#include "AxWrapper1.h"
#include "AxWrapper1PropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEsdAdvancedGraphControlPropPage, COlePropertyPage)



// Message map

BEGIN_MESSAGE_MAP(CEsdAdvancedGraphControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEsdAdvancedGraphControlPropPage, "ESDADVANCEDGRAPHCONTROL.EsdAdvancedGraphControlPropPage.1",
					   0xba72c4c8, 0x70bd, 0x4cf0, 0xbd, 0xac, 0xc1, 0xdc, 0x86, 0x98, 0x7f, 0xb3)



					   // CEsdAdvancedGraphControlPropPage::CEsdAdvancedGraphControlPropPageFactory::UpdateRegistry -
					   // Adds or removes system registry entries for CEsdAdvancedGraphControlPropPage

					   BOOL CEsdAdvancedGraphControlPropPage::CEsdAdvancedGraphControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
		m_clsid, IDS_AXWRAPPER1_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);


}



// CEsdAdvancedGraphControlPropPage::CEsdAdvancedGraphControlPropPage - Constructor

CEsdAdvancedGraphControlPropPage::CEsdAdvancedGraphControlPropPage() :
COlePropertyPage(IDD, IDS_AXWRAPPER1_PPG_CAPTION)
{
}



// CEsdAdvancedGraphControlPropPage::DoDataExchange - Moves data between page and properties

void CEsdAdvancedGraphControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEsdAdvancedGraphControlPropPage message handlers
