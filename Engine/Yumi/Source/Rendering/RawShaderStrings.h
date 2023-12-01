#pragma once

namespace Yumi
{
    const char* g_SpriteVertexShaderSource = R"(
        #version 410 core
        
        layout(location = 0) in vec3  a_Position;
        layout(location = 1) in vec4  a_Color;
        layout(location = 2) in vec2  a_UV;
        layout(location = 3) in int   a_TextureSlot;
        layout(location = 4) in int   a_Shape;
        layout(location = 5) in vec3  a_LocalPosition;
        layout(location = 6) in float a_Thickness;
        layout(location = 7) in float a_Fade;
        
        uniform mat4 u_ProjectionViewMatrix;
        
        // Vertex output
        
        out vec4     v_Color;
        out vec2     v_UV;
        flat out int v_TextureSlot;
        flat out int v_Shape;
        out vec3     v_LocalPosition;
        out float    v_Thickness;
        out float    v_Fade;
        
        void main()
        {
            gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0);
            
            v_Color         = a_Color;
            v_UV            = a_UV;
            v_TextureSlot   = a_TextureSlot;
            v_Shape         = a_Shape;
            v_LocalPosition = a_LocalPosition;
            v_Thickness     = a_Thickness;
            v_Fade          = a_Fade;
        }
    )";

    const char* g_SpriteFragmentShaderSource = R"(
        #version 410 core
        
        layout(location = 0) out vec4 FragColor;
        
        // Vertex input
        in vec4     v_Color;
        in vec2     v_UV;
        flat in int v_TextureSlot;
        flat in int v_Shape;
        in vec3     v_LocalPosition;
        in float    v_Thickness;
        in float    v_Fade;
        
        uniform sampler2D u_TextureSlots[32];
        
        void main()
        {
            if (v_Shape == 0) // Sprite
            {
                FragColor = texture(u_TextureSlots[v_TextureSlot], v_UV) * v_Color;
                return;
            }
            
            if (v_Shape == 1) // Circle
            {
                // Calculate distance and fill circle with white
                vec2 localPos = vec2(v_LocalPosition.x * 2, v_LocalPosition.y * 2);
                float distance = 1.0 - length(localPos);
                vec3 color = vec3(smoothstep(0.0, v_Fade, distance));
                
                color *= vec3(smoothstep(v_Thickness + v_Fade, v_Thickness, distance));
                
                // Set output color
                if (color.x == 0 && color.y == 0 && color.z == 0)
                 discard;
                               
                FragColor = texture(u_TextureSlots[v_TextureSlot], v_UV) * vec4(color, 1.0);
                
                vec3 circleColor = vec3(v_Color.r, v_Color.g, v_Color.b);
                FragColor.rgb *= circleColor;
                return;
            }

            if (v_Shape == 2) // Rect
            {
                float xBound = 0.5 - v_Thickness;
                float yBound = 0.5 - v_Thickness;

                if (abs(v_LocalPosition.x) <= xBound && abs(v_LocalPosition.y) <= yBound)
                {
                    if (v_TextureSlot != 0) FragColor = texture(u_TextureSlots[v_TextureSlot], v_UV) * v_Color;
                    else discard;
                }
                else
                {
                    FragColor = v_Color;
                }                 
                return;
            }                  
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