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

    Shunya::FramebufferSpecification fbspec;
    fbspec.Width = 1280;
    fbspec.Height = 720;
 
    m_FrameBuffer = Shunya::FrameBuffer::Create(fbspec);
    
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

        m_FrameBuffer->Bind();
    
        Shunya::RendererCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        Shunya::RendererCommand::Clear();

    }
    

    Shunya::Renderer2D::BeginScene(m_CameraController.GetCamera());

    static float rotation = 0.0f;
    rotation += ts.GetSeconds() * 1.0f;
    
    
    // Rotated colored quad
    Shunya::Renderer2D::DrawRotateQuad({ -1.0f, 0.0f, 0.0f },glm::radians(-45.0f),{ 0.8f, 0.8f },{ 0.8f, 0.2f, 0.3f, 1.0f });
    Shunya::Renderer2D::DrawRotateQuad({ -1.0f, 0.0f, 0.0f },glm::radians(-45.0f),{ 0.8f, 0.8f } ,{ 0.8f, 0.2f, 0.3f, 1.0f });

    // Normal colored quad
    Shunya::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.0f },{ 0.5f, 0.75f },{ 0.2f, 0.3f, 0.8f, 1.0f });

    Shunya::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f },{ 10.0f, 10.0f },m_Texture,10.0f);
    Shunya::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f },{ 10.0f, 10.0f },m_Texture,10.0f);

    // Rotated textured quad
    Shunya::Renderer2D::DrawRotateQuad({ 0.0f, 0.0f, 0.0f },rotation,{ 1.0f, 1.0f },m_Texture,20.0f,glm::vec4(1.0f));
    Shunya::Renderer2D::EndScene();   



    for (float y = -5.0f; y < 5.0f; y += 0.5)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            glm::vec4 color = { (x + 5.0f) / 10.0f,0.4f,(y + 5.0f) / 10.0f,1.0f };
            Shunya::Renderer2D::DrawQuad({x, y}, { 0.45f,0.45f }, color);
        }
    }
    Shunya::Renderer2D::EndScene();
    m_FrameBuffer->UnBind() ; 
    
}
void Sandbox2D::OnImGuiRender()
{
	SHUNYA_PROFILE_FUNCTION();

    static bool dockspaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if (ImGui::MenuItem("Exit")) Shunya::Application::Get().Close();
            ImGui::EndMenu();
        }
            ImGui::EndMenuBar();
    }

    ImGui::End();
	ImGui::Begin("Settings");

    auto stats = Shunya::Renderer2D::GetStats();
    ImGui::Text("Renderer2D stats :-");
    ImGui::Text("Draw Calls %d",stats.DrawCalls);
    ImGui::Text("Quads %d", stats.QuadCount);
    ImGui::Text("Vertices %d",  stats.GetTotalVertexCount());
    ImGui::Text("Index Count %d",stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
    //--------------------------------------------------------------
    // Add this in OnImGuiRender, after your Settings window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
    ImGui::Begin("Viewport");
    uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
    ImGui::Image((void*)(uint64_t)textureID,
        ImGui::GetContentRegionAvail(),
        ImVec2{ 0,1 }, ImVec2{ 1,0 }); // ← flipped UVs for OpenGL
    ImGui::End();
    ImGui::PopStyleVar();

}
void Sandbox2D::OnEvent(Shunya::Event& e)
{
	m_CameraController.OnEvent(e);
}
