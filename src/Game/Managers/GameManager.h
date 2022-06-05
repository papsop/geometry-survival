#pragma once
#include <Engine/Managers/IManager.h>

namespace Game
{
	class GameManager : public Engine::IManager
	{
	public:
		GameManager() = default;
		~GameManager() override = default;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;
	};
}