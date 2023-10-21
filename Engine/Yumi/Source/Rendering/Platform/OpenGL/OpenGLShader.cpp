#include "OpenGLShader.h"
#include <glad/glad.h>

namespace Yumi
{
    OpenGLShader::OpenGLShader() = default;

    bool OpenGLShader::Load()
    {
        const String absolutePath = GetAssetData().AbsolutePath;
        if (absolutePath == "None")
            return true;

        if (!ReadFromFile(absolutePath, m_VertexSource, m_FragmentSource))
            return false;

        Compile();
        return true;
    }

    void OpenGLShader::Unload()
    {
        glDeleteProgram(m_ShaderId);
    }
    
    void OpenGLShader::Compile()
    {
        Compile(m_VertexSource, m_FragmentSource);
    }

    void OpenGLShader::Compile(const String& vertexSource, const String& fragmentSource)
    {
        if (m_bCompiled) return;

        // Create an empty vertex shader handle
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that String's .c_str is NULL character terminated.
        const GLchar* source = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, nullptr);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            DynamicArray<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());
            printf("Error compiling the vertex shader: '%s'\n", infoLog.data());

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            YCHECK(false, "Vertex shader compilation failed!");
        }

        // Create an empty fragment shader handle
        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that String's .c_str is NULL character terminated.
        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, nullptr);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            DynamicArray<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());
            printf("Error compiling the fragment shader: '%s'\n", infoLog.data());

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            YCHECK(false, "Fragment shader compilation failed!");
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ShaderId = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ShaderId, vertexShader);
        glAttachShader(m_ShaderId, fragmentShader);

        // Link our program
        glLinkProgram(m_ShaderId);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ShaderId, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ShaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            DynamicArray<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ShaderId, maxLength, &maxLength, infoLog.data());

            // We don't need the program anymore.
            glDeleteProgram(m_ShaderId);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            YCHECK(false, "Shader linkage failed!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_ShaderId, vertexShader);
        glDetachShader(m_ShaderId, fragmentShader);

        m_bCompiled = true;
    }

    bool OpenGLShader::ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource)
    {
        static String content;
        std::ifstream fileStream(fileLocation, std::ios::in);

        if (!fileStream.is_open())
        {
            printf("Failed to read %s! File doesn't exist.\n", fileLocation.c_str());
            return false;
        }

        String line;

        enum class ShaderType { None, Vertex, Fragment };
        ShaderType currentShader = ShaderType::None;

        while (!fileStream.eof())
        {
            std::getline(fileStream, line);

            if (line.find("#type") != String::npos)
            {
                if (line.find("vertex") != String::npos)
                {
                    currentShader = ShaderType::Vertex;
                    continue;
                }

                if (line.find("fragment") != String::npos)
                {
                    currentShader = ShaderType::Fragment;
                    continue;
                }
            }

            switch (currentShader)
            {
            case ShaderType::None: continue;
            case ShaderType::Vertex: vertexSource.append(line + "\n"); continue;
            case ShaderType::Fragment: fragmentSource.append(line + "\n"); continue;
            }
        }

        fileStream.close();
        return true;
    }

    void OpenGLShader::SetUniformMat4(const char* uniformName, const Matrix4& mat) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        //glUniformMatrix4fv(id, 1, false, glm::value_ptr(mat));
    }

    void OpenGLShader::SetUniformVec4(const char* uniformName, const Vector4& vec) const
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        //glUniform4fv(id, 1, glm::value_ptr(vec));
    }

    void OpenGLShader::SetUniformInt(const char* uniformName, const int num)
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        glUniform1i(id, num);
    }

    void OpenGLShader::SetUniformIntArray(const char* uniformName, const int32_t* array, const int32_t size)
    {
        const uint32_t id = glGetUniformLocation(m_ShaderId, uniformName);
        glUniform1iv(id, size, array);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderId);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }
}