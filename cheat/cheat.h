#pragma once
#include "memory.h"

namespace cheat
{
	extern int updatedHealth;
	void godmodeon() noexcept;
	void godmodeoff() noexcept;
	extern bool isGodModeOn;


	extern int updatedNade;
	void infnadeon() noexcept;
	void infnadeoff() noexcept;
	extern bool isInfNadeOn;
	
	extern int updatedAmmo;
	void infammoon() noexcept;
	void infammooff() noexcept;
	extern bool isInfAmmoOn;


	void norecoilon() noexcept;
	void norecoiloff() noexcept;
	extern bool isNoRecoilOn;

	extern int updatedArmor;
	void armoron() noexcept;
	void armoroff() noexcept;
	extern bool isArmorOn;

	/*void getinfoon() noexcept;
	extern bool isGetInfoOn;*/

	void aimboton() noexcept;
	void aimbotoff() noexcept;
	extern bool isAimBotOn;


	void espon() noexcept;
	void espoff() noexcept;
	extern bool isESPOn;

	//extern std::uintptr_t headPtr; // Pour stocker les pointeurs vers les t�tes des ennemis
	//extern std::uintptr_t entityL;
	//extern std::uintptr_t entity;
	//extern float headValue;
}


