#include "Sandbox2D.h"
#include <imgui.h>


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
    m_Texture = Shunya::Texture2D::Create("assets/textures/cp.png");

    
}
void Sandbox2D::OnDetch()
{

}


void Sandbox2D::OnUpdate(Shunya::Timestamp ts)
{
    m_CameraController.OnUpdate(ts);

    Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    Shunya::RendererCommand::Clear();


    Shunya::Renderer2D::BeginScene(m_CameraController.GetCamera());
    // Change 0.1f -> 1.0f (Fully Opaque)
    Shunya::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Shunya::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Shunya::Renderer2D::DrawQuad({ 0.0f,0.0f ,-0.1f}, { 10.f, 10.0f }, m_Texture);
    Shunya::Renderer2D::EndScene();   


    // UPLOAD COLOR: We bind the shader and send the color from ImGui

    // RENDER TRIANGLE
    // Note: Explicitly passing Identity Matrix to avoid garbage transform
    //Shunya::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));
    
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
