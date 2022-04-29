#pragma once
#include "../Core.h"
#include "../../Core/GameObject.h"
#include "../../Subsystems/ViewSubsystem.h"

namespace Engine
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent(GameObject& obj);
		~CameraComponent() override;
		void OnCreate() override;
		void Update(float dt) override;
		void OnCollisionStart(GameObject* other) override;

	private:
		CameraData m_cameraData;
	};
}