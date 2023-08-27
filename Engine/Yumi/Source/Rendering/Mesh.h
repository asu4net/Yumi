#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace Yumi
{
    class Mesh
    {
    public:
        Mesh(const String& name, const String& path, const Id& id);

        Shared<VertexArray> GetVertexArray() const { return m_VertexArray; }
        
        bool Load();
        void Initialize();
        bool Unload();

    private:
        Shared<VertexArray> m_VertexArray;
        Shared<VertexBuffer> m_VertexBuffer;
        Shared<IndexBuffer> m_IndexBuffer;
    };
}
