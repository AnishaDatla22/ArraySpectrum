// SampleDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_SAMPLEDLG_H__8ABEB178_9277_4450_9212_F820A5ADA68D__INCLUDED_)
#define AFX_SAMPLEDLG_H__8ABEB178_9277_4450_9212_F820A5ADA68D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg �_�C�A���O

class CSampleDlg : public CDialog
{
// �\�z
public:
	CSampleDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSampleDlg)
	enum { IDD = IDD_SAMPLE_DIALOG };
		// ����: ���̈ʒu�� ClassWizard �ɂ���ăf�[�^ �����o���ǉ�����܂��B
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	SaveData( char* pFileName, WORD *pDataBuff, int nWidth, int nHeight, int nFrameCnt, int nDataIdx );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SAMPLEDLG_H__8ABEB178_9277_4450_9212_F820A5ADA68D__INCLUDED_)
