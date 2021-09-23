#pragma once
#ifndef FLAME_SETTINGS_H
#define FLAME_SETTINGS_H
// CFlameSettings command target

class CFlameSettings : public CObject
{
	//Attributes
public:
    ///Default Peak Wavelength in nm
	double m_dlPeakWL;
	///wavelength tolerance limit (+/-)
	double m_dlPeakWLTOLLimit;
    /// Energy can be either in Voltage(mv) &  ADU
	double m_dblPeakTHLD;

public:
	///
    DECLARE_SERIAL( CFlameSettings )

public:
	///
	CFlameSettings();
	//copy constructor
	CFlameSettings(const CFlameSettings &obj);
	//assignment operator
	CFlameSettings & operator=(const CFlameSettings &obj);
	///
	virtual ~CFlameSettings();
	///
	void Serialize(CArchive& ar);
};

#endif
