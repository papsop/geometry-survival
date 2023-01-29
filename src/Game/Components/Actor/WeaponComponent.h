#pragma once
#include <Engine/Components/Core.h>
#include <Engine/Core/Events.h>

#include "../../Core/EventData.h"
#include "../Actor/RPGComponent.h"
#include "Weapons/IWeapon.h"

namespace Game
{
    class WeaponComponent : public Engine::IComponent, public Engine::IEventListener<event::E_EnemyDied>
    {
    public:
      WeaponComponent(Engine::GameObject& obj);
      ~WeaponComponent() override;

      void OnCreate() override;
      void Update(float dt) override;

      void Fire();
      void Reload();

      void EquipWeapon(std::unique_ptr<IWeapon> weapon);
      Engine::GameObject* CreateBulletGameObject();

      void ProcessMessage(const Engine::Message& message) override;
      void AddAmmo(unsigned int additionalAmmo);

      unsigned int GetMaxAmmo();
      unsigned int GetCurrentAmmo();


      void OnDestroy() override;

    protected:
      void ReceiveEvent(const event::E_EnemyDied& eventData) override;

      void VirtualOnActivated() override;
      void VirtualOnDeactivated() override;
    private:
		  std::unique_ptr<IWeapon> m_equippedWeapon;
      RPGComponent* m_rpgComponent = nullptr;
    };

};

