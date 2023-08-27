#include "RenderCommand.h"
#include "RendererAPI.h"

namespace Yumi
{
    RenderCommand::RenderCommand()
    {
        m_RendererAPI.reset(RendererAPI::Create());
    }
}