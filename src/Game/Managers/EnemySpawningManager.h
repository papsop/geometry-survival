#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Application.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/ImGui/imgui.h>
#include <Engine/Core/Events.h>

#include "../Skills/ISkill.h"
#include "GameTimer.h"

#include "../Components/Enemy/EnemySpawnerComponent.h"
#include "../Core/EventData.h"
#include <vector>
#include <memory>
#include <functional>
#include <random>

namespace Game
{

  struct EnemySpawningEntry
  {
    std::function<Engine::GameObject* (void)> SpawnFunction;
    float TimeMin;
    float TimeMax;
    float Cooldown;
    float CurrentCooldown;
    const char* DebugName;
  };

  class EnemySpawningManager : public Engine::IManager, public Engine::IDebuggable,
    public Engine::IEventListener<event::E_PlayerObjectRegistrationChanged>
  {
  public:
    EnemySpawningManager(Engine::Application& app);
    ~EnemySpawningManager() = default;

    void RegisterSpawnerObject(Engine::GameObject* spawner);
    void UnregisterSpawnerObject();

    void Update(float dt) override;

    void Debug(Engine::VisualDebugContext& debugContext) override;

  protected:
    void VirtualOnInit() override;
    void VirtualOnDestroy() override;
    void ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) override;

  private:
    Engine::Application& m_app;
    Engine::GameObject* m_spawnerObject = nullptr;
    Engine::GameObject* m_player = nullptr;
    GameTimer* m_gameTimer = nullptr;
    std::vector<EnemySpawningEntry> m_spawningEntries;

    float m_spawnRadius = 50.0f;
    float m_biasAngle = Engine::math::M_PI_F / 9.0f;

    // Variables for debug
    float m_lastSpawnAngle = 0.0f;
    Engine::math::Vec2 m_lastSpawnPosition = { 0,0 };

    bool IsEntryInTime(const EnemySpawningEntry& entry);
    Engine::math::Vec2 GetNewSpawnPosition();
    void SpawnEntry(EnemySpawningEntry& entry);
  };
}