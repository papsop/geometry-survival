#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/ViewManager.h"

namespace Engine
{
	class CameraComponent : public IComponent
	{
	public:
		CameraComponent(GameObject& obj, GameObject* target);
		~CameraComponent() override;
		void OnCreate() override;
		void Update(float dt) override;

		void SetTarget(GameObject* newTarget);
	private:
		CameraData m_cameraData;
		GameObject* m_target;
	};
}