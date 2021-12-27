#include "ViewManager.h"
#include "../Components/Core.h"
#include "../Core/GameObject.h"
#include <memory>
#include <assert.h>

namespace Game
{
    namespace view
    {
        void ViewManager::PollEvents()
        {
            assert(m_viewStrategy != nullptr && "No view strategy set.");
            m_viewStrategy->PollEvents();
        }

        void ViewManager::RegisterComponent(IComponent *component)
        {
            
        }

        void ViewManager::PreRender() { m_viewStrategy->PreRender(); }
        
        void ViewManager::PostRender() { m_viewStrategy->PostRender(); }

        void ViewManager::RenderRegisteredComponents()
        {
            m_viewStrategy->PreRender();

            for (auto s : m_shapes)
                m_viewStrategy->Render(*s);

            m_viewStrategy->PostRender();
        }
    };
};