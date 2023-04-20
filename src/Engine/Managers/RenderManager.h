#pragma once
#include "IManager.h"
#include "../Components/Core/IComponent.h"
#include "../Core/Events.h"
#include "../Core/EventData.h"

#include "../Debug/IDebuggable.h"

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace Engine
{
	class Application;

	class RenderManager : public IManager, public IEventListener<event::E_OnShowDebugKeyAction>
	{
	public:
		static RenderManager& Get();

		~RenderManager() = default;

		void Update(float dt) override;

	protected:
		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		RenderManager() = default;

		std::vector<IRenderableComponent*> m_renderableComponents;
		
		friend class Application;


	};
}
