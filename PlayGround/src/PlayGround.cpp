#include <Shunya.h>
#include "Core/openGL/OpenGLShader.h"
#include <imgui.h>
#include "Core/Core.h"

#include "Core/imGui/imguiLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Shunya::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        // -------------------------------------------------------------
        // 1. TRIANGLE RENDERING SETUP
        // -------------------------------------------------------------

        m_VertexArray.reset(Shunya::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        std::shared_ptr<Shunya::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Shunya::VertexBuffer::Create(vertices, sizeof(vertices)));

        Shunya::BufferLayout layout = {
            { Shunya::ShaderDataType::Float3, "a_Position" },
            { Shunya::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<Shunya::IndexBuffer> indexBuffer;
        indexBuffer.reset(Shunya::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // -------------------------------------------------------------
        // 2. SQUARE RENDERING SETUP
        // -------------------------------------------------------------
        m_SquareVA.reset(Shunya::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f,0.0f,
             0.5f, -0.5f, 0.0f,1.0f,0.0f,
             0.5f,  0.5f, 0.0f,1.0f,1.0f,
            -0.5f,  0.5f, 0.0f,0.0f,1.0f
        };
        std::shared_ptr<Shunya::VertexBuffer> squareVB;
        squareVB.reset(Shunya::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({
            { Shunya::ShaderDataType::Float3, "a_Position" },
            { Shunya::ShaderDataType::Float2, "a_TexCoord" }
            });

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Shunya::IndexBuffer> squareIB;
        squareIB.reset(Shunya::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        // -------------------------------------------------------------
        // 3. SHADERS
        // -------------------------------------------------------------
        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
    
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);    
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(Shunya::OpenGLShader::Create(vertexSrc, fragmentSrc));


        std::string blueShaderVertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform; 

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);    
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            
            uniform vec3 u_Color; 

            in vec3 v_Position;
            void main()
            {
                // Use the uniform color instead of hardcoded blue
                color = vec4(u_Color, 1.0); 
            }
        )";

        m_FlatColorShader.reset(Shunya::OpenGLShader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
       
        std::string TextureShaderVertexSrc = R"(
            #version 330 core
    
    
            layout(location = 0) in vec3 a_Position;

            layout(location = 1) in vec2 a_TexCoord; 

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform; 

            out vec2 v_TexCoord; 

            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);    
            }
        )";

        std::string TextureShaderFragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            
            // FIX 1: Must match Vertex Shader output EXACTLY (Case Sensitive!)
            in vec2 v_TexCoord; 
            
            // FIX 2: It is 'sampler2D', not 'sample2D'
            uniform sampler2D u_Texture; 

            void main()
            {
                color = texture(u_Texture, v_TexCoord); 
            }
        )";

        m_TextureShader.reset(Shunya::OpenGLShader::Create(TextureShaderVertexSrc, TextureShaderFragmentSrc));
        

        m_Texture = Shunya::Texture2D::Create("assets/textures/Me.jpg");

        std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

    }
    void OnUpdate(Shunya::Timestamp ts) override
    {
        // FPS
        SHUNYA_INFO("Timestep: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSec());

        if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_LEFT))
            m_CameraPosition.x -= m_CameraSpeed ; 
        else if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_RIGHT))
            m_CameraPosition.x += m_CameraSpeed ; 

        if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_UP))
            m_CameraPosition.y += m_CameraSpeed ; 
        else if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_DOWN))
            m_CameraPosition.y -= m_CameraSpeed ; 

        if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed ; 
        else if (Shunya::Input::IsKeyPressed(SHUNYA_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed ; 

        Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        Shunya::RendererCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Shunya::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        // UPLOAD COLOR: We bind the shader and send the color from ImGui
        std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                glm::vec3 pos(j * 0.11f, i * 0.11f, 0.0f);
                
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                Shunya::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }
        m_Texture->Bind();
        Shunya::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // RENDER TRIANGLE
        // Note: Explicitly passing Identity Matrix to avoid garbage transform
        auto textureShader = m_Shader;
        //Shunya::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));

        Shunya::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
     
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Shunya::Event& event) override
    {
        
    }

private:
    Shunya::Ref<Shunya::Shader> m_Shader;
    Shunya::Ref<Shunya::VertexArray> m_VertexArray;

    Shunya::Ref<Shunya::Shader> m_FlatColorShader,m_TextureShader;
    Shunya::Ref<Shunya::VertexArray> m_SquareVA;

    Shunya::Ref<Shunya::Texture2D> m_Texture;

    Shunya::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;


    float m_CameraSpeed = 0.1f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 45.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class PlayGround : public Shunya::Application
{
public:
    PlayGround()
    {
        PushLayer(new ExampleLayer());
    }
    ~PlayGround()
    {
    }
};

Shunya::Application* Shunya::CreateApplication()
{
    return new PlayGround();
}