#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Application.h>
#include <Engine/Debug/IDebuggable.h>
#include <Engine/ImGui/imgui.h>

#include "../Skills/ISkill.h"
#include "GameTimer.h"

#include "../Components/Enemy/EnemySpawnerComponent.h"

#include <vector>
#include <memory>
#include <functional>

namespace Game
{

	struct EnemySpawningEntry
	{
		std::function<Engine::GameObject*(void)> SpawnFunction;
		float TimeMin;
		float TimeMax;
		float Cooldown;
		float CurrentCooldown;
		const char* DebugName;
	};

	class EnemySpawningManager : public Engine::IManager, public Engine::IDebuggable
	{
	public:
		EnemySpawningManager(Engine::Application& app);
		~EnemySpawningManager() = default;

		void RegisterSpawnerObject(Engine::GameObject* spawner);
		void UnregisterSpawnerObject();

		void Update(float dt) override;

		void Debug(Engine::view::IViewStrategy* viewStrategy) override;

	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		Engine::Application& m_app;
		Engine::GameObject* m_spawnerObject = nullptr;
		GameTimer* m_gameTimer = nullptr;

		std::vector<EnemySpawningEntry> m_spawningEntries;
	};
}