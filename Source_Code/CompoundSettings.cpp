// CompoundSettings.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "CompoundSettings.h"
#include <algorithm>
using namespace std;

// CCompoundSettings
IMPLEMENT_SERIAL(CCompoundSettings, CObject, VERSIONABLE_SCHEMA | 2)

CCompoundSettings::CCompoundSettings()
{
	m_strCompoundName = SULPHUR_COMPOUND;//S,P,Ae,HNo
	m_dlPeakWL = 190;//190-1000nm range of our instrument
	m_dlPeakWLTOLLimit = 1;//by default we assume +/- 1 as wavelength tolerance
	//m_nNoOfEnergyLevels = NO_OF_ENERGY_LEVELS;
	//m_arrPKEnergyLevels.RemoveAll();
	//m_arrPKEnergyLevelsLimits.RemoveAll();
}

CCompoundSettings::~CCompoundSettings()
{
}


// CCompoundSettings member functions

void CCompoundSettings::Serialize(CArchive& ar)
{
	// call base class function first
    // base class is CObject in this case
    CObject::Serialize( ar );

    // now do the stuff for our specific class
    if( ar.IsStoring() )
	{
		ar << m_strCompoundName;
		ar << m_dlPeakWL;
		ar << m_dlPeakWLTOLLimit;
		for(int nIndex = 0; nIndex < NO_OF_ENERGY_LEVELS; nIndex++)
		{
			ar << m_arrPKEnergyLevels[nIndex];
		}
		//m_arrPKEnergyLevels.Serialize(ar);
		//m_arrPKEnergyLevelsLimits.Serialize(ar);
	}
    else
	{
		ar >> m_strCompoundName;
		ar >> m_dlPeakWL;
		ar >> m_dlPeakWLTOLLimit;
		for(int nIndex = 0; nIndex < NO_OF_ENERGY_LEVELS; nIndex++)
		{
			ar >> m_arrPKEnergyLevels[nIndex];
		}
		//m_arrPKEnergyLevels.Serialize(ar);
		//m_arrPKEnergyLevelsLimits.Serialize(ar);
	}
}

//copy constructor
CCompoundSettings::CCompoundSettings(const CCompoundSettings &obj)
{
	//Allocate new memory
	
	//copy the data
	m_strCompoundName = obj.m_strCompoundName;
	m_dlPeakWL = obj.m_dlPeakWL;
	m_dlPeakWLTOLLimit = obj.m_dlPeakWLTOLLimit;
    
	//copy the data
	//std::copy(obj.m_arrPKEnergyLevels,(obj.m_arrPKEnergyLevels)+NO_OF_ENERGY_LEVELS,m_arrPKEnergyLevels);
	//m_arrPKEnergyLevels.Copy(obj.m_arrPKEnergyLevels);
	//m_arrPKEnergyLevelsLimits.Copy(obj.m_arrPKEnergyLevelsLimits);

	for(int nEnergyLevelIndex =0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
	{
		m_arrPKEnergyLevels[nEnergyLevelIndex] = obj.m_arrPKEnergyLevels[nEnergyLevelIndex];
	}

}

//assignment operator
CCompoundSettings & CCompoundSettings::operator=(const CCompoundSettings &obj)
{
	if (this != &obj) // protect against invalid self-assignment
	{
		//Allocate new memory
		
		//deallocate old memory
		
		//assign the new memory to the object
	
		//copy the data
		m_strCompoundName = obj.m_strCompoundName;
		m_dlPeakWL = obj.m_dlPeakWL;
		m_dlPeakWLTOLLimit = obj.m_dlPeakWLTOLLimit;
		
		//copy the data
		//std::copy(obj.m_arrPKEnergyLevels,(obj.m_arrPKEnergyLevels)+NO_OF_ENERGY_LEVELS,m_arrPKEnergyLevels);

		//m_arrPKEnergyLevels.Copy(obj.m_arrPKEnergyLevels);
		//m_arrPKEnergyLevelsLimits.Copy(obj.m_arrPKEnergyLevelsLimits);
		for(int nEnergyLevelIndex =0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
		{
			m_arrPKEnergyLevels[nEnergyLevelIndex] = obj.m_arrPKEnergyLevels[nEnergyLevelIndex];
		}
	}
	// by convention, always return *this
	return *this;
}
