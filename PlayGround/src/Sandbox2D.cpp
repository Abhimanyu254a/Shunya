#include "Sandbox2D.h"
#include <imgui.h>

#include "Core/openGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
    
Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}
Sandbox2D::~Sandbox2D()
{ }

void Sandbox2D::OnAttach() 
{
    // -------------------------------------------------------------
    // 2. SQUARE RENDERING SETUP
    // -------------------------------------------------------------
    m_SquareVA = Shunya::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    std::shared_ptr<Shunya::VertexBuffer> squareVB;
    squareVB.reset(Shunya::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

    squareVB->SetLayout({
            { Shunya::ShaderDataType::Float3, "a_Position" },
        });

    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    std::shared_ptr<Shunya::IndexBuffer> squareIB;
    squareIB.reset(Shunya::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Shunya::Shader::Create("assets/Shaders/FlatColor.glsl");
}
void Sandbox2D::OnDetch()
{

}


void Sandbox2D::OnUpdate(Shunya::Timestamp ts)
{
    m_CameraController.OnUpdate(ts);

    Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    Shunya::RendererCommand::Clear();


    Shunya::Renderer::BeginScene(m_CameraController.GetCamera());

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    // UPLOAD COLOR: We bind the shader and send the color from ImGui
    std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Shunya::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    Shunya::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // RENDER TRIANGLE
    // Note: Explicitly passing Identity Matrix to avoid garbage transform

    //Shunya::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));

    Shunya::Renderer::EndScene();   
}
void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}
void Sandbox2D::OnEvent(Shunya::Event& e)
{
	m_CameraController.OnEvent(e);
}
