#include "Shunya.h"
#include "EditorLayer.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Scene/Entity.h"
#include "Core/Rendered/FrameBuffer.h"
#include "Core/Scene/SceneCamera.h"
#include "Panels/ScenePanel.h"
#include "Core/Scene/SceneSerializer.h"
#include "Core/Utils/PlatformUtils.h"
#include "ImGuizmo.h"
#include "Core/Math/Math.h"

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

        
        m_ActiveScene = std::make_shared<Scene>();
#if 0

        m_SquareEntity = m_ActiveScene->CreateEntity("Blue Square");
        m_SquareEntity.AddComponent<SpriteRendererComponent>(
            glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });

        auto redSquare = m_ActiveScene->CreateEntity("Red Square");
        redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptingEntity
        {
        public:

            virtual void OnCreate() override
            {
                auto& translation = GetComponent<TransformComponent>().Translation;
                translation.x = rand() % 10 - 5.0f;
            }

            virtual void OnDestroy() override
            {
            }

            virtual void OnUpdate(Timestamp ts) override
            {
                auto& transform = GetComponent<TransformComponent>().Translation;
                float speed = 5.0f;

                if (Input::IsKeyPressed(SHUNYA_KEY_A))
                    transform.x -= speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_D))
                    transform.x += speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_W))
                    transform.y += speed * ts.GetSeconds();
                if (Input::IsKeyPressed(SHUNYA_KEY_S))
                    transform.y -= speed * ts.GetSeconds();
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
        
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    
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
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        style.WindowMinSize.x = minWinSizeX;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N"))
                    NewScene();

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    OpenScene();

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    SaveSceneAs();

                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End(); // DockSpace

        m_SceneHierarchyPanel.OnImGuiRender();
        // ──   s panel ──────────────────────────────────────
        ImGui::Begin("Settings");

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads:      %d", stats.QuadCount);
        ImGui::Text("Vertices:   %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices:    %d", stats.GetTotalIndexCount());
        ImGui::Separator();

        ImGui::End(); // Settings

        // ── Viewport panel ───────────────────────────────────────
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportHovered);

        // ✅ Capture viewport size for resize next frame
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)(uint64_t)textureID,
            viewportPanelSize,
            ImVec2{ 0, 1 }, ImVec2{ 1, 0 }); // flipped for OpenGL


        // Gizmos
        Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
        if (selectedEntity && m_GizmoType != -1)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            float windowWidth = (float)ImGui::GetWindowWidth();
            float windowHeight = (float)ImGui::GetWindowHeight();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

            // Camera
            auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
            const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
            const glm::mat4& cameraProjection = camera.GetProjection();
            glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

            // Entity transform
            auto& tc = selectedEntity.GetComponent<TransformComponent>();
            glm::mat4 transform = tc.GetTransform();

            // Snapping
            bool snap = Input::IsKeyPressed(SHUNYA_KEY_LEFT_CONTROL);
            float snapValue = 0.5f; // Snap to 0.5m for translation/scale
            // Snap to 45 degrees for rotation
            if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;

            float snapValues[3] = { snapValue, snapValue, snapValue };

            ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
                (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
                nullptr, snap ? snapValues : nullptr);

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 translation, rotation, scale;
                Math::DecomposeTransform(transform, translation, rotation, scale);

                glm::vec3 deltaRotation = rotation - tc.Rotation;
                tc.Translation = translation;
                tc.Rotation += deltaRotation;
                tc.Scale = scale;
            }
        }



        ImGui::End(); // Viewport
        ImGui::PopStyleVar();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        if (m_ViewportFocused && m_ViewportHovered)
            m_CameraController.OnEvent(e);
        ImGuiIO& io = ImGui::GetIO();
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SHUNYA_BIND(EditorLayer::OnKeyPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        // Shortcuts
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(SHUNYA_KEY_LEFT_CONTROL) || Input::IsKeyPressed(SHUNYA_KEY_RIGHT_CONTROL);
        bool shift = Input::IsKeyPressed(SHUNYA_KEY_LEFT_SHIFT) || Input::IsKeyPressed(SHUNYA_KEY_RIGHT_SHIFT);
        switch (e.GetKeyCode())
        {
        case SHUNYA_KEY_N:
        {
            if (control)
                NewScene();

            break;
        }
        case SHUNYA_KEY_O:
        {
            if (control)
                OpenScene();

            break;
        }
        case SHUNYA_KEY_S:
        {
            if (control && shift)
                SaveSceneAs();

            break;
        }
        // Gizmos
        case SHUNYA_KEY_Q:
            m_GizmoType = -1;
            break;
        case SHUNYA_KEY_W:
            m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case SHUNYA_KEY_E:
            m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            break;
        case SHUNYA_KEY_R:
            m_GizmoType = ImGuizmo::OPERATION::SCALE;
            break;
        }
        return false;
    }

    void EditorLayer::NewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Shunya Scene (*.shunya)\0*.shunya\0");
        if (!filepath.empty())
        {
            m_ActiveScene = CreateRef<Scene>();
            m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_SceneHierarchyPanel.SetContext(m_ActiveScene);

            SceneSerializer serializer(m_ActiveScene);
            serializer.Deserialize(filepath);
        }
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile("Shunya Scene (*.shunya)\0*.shunya\0");
        if (!filepath.empty())
        {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(filepath);
        }
    }
}