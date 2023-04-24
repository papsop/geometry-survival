#pragma once
#include "../View/IViewStrategy.h"
#include "VisualDebugContext.h"

namespace Engine
{
  class IDebuggable
  {
  public:
    IDebuggable() = default;
    virtual ~IDebuggable() = default;

      virtual void Debug(view::IViewStrategy* viewStrategy) {};
      virtual void Debug(VisualDebugContext& debugContext) {};

    protected:
      void DebuggableOnInit();
      void DebuggableOnDestroy();
    };

    class IDebuggableComponent : public IDebuggable
    {
    public:
      IDebuggableComponent()
      {
        IDebuggable::DebuggableOnInit();
      }
      ~IDebuggableComponent()
      {
        IDebuggable::DebuggableOnDestroy();
      }
    };
};