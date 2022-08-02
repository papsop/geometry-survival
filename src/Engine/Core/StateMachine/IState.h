#pragma once
#include <type_traits>
#include "../Messaging/MessageTypes.h"

namespace Engine
{

    class Scene;
    class FiniteStateMachine;

    class IState
    {
    public:
        IState(FiniteStateMachine& parentStateMachine) 
            : m_parentStateMachine(parentStateMachine) {};

        virtual ~IState() = default;

        virtual void OnTransitionIn() {}
        virtual void OnTransitionOut() {}; 

        virtual void Update(float dt) = 0;
        virtual void ProcessMessage(const Message& message) { };

    protected:
        FiniteStateMachine& m_parentStateMachine;
    };

	template<typename T>
	using enable_if_base_of_state = std::enable_if_t< std::is_base_of<IState, T>::value >;
}
