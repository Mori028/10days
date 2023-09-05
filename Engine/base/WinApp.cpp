#include "WinApp.h"
#include <tchar.h>

#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WinApp::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ImGui�p�E�B���h�E�v���V�[�W���Ăяo��
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}
	//���b�Z�[�W�ŕ���
	switch (msg) {
	case WM_DESTROY: //�E�B���h�E���j�����ꂽ
		PostQuitMessage(0); //OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); //�W���̏������s��

	return false;
}

bool WinApp::ProcessMessage()
{
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		return true;
	}

	return false;
}

void WinApp::Initialize()
{

	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProcedure;	//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = _T("DX12Sample");			//�E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);		//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);	//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y{X���W�@Y���W�@�����@�c��}
	RECT wrc = { 0,0,window_width,window_height };
	//�֐����g���ăE�B���h�E�̃T�C�Y�������ŕ␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	/*HWND*/ hwnd = CreateWindow(w.lpszClassName,//�N���X���w��
		_T("10days"),	//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,			//�^�C�g���o�[�Ƌ��E��������E�B���h�E
		CW_USEDEFAULT,					//�\��x���W��OS�ɂ��C��
		CW_USEDEFAULT,					//�\��y���W��OS�ɂ��C��
		wrc.right - wrc.left,			//�E�B���h�E��
		wrc.bottom - wrc.top,			//�E�B���h�E��
		nullptr,						//�e�E�B���h�E�n���h��
		nullptr,						//���j���[�n���h��
		w.hInstance,					//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);						//�ǉ��p�����[�^�[(�I�v�V����)

	//�E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{
}

void WinApp::Finalize()
{
	//�E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}