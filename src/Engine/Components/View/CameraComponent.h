#pragma once
#include "../Core.h"
#include "../../Core/GameObject.h"

namespace Engine
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent(GameObject& obj);
		~CameraComponent() override;
		void OnCreate() override;
		void Update(float dt) override;
		void OnCollision(GameObject& other) override;

	private:
		sf::View m_view;
	};
}