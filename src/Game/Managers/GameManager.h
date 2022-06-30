#pragma once
#include <Engine/Managers/IManager.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
	class GameManager : public Engine::IManager
	{
	public:
		GameManager() = default;
		~GameManager() override = default;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

		void RegisterPlayerGameObject(Engine::GameObject* player);
		void UnregisterPlayerGameObject();
		Engine::GameObject* GetPlayerGameObject();

	private:
		Engine::GameObject* m_player;
	};
}