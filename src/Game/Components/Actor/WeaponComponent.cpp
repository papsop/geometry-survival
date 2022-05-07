#include "WeaponComponent.h"
#include "ActorComponent.h"
#include "BulletComponent.h"

#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Managers/GameObjectManager.h>
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/ViewManager.h>
#include <Engine/Components/Physics.h>

#include "../../Physics/Filters.h"
namespace Game
{
    WeaponComponent::WeaponComponent(Engine::GameObject& obj)
        : IComponent(obj)
    {
        RequiredComponents<ActorComponent>();
    }

    void WeaponComponent::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    WeaponComponent::~WeaponComponent()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }


    void WeaponComponent::Update(float dt)
    {
        if (m_equippedWeapon)
            m_equippedWeapon->Update(dt);
    }

    void WeaponComponent::EquipWeapon(std::unique_ptr<IWeapon> weapon)
    {
        m_equippedWeapon = std::move(weapon);
    }

    void WeaponComponent::Fire()
    {
        if (m_equippedWeapon)
            m_equippedWeapon->Fire();
    }

    Engine::GameObject* WeaponComponent::CreateBulletGameObject()
    {
        auto zIndex = Engine::ViewManager::Get().GetZIndexFromPool();
        auto bullet = Engine::GameObjectManager::Get().CreateGameObject("Bullet");

        // add offset and stuff
        bullet->GetTransform().Position = Owner.GetTransform().Position + Owner.GetTransform().Forward();
        bullet->GetTransform().Scale = { 1.f, 1.f };
        bullet->GetTransform().Rotation = Owner.GetTransform().Rotation;

        Engine::PhysicsBodyDef physBodyDef;
        physBodyDef.BodyType = b2_dynamicBody;
        physBodyDef.IsBullet = true;
		physBodyDef.CategoryBits = physics::EntityCategory::PLAYER_BULLET;
		physBodyDef.MaskBits = physics::EntityMask::M_PLAYER_BULLET;

        bullet->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
        bullet->AddComponent<Engine::CircleFixtureComponent>(0.5f);

        Engine::ShapeViewDef shapeViewDef;
        shapeViewDef.Color = sf::Color::Blue;
        shapeViewDef.PointCount = 3;
        shapeViewDef.Radius = 0.5f;
        bullet->AddComponent<Engine::ShapeViewComponent>(zIndex, shapeViewDef);

        bullet->AddComponent<BulletComponent>();

        Owner.GetScene().AddGameObject(bullet->c_ID);
        return bullet;
    }
    
}