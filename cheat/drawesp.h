#pragma once

#include <d3d9.h>
#include <Windows.h>

namespace drawesp {
    extern LPDIRECT3D9 pD3D;  // D�claration externe de l'objet Direct3D
    extern LPDIRECT3DDEVICE9 pD3DDevice;  // D�claration externe du p�riph�rique de rendu Direct3D
    constexpr int WIDTH = 800;  // Largeur de la fen�tre
    constexpr int HEIGHT = 600;  // Hauteur de la fen�tre

    bool InitDirect3D(HWND hWnd);  // D�claration de la fonction d'initialisation
    void CleanupDirect3D();       // D�claration de la fonction de nettoyage
    void RenderFrame();           // D�claration de la fonction de rendu
    HWND CreateWindowApp(HINSTANCE hInstance, int nCmdShow); // D�claration de la fonction de cr�ation de fen�tre
}
