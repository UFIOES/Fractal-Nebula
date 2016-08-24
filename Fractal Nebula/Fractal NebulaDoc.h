
// Fractal NebulaDoc.h : interface of the CFractalNebulaDoc class
//


#pragma once

#include "Generator.h"


class CFractalNebulaDoc : public CDocument {
	protected: // create from serialization only
	CFractalNebulaDoc();
	DECLARE_DYNCREATE(CFractalNebulaDoc)

	// Attributes
	public:
	int nebulaSize = 200000;
	nebulaData* nebula;
	int variations;
	variation* functions;
	BOOL valid = FALSE;
	BOOL built = FALSE;
	
	// Operations
	public:

	// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
	#endif // SHARED_HANDLERS

	// Implementation
	public:
	virtual ~CFractalNebulaDoc();
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif
	void build();

	protected:

	// Generated message map functions
	protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
	#endif // SHARED_HANDLERS
};
