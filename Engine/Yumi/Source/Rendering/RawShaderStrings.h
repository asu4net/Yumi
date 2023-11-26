#pragma once

namespace Yumi
{
    const char* g_SpriteVertexShaderSource = R"(
        #version 410 core
        
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;
        layout(location = 2) in vec2 a_UV;
        layout(location = 3) in int a_TextureSlot;
        
        uniform mat4 u_ProjectionViewMatrix;
        
        // Vertex output
        out vec4 v_Color;
        out vec2 v_UV;
        flat out int v_TextureSlot;
        
        void main()
        {
            gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0);
            
            v_Color = a_Color;
            v_UV = a_UV;
            v_TextureSlot = a_TextureSlot;
        }
    )";

    const char* g_SpriteFragmentShaderSource = R"(
        #version 410 core
        
        layout(location = 0) out vec4 color;
        
        // Vertex input
        in vec4 v_Color;
        flat in int v_TextureSlot;
        in vec2 v_UV;
        
        uniform sampler2D u_TextureSlots[32];
        
        void main()
        {
            color = texture(u_TextureSlots[v_TextureSlot], v_UV) * v_Color;
        }
    )";

    const char* g_CircleVertexShaderSource = R"(
        #version 410 core
        
        layout(location = 0) in vec3  a_Position;
        layout(location = 1) in vec3  a_LocalPosition;
        layout(location = 2) in vec4  a_Color;
        layout(location = 3) in float a_Thickness;
        layout(location = 4) in float a_Fade;
        
        uniform mat4 u_ProjectionViewMatrix;
        
        // Vertex output
        out vec3  v_LocalPosition;
        out vec4  v_Color;
        out float v_Thickness;
        out float v_Fade;
        
        void main()
        {
            gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0);
            
            v_LocalPosition  = a_LocalPosition;
            v_Color          = a_Color;
            v_Thickness      = a_Thickness;
            v_Fade           = a_Fade;
        }
    )";

    const char* g_CircleFragmentShaderSource = R"(
        #version 410 core
        
        layout(location = 0) out vec4 FragColor;

        // Vertex input
        in vec3  v_LocalPosition;
        in vec4  v_Color;
        in float v_Thickness;
        in float v_Fade;
        
        void main()
        {
            // Calculate distance and fill circle with white
            vec2 localPos = vec2(v_LocalPosition.x * 2, v_LocalPosition.y * 2);
            float distance = 1.0 - length(localPos);
            vec3 color = vec3(smoothstep(0.0, v_Fade, distance));

            color *= vec3(smoothstep(v_Thickness + v_Fade, v_Thickness, distance));

            // Set output color
            if (color.x == 0 && color.y == 0 && color.z == 0)
             discard;

            FragColor = vec4(color, 1.0);

            vec3 circleColor = vec3(v_Color.r, v_Color.g, v_Color.b);
            FragColor.rgb *= circleColor;
        }
    )";

    const char* g_FlatColorVertexShaderSource = R"(
        #version 410 core
        
        layout(location = 0) in vec3 a_Position;
        
        uniform mat4 u_MvpMatrix;
        
        void main()
        {
            gl_Position = u_MvpMatrix * vec4(a_Position, 1.0);
        }
    )";

    const char* g_FlatColorFragmentShaderSource = R"(        
        #version 410 core
        
        layout(location = 0) out vec4 color;
        
        uniform vec4 u_Color;
        
        void main()
        {
            color = u_Color;
        }
    )";
}