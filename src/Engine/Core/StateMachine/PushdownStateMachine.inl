#include "PushdownStateMachine.h"

namespace Engine
{
	template<typename _State>
	template<typename T, typename ... Args>
	void PushdownStateMachine<_State>::AddState(Args&& ... args)
	{
		if(m_activeState)
			m_activeState->OnTransitionOut();
		m_states.push(std::make_unique<T>(m_ownerGameObject, *this, std::forward<Args>(args) ...));
		m_activeState = m_states.top().get();
		m_activeState->OnTransitionIn();
	}

	template<typename _State>
  void PushdownStateMachine<_State>::Update(float dt)
  {
    if (m_activeState)
      m_activeState->Update(dt);
  }

  template<typename _State>
  bool PushdownStateMachine<_State>::IsEmpty()
  {
    return m_states.empty();
  }

  template<typename _State>
  _State* PushdownStateMachine<_State>::GetActiveState()
  {
    return m_activeState;
  }

  template<typename _State>
  void PushdownStateMachine<_State>::ProcessMessage(const Engine::Message& message)
  {
    if (m_activeState)
      m_activeState->ProcessMessage(message);
  }

  template<typename _State>
  void PushdownStateMachine<_State>::PopState()
  {
    m_activeState->OnTransitionOut();
    m_states.pop();
    m_activeState = m_states.top().get();
    m_activeState->OnTransitionIn();
  }

  template<typename _State>
  void PushdownStateMachine<_State>::Clear()
  {
    while (!m_states.empty())
    {
      m_states.pop();
    }
    m_activeState = nullptr;
  }
};