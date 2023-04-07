#pragma once
#include <algorithm>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	struct WeaponData
	{
	public:
		unsigned int GetMaxAmmo() const { return MaxAmmo; }
		float GetFireRate() const { return FireRate; }
		float GetBulletDamage() const { return BulletDamage; }
		float GetReloadTime() const { return ReloadTime; }

	protected:
		unsigned int MaxAmmo;
		float FireRate;
		float BulletDamage;
		float ReloadTime;
		unsigned int BulletHits;
	};

	struct PistolWeapon : public WeaponData
	{
		PistolWeapon()
		{
			MaxAmmo = 100;
			FireRate = 0.5f;
			BulletDamage = 5.0f;
			ReloadTime = 2.0f;
		}
	};

}