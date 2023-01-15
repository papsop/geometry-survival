#include "CombatTextComponent.h"
#include <Engine/Application.h>
#include <Engine/Managers/ViewManager.h>
#include "../../Managers/GameManager.h"

namespace Game
{

  CombatTextComponent::CombatTextComponent(Engine::GameObject& obj)
    : IUIComponent(obj)
  {

  }

  void CombatTextComponent::AddCombatTextEntry(CombatTextDef def)
  {
    return;


    // TODO:
    //  - TGUI isn't really helpful with positioning labels in world coordinates
    //  - conversion from world to space doesn't work for some reason, the label gets shown in weird locations
    

//     CombatTextEntry entry;
//       entry.Def = def;
//   
//       tgui::Label::Ptr labelPtr = tgui::Label::create(def.Value);
//       auto pixels = Engine::ViewManager::Get().MapCoordsToPixel({ def.Position.x, def.Position.y});
//       labelPtr->setOrigin(0.5f, 0.5f);
//       labelPtr->setPosition({pixels.x, pixels.y});
//       labelPtr->setTextSize(48);
//       labelPtr->setVisible(true);
//   
//       entry.LabelPtr = labelPtr;
//       m_group->add(entry.LabelPtr);
//       m_entries.emplace_back(entry);
//     
  } 

  void CombatTextComponent::RegisterUIElements()
  {
  }
  
  void CombatTextComponent::UIShown()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RegisterCombatTextComponent(this);
  }

  void CombatTextComponent::UIHidden()
  {
    Engine::Application::Instance().GetGameManager<GameManager>()->RegisterCombatTextComponent(nullptr);
  }

  void CombatTextComponent::Update(float dt)
  {

  }

}