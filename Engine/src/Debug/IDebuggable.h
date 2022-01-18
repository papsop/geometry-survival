#pragma once
#include "../View/IViewStrategy.h"

namespace Engine
{
    class IDebuggable
    {
    public:
        IDebuggable();
        virtual ~IDebuggable() = default;

        virtual void Debug(view::IViewStrategy* viewStrategy) = 0;
    };
};