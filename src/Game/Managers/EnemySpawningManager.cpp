#include "EnemySpawningManager.h"

#include <stdlib.h>
#include <time.h>

#include "../Components/Actor/ActorComponent.h"
#include "../Core/GameObject/GameObjectFactory.h"
#include "GameManager.h"
namespace Game {
EnemySpawningManager::EnemySpawningManager(Engine::Application& app) : m_app(app)
{
  srand(time(NULL));

  {
    EnemySpawningEntry entry;
    entry.DebugName = "EasyEnemy";
    entry.SpawnFunction = [&]() {
      EnemyFactoryDef def;
      def.MovementSpeed = 5.0f;
      def.Position = GetNewSpawnPosition();
      def.DamagePerSecond = 10.0f;
      def.Color = sf::Color::Magenta;
      def.MaxHealth = 10.0f;
      return GameObjectFactory::CreateEnemy(def);
    };
    entry.Cooldown = 0.1f;
    entry.CurrentCooldown = 0.0f;
    entry.TimeMin = 1.f;
    entry.TimeMax = 25.0f;

    // m_spawningEntries.push_back(entry);
  }

  {
    EnemySpawningEntry entry;
    entry.DebugName = "EasyEnemy2";
    entry.SpawnFunction = [&]() {
      EnemyFactoryDef def;
      def.MovementSpeed = 5.0f;
      def.Position = GetNewSpawnPosition();
      def.DamagePerSecond = 20.0f;
      def.Color = sf::Color::Red;
      def.MaxHealth = 20.0f;
      return GameObjectFactory::CreateEnemy(def);
    };
    entry.Cooldown = 0.1f;
    entry.CurrentCooldown = 0.0f;
    entry.TimeMin = 10.0f;
    entry.TimeMax = 100.0f;

    // m_spawningEntries.push_back(entry);
  }
}

void EnemySpawningManager::VirtualOnInit()
{
  m_gameTimer = m_app.GetGameManager<GameManager>()->GetGameTimerPtr();
  m_player = m_app.GetGameManager<GameManager>()->GetPlayerGameObject();
  IEventListener<event::E_PlayerObjectRegistrationChanged>::RegisterListener();
  DebuggableOnInit();
}

void EnemySpawningManager::VirtualOnDestroy()
{
  IEventListener<event::E_PlayerObjectRegistrationChanged>::UnregisterListener();
  DebuggableOnDestroy();
}

void EnemySpawningManager::RegisterSpawnerObject(Engine::GameObject* spawner) { m_spawnerObject = spawner; }

void EnemySpawningManager::UnregisterSpawnerObject() { m_spawnerObject = nullptr; }

Engine::math::Vec2 EnemySpawningManager::GetNewSpawnPosition()
{
  if (!m_player) return {0.0f, 0.0f};

  float randomAngle;
  if (m_player->GetComponent<ActorComponent>()->IsMoving()) {
    auto movingDir = m_player->GetComponent<ActorComponent>()->GetMovingDir();
    auto movingAngle = Engine::math::AngleBetweenVecs({0.0f, 0.0f}, movingDir);

    auto biasLeft = movingAngle + Engine::math::M_PI_F / 4.0f;
    auto biasRight = movingAngle - Engine::math::M_PI_F / 4.0f;

    float min = std::min(biasLeft, biasRight);
    float max = std::max(biasLeft, biasRight);

    randomAngle = Engine::math::RandomFloatBetween(min, max);
  }
  else {
    randomAngle = Engine::math::DEG_TO_RAD(rand() % 361);
  }

  m_lastSpawnPosition = Engine::math::GetVectorFromAngle(randomAngle);

  m_lastSpawnPosition *= m_spawnRadius;
  m_lastSpawnPosition += m_player->GetTransform()->GetPosition();
  return m_lastSpawnPosition;
}

void EnemySpawningManager::SpawnEntry(EnemySpawningEntry& entry)
{
  auto* enemy = entry.SpawnFunction();
  m_spawnerObject->GetTransform()->AddChild(enemy);
  entry.CurrentCooldown = entry.Cooldown;
}

void EnemySpawningManager::Update(float dt)
{
  if (GameManager::Get()->GetCurrentGameState() != GameState::Gameplay) return;

  if (!m_spawnerObject || !m_gameTimer || !m_player) return;

  float currentTime = m_gameTimer->GetTimerSeconds();

  for (auto&& entry : m_spawningEntries) {
    // Time
    if (!entry.IsEntryInTime(currentTime)) continue;

    // Cooldown
    entry.CurrentCooldown -= dt;
    if (entry.CurrentCooldown > 0.0f) continue;

    // Spawning
    SpawnEntry(entry);
  }
}

void EnemySpawningManager::ReceiveEvent(const event::E_PlayerObjectRegistrationChanged& eventData) { m_player = eventData.PlayerObject; }

void EnemySpawningManager::Debug(Engine::VisualDebugContext& debugContext)
{
  // Visual debug
  // TODO: shouldn't be calculated here
  if (m_player) {
    debugContext.DebugRenderCircle(Engine::ITransform::PositionSpace::WorldSpace, m_player->GetTransform()->GetPosition(), m_spawnRadius, sf::Color::Yellow);
    debugContext.DebugRenderCircle(Engine::ITransform::PositionSpace::WorldSpace, m_lastSpawnPosition, 1.0f, sf::Color::Red);

    auto movingDir = m_player->GetComponent<ActorComponent>()->GetMovingDir();
    auto movingAngle = Engine::math::AngleOfVec(movingDir);

    Engine::math::Vec2 dir = Engine::math::GetVectorFromAngle(movingAngle);
    dir *= m_spawnRadius;
    debugContext.DebugRenderLine(Engine::ITransform::PositionSpace::WorldSpace, m_player->GetTransform()->GetPosition(),
                                 m_player->GetTransform()->GetPosition() + dir, sf::Color::Cyan);

    // bias
    float movingBiasLeft = movingAngle + m_biasAngle;
    float movingBiasRight = movingAngle - m_biasAngle;

    Engine::math::Vec2 biasLeft = Engine::math::GetVectorFromAngle(movingBiasLeft);
    Engine::math::Vec2 biasRight = Engine::math::GetVectorFromAngle(movingBiasRight);
    biasLeft *= m_spawnRadius;
    biasRight *= m_spawnRadius;

    debugContext.DebugRenderLine(Engine::ITransform::PositionSpace::WorldSpace, m_player->GetTransform()->GetPosition(),
                                 m_player->GetTransform()->GetPosition() + biasLeft, sf::Color::Green);
    debugContext.DebugRenderLine(Engine::ITransform::PositionSpace::WorldSpace, m_player->GetTransform()->GetPosition(),
                                 m_player->GetTransform()->GetPosition() + biasRight, sf::Color::Red);
  }

  float currentTime = m_gameTimer->GetTimerSeconds();
  // ImGui debug
  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImVec2 work_size = viewport->WorkSize;
  ImGui::SetNextWindowPos(ImVec2(0.0f, 400.0f), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowBgAlpha(0.1f);  // Transparent background
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
  ImU32 rowBgSpawning = ImGui::GetColorU32(ImVec4(0.3f, 0.7f, 0.3f, 0.65f));
  ImU32 rowBgNotSpawning = ImGui::GetColorU32(ImVec4(0.7f, 0.3f, 0.3f, 0.65f));

  if (ImGui::Begin("EnemySpawningManager", NULL, window_flags)) {
    ImGui::Text(m_gameTimer->GetTimerAsString().c_str());
    ImGui::Separator();
    ImGui::Text("Registered enemies");
    ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    if (ImGui::BeginTable("RegisteredEnemies", 3, tableFlags)) {
      ImGui::TableSetupColumn("Name");
      ImGui::TableSetupColumn("Cooldown");
      ImGui::TableSetupColumn("Spawning time");
      ImGui::TableHeadersRow();
      for (const auto& entry : m_spawningEntries) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%s", entry.DebugName);
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("%.1f/%.1f", entry.CurrentCooldown, entry.Cooldown);
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("<%.1f, %.1f>", entry.TimeMin, entry.TimeMax);
        ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg1, entry.IsEntryInTime(currentTime) ? rowBgSpawning : rowBgNotSpawning);
      }
      ImGui::EndTable();
    }
  }
  ImGui::End();
}

bool EnemySpawningEntry::IsEntryInTime(float currentTime) const
{
  // Time checks
  if (TimeMin < TimeMax) {                                             // consider both sides
    if (currentTime < TimeMin || currentTime > TimeMax) return false;  // skip
  }
  else {                                      // only consider timeMin
    if (currentTime < TimeMin) return false;  // skip
  }

  return true;
}

}  // namespace Game
