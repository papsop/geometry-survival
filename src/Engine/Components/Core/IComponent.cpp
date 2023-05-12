#include "IComponent.h"

#include "../../Core/GameObject/GameObject.h"
#include "../../Application.h"
#include "../../Managers/RenderManager.h"

#include "../../ImGui/imgui.h"
namespace Engine
{
	// =========================================================
	// GENERIC COMPONENT
	// =========================================================
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



	// =========================================================
	// DRAWABLE COMPONENT
	// =========================================================
	IDrawableComponent::IDrawableComponent(GameObject& obj, view::Layer layer)
		: IComponent(obj)
		, m_layer(layer)
		, m_renderManager(RenderManager::Get())
	{

	}
	void IDrawableComponent::OnCreate()
	{
		RenderManager::Get().RegisterComponent(this);
	}

  sf::Drawable* IDrawableComponent::GetDrawableDataForRendering(ITransform::AbsoluteTransform transform, sf::Transformable* transformable)
  {
		transformable->setPosition(m_renderManager.coordsPosToPixelsPos(transform.Position));
		transformable->setRotation(m_renderManager.Box2DRotationToSFML(transform.Rotation));
    // not quite sure right now
    auto transformableScale = transformable->getScale();
		transformable->setScale({ transform.Scale.x * transformableScale.x, transform.Scale.y * transformableScale.y });

		return dynamic_cast<sf::Drawable*>(transformable);
  }

  IDrawableComponent::~IDrawableComponent()
	{
		RenderManager::Get().UnregisterComponent(this);
	}

	bool IComponent::ShouldUpdate()
	{
    return Owner.ShouldUpdate() && IsActive() && IsEnabled();
	}

	// =========================================================
	// ImGui COMPONENT
	// =========================================================
  IImGuiComponent::IImGuiComponent(GameObject& obj)
    : IComponent(obj)
	{
	}

	void IImGuiComponent::OnCreate()
	{
		RenderManager::Get().RegisterComponent(this);
	}

	void IImGuiComponent::OnDestroy()
	{
		RenderManager::Get().UnregisterComponent(this);
	}

	void IImGuiComponent::InitializeOverlayWindow(const char* name, math::Vec2 RelativePos, math::Vec2 Size, bool IsSizeRelative, math::Vec2 pivot)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_size = viewport->WorkSize;		
		ImVec2 work_pos = viewport->WorkPos;

		ImGui::SetNextWindowPos(ImVec2(work_pos.x + work_size.x * RelativePos.x, work_pos.y + work_size.y * RelativePos.y), ImGuiCond_Always, ImVec2(pivot.x, pivot.y));
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