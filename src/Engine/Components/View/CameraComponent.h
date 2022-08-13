#pragma once
#include "../Core.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../Managers/ViewManager.h"
#include "../../Debug/IDebuggable.h"

namespace Engine
{
	class CameraComponent : public IComponent, public IDebuggableComponent
	{
	public:
		CameraComponent(GameObject& obj, GameObject* target);
		~CameraComponent() override;
		void OnCreate() override;
		void Update(float dt) override;

		void SetTarget(GameObject* newTarget);

		void Debug(view::IViewStrategy* viewStrategy) override;

	private:
		CameraData m_cameraData;
		GameObject* m_target;
	};
}