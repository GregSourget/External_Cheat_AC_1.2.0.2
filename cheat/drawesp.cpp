#include <d3d9.h>
#include <Windows.h>
#include <iostream>
#include "drawesp.h"

LPDIRECT3D9 pD3D = nullptr;              // Définir l'objet Direct3D
LPDIRECT3DDEVICE9 pD3DDevice = nullptr;  // Définir le périphérique de rendu Direct3D

bool drawesp::InitDirect3D(HWND hWnd)
{
    pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if (!pD3D)
    {
        MessageBoxA(nullptr, "Direct3D 9 ne peut pas être initialisé.", "Erreur", MB_ICONERROR);
        return false;
    }

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = WIDTH;
    d3dpp.BackBufferHeight = HEIGHT;
    d3dpp.hDeviceWindow = hWnd;

    HRESULT hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3DDevice);
    if (FAILED(hr))
    {
        MessageBoxA(nullptr, "Impossible de créer le périphérique Direct3D.", "Erreur", MB_ICONERROR);
        return false;
    }

    return true;
}

void drawesp::CleanupDirect3D()
{
    if (pD3DDevice) pD3DDevice->Release();
    if (pD3D) pD3D->Release();
}

void drawesp::RenderFrame()
{
    pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    pD3DDevice->BeginScene();
    pD3DDevice->EndScene();
    pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

HWND drawesp::CreateWindowApp(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, "D3DWindow", nullptr };
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindow(wc.lpszClassName, "Direct3D 9 Window", WS_OVERLAPPEDWINDOW, 100, 100, WIDTH, HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}
