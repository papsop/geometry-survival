#pragma once
#include <type_traits>
#include "../Messaging/MessageTypes.h"

namespace Engine
{
    class Scene;
    class PushdownStateMachine;
    class FiniteStateMachine;

    template<
        typename T, 
        typename = std::enable_if_t< std::is_same_v<PushdownStateMachine, T> || std::is_same_v<FiniteStateMachine, T> >
        >
    class IState
    {
    public:
        IState(T& parentStateMachine) 
            : m_parentStateMachine(parentStateMachine) {};

        virtual ~IState() = default;

        virtual void OnTransitionIn() {}
        virtual void OnTransitionOut() {}; 

        virtual void Update(float dt) = 0;
        virtual void ProcessMessage(const Message& message) { };

    protected:
        T& m_parentStateMachine;
    };

	template<typename _StateMachine, typename T>
	using enable_if_base_of_state = std::enable_if_t< std::is_base_of<IState<_StateMachine>, T>::value >;
}