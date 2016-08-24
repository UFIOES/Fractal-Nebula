
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
	ON_WM_KEYDOWN(&CFractalNebulaView::OnKeyDown)
END_MESSAGE_MAP()

//VERTEX triangle[] = {
//	{0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
//	{0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
//	{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
//};

// CFractalNebulaView construction/destruction

CFractalNebulaView::CFractalNebulaView() {
	// TODO: add construction code here
	
}

void CFractalNebulaView::InitDirect3D() {

	RECT area;

	this->GetClientRect(&area);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = area.right - area.left;
	sd.BufferDesc.Height = area.bottom - area.top;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = this->GetSafeHwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_REFERENCE, NULL, 0, &level, 1, D3D11_SDK_VERSION,
								  &sd, &swapChain, &device, NULL, &deviceContext);

	ID3D11Texture2D* texture;

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &texture);

	device->CreateRenderTargetView(texture, NULL, &backBuffer);

	deviceContext->OMSetRenderTargets(1, &backBuffer, NULL);

	D3D11_VIEWPORT viewpoint;

	ZeroMemory(&viewpoint, sizeof(D3D11_VIEWPORT));

	viewpoint.TopLeftX = area.left;
	viewpoint.TopLeftY = area.top;
	viewpoint.Width = area.right - area.left;
	viewpoint.Height = area.bottom - area.top;

	deviceContext->RSSetViewports(1, &viewpoint);

	ID3D10Blob* PS;
	ID3D10Blob* VS;

	LPCWSTR PPath = L"PixelShader.hlsl";
	LPCWSTR VPath = L"VertexShader.hlsl";

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;

	#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG;
	#endif //_DEBUG

	D3DCompileFromFile(PPath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_4_0", flags, 0, &PS, NULL);
	D3DCompileFromFile(VPath, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_4_0", flags, 0, &VS, NULL);

	device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pixelShader);
	device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &vertexShader);

	deviceContext->PSSetShader(pixelShader, 0, 0);
	deviceContext->VSSetShader(vertexShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &layout);

	deviceContext->IASetInputLayout(layout);

	matrixStruct.world = DirectX::XMMatrixIdentity();

	matrixStruct.view = DirectX::XMMatrixLookToRH({0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f});

	matrixStruct.projection = DirectX::XMMatrixOrthographicRH((float) (area.right - area.left) / (float) (area.bottom - area.top), 1.0f, 0.1f, 100.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(BufferStruct);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	device->CreateBuffer(&bd, NULL, &matrixBuffer);

	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer);


	PS->Release();
	VS->Release();

	ready = TRUE;

}

CFractalNebulaView::~CFractalNebulaView() {
	swapChain->Release();
	backBuffer->Release();
	vertexBuffer->Release();
	matrixBuffer->Release();
	pixelShader->Release();
	vertexShader->Release();
	layout->Release();
	device->Release();
	deviceContext->Release();
}

BOOL CFractalNebulaView::PreCreateWindow(CREATESTRUCT& cs) {
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);

}

// CFractalNebulaView drawing

void CFractalNebulaView::OnDraw(CDC* /*pdc*/) {
	CFractalNebulaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc || !pDoc->valid) return;

	if (!ready) this->InitDirect3D();

	if (!pDoc->built) {
		pDoc->build();

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(nebulaData) * pDoc->nebulaSize;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		device->CreateBuffer(&bd, NULL, &vertexBuffer);

		D3D11_MAPPED_SUBRESOURCE ms;
		deviceContext->Map(vertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, pDoc->nebula, sizeof(nebulaData) * pDoc->nebulaSize);
		deviceContext->Unmap(vertexBuffer, NULL);

	}

	// TODO: add draw code for native data here


	float* color = new float[4];

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;


	deviceContext->ClearRenderTargetView(backBuffer, color);


	D3D11_MAPPED_SUBRESOURCE ms;
	deviceContext->Map(matrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &matrixStruct, sizeof(BufferStruct));
	deviceContext->Unmap(matrixBuffer, NULL);


	UINT stride = sizeof(nebulaData);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);

	deviceContext->Draw(pDoc->nebulaSize, 0);

	swapChain->Present(0, 0);

	free(color);

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

void CFractalNebulaView::OnKeyDown(UINT key, UINT rep, UINT flags) {
	DirectX::XMVECTOR axis = {0.0f, 1.0f, 0.0f, 0.0f};
	D3D11_MAPPED_SUBRESOURCE ms;
	switch (key) {
	case VK_LEFT:
		matrixStruct.world *= DirectX::XMMatrixRotationAxis(axis, 0.1f);
		OnDraw(NULL);
		break;
	case VK_RIGHT:
		matrixStruct.world *= DirectX::XMMatrixRotationAxis(axis, -0.1f);
		OnDraw(NULL);
		break;
	case VK_UP:

		break;
	case VK_DOWN:

		break;
	case VK_F1:

		CFractalNebulaDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc || !pDoc->valid) return;

		if (pDoc->built) {
			for (int i = 0; i < pDoc->nebulaSize; i++) {

				nebulaData data = pDoc->nebula[i];

				printf("{%f, %f, %f}\n", data.x, data.y, data.z);

			}
		}

		break;
	}
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
