#pragma once

namespace Game
{
  class UIStateMachine;
  
  class UIState
  {
  public:
    UIState() = default;
    ~UIState() = default;
    
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void OnEscapeAction() = 0;

    // A state can be created before being assigned to a state machine
    // therefore we need to set it after the creation
    // TODO: template UIStateMachine method to create states and have the ownership? 
    // then we can use a reference in the constructor
    void SetParentStateMachine(UIStateMachine* fsm){ m_stateMachine = fsm; }
  protected:
    UIStateMachine* m_stateMachine;
  };
}