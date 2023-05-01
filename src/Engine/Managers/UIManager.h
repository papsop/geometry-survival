#pragma once
#include "IManager.h"
#include "../Core/Events.h"
#include "../Core/EventData.h"

namespace Engine
{
	class Application;

	class UIManager : public IManager, public IEventListener<event::E_SFMLEvent>
	{
	public:
    static UIManager& Get();
		~UIManager() = default;

		void DrawGui();

  protected:
    void ReceiveEvent(const event::E_SFMLEvent& eventData) override;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		UIManager() = default;

		friend class Application;
	};
}