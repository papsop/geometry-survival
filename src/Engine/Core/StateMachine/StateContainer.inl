#include "StateContainer.h"

namespace Engine
{
	template<typename T, typename ... Args, typename>
	void StateContainer::CreateAndSetState(Args&&... args)
	{
		if(m_currentState)
			m_previousState = std::move(m_currentState);

		m_currentState = std::make_unique<T>(*this, std::forward<Args>(args) ...);
		m_currentState->OnInit();
	}
}