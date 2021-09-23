#pragma once


// CPropertiesPane

#include "PropertiesPaneDlg.h"

class CPropertiesPane : public CDockablePane
{
	DECLARE_DYNAMIC(CPropertiesPane)
public:
	CPropertiesPaneDlg m_PropertiesPaneDlg;
public:
	CPropertiesPane();
	virtual ~CPropertiesPane();

protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


