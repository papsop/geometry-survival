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
		unsigned int GetNumberOfBullets() const { return NumberOfBullets; }

	protected:
		unsigned int MaxAmmo;
		float FireRate;
		float BulletDamage;
		float ReloadTime;
		unsigned int NumberOfBullets;
	};

	struct PistolWeapon : public WeaponData
	{
		PistolWeapon()
		{
			MaxAmmo = 100;
			FireRate = 0.01f;
			BulletDamage = 10.0f;
			ReloadTime = 2.0f;
			NumberOfBullets = 1;
		}
	};

}