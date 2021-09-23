// SampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sample.h"
#include "SampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg dialog

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CAPTURE, OnBtnCapture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg message handlers

BOOL CSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnBtnCapture() 
{
	DWORD	dwRetStatus = DCAM_WAITSTATUS_UNCOMPLETED;
	WORD*	pDataBuff   = NULL;
	int		nWidth = 0, nHeight = 0, nImageSize = 0, nLineCount = 0, nBitSize = 0;

	nWidth = nHeight = nImageSize = 0;
	nLineCount = 50;										// Line Count( 50 line )

	DcamInitialize();										// Initialize DLL
	DcamOpen();												// Open the device
	DcamStop();												// Stop acquisition

	DcamSetGain( 1 );										// Set the gain 1
	DcamSetOffset( 40 );									// Set the offset 10
	DcamSetBinning( DCAM_BINNING_FULL );					// Set the Full line binning
	DcamSetTriggerPolarity( DCAM_TRIGPOL_NEGATIVE );		// Set the trigger polarity negative
	DcamSetTriggerMode( DCAM_TRIGMODE_INT2 );			// Set the trigger mode "Internal Mode"

	DcamSetMeasureDataCount( nLineCount );					// Set the line count 5

	DcamGetBitPerPixel( &nBitSize );						// Get the bit size

	DcamGetImageSize( &nWidth, &nHeight );					// Get the image size
	CString strM;
	strM.Format("Image w=%d,h=%d", nWidth,nHeight);
	AfxMessageBox(strM);
	nImageSize = nWidth * nHeight;

	pDataBuff = new WORD[ nImageSize * nLineCount ];

	if( pDataBuff != NULL )
	{
		memset( pDataBuff, '\0', nImageSize * nLineCount );

		// Acquire the image data
		DcamCapture( pDataBuff, (nImageSize * nLineCount) * 2 );

		while( TRUE )
		{
			// Wait to complete the image acquisition
			DcamWait( &dwRetStatus, 0 );

			if( dwRetStatus == DCAM_WAITSTATUS_COMPLETED )
			{
				break;
			}
		}
	}
	else
	{
		DcamClose();
		DcamUninitialize();
		return ;
	}

	// Save data
	SaveData( "Sample.txt", pDataBuff, nWidth, nHeight, nLineCount );
	
	delete [] pDataBuff;

	DcamStop();											// Stop acquisition
	DcamClose();										// Close the device
	DcamUninitialize();									// Uninitialize DLL
}

// Save data
void CSampleDlg::SaveData( char* pFileName, WORD *pDataBuff, int nWidth, int nHeight, int nFrame ) 
{
	FILE *fp;
	int  nCountW, nCountH, nCountF;
	
	fp = fopen( pFileName, "w" );
	if( fp == NULL )	return;

	WORD *pData = pDataBuff;

	CString s;
	s.Format("Width=%d,Height=%d,Frames=%d",nWidth,nHeight,nFrame);
	AfxMessageBox(s);
	for(nCountF = 0; nCountF < nFrame; nCountF++)
	{
		for( nCountH = 0; nCountH < nHeight; nCountH++ )
		{
			for( nCountW = 0; nCountW < nWidth; nCountW++ )
			{
				//fprintf( fp, "%d,", *pData );
				fprintf( fp, "%d\n", *pData );

				pData ++;
			}
			fprintf( fp, "\n" );
		}
		//njrs
		fprintf(fp,"Frame%d Ends\n",nCountF);
	}

	fclose( fp );
}
