#pragma once
#include "RenderCommand.h"

namespace Yumi
{
    class RenderCommandQueue
    {
    public:
        RenderCommandQueue() = default;
        bool IsEmpty() const  { return m_CommandQueue.empty(); }
        
        template<typename T, typename ...TArgs>
        void Submit(TArgs&& ...args)
        {
            Shared<T> command = std::make_shared<T>(std::forward<TArgs>(args)...);
            m_CommandQueue.push_back(command);
        }

        void ExecuteNext();
        
    private:
        DynamicArray<Shared<RenderCommand>> m_CommandQueue; 
    };
}
