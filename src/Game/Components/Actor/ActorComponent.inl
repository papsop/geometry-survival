#include "ActorComponent.h"

namespace Game
{
	template<typename T,
			typename ... Args,
			typename
	>
	void ActorComponent::AddCommand(Args&& ... args)
	{
		auto command = std::make_unique<T>(std::forward<Args>(args) ... );
		m_commandsQueue.push(std::move(command));
	}
}