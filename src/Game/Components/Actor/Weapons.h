#pragma once

namespace Game
{
	struct WeaponData
	{
	public:
		float GetFireRate() const { return FireRate; }
		float GetBulletDamage() const { return BulletDamage; }
		float GetReloadTime() const { return ReloadTime; }

	protected:
		float FireRate;
		float BulletDamage;
		float ReloadTime;
		unsigned int BulletHits;
	};

	struct PistolWeapon : public WeaponData
	{
		PistolWeapon()
		{
			FireRate = .4f;
			BulletDamage = 5.0f;
			ReloadTime = 1.5f;
		}
	};

}