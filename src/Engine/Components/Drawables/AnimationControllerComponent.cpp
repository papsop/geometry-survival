#include "AnimationControllerComponent.h"
#include "../../Managers/ResourceManager.h"
#include "../../Managers/AnimationManager.h"
#include "../Animations/AnimationData.h"

namespace Engine
{
	AnimationControllerComponent::AnimationControllerComponent(GameObject& obj)
		: IComponent(obj)
		, m_stateMachine(*this)
	{
		SetRequiredComponents<Engine::SpriteDrawableComponent>();
	}

	void AnimationControllerComponent::VirtualOnCreate()
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
		if(!m_isPlayingForcedAnimation)
			m_stateMachine.Update(dt);

		UpdateAnimation(dt);
	}

	void AnimationControllerComponent::FixedUpdate(float dt)
	{

	}

	void AnimationControllerComponent::PlayForcedAnimationClip(const char* animationClipName)
	{
		m_isPlayingForcedAnimation = true;
		PlayAnimationClipFromSM(animationClipName);
	}

	std::string AnimationControllerComponent::GetRunningAnimationClipName()
	{
		return (m_currentAnimationClip) ? m_currentAnimationClip->Name : "";
	}

	void AnimationControllerComponent::UpdateAnimation(float dt)
  {
		if (!m_currentAnimationClip)
			return;

    m_currentSampleTimer -= dt;
    if (m_currentSampleTimer <= 0.0f)
    {
      m_currentSample++;

			if (m_currentSample == m_currentAnimationClip->Samples.size())
			{
				m_currentSample = 0;
				if (m_isPlayingForcedAnimation)
				{
					m_stateMachine.ResetToDefaultState();
					m_isPlayingForcedAnimation = false;
				}
			}

      m_currentSampleTimer = 0.0f;
      ApplySampleData(m_currentAnimationClip->Samples[m_currentSample]);
    }
  }

	void AnimationControllerComponent::ApplySampleData(const AnimationSample& sample)
	{
		sf::IntRect textureRect;
		textureRect.left = sample.TextureCoord.x;
		textureRect.top = sample.TextureCoord.y;
		textureRect.width = m_currentAnimationClip->SampleTextureSize.x;
		textureRect.height = m_currentAnimationClip->SampleTextureSize.y;
    m_currentSampleTimer = sample.Duration;

		m_spriteComponent->SetTextureRect(textureRect);
		//LOG_ERROR("Apply sample: [%d, %d, %d, %d]", textureRect.left, textureRect.top, textureRect.width, textureRect.height);
	}

	void AnimationControllerComponent::PlayAnimationClipFromSM(const char* animationClipName)
	{
		return;
		//m_currentAnimationClip = ResourceManager::Get().GetAnimation(animationClipName).get();
		if (m_currentAnimationClip->Samples.size() == 0)
		{
			LOG_ERROR("Animation clip '%s' has no samples", animationClipName);
			return;
		}
		m_currentSample = 0;
		m_currentSampleTimer = 0.0f;
		m_spriteComponent->SetTexture(m_currentAnimationClip->TextureName.c_str());
		ApplySampleData(m_currentAnimationClip->Samples[m_currentSample]);
		LOG_INFO("Entity '%s' starting animation '%s'", Owner.DebugName, animationClipName);
	}
}