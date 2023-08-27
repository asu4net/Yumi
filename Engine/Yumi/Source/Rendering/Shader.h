#pragma once

namespace Yumi
{
    class Shader
    {
    public:
        Shader() = default;
        Shader(const String& name, const String& path, const Id& id);
        
        bool Load();
        void Initialize();
        bool Unload();
        
        bool ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource);
        bool Initialized() const { return m_bCompiled; }

        void Compile();
        void Compile(const String& vertexSource, const String& fragmentSource);
        
        void SetUniformMat4(const char* uniformName, const Matrix4& mat) const;
        void SetUniformVec4(const char* uniformName, const Vector4& vec) const;
        void SetUniformInt(const char* uniformName, int num);
        void SetUniformIntArray(const char* uniformName, const int32_t* array, int32_t size);
        
        void Bind() const;
        void Unbind() const;
        
    private:
        uint32_t m_ShaderId{0};
        bool m_bCompiled{false};
        String m_VertexSource;
        String m_FragmentSource;        
    };
}
