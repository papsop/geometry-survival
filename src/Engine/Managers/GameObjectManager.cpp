#include "GameObjectManager.h"

#include "../Application.h"
#include "../Core/EventData.h"

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
    return m_gameObjects[ID].get();
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

  void GameObjectManager::Update(float dt)
	{
    for (auto& gameObject : m_gameObjects)
    {
      if (gameObject.second->ShouldUpdate())
      {
        gameObject.second->Update(dt);
      }
    }
	}

	void GameObjectManager::DestroyGameObject(uint32_t ID)
  {
    auto* gameObject = GetGameObjectByID(ID);
    if (gameObject != nullptr)
    {
      gameObject->m_shouldDestroy = true;
      m_gameObjectsToCleanup.push(gameObject);
    }
  }

  void GameObjectManager::CleanupGameObjects()
  {
    while (!m_gameObjectsToCleanup.empty())
    {
      auto* e = m_gameObjectsToCleanup.front();

      e->OnDestroy();
      event::E_GameObjectDeleted eventData(e->ID);

      m_gameObjects.erase(e->ID);
      m_gameObjectsToCleanup.pop();

      EventManager::Get().DispatchEvent(eventData);
    }
  }

  void GameObjectManager::DebugDraw_ExpandGameObject(view::IViewStrategy* viewStrategy, GameObject* obj, unsigned& line, unsigned depth)
  {
    DebugDraw_WriteGameObjectLine(viewStrategy, obj, line, depth);

    auto& children = obj->GetTransform()->GetChildren();
    if (children.size() == 0)
      return; // stop recursion

    for (const auto& child : children)
    {
      DebugDraw_ExpandGameObject(viewStrategy, child, line, depth + 1);
    }
  }

  // Helper function to write into viewStrategy
  void GameObjectManager::DebugDraw_WriteGameObjectLine(view::IViewStrategy* viewStrategy, GameObject* obj, unsigned& line, unsigned depth)
  {
    float topOffset = 50.0f;

    math::Vec2 position = { 15.0f + 25.0f * depth, topOffset + 16.0f * line };

    std::string text = std::to_string(obj->ID) + " - " + obj->DebugName;
    sf::Color color = obj->IsActive() ? sf::Color::Green : sf::Color::Red;
    viewStrategy->DebugRenderText(ITransform::PositionSpace::CameraSpace, text, position, false, 12.0f, color);
    line++;
  }

  void GameObjectManager::Debug(view::IViewStrategy* viewStrategy)
  {
    unsigned line = 0;
    for (const auto& [ID, gameObject] : m_gameObjects)
    {
      auto* gameObject_ptr = gameObject.get();
      if (gameObject_ptr->GetTransform()->GetParent() == nullptr)
      {
        DebugDraw_ExpandGameObject(viewStrategy, gameObject_ptr, line, 0);
      }
    }
  }

};