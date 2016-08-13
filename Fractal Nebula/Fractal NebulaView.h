
// Fractal NebulaView.h : interface of the CFractalNebulaView class
//

#pragma once


class CFractalNebulaView : public CView {
	protected: // create from serialization only
	CFractalNebulaView();
	DECLARE_DYNCREATE(CFractalNebulaView)

	// Attributes
	public:
	CFractalNebulaDoc* GetDocument() const;

	private:
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	
	// Operations
	public:

	// Overrides
	public:
	virtual void OnDraw(CDC* pdc);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:

	// Implementation
	public:
	virtual ~CFractalNebulaView();
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:

	// Generated message map functions
	protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Fractal NebulaView.cpp
inline CFractalNebulaDoc* CFractalNebulaView::GetDocument() const {
	return reinterpret_cast<CFractalNebulaDoc*>(m_pDocument);
}
#endif

