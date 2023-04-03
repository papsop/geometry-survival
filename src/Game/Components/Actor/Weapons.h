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
		unsigned int GetNumberOfBullets() const { return NumberOfBullets; }

	protected:
		unsigned int MaxAmmo;
		float FireRate;
		float BulletDamage;
		unsigned int NumberOfBullets;
	};

	struct PistolWeapon : public WeaponData
	{
		PistolWeapon()
		{
			MaxAmmo = 12;
			FireRate = 0.5f;
			BulletDamage = 10.0f;
			NumberOfBullets = 1;
		}
	};

}