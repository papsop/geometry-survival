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
		if (m_animationStates.size() == 0)
			return;

		// [0] is always default state
		if (!m_currentAnimationState)
			SwapAnimationState(m_animationStates[0].get());

		UpdateAnimation(dt);
		CheckStateTransitions();
	}

	void AnimationControllerComponent::FixedUpdate(float dt)
	{

	}

	AnimationState* AnimationControllerComponent::AddAnimationState(const char* animationClipName)
	{
		auto state = std::make_unique<AnimationState>(animationClipName);
		m_animationStates.emplace_back(std::move(state));
		return m_animationStates[m_animationStates.size() - 1].get();
	}

  void AnimationControllerComponent::UpdateAnimation(float dt)
  {
    m_currentSampleTimer -= dt;

    if (m_currentSampleTimer <= 0.0f)
    {
      m_currentSample++;

      if (m_currentSample == m_currentAnimationClip->Samples.size())
        m_currentSample = 0;

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

  void AnimationControllerComponent::CheckStateTransitions()
  {
    // Check current state transitions
    for (const auto& transition : m_currentAnimationState->GetStateTransitions())
    {
      if (transition->CheckTransitionCondition())
      {
        SwapAnimationState(transition->TargetAnimationState);
        return;
      }
    }

    // Check any state transitions
    for (const auto& transition : m_anyStateTransitions)
    {
      // Ignore transitions that point to the current state
      if(*transition->TargetAnimationState == *m_currentAnimationState)
        return;

      if (transition->CheckTransitionCondition())
      {
        SwapAnimationState(transition->TargetAnimationState);
        return;
      }
    }
  }

  void AnimationControllerComponent::SwapAnimationState(AnimationState* newState)
  {
    m_currentAnimationState = newState;
    m_currentSample = 0;
    m_currentSampleTimer = 0.0f;
    m_currentAnimationClip = newState->GetStateAnimationClip().get();
    m_spriteComponent->SetTexture(m_currentAnimationClip->TextureName.c_str());
    ApplySampleData(m_currentAnimationClip->Samples[m_currentSample]);
  }
}