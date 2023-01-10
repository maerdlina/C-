
// Coursework.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCourseworkApp:
// Сведения о реализации этого класса: Coursework.cpp
//

class CCourseworkApp : public CWinApp
{
public:
	CCourseworkApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCourseworkApp theApp;
