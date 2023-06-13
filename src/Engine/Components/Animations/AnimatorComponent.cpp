#include "AnimatorComponent.h"

namespace Engine
{

	AnimatorComponent::AnimatorComponent(GameObject& obj)
		: IComponent(obj)
	{
		SetRequiredComponents<SpriteDrawableComponent>();
	}

	void AnimatorComponent::OnCreate()
	{
		AnimationManager::Get().RegisterAnimator(this);
		m_spriteComponent = Owner.GetComponent<SpriteDrawableComponent>();
	}

	void AnimatorComponent::OnDestroy()
	{
		AnimationManager::Get().UnregisterAnimator(this);
		m_animatorController = nullptr;
	}

	void AnimatorComponent::Update(float dt)
	{
		if (m_animatorController)
		{
			m_animatorController->Update(dt);
		}

		if (m_requestFinished)
			return; // nothing to do, just wait for a new request

		if (m_currentClip)
		{
			m_currentSampleTimer -= dt;
			if (m_currentSampleTimer <= 0.0f)
			{
				m_currentSampleIndex++;

				// Check if it was the last sample
				if (m_currentSampleIndex == m_currentClip->Samples.size())
				{
					if (!m_currentRequest.Data.IsLooped)
					{
						m_requestFinished = true;
						if (m_shouldNotify)
							m_currentRequest.Requester->OnAnimationFinished();
					}
					else
					{
						m_currentSampleIndex = 0;
					}
				}

				if (!m_requestFinished)
				{
					AnimationSample nextSample = m_currentClip->Samples[m_currentSampleIndex];
					m_currentSampleTimer += nextSample.Duration; // '+=' in case of skipping
					ApplySampleDataToSprite(nextSample);
				}
			}
		}
	}

	void AnimatorComponent::SetAnimatorController(std::unique_ptr<AnimatorController> controller)
	{
		m_animatorController = std::move(controller);
		m_animatorController->SetOwnerAnimatorComponent(this);
	}
	
	void AnimatorComponent::RequestAnimationPlay(AnimationPlayRequest request)
	{
		m_currentRequest = request;
		m_shouldNotify = (request.Requester != nullptr);
		m_currentClip = ResourceManager::Get().GetAnimation(request.Data.Clip).get();

		// Reset everything
		m_currentSampleIndex = 0;
		m_currentSampleTimer = m_currentClip->Samples[0].Duration;
		m_requestFinished = false;
		m_spriteComponent->SetTexture(m_currentClip->TextureName.c_str());
		ApplySampleDataToSprite(m_currentClip->Samples[0]);
		if (m_shouldNotify)
		{
			m_currentRequest.Requester->OnAnimationStarted();
		}
	}

	void AnimatorComponent::ApplySampleDataToSprite(AnimationSample& sample)
	{
		sf::IntRect textureRect;
		textureRect.left = sample.TextureCoord.x;
		textureRect.top = sample.TextureCoord.y;
		textureRect.width = m_currentClip->SampleTextureSize.x;
		textureRect.height = m_currentClip->SampleTextureSize.y;

		m_spriteComponent->SetTextureRect(textureRect);
		//LOG_ERROR("Apply sample: [%d, %d, %d, %d]", textureRect.left, textureRect.top, textureRect.width, textureRect.height);
	}

}