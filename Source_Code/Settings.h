#pragma once
// CSettings command target

#include "FlameSettings.h"
#include "CompoundSettings.h"

class CSettings : public CObject
{
	//Attributes
private:
	///

public:
    DECLARE_SERIAL( CSettings )

public:
	///
	CSettings();
	///Copy Constructor
	CSettings(const CSettings &obj);
	///assignment operator
	CSettings & operator=(const CSettings &obj);
	///
	virtual ~CSettings();

	///
	void Serialize(CArchive& ar);
    
	///
	CFlameSettings m_objFlameSettings;
    ///
	//CArray<CCompoundSettings,CCompoundSettings> m_arrobjCompoundSettings;
	CCompoundSettings m_arrobjCompoundSettings[NO_OF_COMPOUNDS];
	///
	CStringArray  m_arrStrBuzzerLevels;
};