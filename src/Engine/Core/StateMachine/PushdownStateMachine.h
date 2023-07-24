#pragma once
#include "IState.h"
#include <stack>
#include <memory>

namespace Engine
{

	class GameObject;

	template<typename _State>
	class PushdownStateMachine
	{
	public:
		PushdownStateMachine(GameObject& owner) : m_ownerGameObject(owner) {};
		~PushdownStateMachine() = default;

		void Update(float dt);
		void PopState();
		void Clear();

		template<
			typename T,
			typename ... Args
		>
		void AddState(Args&& ... args);

		bool IsEmpty();
		_State* GetActiveState();

	private:
		std::stack< std::unique_ptr<_State> > m_states = {};
		_State* m_activeState = nullptr;
		GameObject& m_ownerGameObject;
	};
};

#include "PushdownStateMachine.inl"