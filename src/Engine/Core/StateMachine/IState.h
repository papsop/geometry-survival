#pragma once
#include <type_traits>
#include "../Messaging/MessageTypes.h"

namespace Engine
{

    class Scene;
    class StateContainer;

    class IState
    {
    public:
        IState(StateContainer& container)
            : m_parentContainer(container) {};
        ~IState() = default;

        virtual void OnInit() {};
        virtual void OnDestroy() {};

        virtual void OnReset() {};

        virtual void Update(float dt) = 0;
        virtual void ProcessMessage(const Message& message) { };
    protected:
        StateContainer& m_parentContainer;
    };

	template<typename T>
	using enable_if_base_of_state = std::enable_if_t< std::is_base_of<IState, T>::value >;
}
