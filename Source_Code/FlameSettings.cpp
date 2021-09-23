// FlameSettings.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "FlameSettings.h"


// CFlameSettings
IMPLEMENT_SERIAL(CFlameSettings, CObject, VERSIONABLE_SCHEMA | 2)

CFlameSettings::CFlameSettings()
{
	m_dlPeakWL = 306;//190-1000nm range of our instrument
	m_dlPeakWLTOLLimit = 5;//by default we assume +/- 1 as wavelength tolerance
    //TODO: need to get the default energy value to be assumed from RND team
	m_dblPeakTHLD = 400;
}

CFlameSettings::~CFlameSettings()
{

}


// CFlameSettings member functions
void CFlameSettings::Serialize(CArchive& ar)
{
	// call base class function first
    // base class is CObject in this case
    CObject::Serialize( ar );

    // now do the stuff for our specific class
    if( ar.IsStoring() )
	{
		ar << m_dlPeakWL;
		ar << m_dlPeakWLTOLLimit;
		ar << m_dblPeakTHLD;
	}
    else
	{
		ar >> m_dlPeakWL;
		ar >> m_dlPeakWLTOLLimit;
		ar >> m_dblPeakTHLD;		
	}
}


//copy constructor
CFlameSettings::CFlameSettings(const CFlameSettings &obj)
{
	//Allocate new memory
	
	//copy the data
	m_dlPeakWL = obj.m_dlPeakWL;
	m_dlPeakWLTOLLimit = obj.m_dlPeakWLTOLLimit;
	m_dblPeakTHLD = obj.m_dblPeakTHLD;
}

//assignment operator
CFlameSettings & CFlameSettings::operator=(const CFlameSettings &obj)
{
	if (this != &obj) // protect against invalid self-assignment
	{
		//Allocate new memory
		
		//deallocate old memory
		
		//assign the new memory to the object
	
		//copy the data
		m_dlPeakWL = obj.m_dlPeakWL;
		m_dlPeakWLTOLLimit = obj.m_dlPeakWLTOLLimit;
		m_dblPeakTHLD = obj.m_dblPeakTHLD;
	}
	// by convention, always return *this
	return *this;
}
