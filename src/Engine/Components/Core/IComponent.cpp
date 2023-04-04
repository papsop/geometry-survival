#include "IComponent.h"

#include "../../Core/GameObject/GameObject.h"
#include "../../Application.h"
#include "../../Managers/ViewManager.h"
#include "../../Managers/UIManager.h"

#include "../../ImGui/imgui.h"
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
			m_isActive = m_isEnabled = true;
			VirtualOnActivated();
		}
	}

	void IComponent::Deactivate()
	{
		if (m_isActive)
		{
			m_isActive = m_isEnabled = false;
			VirtualOnDeactivated();
		}
	}

	bool IComponent::ShouldUpdate()
	{
    return Owner.ShouldUpdate() && IsActive() && IsEnabled();
	}

  // ImGui
  IImGuiComponent::IImGuiComponent(GameObject& obj)
    : IComponent(obj)
	{
	}

	void IImGuiComponent::InitializeOverlayWindow(const char* name, math::Vec2 RelativePos, math::Vec2 Size, bool IsSizeRelative)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;
		ImGui::SetNextWindowPos(ImVec2(work_size.x * RelativePos.x, work_size.y * RelativePos.y), ImGuiCond_Always, ImVec2(0.0f, 0.0f));
		if (IsSizeRelative)
		{
			ImGui::SetNextWindowSize(ImVec2(work_size.x * Size.x, work_size.y * Size.y));
		}
		else
		{
			ImGui::SetNextWindowSize(ImVec2(Size.x, Size.y));
		}
		
		ImGui::SetNextWindowBgAlpha(0.1f); // Transparent background
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_NoBackground | 
			ImGuiWindowFlags_NoDocking;
		ImGui::Begin(name, NULL, window_flags);

	}

};