#include "Shunya.h"
#include "EditorLayer.h"
#include <imgui.h>

#include <iostream>
#include <chrono>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Scene/Entity.h"

namespace Shunya
{ 
    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
    {
    }
    EditorLayer::~EditorLayer()
    {
    }

    void EditorLayer::OnAttach() 
    {
        m_Texture = Shunya::Texture2D::Create("assets/textures/cp.png");
        SHUNYA_INFO("Texture size: {0}x{1}", m_Texture->GetWidth(), m_Texture->GetHeight());

        Shunya::FramebufferSpecification fbspec;
        fbspec.Width = 1280;
        fbspec.Height = 720;
 
        m_FrameBuffer = Shunya::FrameBuffer::Create(fbspec);

        m_ActiveScene = std::make_shared<Scene>();
        Entity square = m_ActiveScene->CreateEntity("Square");
        square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });
        m_SquareEntity = square;
    
        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

        m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f));
        cc.Primary = false;
    }
    void EditorLayer::OnDetch()
    {

    }


    void EditorLayer::OnUpdate(Shunya::Timestamp ts)
    {
        if (m_ViewportFocused) m_CameraController.OnUpdate(ts);

        // 1. Bind framebuffer FIRST
        m_FrameBuffer->Bind();
        RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RendererCommand::Clear();

        // 2. Begin scene
        Renderer2D::ResetStats();

        // 3. THEN update scene (draws happen here)
        m_ActiveScene->OnUpdate(ts);

        // 4. End scene and unbind
        m_FrameBuffer->UnBind();
    }

    void EditorLayer::OnImGuiRender()
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

        auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
        ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));


        ImGui::DragFloat3("Camera Transform",
            glm::value_ptr(m_CameraEntity.GetComponent<TransformComponent>().Transform[3]));

        if (ImGui::Checkbox("Camera A", &m_PrimaryCamera))
        {
            m_CameraEntity.GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
            m_SecondCamera.GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
        }
	    
	    ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
        ImGui::Begin("Viewport");
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused && !m_ViewportHovered);
        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)(uint64_t)textureID,
            ImGui::GetContentRegionAvail(),
            ImVec2{ 0,1 }, ImVec2{ 1,0 }); // ← flipped UVs for OpenGL
        ImGui::End();
        ImGui::PopStyleVar();

    }
    void EditorLayer::OnEvent(Shunya::Event& e)
    {
	    m_CameraController.OnEvent(e);
    }

}
