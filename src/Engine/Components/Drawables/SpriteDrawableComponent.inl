#include "SpriteDrawableComponent.h"

namespace Engine
{
  template<typename ... Args>
  void Engine::SpriteDrawableComponent::SetShaderParameter(const char* parameter, Args&& ... args)
  {
    if(!m_shader)
      return;

    m_shader->setParameter(parameter, std::forward<Args>(args) ... );
  }

}