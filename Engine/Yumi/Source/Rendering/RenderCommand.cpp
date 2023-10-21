#include "RenderCommand.h"
#include "RendererAPI.h"

namespace Yumi
{
    RenderCommand::RenderCommand(const SharedPtr<RendererAPI>& api)
        : m_RendererAPI(api)
    {
    }
}