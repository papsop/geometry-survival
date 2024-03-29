#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"
#include "../../Core/ColliderData.h"
#include "../../Debug/Logger.h"
#include "../../Managers/ViewLayers.h"
#include "../../Core/EventData.h"
#include "../../Core/Events.h"
#include "../../ImGui/imgui.h"

#include <functional>
#include <iostream>
#include <stdint.h>
#include <type_traits>
#include <vector>

namespace Engine
{

  class GameObject;
  struct CollisionData;

  class IComponent
  {
  public:
    using TRequiredFunc = std::function<void(const GameObject&)>;

    IComponent(GameObject& obj) : Owner(obj) {};
    virtual ~IComponent() = default;

    void Activate();
    void Deactivate();
    bool IsActive() { return m_isActive; }
    bool IsEnabled() { return m_isEnabled; }
    void SetEnabled(bool val) { m_isEnabled = val; }
    bool ShouldUpdate();

    void OnCreate();

    virtual void VirtualOnCreate() {};
    virtual void OnDestroy() {};
    virtual void Update(float dt) {};
    virtual void FixedUpdate(float dt) {};
    virtual void OnCollisionStart(CollisionData& collision) {};
    virtual void OnCollisionEnd(CollisionData& collision) {};

    GameObject& Owner;

    void CheckRequiredComponents()
    {
      if (m_requiredFunction != nullptr)
        m_requiredFunction(Owner);
    }

  protected:
    template<typename... Ts>
    struct requires_impl;

    template<typename T>
    struct requires_impl<T>;
        
    template<typename T, typename... Ts>
    struct requires_impl<T, Ts...>;

    // This function asserts required components on the Owner gameObject.
    // Function call gets stored and called every time a component
    // is removed/added from the owner
    template<typename... Ts>
    void SetRequiredComponents();

    TRequiredFunc m_requiredFunction = nullptr;

    virtual void VirtualOnActivated() {};
    virtual void VirtualOnDeactivated() {};

  protected:
      bool m_isActive = false;
      bool m_isEnabled = false;   // controls only Updating
      // TODO: add OnEnabled callback, but isn't needed right now
  };
  // ==============================================================================================================
  // Views
  // SHOULDN'T BE USED
  class IRenderableComponent : public IComponent
  {
  public:
    IRenderableComponent(GameObject& obj, view::Layer layer) : IComponent(obj), m_layer(layer) { };

    ~IRenderableComponent() = default;
      
    void VirtualOnCreate() override {};

    virtual view::Renderable GetRenderable() = 0;
    virtual view::Renderable& GetMutableRenderable() = 0;

    view::Layer GetLayer() const { return m_layer; };
  protected:
    view::Layer m_layer;
  };
	// =========================================================
	// DRAWABLE COMPONENT
	// =========================================================

  struct DrawableData
  {
    sf::Drawable* Drawable;
    sf::Shader* Shader = nullptr;
  };

  class IDrawableComponent : public IComponent
  {
  public:
    using TDrawablesMap = std::array<std::vector<DrawableData>, static_cast<size_t>(view::Layer::COUNT)>;

    IDrawableComponent(GameObject& obj, view::Layer layer);
    ~IDrawableComponent();

    void VirtualOnCreate() override final;

    virtual void GetDrawables(TDrawablesMap& drawables) {};

    view::Layer GetLayer() const { return m_layer; };
    size_t GetLayerAsIndex() const { return static_cast<size_t>(m_layer); }
  protected:
    sf::Drawable* GetDrawableDataForRendering(ITransform::AbsoluteTransform transform, sf::Transformable* transformable);
    view::Layer m_layer;
    RenderManager& m_renderManager;
  };
  // ==============================================================================================================
  // UI
  // SHOULDN'T BE USED
  class IUIComponent : public IComponent, public IEventListener<event::E_GUIReset>
  {
  public:
    IUIComponent(GameObject& obj) : IComponent(obj) {};
    ~IUIComponent() = default;

    virtual void VirtualOnCreate() {};
    virtual void OnDestroy() final {};
    virtual void VirtualOnActivated() final {};
    virtual void VirtualOnDeactivated() final {};
    virtual void Update(float dt) {};

  protected:
    virtual void RegisterUIElements() = 0;
    virtual void UIShown() {};
    virtual void UIHidden() {};

    void ReceiveEvent(const event::E_GUIReset& eventData) override {};

  private:
  };
	// =========================================================
	// ImGui COMPONENT
	// =========================================================
  class IImGuiComponent : public IComponent
  {
  public:
    IImGuiComponent(GameObject& obj);
    ~IImGuiComponent() = default;

    virtual void VirtualOnCreate();
    virtual void OnDestroy() final;
      
    virtual void Update(float dt) {};
  protected:
    void InitializeOverlayWindow(const char* name, math::Vec2 RelativePos, math::Vec2 Size, bool IsSizeRelative, math::Vec2 pivot = {0.0f,0.0f});
    ImGuiWindowFlags m_staticUIFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
  };

	template<typename T>
	using enable_if_base_of_component = std::enable_if_t< std::is_base_of<IComponent, T>::value >;
};

#include "IComponent.inl"