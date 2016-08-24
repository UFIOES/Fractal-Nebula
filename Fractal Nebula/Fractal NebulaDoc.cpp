
// Fractal NebulaDoc.cpp : implementation of the CFractalNebulaDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Fractal Nebula.h"
#endif


#include "Fractal NebulaDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFractalNebulaDoc

IMPLEMENT_DYNCREATE(CFractalNebulaDoc, CDocument)

BEGIN_MESSAGE_MAP(CFractalNebulaDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFractalNebulaDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IFractalNebula to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {5174CC65-0307-431F-B751-4455EEC4ADAA}
static const IID IID_IFractalNebula =
{0x5174CC65, 0x307, 0x431F, { 0xB7, 0x51, 0x44, 0x55, 0xEE, 0xC4, 0xAD, 0xAA }};

BEGIN_INTERFACE_MAP(CFractalNebulaDoc, CDocument)
	INTERFACE_PART(CFractalNebulaDoc, IID_IFractalNebula, Dispatch)
END_INTERFACE_MAP()


// CFractalNebulaDoc construction/destruction

CFractalNebulaDoc::CFractalNebulaDoc() {
	// TODO: add one-time construction code here

	nebula = new nebulaData[nebulaSize];

	EnableAutomation();

	AfxOleLockApp();
}

CFractalNebulaDoc::~CFractalNebulaDoc() {
	AfxOleUnlockApp();
}

BOOL CFractalNebulaDoc::OnNewDocument() {

	if (!CDocument::OnNewDocument()) return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	built = FALSE;

	std::mt19937 engine(time(NULL));
	std::uniform_real_distribution<float> point(-1.0f, 1.0f);
	std::uniform_real_distribution<float> weight(1.0f, 2.0f);
	std::uniform_real_distribution<float> color(0.0f, 1.0f);

	variations = 3;

	functions = new variation[variations];
	
	for (int i = 0; i < variations; i++) {

		functions[i] = {
			weight(engine),
			point(engine), point(engine), point(engine), point(engine),
			point(engine), point(engine), point(engine), point(engine),
			point(engine), point(engine), point(engine), point(engine),
			0.0f, 1.0f, i / 2.0f, 1.0f,
		};

	}

	valid = TRUE;

	return TRUE;

}


void CFractalNebulaDoc::build() {

	if (built) return;

	generate(nebulaSize, functions, variations, nebula);

	built = TRUE;

}

// CFractalNebulaDoc serialization

void CFractalNebulaDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {

		ar.Write(&variations, 1);

		for (int i = 0; i < variations; i++) ar.Write(&functions[i], sizeof(variation));

	} else {

		ar.Read(&variations, 1);

		for (int i = 0; i < variations; i++) ar.Read(&functions[i], sizeof(variation));

		built = FALSE;

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFractalNebulaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFractalNebulaDoc::InitializeSearchContent() {
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFractalNebulaDoc::SetSearchContent(const CString& value) {
	if (value.IsEmpty()) {
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	} else {
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL) {
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFractalNebulaDoc diagnostics

#ifdef _DEBUG
void CFractalNebulaDoc::AssertValid() const {
	CDocument::AssertValid();
}

void CFractalNebulaDoc::Dump(CDumpContext& dc) const {
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFractalNebulaDoc commands
