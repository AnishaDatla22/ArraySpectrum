// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "ArraySpectrum.h"
#include "Settings.h"


// CSettings
IMPLEMENT_SERIAL(CSettings, CObject, VERSIONABLE_SCHEMA | 2)

CSettings::CSettings()
{
	//m_arrobjCompoundSettings.RemoveAll();
	m_arrStrBuzzerLevels.RemoveAll();
	
	//Read the ini file and get FirstTimeExecution([Application Settings])
	
	//TCHAR buff[1000];
	//GetPrivateProfileString(_T("Application Settings"),_T("FirstTimeExecution"),_T("0"),buff,1000,theApp.m_strConfigIniPath);
	//int nFirstTimeExecution = _tcstol(buff,NULL);
	//if(nFirstTimeExecution == 0)
	//{
	//	
	//}
	///*else if(nFirstTimeExecution == 1)
	//{
	//	
	//}*/
}

CSettings::~CSettings()
{
}


// CSettings member functions

void CSettings::Serialize(CArchive& ar)
{
	// call base class function first
    // base class is CObject in this case
    CObject::Serialize( ar );

    // now do the stuff for our specific class
    if( ar.IsStoring() )
	{
		m_objFlameSettings.Serialize(ar);
		//m_arrobjCompoundSettings.Serialize(ar);
		for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
		{
			ar << m_arrobjCompoundSettings[nIndex].m_strCompoundName;
			ar << m_arrobjCompoundSettings[nIndex].m_dlPeakWL;
			ar << m_arrobjCompoundSettings[nIndex].m_dlPeakWLTOLLimit;
			for(int nEnergyLevelIndex = 0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
			{
				ar << m_arrobjCompoundSettings[nIndex].m_arrPKEnergyLevels[nEnergyLevelIndex];
			}
		}
		m_arrStrBuzzerLevels.Serialize(ar);
	}
    else
	{
		m_objFlameSettings.Serialize(ar);
		//m_arrobjCompoundSettings.Serialize(ar);
		for(int nIndex = 0; nIndex < NO_OF_COMPOUNDS; nIndex++)
		{
			ar >> m_arrobjCompoundSettings[nIndex].m_strCompoundName;
			ar >> m_arrobjCompoundSettings[nIndex].m_dlPeakWL;
			ar >> m_arrobjCompoundSettings[nIndex].m_dlPeakWLTOLLimit;
			for(int nEnergyLevelIndex = 0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
			{
				ar >> m_arrobjCompoundSettings[nIndex].m_arrPKEnergyLevels[nEnergyLevelIndex];
			}
		}
		m_arrStrBuzzerLevels.Serialize(ar);		
	}
}

//copy constructor
CSettings::CSettings(const CSettings &obj)
{
	//Allocate new memory
	
	//copy the data
	m_objFlameSettings = obj.m_objFlameSettings;
	
	for(int nCompoundIndex = 0; nCompoundIndex < NO_OF_COMPOUNDS; nCompoundIndex++)
	{
		m_arrobjCompoundSettings[nCompoundIndex].m_strCompoundName = obj.m_arrobjCompoundSettings[nCompoundIndex].m_strCompoundName;
		m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWL = obj.m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWL;
		m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWLTOLLimit = obj.m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWLTOLLimit;
		for(int nEnergyLevelIndex =0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
		{
			m_arrobjCompoundSettings[nCompoundIndex].m_arrPKEnergyLevels[nEnergyLevelIndex] = obj.m_arrobjCompoundSettings[nCompoundIndex].m_arrPKEnergyLevels[nEnergyLevelIndex];
		}
	}
	//m_arrobjCompoundSettings = obj.m_arrobjCompoundSettings;

	m_arrStrBuzzerLevels.Copy(obj.m_arrStrBuzzerLevels);
}

//assignment operator
CSettings & CSettings::operator=(const CSettings &obj)
{
	if (this != &obj) // protect against invalid self-assignment
	{
		//Allocate new memory
		
		//deallocate old memory
		
		//assign the new memory to the object
	
		//copy the data
		m_objFlameSettings = obj.m_objFlameSettings;
		//m_arrobjCompoundSettings = obj.m_arrobjCompoundSettings;
		for(int nCompoundIndex = 0; nCompoundIndex < NO_OF_COMPOUNDS; nCompoundIndex++)
		{
			m_arrobjCompoundSettings[nCompoundIndex].m_strCompoundName = obj.m_arrobjCompoundSettings[nCompoundIndex].m_strCompoundName;
			m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWL = obj.m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWL;
			m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWLTOLLimit = obj.m_arrobjCompoundSettings[nCompoundIndex].m_dlPeakWLTOLLimit;
			for(int nEnergyLevelIndex =0; nEnergyLevelIndex < NO_OF_ENERGY_LEVELS; nEnergyLevelIndex++)
			{
				m_arrobjCompoundSettings[nCompoundIndex].m_arrPKEnergyLevels[nEnergyLevelIndex] = obj.m_arrobjCompoundSettings[nCompoundIndex].m_arrPKEnergyLevels[nEnergyLevelIndex];
			}
		}
		m_arrStrBuzzerLevels.Copy(obj.m_arrStrBuzzerLevels);
	}
	// by convention, always return *this
	return *this;
}
