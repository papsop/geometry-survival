#pragma once
#include <type_traits>
#include "../Messaging/MessageTypes.h"

namespace Engine
{
    class Scene;
    template<typename _State>
    class PushdownStateMachine;
    class GameObject;

    template<
      typename T,
      typename = std::enable_if_t< std::is_enum_v<T> >
    >
    class IState
    {
    public:
      using StateMachine = PushdownStateMachine < IState<T> >;

      IState(GameObject& go, StateMachine& sm, T st)
        : m_parentGameObject(go)
        , m_parentStateMachine(sm)
        , m_stateValue(st) {};

      virtual ~IState() = default;

      virtual void OnTransitionIn() {}
      virtual void OnTransitionOut() {};

      virtual void Update(float dt) = 0;
      virtual void ProcessMessage(const Message & message) { };

      T GetStateValue() { return m_stateValue; }
    protected:
      T m_stateValue; // always enum that identifies this state
      GameObject& m_parentGameObject;
      StateMachine& m_parentStateMachine;
    };

	template<typename _StateMachine, typename T>
	using enable_if_base_of_state = std::enable_if_t< std::is_base_of<IState<_StateMachine>, T>::value >;
}