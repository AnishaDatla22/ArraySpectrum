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
	int	nWidth = 0;
	int	nHeight = 0;
	int	nImageSize = 0;
	int	nFrameCount = 10;
	int	nBitSize = 0;

 	DcamInitialize();		// Initialize library(DLL).
	DcamOpen();				// Open camera
	DcamStop();				// Stop Acquisition

	// Set camera parameters
	DcamSetLEDOperatingMode(DCAM_LEDOPMODE_ON);		// LED operation
	DcamSetStandardTimeUnit(DCAM_TIME_UNIT_TYPE1);	// Standard time unit
	DcamSetBinning(DCAM_BINNING_FULL);				// Full line binning
	DcamSetTriggerMode(DCAM_TRIGMODE_INT);			// Trigger mode to INTERNAL
	DcamSetTriggerPolarity(DCAM_TRIGPOL_NEGATIVE);	// Trigger polarity
	DcamSetExposureTime(100);						// Exposure Time
	DcamSetGain(1);									// Gain 1
	DcamSetOffset(10);								// Offset 10
	DcamSetMeasureDataCount(nFrameCount);			// Acquisition frame count
 
	// Get camera parameters
	DcamGetBitPerPixel(&nBitSize);					// Bit per pixel
	DcamGetImageSize(&nWidth, &nHeight);			// Image size
	char szVersion[256] = {0};
	DcamGetVersion(szVersion, 256);					// DLL Version number string

	// Calculation Image size and allocate buffer
	nImageSize = nWidth * nHeight; 
	pDataBuff = new WORD[ nImageSize * nFrameCount];

	// Acquisition execute
	if(pDataBuff != NULL)
	{
		// 256 times capture sample
		for(int nDataIdx=0; nDataIdx<256; nDataIdx++)
		{
			// Stop capture (clear camera buffer)
			DcamStop();
			// Start image acquisition
			if(DcamCapture(pDataBuff,   nImageSize * nFrameCount * sizeof(WORD)) == FALSE)
			{
				// Fail the start acquisition.
				break;
			}
			DWORD dwLastError = DcamGetLastError();
			TRACE(_T("$$$$$ %d $$$$$"), dwLastError);
			// Wait to complete the capture image
			DWORD dwRetStatus = DCAM_WAITSTATUS_COMPLETED;
			while(TRUE)
			{
				if( DcamWait(&dwRetStatus, 0) == FALSE)
				{
					break;
				}

				if( dwRetStatus == DCAM_WAITSTATUS_COMPLETED )
				{
					// Data process
					SaveData("Sample.csv" , pDataBuff, nWidth, nHeight, nFrameCount, nDataIdx);
					break;
				}
			}
		}
	}
	// Process for exit. 
	DcamStop(); // Stop acquisition
	delete [] pDataBuff; // Release acquisition buffer
	DcamClose(); // Close the device
	DcamUninitialize(); // Uninitialize DLL
}

// Save data
void CSampleDlg::SaveData( char* pFileName, WORD *pDataBuff, int nWidth, int nHeight, int nFrameCnt, int nDataIdx ) 
{
	errno_t err;
	FILE *fp;
	int  nCountW, nCountH, nCountF;
	
	err = fopen_s( &fp, pFileName, "a+" );
	if( err != 0 )
	{
		return;
	}

	WORD *pData = pDataBuff;
	for(nCountF = 0; nCountF < nFrameCnt; nCountF++)
	{
		fprintf(fp, "[%d - %d]\n", nDataIdx, nCountF);
		for( nCountH = 0; nCountH < nHeight; nCountH++ )
		{
			for( nCountW = 0; nCountW < nWidth; nCountW++ )
			{
				fprintf( fp, "%d,", *pData );
				pData ++;
			}
			fprintf( fp, "\n" );
		}
	}

	fclose( fp );
}
