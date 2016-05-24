#include <windows.h>
#include "Window.h"

BOOL CWindow::m_bResist;
TCHAR CWindow::szClassName[] = TEXT("CWindow");

CWindow::CWindow(HINSTANCE hInstance, int nCmdShow)
	:
	m_hWnd(0),
	m_hInstance(hInstance),
	m_nCmdShow(nCmdShow)
{
}

CWindow::~CWindow()
{
}

void CWindow::Create()
{
	if (!m_bResist)
	{
		Resist();
	}
	if (!m_hWnd)
	{
		const DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
		RECT rect = { 0,0,1024,768 };
		AdjustWindowRect(&rect, dwStyle, 0);
		CreateWindowEx(
			0 /*WS_EX_COMPOSITED*/,
			szClassName,
			TEXT("ƒ^ƒCƒgƒ‹"),
			dwStyle,
			CW_USEDEFAULT,
			0,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			m_hInstance,
			this
		);
	}
}

void CWindow::Show()
{
	if (!m_hWnd)
	{
		Create();
	}
	if (m_hWnd)
	{
		ShowWindow(m_hWnd, m_nCmdShow);
		UpdateWindow(m_hWnd);
	}
}

void CWindow::Resist()
{
	const WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WindowProc,
		0,
		0,
		m_hInstance,
		LoadCursor(0,IDC_ARROW),
		0,
		0,
		0,
		szClassName
	};
	if (RegisterClass(&wndclass))
	{
		m_bResist = TRUE;
	}
}

LRESULT CALLBACK CWindow::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static CWindow* pThis;
	switch (msg)
	{
	case WM_CREATE:
		pThis = (CWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		if (!pThis) return -1;
		pThis->m_hWnd = hWnd;
		pThis->OnCreate();
		break;
	case WM_COMMAND:
		//switch (LOWORD(wParam))
		//{
		//	break;
		//}
		break;
	case WM_SIZE:
		pThis->OnSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		pThis->OnDestroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void CWindow::OnCreate()
{
}

void CWindow::OnSize(int nWidth, int nHeight)
{
}

void CWindow::OnDestroy()
{
}
