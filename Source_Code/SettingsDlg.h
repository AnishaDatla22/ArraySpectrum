#pragma once
#include "afxwin.h"
#include "Settings.h"
#include "LevelIndicator.h"
#include "CustomBitmapButton.h"

// CSettingsDlg dialog
class CArraySpectrumDoc;//Forward declartion

class CSettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingsDlg)
	///Attributes
private:
	///
	//CButton m_btnFlameOnOFF;
	CCustomBitmapButton m_btnFlameOnOFF;
	///
	CButton m_btnFlameSettings;
	///
	CEdit m_edtFlamePeakWL;
	///
	CEdit m_edtPeakWLTOLLimit;
	///
	CEdit m_edtFlameTHOLD;
	///
	double m_dblFlamePeakWL;
	///
	double m_dblFlamePeakTOLLimits;
	///
	double m_dblFlamePeakTHOLD;
	///
	//CWnd* m_pParent;
	bool m_bFlameON;
	///
	double m_dblSPeakWL;
	///
	double m_dblSPeakWLTolLimit;
	///
	double m_dblSLevel1THLD;
	///
	double m_dblSLevel1ThldTolLimit;
	///
	double m_dblSLevel2THLD;
	///
	double m_dblSLevel2ThldTolLimit;
	///
	double m_dblSLevel3THLD;
	///
	double m_dblSLevel3ThldTolLimit;
	///
	double m_dblSLevel4THLD;
	///
	double m_dblSLevel4ThldTolLimit;
	///
	double m_dblSLevel5THLD;
	///
	double m_dblSLevel5ThldTolLimit;
	///
	int m_nSEnergyLevel;
	///
	//CStatic m_staticPLevelIndicator;
	CLevelIndicator m_staticPLevelIndicator;
	///
	//CStatic m_staticASLevelIndicator;
	CLevelIndicator m_staticASLevelIndicator;
	///
	//CStatic m_staticHNOLevelIndicator;
	CLevelIndicator m_staticHNOLevelIndicator;
	///
	//CStatic m_staticSLevelIndicator;
	CLevelIndicator m_staticSLevelIndicator;

	///
	CComboBox m_cmbCompoundNames;
	///
	CStatic m_staticSelCompoundName;
	///
	//CArray<int,int> m_arrnCompoundLevelIndicators;
	int m_arrnCompoundLevelIndicators[NO_OF_COMPOUNDS];
	///
	//CArray<long,long> m_arrCompoundEnergyAtPeakWL;
	double m_arrCompoundEnergyAtPeakWL[NO_OF_COMPOUNDS];
	/////
	//CSettings m_objTempSettings;
	///
	bool m_bShowFlameSettings;
	///
	bool m_bShowCompoundSettings;
	///
	CFont m_fntCompoundName;
	///
	CStatic m_staticSLevelLable;
	///
	CStatic m_staticPLevelLable;
	///
	CStatic m_saticASLevelLable;
	///
	CStatic m_staticHNOLevelLable;
	///
	CRect m_rectCollapsedSettings;
	///
	CRect m_rectExpandedSettings;
public:
    /// Dialog Data
	enum { IDD = IDD_SETTINGS };
	///
	CArraySpectrumDoc* m_pDoc;


public:
	/// standard constructor
	CSettingsDlg(CWnd* pParent = NULL);   

	virtual ~CSettingsDlg();


protected:
	/// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	///
	afx_msg void OnClose();
	///
	afx_msg void OnPaint();
	///
	virtual BOOL OnInitDialog();
    ///
	void ApplyDocDataIntoCtrls();
	///
	void ApplyCtrlsDataIntoDoc();
	///
	void ApplyFlameSettings();
	///
	void ApplyStatesToDlgCtrls();
	///
	void ApplyCompoundSettings();
	///
	afx_msg void OnBnClickedBtnFlammableSettings();
	///
	afx_msg void OnBnClickedBtnApply();
	
	///
	afx_msg void OnCbnSelchangeComboCompoundNamesCol();
public:
	///
	void FillCompoundSettingsCtrl(int nSelIndex);
	///
	void UpdateCompoundLevelIndicators();
	///if bSave is TRUE, The settings are saved to a INI file otherwise they will be rerieved from the 
	void SerializeSettingsData(bool bSave);
	///
	void UpdateCompoundSettingIntoDoc(int nSelIndex);
	///
	afx_msg void OnBnClickedOk();
	///
	void ShowOrHideFlameSettings(bool bShow);
	///
	void ShowOrHideCompoundSettings(bool bShow);
	///
	afx_msg void OnBnClickedBtnCompoundSettings();
	///
	afx_msg void OnStnClickedSLevelIndicator();
	///
	afx_msg void OnStnClickedStaticPLevelLable();
	///
	void UpdateSettings();
	///
	void UpdateFlameIndicator();
	///
	afx_msg void OnBnClickedBtnFlameApply();
	///
	LRESULT OnApplySettings(WPARAM wp , LPARAM lp);
	
	
};
