#pragma once
#include <d3d9.h>

namespace gui
{

	extern HWND g_hCheckbox;
	extern HWND g_hEdit;

	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 700;

	inline bool isRunning = true;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void RenderTrainerTab() noexcept;
	void RenderPlayerInfoTab() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;

	inline bool showInfoWindow = false;

	extern void godmodeon() noexcept;
	extern void godmodeoff() noexcept;
	extern bool isGodModeOn;
	extern int updatedHealth;

	extern void infnadeon() noexcept;
	extern void infnadeoff() noexcept;
	extern bool isInfNadeOn;
	extern int updatedNade;

	extern void infammoon() noexcept;
	extern void infammooff() noexcept;
	extern bool isInfAmmoOn;
	extern int updatedAmmo;

	extern void rapidfireon() noexcept;
	extern void rapidfireoff() noexcept;
	extern bool isRapidFireOn;
	extern int updatedFire;

	extern void norecoilon() noexcept;
	extern void norecoiloff() noexcept;
	extern bool isNoRecoilOn;

	extern void Armoron() noexcept;
	extern void Armoroff() noexcept;
	extern bool isArmorOn;
	extern int updatedArmor;

	/*extern void getinfoon() noexcept;
	extern bool isGetInfoOn;*/

	extern void aimboton() noexcept;
	extern void aimbotoff() noexcept;
	extern bool isAimBotOn;

	/*extern void espon() noexcept;
	extern void espoff() noexcept;
	extern bool isESPOn;*/

	
	//extern int headValue;
}
