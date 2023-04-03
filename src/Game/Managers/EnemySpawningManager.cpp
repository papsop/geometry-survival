#include "EnemySpawningManager.h"

#include "../Core/GameObject/GameObjectFactory.h"
#include "GameManager.h"
namespace Game
{
	EnemySpawningManager::EnemySpawningManager(Engine::Application& app)
		: m_app(app)
	{
		EnemySpawningEntry entry;
		entry.DebugName = "EasyEnemy";
		entry.SpawnFunction = [&]() { 
			EnemyFactoryDef def;
			def.MovementSpeed = 5.0f;
			def.Position = m_spawnerObject->GetTransform()->GetPosition();
			return GameObjectFactory::CreateEnemy(def); 
		};
		entry.Cooldown = 2.0f;
		entry.CurrentCooldown = 0.0f;
		entry.TimeMin = 5.0f;
		entry.TimeMax = -1.0f;

		m_spawningEntries.push_back(entry);
	}

	void EnemySpawningManager::VirtualOnInit()
	{
		m_gameTimer = m_app.GetGameManager<GameManager>()->GetGameTimerPtr();
		DebuggableOnInit();
	}

	void EnemySpawningManager::VirtualOnDestroy()
	{
		DebuggableOnDestroy();
	}

	bool EnemySpawningManager::IsEntryInTime(const EnemySpawningEntry& entry)
	{
		auto currentTime = m_gameTimer->GetTimerSeconds();
		// Time checks
		if (entry.TimeMin < entry.TimeMax)
		{ // consider both sides
			if (currentTime < entry.TimeMin || currentTime > entry.TimeMax)
				return false; // skip
		}
		else
		{ // only consider timeMin
			if (currentTime < entry.TimeMin)
				return false; // skip
		}

		return true;
	}

	void EnemySpawningManager::RegisterSpawnerObject(Engine::GameObject* spawner)
	{
		m_spawnerObject = spawner;
	}

	void EnemySpawningManager::UnregisterSpawnerObject()
	{
		m_spawnerObject = nullptr;
	}

	void EnemySpawningManager::Update(float dt)
	{
		if (GameManager::Get()->GetCurrentGameState() != GameState::Gameplay)
			return;

		if (!m_spawnerObject || !m_gameTimer)
			return;

		
		for (auto&& entry : m_spawningEntries)
		{
			// Time
			if (!IsEntryInTime(entry))
				continue;

			// Cooldown
			entry.CurrentCooldown -= dt;
			if (entry.CurrentCooldown > 0.0f)
				continue; 

			// Spawning
			auto* enemy = entry.SpawnFunction();
			m_spawnerObject->GetTransform()->AddChild(enemy);
			entry.CurrentCooldown = entry.Cooldown;
		}

	}

	void EnemySpawningManager::Debug(Engine::view::IViewStrategy* viewStrategy)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(0.0f, 200.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.1f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
		ImU32 rowBgSpawning		 = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
		ImU32 rowBgNotSpawning = ImGui::GetColorU32(ImVec4(0.7f, 0.3f, 0.3f, 0.65f));


		if (ImGui::Begin("EnemySpawningManager", NULL, window_flags))
		{
			ImGui::Text(m_gameTimer->GetTimerAsString().c_str());
			ImGui::Separator();
			ImGui::Text("Registered enemies");
			ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
			if (ImGui::BeginTable("RegisteredEnemies", 3, tableFlags))
			{
				ImGui::TableSetupColumn("Name");
				ImGui::TableSetupColumn("Cooldown");
				ImGui::TableSetupColumn("Spawning time");
				ImGui::TableHeadersRow();
				for(const auto& entry : m_spawningEntries)
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%s", entry.DebugName);
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%.1f/%.1f", entry.CurrentCooldown, entry.Cooldown);
					ImGui::TableSetColumnIndex(2);
					ImGui::Text("<%.1f, %.1f>", entry.TimeMin, entry.TimeMax);
					ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg1, IsEntryInTime(entry) ? rowBgSpawning : rowBgNotSpawning);
				}
				ImGui::EndTable();
			}

		}
		ImGui::End();
	}
}