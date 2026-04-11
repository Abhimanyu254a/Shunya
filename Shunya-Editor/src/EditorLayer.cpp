#include "Shunya.h"
#include "EditorLayer.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Scene/Entity.h"
#include "Core/Rendered/FrameBuffer.h"
#include "Core/Scene/SceneCamera.h"

namespace Shunya {

    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f, true)
    {
    }

    EditorLayer::~EditorLayer() {}

    void EditorLayer::OnAttach()
    {
        m_Texture = Texture2D::Create("assets/textures/cp.png");

        FramebufferSpecification fbspec;
        fbspec.Width = 1280;
        fbspec.Height = 720;
        m_FrameBuffer = FrameBuffer::Create(fbspec);

        // ✅ Scene setup
        m_ActiveScene = std::make_shared<Scene>();

        m_SquareEntity = m_ActiveScene->CreateEntity("Square");
        m_SquareEntity.AddComponent<SpriteRendererComponent>(
            glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptingEntity
        {
        public:
            void OnCreate()
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                transform[3][0] = rand() % 10 - 5.0f;
            }

            void OnDestroy()
            {
            }

            void OnUpdate(Timestamp ts)
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                float speed = 5.0f;

                if (Input::IsKeyPressed(SHUNYA_KEY_A))
                    transform[3][0] -= speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_D))
                    transform[3][0] += speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_W))
                    transform[3][1] += speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_S))
                    transform[3][1] -= speed * ts.GetSeconds();
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
    }

    void EditorLayer::OnDetch() {}

    void EditorLayer::OnUpdate(Timestamp ts)
    {
        SHUNYA_PROFILE_FUNCTION();

        // ✅ Resize framebuffer if viewport size changed
        FramebufferSpecification spec = m_FrameBuffer->GetSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.Width != (uint32_t)m_ViewportSize.x ||
                spec.Height != (uint32_t)m_ViewportSize.y))
        {
            m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x,
                (uint32_t)m_ViewportSize.y);
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize(
                (uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        if (m_ViewportFocused)
            m_CameraController.OnUpdate(ts);

        // ✅ Render into framebuffer
        Renderer2D::ResetStats();
        m_FrameBuffer->Bind();
        RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RendererCommand::Clear();

        m_ActiveScene->OnUpdate(ts); // BeginScene/EndScene inside Scene::OnUpdate

        m_FrameBuffer->UnBind();
    }

    void EditorLayer::OnImGuiRender()
    {
        SHUNYA_PROFILE_FUNCTION();

        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoNavFocus;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar(); // WindowPadding
        if (opt_fullscreen)
            ImGui::PopStyleVar(2); // WindowRounding + WindowBorderSize

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
                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End(); // DockSpace

        // ── Settings panel ──────────────────────────────────────
        ImGui::Begin("Settings");

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads:      %d", stats.QuadCount);
        ImGui::Text("Vertices:   %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices:    %d", stats.GetTotalIndexCount());
        ImGui::Separator();

        auto& squareColor = m_SquareEntity
            .GetComponent<SpriteRendererComponent>().Color;
        ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
        ImGui::Separator();

        ImGui::DragFloat3("Camera Transform",
            glm::value_ptr(
                m_CameraEntity.GetComponent<TransformComponent>().Transform[3]));

        if (ImGui::Checkbox("Primary Camera", &m_PrimaryCamera))
        {
            m_CameraEntity.GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
            m_SecondCamera.GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
        }

        auto& camera = m_SecondCamera.GetComponent<CameraComponent>().Camera;
        float orthoSize = camera.GetOrthographicSize();
        if (ImGui::DragFloat("2nd Camera Ortho Size", &orthoSize))
            camera.SetOrthographicSize(orthoSize);

        ImGui::End(); // Settings

        // ── Viewport panel ───────────────────────────────────────
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->SetBlockEvents(
            !m_ViewportFocused && !m_ViewportHovered);

        // ✅ Capture viewport size for resize next frame
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)(uint64_t)textureID,
            viewportPanelSize,
            ImVec2{ 0, 1 }, ImVec2{ 1, 0 }); // flipped for OpenGL

        ImGui::End(); // Viewport
        ImGui::PopStyleVar();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
    }
}