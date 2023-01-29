#include "IComponent.h"

#include "../../Core/GameObject/GameObject.h"
#include "../../Application.h"
#include "../../Managers/ViewManager.h"
#include "../../Managers/UIManager.h"

namespace Engine
{
   // view
  IRenderableComponent::IRenderableComponent(GameObject& obj, view::Layer layer)
    : IComponent(obj)
    , m_layer(layer)
  {
	};	
	
	void IRenderableComponent::OnCreate()
	{
		ViewManager::Get().RegisterComponent(this);
	}

	IRenderableComponent::~IRenderableComponent()
	{
		ViewManager::Get().UnregisterComponent(this);
	}


	void IComponent::Activate()
	{
		if (!m_isActive)
		{
			m_isActive = true;
			VirtualOnActivated();
		}
	}

	void IComponent::Deactivate()
	{
		if (m_isActive)
		{
			m_isActive = false;
			VirtualOnDeactivated();
		}
	}

  // UI COMPONENT


  IUIComponent::IUIComponent(GameObject& obj)
    : IComponent(obj)
  {

  }

  void IUIComponent::OnCreate()
  {
    m_gui = Engine::UIManager::Get().GetGui();
    if (!m_gui) return;

    ViewManager::Get().RegisterComponent(this);
    m_group = tgui::Group::create();
    m_gui->add(m_group);
    m_group->setVisible(false);

    // For the derived class
    RegisterUIElements();
  }

  void IUIComponent::OnDestroy()
  {
    if (!m_gui) return;

    ViewManager::Get().UnregisterComponent(this);
    UIHidden();
    m_gui->remove(m_group);
  }

  void IUIComponent::VirtualOnActivated()
  {
    m_group->setVisible(true);
    UIShown();
  }

  void IUIComponent::VirtualOnDeactivated()
  {
    m_group->setVisible(false);
    UIHidden();
  }

};