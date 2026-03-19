#include "Shunya.h"
#include "Sandbox2D.h"
#include <imgui.h>

#include <iostream>
#include <chrono>
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
    SHUNYA_INFO("Texture size: {0}x{1}", m_Texture->GetWidth(), m_Texture->GetHeight());

    
}
void Sandbox2D::OnDetch()
{

}


void Sandbox2D::OnUpdate(Shunya::Timestamp ts)
{
	SHUNYA_PROFILE_FUNCTION();
    m_CameraController.OnUpdate(ts);

    Shunya::Renderer2D::ResetStats();
    {
        SHUNYA_PROFILE_SCOPE("Renderer Clear");
    
        Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        Shunya::RendererCommand::Clear();

    }
    

    Shunya::Renderer2D::BeginScene(m_CameraController.GetCamera());

    static float rotation = 0.0f;
    rotation += ts.GetSeconds() * 1.0f;
    
    
    // Rotated colored quad
    Shunya::Renderer2D::DrawRotateQuad(
        { -1.0f, 0.0f, 0.0f },
        glm::radians(-45.0f),
        { 0.8f, 0.8f },
        { 0.8f, 0.2f, 0.3f, 1.0f }
    );

    // Normal colored quad
    Shunya::Renderer2D::DrawQuad(
        { 0.5f, -0.5f, 0.0f },
        { 0.5f, 0.75f },
        { 0.2f, 0.3f, 0.8f, 1.0f }
    );

    Shunya::Renderer2D::DrawQuad(
        { -5.0f, -5.0f, -0.1f },
        { 10.0f, 10.0f },
        m_Texture,
        10.0f
    );

    // Rotated textured quad
    Shunya::Renderer2D::DrawRotateQuad(
        { 0.0f, 0.0f, 0.0f },
        rotation,
        { 1.0f, 1.0f },
        m_Texture,
        20.0f,
        glm::vec4(1.0f)   // tint
    );
    Shunya::Renderer2D::EndScene();   



    Shunya::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y < 5.0f; y += 0.5)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            glm::vec4 color = { (x + 5.0f) / 10.0f,0.4f,(y + 5.0f) / 10.0f,1.0f };
            Shunya::Renderer2D::DrawQuad({x, y}, { 0.45f,0.45f }, color);
        }
    }
    Shunya::Renderer2D::EndScene();
    
}
void Sandbox2D::OnImGuiRender()
{
	SHUNYA_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

    auto stats = Shunya::Renderer2D::GetStats();
    ImGui::Text("Renderer2D stats :-");
    ImGui::Text("Draw Calls %d",stats.DrawCalls);
    ImGui::Text("Quads %d", stats.QuadCount);
    ImGui::Text("Vertices %d",  stats.GetTotalVertexCount());
    ImGui::Text("Index Count %d",stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();

}
void Sandbox2D::OnEvent(Shunya::Event& e)
{
	m_CameraController.OnEvent(e);
}
