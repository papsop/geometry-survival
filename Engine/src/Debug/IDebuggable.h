#pragma once
#include "../View/IViewStrategy.h"

namespace Engine
{
    class IDebuggable
    {
    public:
        IDebuggable();
        virtual ~IDebuggable();

        virtual void Debug(view::IViewStrategy* viewStrategy) = 0;
    };
};