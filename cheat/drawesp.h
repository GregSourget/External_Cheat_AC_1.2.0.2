#pragma once

#include <d3d9.h>
#include <Windows.h>

namespace drawesp {
    extern LPDIRECT3D9 pD3D;  // Déclaration externe de l'objet Direct3D
    extern LPDIRECT3DDEVICE9 pD3DDevice;  // Déclaration externe du périphérique de rendu Direct3D
    constexpr int WIDTH = 800;  // Largeur de la fenêtre
    constexpr int HEIGHT = 600;  // Hauteur de la fenêtre

    bool InitDirect3D(HWND hWnd);  // Déclaration de la fonction d'initialisation
    void CleanupDirect3D();       // Déclaration de la fonction de nettoyage
    void RenderFrame();           // Déclaration de la fonction de rendu
    HWND CreateWindowApp(HINSTANCE hInstance, int nCmdShow); // Déclaration de la fonction de création de fenêtre
}
