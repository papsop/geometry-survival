#include "GameObjectManager.h"

#include "../Application.h"
#include "../Core/EventData.h"

#include "../ImGui/imgui.h"
// TODO: Entity cleanup and notifications about deletion

namespace Engine
{
  GameObjectManager& GameObjectManager::Get() { return Application::Instance().GetGameObjectManager(); }

  void GameObjectManager::VirtualOnInit()
  {
    DebuggableOnInit();
  }
  void GameObjectManager::VirtualOnDestroy()
  {
    DebuggableOnDestroy();
    m_gameObjects.clear();
  }

  GameObject* GameObjectManager::CreateGameObject(const char* name, GameObjectTag tag, const ITransform::TransformDefinition& transformDef)
  {
    uint32_t ID = m_nextGameObjectID++;
    m_gameObjects[ID] = std::make_unique<GameObject>(ID, name, tag, transformDef);
    auto* gameObject_ptr = m_gameObjects[ID].get();
    m_gameObjectsToInitialize.push(gameObject_ptr);
    return gameObject_ptr;
  };

  GameObject* GameObjectManager::GetGameObjectByID(uint32_t ID)
  {
    if (m_gameObjects.find(ID) != m_gameObjects.end())
      return m_gameObjects[ID].get();
    else
    {
      return nullptr;
    } 
  }

	std::vector<GameObject*> GameObjectManager::GetGameObjectsByTag(GameObjectTag tag)
	{
    std::vector<GameObject*> result;

    for (auto& entry : m_gameObjects)
    {
      if (!entry.second->ShouldDestroy() && entry.second->Tag == tag)
      {
        result.push_back(entry.second.get());
      }
    }

    return result;
	}

	void GameObjectManager::Update(float dt)
	{
    for (auto& entry : m_gameObjects)
    {
      if (entry.second->ShouldUpdate())
      {
        entry.second->Update(dt);
      }
    }
	}

	void GameObjectManager::DestroyGameObject(uint32_t ID)
  {
    auto* gameObject = GetGameObjectByID(ID);
    if (gameObject != nullptr)
    {

      if (gameObject->ShouldDestroy())
        return; // GameObject is already scheduled to be destroyed

      gameObject->m_shouldDestroy = true;
      m_gameObjectsToCleanup.push(gameObject);
    }
  }

  void GameObjectManager::DestroyAllGameObjects()
  {
    for (auto& gameObject : m_gameObjects)
    {
      gameObject.second->Destroy();
    }

    //CleanupGameObjects();
  }

  void GameObjectManager::CleanupGameObjects()
  {
    while (!m_gameObjectsToCleanup.empty())
    {
      auto* gameObject = m_gameObjectsToCleanup.front();

			gameObject->OnDestroy();
			event::E_GameObjectDeleted eventData(gameObject->ID);
			EventManager::Get().DispatchEvent(eventData);

      m_gameObjects.erase(gameObject->ID);
      m_gameObjectsToCleanup.pop();
    }
  }

	void GameObjectManager::InitializeGameObjects()
	{
		while (!m_gameObjectsToInitialize.empty())
		{
			auto* gameObject = m_gameObjectsToInitialize.front();

      gameObject->ForEachComponent([](IComponent* component) {
        component->OnCreate();
      });

			gameObject->SetActive(true);
      m_gameObjectsToInitialize.pop();
		}
	}

	void GameObjectManager::DebugDraw_ExpandGameObject(GameObject* obj)
  {
    auto& children = obj->GetTransform()->GetChildren();
    if (children.size() > 0)
    {
			if (ImGui::TreeNode(obj->DebugName))
			{
       
				auto& children = obj->GetTransform()->GetChildren();
				for (const auto& child : children)
				{
					DebugDraw_ExpandGameObject(child);
				}
				ImGui::TreePop();
			}
    }
    else
    {
      ImGui::BulletText(obj->DebugName);
    }
  }

	void GameObjectManager::Debug(VisualDebugContext& debugContext)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * 0.9f, work_size.y * 0.1f), ImGuiCond_Once, ImVec2(1.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.1f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;

		if (ImGui::Begin("GameObjectManager", NULL, window_flags))
		{
			ImGui::Text("Number of GameObjects: %d", m_gameObjects.size());
			ImGui::Separator();
			for (const auto& [ID, gameObject] : m_gameObjects)
			{
				auto* gameObject_ptr = gameObject.get();
				if (gameObject_ptr->GetTransform()->GetParent() == nullptr)
				{
					DebugDraw_ExpandGameObject(gameObject_ptr);
				}
			}

		}
		ImGui::End();
	}

};