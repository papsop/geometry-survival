#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

namespace Engine{
namespace view {

  class IGuiView
  {
  public:
    tgui::Gui& GetGui() { return m_gui; };

  protected:
    tgui::Gui m_gui;
  };

}};