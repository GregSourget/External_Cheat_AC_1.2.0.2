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

	extern int updatedArmor;
	void armoron() noexcept;
	void armoroff() noexcept;
	extern bool isArmorOn;

	extern int updatedFire;
	void rapidfireon() noexcept;
	void rapidfireoff() noexcept;
	extern bool isRapidFireOn;

	extern int updatedRecoil;
	void norecoilon() noexcept;
	void norecoiloff() noexcept;
	extern bool isNoRecoilOn;

	/*extern int updatedFly;
	void flyon() noexcept;
	void flyoff() noexcept;
	extern bool isFlyOn;*/

	void getinfoon() noexcept;
	extern bool isGetInfoOn;
	extern std::uintptr_t headPtr; // Pour stocker les pointeurs vers les t�tes des ennemis
	extern std::uintptr_t entityL;
	extern std::uintptr_t entity;
	extern float headValue;
}