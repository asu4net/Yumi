#include "RenderCommand.h"
#include "RendererAPI.h"

namespace Yumi
{
    RenderCommand::RenderCommand(const Shared<RendererAPI>& api)
        : m_RendererAPI(api)
    {
    }
}