#pragma once
#include "Shunya.h"
#include "Panels/ScenePanel.h"
#include "Core/Rendered/EditorCamera.h"

namespace Shunya {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer();
        virtual void OnAttach() override;
        virtual void OnDetch() override;
        void OnUpdate(Timestamp ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Event& e) override;

    private:
        OrthographicCameraController m_CameraController;

        Ref<FrameBuffer> m_FrameBuffer;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f }; // ✅ track viewport size

        Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;
        Entity m_CameraEntity;
        Entity m_SecondCamera;
        Entity m_HoveredEntity;
        bool m_PrimaryCamera = true;

        Ref<Texture2D> m_Texture;
        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;
        SceneHierarchyPanel m_SceneHierarchyPanel;
        EditorCamera m_EditorCamera;
        int m_GizmoType = -1;
    private:
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);

        void NewScene();
        void OpenScene();
        void SaveSceneAs();
        glm::vec2 m_ViewportBounds[2];
    private:
        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };
}