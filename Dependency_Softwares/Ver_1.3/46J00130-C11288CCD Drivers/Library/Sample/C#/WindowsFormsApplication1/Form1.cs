using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;       // 外部dllに対する宣言には、この行が必要です
using DCamUSB_CS;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //
        //  This method is sample of to controle the imaging device and capture data.
        //
        private void btnDCamUSB_Click(object sender, EventArgs e)
        {
            UInt32	dwRetStatus = ClsDCamUSB_CS.DCAM_WAITSTATUS_UNCOMPLETED;
            Int32 nWidth = 0;
            Int32 nHeight = 0;
            Int32 nImageSize = 0;
            Int32 nFrameCount = 10;
            Int32 nBitSize = 0;
            bool bStat = true;
            textBox1.Text = "";         // Clear List

            // controll block

            bStat = ClsDCamUSB_CS.ClsDCamInitialize();      // Initialize library
            bStat = ClsDCamUSB_CS.ClsDCamOpen();            // open camera
            bStat = ClsDCamUSB_CS.ClsDCamStop();            // Stop measurement

            // Set camera parameters
            bStat = ClsDCamUSB_CS.ClsDCamSetLEDOperatingMode(ClsDCamUSB_CS.DCAM_LEDOPMODE_ON);		// LED operation
            bStat = ClsDCamUSB_CS.ClsDCamSetStandardTimeUnit(ClsDCamUSB_CS.DCAM_TIME_UNIT_TYPE1);	// Standard time unit
            bStat = ClsDCamUSB_CS.ClsDCamSetBinning(ClsDCamUSB_CS.DCAM_BINNING_FULL);				// Full line binning
            bStat = ClsDCamUSB_CS.ClsDCamSetTriggerMode(ClsDCamUSB_CS.DCAM_TRIGMODE_INT);			// Trigger mode to INTERNAL
            bStat = ClsDCamUSB_CS.ClsDCamSetTriggerPolarity(ClsDCamUSB_CS.DCAM_TRIGPOL_NEGATIVE);	// Trigger polarity
            bStat = ClsDCamUSB_CS.ClsDCamSetExposureTime(100);						                // Exposure Time

			bStat = ClsDCamUSB_CS.ClsDCamSetGain(1);									            // Gain 1
            bStat = ClsDCamUSB_CS.ClsDCamSetOffset(10);								                // Offset 10
			bStat = ClsDCamUSB_CS.ClsDCamSetMeasureDataCount(nFrameCount);			                // Acquisition frame count
			Int32 nCount = 0;
			bStat = ClsDCamUSB_CS.ClsDCamGetSensorSignalPulseWidth(0, ref nCount);			                // Acquisition frame count

	        // Get camera parameters
            bStat = ClsDCamUSB_CS.ClsDCamGetBitPerPixel(ref nBitSize);                              // Get pixel depth
            bStat = ClsDCamUSB_CS.ClsDCamGetImageSize(ref nWidth, ref nHeight);                     // Get image pixel size

            // Capturing block
            nImageSize = nWidth * nHeight;

            try
            {
                unsafe
                {
                    // Allocation measure buffer
                    IntPtr pMeasBuffer = Marshal.AllocHGlobal((nImageSize * nFrameCount * 2));   // "2" means 2 bytes (=16bit) pixel depth.
                    bStat = ClsDCamUSB_CS.ClsDCamStop();
                    // capture data
                    if ((bStat = ClsDCamUSB_CS.ClsDCamCapture(ref pMeasBuffer, nFrameCount)) == true)
                    {
                        while (true)
                        {
                            // Wait data
                            if (ClsDCamUSB_CS.ClsDCamWait(ref dwRetStatus, 0) == false)
                            {
                                break;
                            }
                            if (dwRetStatus == ClsDCamUSB_CS.DCAM_WAITSTATUS_COMPLETED)
                            {
                                ClsDCamUSB_CS.ClsDCamStop();
                                // Dump data
                                unsafe
                                {
                                    UInt16* pPtr = (UInt16*)pMeasBuffer.ToPointer();
                                    string strData = "";
                                    for (int n = 0; n < nHeight; n++)
                                    {
                                        for (int m = 0; m < nWidth; m++)
                                        {
                                            strData += (*pPtr).ToString("d5");
                                            strData += ", ";
                                            pPtr++;
                                        }
                                        strData += "\r\n";
                                    }
                                    textBox1.Text = strData;
                                }
                                break;
                            }
                        }

                    }
                    Marshal.FreeHGlobal(pMeasBuffer);
                }

            }
            catch (Exception excp)
            {
                Debug.WriteLine(excp.Message);
            }
            finally
            {
                ClsDCamUSB_CS.ClsDCamClose();
                ClsDCamUSB_CS.ClsDCamUninitialize();
            }
        }

        //
        //  This method is sample of to control the temperature functions.
        //
        private void btnDCamTmpCtrl_Click(object sender, EventArgs e)
        {
            bool bStat = true;
            bool bCoolingCtrl = false;
            Int32 nCoolingTmp = 0;
            Int32 nCurrentTmp = 0;
            Int32 nThermistor = 0;
            Int32 nTmpStatus = 0;
            textBox1.Text = "";         // Clear List

            // controll block
            try
            {
                string strData = "";
                // Initialize DCamUSB and open device.
                bStat = ClsDCamUSB_CS.ClsDCamInitialize();
                bStat = ClsDCamUSB_CS.ClsDCamOpen();
                // Initialize Temperature Function
                bStat = ClsDCamUSB_CS.ClsDCamTmpCtrlInitialize();
                // Load cooling parameter from EEPROM.
                bStat = ClsDCamUSB_CS.ClsDCamLoadCoolingParameter();
                // Get and set the cooling switch.
                bStat = ClsDCamUSB_CS.ClsDCamGetCoolingControl(ref bCoolingCtrl);
                bStat = ClsDCamUSB_CS.ClsDCamSetCoolingControl(!bCoolingCtrl);
                strData = "Cooling control = " + ((bCoolingCtrl) ? "ON" : "OFF") + "\r\n";
                textBox1.Text += strData;
                // Get and set the cooling target.
                bStat = ClsDCamUSB_CS.ClsDCamGetCoolingTemperature(ref nCoolingTmp);
                bStat = ClsDCamUSB_CS.ClsDCamSetCoolingTemperature(nCoolingTmp - 5);
                strData = "Cooling cooling temperature = " + nCoolingTmp.ToString("d5") + "\r\n";
                textBox1.Text += strData;
                // Get current sensor temperature.
                bStat = ClsDCamUSB_CS.ClsCcamCurrentTemperature(ref nCurrentTmp);
                strData = "Current temperature = " + nCoolingTmp.ToString("d5") + "\r\n";
                textBox1.Text += strData;
                // Get thermistor temperature
                bStat = ClsDCamUSB_CS.ClsDCamGetThermistorStatus(ref nThermistor);
                strData = "Current thermistor temperature = " + nThermistor.ToString("d5") + "\r\n";
                textBox1.Text += strData;
                // Get thermistor temperature
                bStat = ClsDCamUSB_CS.ClsDCamGetCoolingStatus(ref nTmpStatus);
                strData = "Current cooling status = " + nTmpStatus.ToString("d5") + "\r\n"; 
                textBox1.Text += strData;
                // Save Cooling paramerer
                bStat = ClsDCamUSB_CS.ClsDCamSaveCoolingParameter();
                // Get last error code
                UInt32 dwStat = ClsDCamUSB_CS.ClsDCamGetTmpCtrlLastError();
            }
            catch (Exception excp)
            {
                Debug.WriteLine(excp.Message);
            }
            finally
            {
                ClsDCamUSB_CS.ClsDCamTmpCtrlUninitialize();
                ClsDCamUSB_CS.ClsDCamClose();
                ClsDCamUSB_CS.ClsDCamUninitialize();
            }
        }
    }
}
