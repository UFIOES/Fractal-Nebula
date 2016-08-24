
// Fractal Nebula.h : main header file for the Fractal Nebula application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFractalNebulaApp:
// See Fractal Nebula.cpp for the implementation of this class
//

class CFractalNebulaApp : public CWinAppEx {
	public:
	CFractalNebulaApp();


	// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation
	COleTemplateServer m_server;
	// Server object for document creation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFractalNebulaApp theApp;
