#pragma once

class CWindow
{
	int m_nCmdShow;
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	static BOOL m_bResist;
	static TCHAR szClassName[];
	void Resist();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnCreate();
	void OnSize(int nWidth, int nHeight);
	void OnDestroy();

public:
	CWindow(HINSTANCE hInstance, int nCmdShow);
	~CWindow();
	void Create();
	void Show();
};