#include "Mesh.h"

namespace Yumi
{
    struct MeshVertex
    {
        Vector3 Position;
        Vector3 Normal;
        Vector2 UV;
    };
    
    Mesh::Mesh(const String& name, const String& path, const Id& id)
    {
    }

    bool Mesh::Load()
    {
        
        
        return true;
    }

    void Mesh::Initialize()
    {
        //tinyobj::attrib_t attrib;
        //DynamicArray<tinyobj::shape_t> shapes;
        //DynamicArray<tinyobj::material_t> materials;
        //String warn, err;

        //if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, GetAbsolutePath().c_str()))
        //{
        //    if (!warn.empty())
        //        std::cout << "Model loading warning: " << warn;
        //    if (!err.empty())
        //        std::cout << "Model loading error: " << err;
        //    
        //    return;
        //}

        //DynamicArray<MeshVertex*> meshVertices;
        //DynamicArray<uint32_t*> meshIndices;
        //
        //for (const auto& shape : shapes)
        //{
        //    for (const auto& index : shape.mesh.indices)
        //    {
        //        // Vertices
        //        MeshVertex* meshVertex = new MeshVertex();
        //        meshVertex->Position.x = attrib.vertices[3 * index.vertex_index + 0];
        //        meshVertex->Position.y = attrib.vertices[3 * index.vertex_index + 1];
        //        meshVertex->Position.z = attrib.vertices[3 * index.vertex_index + 2];
        //        
        //        meshVertex->Normal.x = attrib.normals[3 * index.normal_index + 0];
        //        meshVertex->Normal.y = attrib.normals[3 * index.normal_index + 1];
        //        meshVertex->Normal.z = attrib.normals[3 * index.normal_index + 2];
        //        
        //        meshVertex->UV.x = attrib.texcoords[2 * index.texcoord_index + 0];
        //        meshVertex->UV.y = attrib.texcoords[2 * index.texcoord_index + 1];
        //        meshVertices.push_back(meshVertex);
        //        
        //        // Indices
        //        uint32_t* indexPtr = new uint32_t();
        //        *indexPtr = index.vertex_index;
        //        meshIndices.push_back(indexPtr);
        //    }
        //}
        //
        //m_VertexArray = VertexArray::Create();
        //m_VertexBuffer = VertexBuffer::Create(meshVertices[0], sizeof(MeshVertex) * meshVertices.size());
        //
        //m_VertexBuffer->SetLayout({
        //        {ShaderDataType::Float3, "a_Position"},
        //        {ShaderDataType::Float3, "a_Normal"},
        //        {ShaderDataType::Float2, "a_UV"},
        //});
        //
        //m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        //m_IndexBuffer = IndexBuffer::Create(meshIndices[0], meshIndices.size());
        //m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    bool Mesh::Unload()
    {
        //return Asset::Unload();
        return false;
    }
}
