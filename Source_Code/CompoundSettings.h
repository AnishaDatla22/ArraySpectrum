#pragma once
#ifndef COMPOUNDSETTINGS_H
#define COMPOUNDSETTINGS_H
// CCompoundSettings command target

class CCompoundSettings : public CObject
{
	//Attributes
public:
	///Stores Compound's Symbolic Name
	CString m_strCompoundName;
    ///Default Peak Wavelength in nm
	double m_dlPeakWL;
	///wavelength tolerance limit (+/-)
	double m_dlPeakWLTOLLimit;
	///
	//int m_nNoOfEnergyLevels;
	///Peak Energy Levels
	//CArray<double,double> m_arrPKEnergyLevels;
	double m_arrPKEnergyLevels[NO_OF_ENERGY_LEVELS];
	///Tolerance Limits for each energy level peak
	//CArray<double,double> m_arrPKEnergyLevelsLimits;

public:
	///
    DECLARE_SERIAL( CCompoundSettings )
public:
	///
	CCompoundSettings();
	///Copy Constructor
	CCompoundSettings(const CCompoundSettings &obj);
	///assignment operator
	CCompoundSettings & operator=(const CCompoundSettings &obj);
	///
	virtual ~CCompoundSettings();
	///
	void Serialize(CArchive& ar);
};
#endif