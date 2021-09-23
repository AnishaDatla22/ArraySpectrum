#pragma once

// AxWrapper1PropPage.h : Declaration of the CEsdAdvancedGraphControlPropPage property page class.


// CEsdAdvancedGraphControlPropPage : See AxWrapper1PropPage.cpp for implementation.

class CEsdAdvancedGraphControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEsdAdvancedGraphControlPropPage)
	DECLARE_OLECREATE_EX(CEsdAdvancedGraphControlPropPage)

// Constructor
public:
	CEsdAdvancedGraphControlPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_AXWRAPPER1 };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

