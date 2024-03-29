#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

#include "../Components/Core/IComponent.h"
#include "../Core/EventData.h"
#include "../Core/Events.h"
#include "../Core/Signal.h"
#include "../Debug/IDebuggable.h"
#include "../Debug/VisualDebugContext.h"
#include "IManager.h"

namespace Engine {
class Application;

struct ResolutionEntry {
  const char* Name;
  math::Vec2 Value;
  ResolutionEntry(const char* name, math::Vec2 val) : Name(name), Value(val) {}
  ResolutionEntry() = default;
};

struct RenderManagerSettings {
  ResolutionEntry ResolutionEntry;
  bool Fullscreen;
};

class RenderManager : public IManager, public IEventListener<event::E_OnShowDebugKeyAction> {
  friend class Application;

 public:
  static RenderManager& Get();

  ~RenderManager() = default;

  void Update(float dt) override;

  void PollEvents();
  sf::Vector2f GetMousePosition();

  // Component registration
  void RegisterComponent(IDrawableComponent* component);
  void RegisterComponent(IDebuggable* component);
  void RegisterComponent(IImGuiComponent* component);
  void UnregisterComponent(IDrawableComponent* component);
  void UnregisterComponent(IImGuiComponent* component);
  void UnregisterComponent(IDebuggable* component);

  // Helper functions
  inline float coordToPixel(float coord) { return coord * m_pixelsPerMeter; };
  inline float pixelToCoord(float pixel) { return pixel / m_pixelsPerMeter; };
  inline sf::Vector2f coordsPosToPixelsPos(b2Vec2 coords) { return {coords.x * m_pixelsPerMeter, -coords.y * m_pixelsPerMeter}; };
  inline b2Vec2 pixelsPosToCoordsPos(sf::Vector2f pixels) { return {pixels.x / m_pixelsPerMeter, -pixels.y / m_pixelsPerMeter}; };
  inline sf::Vector2f coordsToPixels(b2Vec2 coords) { return {coords.x * m_pixelsPerMeter, coords.y * m_pixelsPerMeter}; };
  inline b2Vec2 pixelsToCoords(sf::Vector2f pixels) { return {pixels.x / m_pixelsPerMeter, pixels.y / m_pixelsPerMeter}; };
  inline float Box2DRotationToSFML(float angle) { return 360.0f - math::RAD_TO_DEG(angle); }

  float GetPPM() { return m_pixelsPerMeter; }
  void SetView(CameraData cameraData);

  RenderManagerSettings GetSettings() const { return m_currentSettings; }
  void SetSettings(RenderManagerSettings settings);
  Signal<void> OnSettingsChanged;

  const sf::Font& GetFont() const { return m_font; }
  std::vector<ResolutionEntry> GetResolutionEntries() const { return m_resolutionEntries; }

  void ReloadWindow();
  void DestroyWindow();

  void ShowMouse(bool val);

  bool IsDebugEnabled(std::string val);
  void RegisterDebug(std::string val);

 protected:
  void VirtualOnInit() override;
  void VirtualOnDestroy() override;

  void ReceiveEvent(const event::E_OnShowDebugKeyAction& eventData) override;

 private:
  bool m_shouldUpdateDebugs = false;
  float m_pixelsPerMeter = 7.f;
  std::unique_ptr<sf::RenderWindow> m_window;
  std::vector<IDrawableComponent*> m_drawableComponents;
  std::vector<IImGuiComponent*> m_imGuiComponents;
  std::vector<IDebuggable*> m_debuggableComponents;
  sf::Font m_font;
  VisualDebugContext m_debugContext;
  std::unordered_map<std::string, bool> m_debugs;  // default is false for every debug
  std::vector<ResolutionEntry> m_resolutionEntries;
  RenderManagerSettings m_currentSettings;

  RenderManager();
  void RenderDebugDraw(float dt);
  void RenderDrawables(float dt);
  void RenderImGui(float dt);
};
}  // namespace Engine
