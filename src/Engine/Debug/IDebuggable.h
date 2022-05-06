#pragma once
#include "../View/IViewStrategy.h"

namespace Engine
{
    class IDebuggable
    {
    public:
        IDebuggable() = default;
        virtual ~IDebuggable() = default;

        virtual void Debug(view::IViewStrategy* viewStrategy) = 0;

    protected:
        void OnInit();
        void OnDestroy();
    };

    class IDebuggableComponent : public IDebuggable
    {
    public:
        IDebuggableComponent()
        {
            IDebuggable::OnInit();
        }
        ~IDebuggableComponent()
        {
            IDebuggable::OnDestroy();
        }
    };
};