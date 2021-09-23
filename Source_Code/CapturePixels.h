#ifndef __CAPTURE_PIXELS
#define __CAPTURE_PIXELS



//This structure contains the parameteres set to the Data Acquisition h/w while capturing the Sepectrum
class CCapturePixels:public CObject
{
public:
	int m_nGain; 
	int m_nExposureTime;
	int m_nLineCount;
	
	int m_nOffset;
	int nDevID;
	//When this flag is true, The data Grid shows an extra column to display the average of the Continuously Captured Spectrum pixels in "Capture Mode"
	BOOL m_bShowAvg;
	
	//When this flag is true, The data Grid shows an extra column to display the RSD of the Continuously Captured Spectrum Pixels in "Capture Mode"
	BOOL m_bShowRSD;
	
	//When this flag is true, The data Grid shows an extra column to display the SD of the Continuously Captured Spectrum Pixels in "Capture Mode"
	BOOL m_bShowSD;
	
	//this array represents the array of pixel data points for all the Line Scans from the CCD.
	//For Every Capture,this array will grow to contain the number of pixel data lines as specified in the "m_LineCount" parameter 
	//This is cleared before starting a new Snap shot 
	WORD * m_pBuffPixelData;
	//double * m_pBuffPixelData;//1.3
	
	//The length (in terms of WORDs] of the Total PixelBuffer to hold the required number of Pixel Lines.  This is calculated at the time 
	//of capturing the Snap Shot based on the given Line Count.
	//Note: Multiply this value with 2 to get the buffer length in BYTEs
    int m_nPixelBufImageSize;
	
	//This contains the averaged pixel data of all the Lines
	double * m_pBufAvgPixelData;

	//This contains the Stadard Deviation (SD) pixel data of all the Lines
	double * m_pBufSDPixelData;

	//This contains the Relative Stadard Deviation (RSD) pixel data of all the Lines
	double * m_pBufRSDPixelData;

	//This is array of pixel line buffers. This is prepared when a Snapshot is captured
	WORD **m_pPixelLines;
	//double **m_pPixelLines;//1.3

	CCapturePixels();
	
	void ClearPixelBuffer();
	
	~CCapturePixels();

	//Returns the Pixel buffer of a scanned line with the given Line Number.
	//The Length of the returned pixel buffer is defined by MAX_PIXEL_DATA_COUNT_PER_LINE value
	WORD* GetLinePixelBuf(int nLineNo);
	//double* GetLinePixelBuf(int nLineNo);//1.3
    
	//Start the Capturing of Pixel Buffer as per the given Line Count
	void CaptureSnapShot();
	
	// //Notify the Frame to Clear all the  Data Presentation of the Views. Here the FrameWnd will  notify the Views to Clear the existing Data Presentations
	void NotifyToClearAllViews(void);
	
	//Prepare a series of buffers to reference each Scan Pixel Line buffer individually
	void PreparePixelLineBuffFromSnapShot();
	// Get the pixel buffer with the Average of all the Pixel line buffers
	double* GetAvgPixelDataBuf(void);

    //TRUE, if Continuous Capturing is Started
	BOOL m_bContinuousCapture;
    
	//if TRUE, SnapShot mode is active
	BOOL m_bSnapShot;
    
	int m_nVersion;
	
	//Start Capturing Continuous Frames
	void CCapturePixels::StartCapture(void);

	// Stop Capturing Continuous Frames
	void StopCapture(void);
	
	// Get the Pixel buffer with the Standard Deviation of all the Pixel Line buffers
	double* GetSDPixelBuffer(void);
	
	// Get the Pixel Buffer with the RSD of  all the Pixel Line Buffers
	double* GetRSDPixelBuffer(void);
	
	//Saves the Data to a CSV file. If nMode=0, the Pixel Data is saved. If nMode=1, the WaveLength Data is Saved
	void SaveDataToCSVFile( CString strFileName, int nMode);
    
	//returns TRUE, if the Pixel Data Buffer is NULL (i.e No Captured Data is Available)
	BOOL ISEmpty();

	virtual void Serialize(CArchive& ar);
	
};
#endif
