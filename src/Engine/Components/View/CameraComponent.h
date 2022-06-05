#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/ViewManager.h"

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