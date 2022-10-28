#pragma once
#include "IManager.h"
#include "../Core/Events.h"
#include "../Core/EventData.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Engine
{
	class Application;

	class UIManager : public IManager, public IEventListener<event::E_SFMLEvent>
	{
	public:
    static UIManager& Get();
		~UIManager() = default;

		void SetSFMLWindow(sf::RenderWindow& window);
		void DrawGui();
		tgui::Gui* GetGui();

  protected:
    void ReceiveEvent(const event::E_SFMLEvent& eventData) override;

		void VirtualOnInit() override;
		void VirtualOnDestroy() override;

	private:
		UIManager() = default;

		std::unique_ptr<tgui::Gui> m_gui = nullptr;

		friend class Application;
	};
}