#include "AnimationControllerComponent.h"
#include "../../Managers/AnimationManager.h"
#include "../../Managers/ResourceManager.h"

namespace Engine
{
	AnimationControllerComponent::AnimationControllerComponent(GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<Engine::SpriteDrawableComponent>();
	}

	void AnimationControllerComponent::OnCreate()
	{
		AnimationManager::Get().RegisterAnimationController(this);
		m_spriteComponent = Owner.GetComponent<SpriteDrawableComponent>();
	}

	void AnimationControllerComponent::OnDestroy()
	{
		AnimationManager::Get().UnregisterAnimationController(this);
	}

	void AnimationControllerComponent::Update(float dt)
	{
		if (m_maxSamples == 0)
			return;

		m_currentTimer += dt;

		AnimationSample& currentSample = m_animationClip->Samples[m_currentSample];

		if (m_currentTimer > currentSample.Duration)
		{
			m_currentSample++;
			if (m_currentSample == m_maxSamples)
			{
				m_currentSample = 0;
			}
			m_currentTimer = 0.0f;
		}

		m_spriteComponent->SetTexture(m_animationClip->TextureName.c_str());
		sf::IntRect textureRect;
		textureRect.top = currentSample.TextureCoord.y;
		textureRect.left = currentSample.TextureCoord.x;
		textureRect.width = m_animationClip->SampleTextureSize.x;
		textureRect.height = m_animationClip->SampleTextureSize.y;
		
		m_spriteComponent->SetTextureRect(textureRect);
	}

	void AnimationControllerComponent::FixedUpdate(float dt)
	{

	}

	void AnimationControllerComponent::AddAnimationClip(const char* name)
	{
		m_animationClip = ResourceManager::Get().GetAnimation(name);
		m_currentTimer = 0.0f;
		m_currentSample = 0;
		m_maxSamples = m_animationClip->Samples.size();
	}

}