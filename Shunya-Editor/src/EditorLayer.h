//#pragma once
//
//#include "Shunya.h"
//
//struct ProfileResult
//{
//	const char* Name;
//	double Time;
//};
//
//namespace Shunya{
//
//	class EditorLayer : public Shunya::Layer
//	{
//	public:
//		EditorLayer();
//		virtual ~EditorLayer();
//		virtual void OnAttach() override;
//		virtual void OnDetch() override;
//
//		void OnUpdate(Timestamp ts) override;
//		virtual void OnImGuiRender() override;
//		void OnEvent(Event& e) override;
//
//	private:
//		Shunya::OrthographicCameraController m_CameraController;
//
//		Ref<VertexArray> m_SquareVA;
//		Ref<Shader> m_FlatColorShader;
//		Ref<FrameBuffer> m_FrameBuffer;
//		
//		Ref<Scene> m_ActiveScene = std::make_shared<Scene>();
//		Entity m_SquareEntity;
//		Entity m_CameraEntity;
//		Entity m_SecondCamera;
//
//		bool m_PrimaryCamera = true;
//
//		Ref<Texture2D> m_Texture;
//		bool m_ViewportFocused = false;
//		bool m_ViewportHovered = false;
//
//		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f,1.0f};
//	};
//}












#pragma once
#include "Shunya.h"
#include "Panels/ScenePanel.h"

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
        bool m_PrimaryCamera = true;

        Ref<Texture2D> m_Texture;
        bool m_ViewportFocused = false;
        bool m_ViewportHovered = false;
        SceneHierarchyPanel m_SceneHierarchyPanel;

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };
}