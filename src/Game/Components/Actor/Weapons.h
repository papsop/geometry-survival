#pragma once
#include <Engine/Utils/VectorUtils.h>

namespace Game
{
	struct WeaponData
	{
	public:
		float GetFireRate() const { return FireRate; }
		float GetBulletDamage() const { return BulletDamage; }
		float GetSpread() const { return Spread; }

	protected:
		float FireRate;
		float BulletDamage;
		float Spread; // angles
		unsigned int BulletHits;
	};

	struct PistolWeapon : public WeaponData
	{
		PistolWeapon()
		{
			FireRate = 0.f;
			BulletDamage = 1.0f;
			Spread = Engine::math::M_PI_F / 4.0f;
		}
	};

}