
// Fractal NebulaView.cpp : implementation of the CFractalNebulaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Fractal Nebula.h"
#endif

#include "Fractal NebulaDoc.h"
#include "Fractal NebulaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFractalNebulaView

IMPLEMENT_DYNCREATE(CFractalNebulaView, CView)

BEGIN_MESSAGE_MAP(CFractalNebulaView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFractalNebulaView construction/destruction

CFractalNebulaView::CFractalNebulaView() {
	// TODO: add construction code here
	

}

CFractalNebulaView::~CFractalNebulaView() {}

BOOL CFractalNebulaView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 640;
	sd.BufferDesc.Height = 480;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = cs.hwndParent;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
	
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, 0, &level, 1, D3D11_SDK_VERSION, 
								  &sd, &swapChain, &device, NULL, &deviceContext);

	return CView::PreCreateWindow(cs);
}

// CFractalNebulaView drawing

void CFractalNebulaView::OnDraw(CDC* pdc) {
	CFractalNebulaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	// TODO: add draw code for native data here

	float* color = new float[4];

	color = {0.0f, 0.0f, 0.0f, 0.0f};



	deviceContext->ClearRenderTargetView(NULL, color);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->Draw(3, 0);

	swapChain->Present(0, 0);

}

void CFractalNebulaView::OnRButtonUp(UINT /* nFlags */, CPoint point) {
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFractalNebulaView::OnContextMenu(CWnd* /* pWnd */, CPoint point) {
	#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	#endif
}


// CFractalNebulaView diagnostics

#ifdef _DEBUG
void CFractalNebulaView::AssertValid() const {
	CView::AssertValid();
}

void CFractalNebulaView::Dump(CDumpContext& dc) const {
	CView::Dump(dc);
}

// non-debug version is inline
CFractalNebulaDoc* CFractalNebulaView::GetDocument() const {
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFractalNebulaDoc)));
	return (CFractalNebulaDoc*) m_pDocument;
}
#endif //_DEBUG


// CFractalNebulaView message handlers
