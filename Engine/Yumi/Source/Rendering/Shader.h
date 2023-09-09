#pragma once
#include "GraphicsAPI.h"
#include "Asset/Asset.h"

namespace Yumi
{
    class Shader : public Asset
    {
    public:
        static Shared<Shader> Create(GraphicsAPI api);

        virtual ~Shader() = 0;

        virtual bool ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource) = 0;
        virtual bool Initialized() const = 0;

        virtual void Compile() = 0;
        virtual void Compile(const String& vertexSource, const String& fragmentSource) = 0;
        
        virtual void SetUniformMat4(const char* uniformName, const Matrix4& mat) const = 0;
        virtual void SetUniformVec4(const char* uniformName, const Vector4& vec) const = 0;
        virtual void SetUniformInt(const char* uniformName, int num) = 0;
        virtual void SetUniformIntArray(const char* uniformName, const int32_t* array, int32_t size) = 0;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;      
    };
}
