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

	extern int updatedFire;
	void rapidfireon() noexcept;
	void rapidfireoff() noexcept;
	extern bool isRapidFireOn;

	void norecoilon() noexcept;
	void norecoiloff() noexcept;
	extern bool isNoRecoilOn;

	extern int updatedArmor;
	void armoron() noexcept;
	void armoroff() noexcept;
	extern bool isArmorOn;

	void aimboton() noexcept;
	void aimbotoff() noexcept;
	extern bool isAimBotOn;
}


