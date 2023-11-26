﻿#include "Shader.h"
#include "Core\Engine.h"
#include "Renderer.h"

namespace Yumi
{
    bool Shader::Load()
    {
        const String absolutePath = GetAssetData().AbsolutePath;
        if (absolutePath == "None")
            return true;

        if (!ReadFromFile(absolutePath, m_VertexSource, m_FragmentSource))
            return false;

        m_RendererShaderId = GetRenderer().CreateShader(m_VertexSource.c_str(), m_FragmentSource.c_str());
        return true;
    }

    void Shader::Unload()
    {
        GetRenderer().DestroyShader(m_RendererShaderId);
    }

    bool Shader::ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource)
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
}