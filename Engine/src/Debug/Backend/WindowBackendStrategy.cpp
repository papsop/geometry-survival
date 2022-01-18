#include "WindowBackendStrategy.h"

#include "../../Components/Core.h"
#include "../../View/Renderables.h"
#include <iostream>

namespace Engine
{
    void WindowBackendStrategy::WriteText(LOGGER_LEVEL level, const char* source, const char* text)
    {
        m_texts.emplace_back(std::string(text));
    }

    void WindowBackendStrategy::Debug(view::IViewStrategy* viewStrategy)
    {
        for (size_t i=0; i< m_texts.size(); ++i)
        {
            Transform t;
            t.Position = sf::Vector2f(15.0f, 10.0f* i);
            view::Text text(t);
            text.Size = 9;
            text.Color = sf::Color::Red;
            text.Value = m_texts[i];
            viewStrategy->Render(text);
        }
    }
};