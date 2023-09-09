#pragma once
#include "Rendering/Shader.h"

namespace Yumi
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader() = default;
        OpenGLShader(const String& name, const String& path, const Id& id);
        ~OpenGLShader() override = default;

        bool Load() override;
        void Initialize() override;
        bool Unload() override;

        bool ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource) override;
        bool Initialized() const override { return m_bCompiled; }

        void Compile() override;
        void Compile(const String& vertexSource, const String& fragmentSource) override;

        void SetUniformMat4(const char* uniformName, const Matrix4& mat) const override;
        void SetUniformVec4(const char* uniformName, const Vector4& vec) const override;
        void SetUniformInt(const char* uniformName, int num) override;
        void SetUniformIntArray(const char* uniformName, const int32_t* array, int32_t size) override;

        void Bind() const override;
        void Unbind() const override;

        String GetTypeName() const override { return m_TypeName; }
        String GetName() const override { return m_Name; }
        String GetPath() const override { return m_Path; }
        String GetAbsolutePath() const override { return m_AbsolutePath; }
        Id GetId() const override { return m_Id; }

    private:
        uint32_t m_ShaderId{ 0 };
        bool m_bCompiled{ false };
        String m_VertexSource;
        String m_FragmentSource;

        String m_Name;
        String m_Path;
        String m_AbsolutePath;
        String m_TypeName;
        Id m_Id{ 0 };
    };
}