#include "SNY-PCH.h"
#include "Core/Application.h"


#include "imguiLayer.h"
#include "imgui.h"

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>






namespace Shunya
{

    static inline float Saturate(float v) { return v < 0.0f ? 0.0f : v  > 1.0f ? 1.0f : v; }

    imGUILayer::imGUILayer()
        :Layer("imGUI_Layer") {
    }

    imGUILayer::~imGUILayer() {}

    void imGUILayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();

        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, false);

        //--------------------------------------------------------
 
        ImGui_ImplOpenGL3_Init("#version 410");

        ImGui::StyleColorsDark();
    }

    void imGUILayer::OnDetch()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void imGUILayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }


    void imGUILayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetBreadth(), (float)app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


    }
    void imGUILayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::Begin("ImGUI");
        ImGui::Text("Hello World");
        ImGui::End();
        ImGui::ShowDemoWindow();
    }

    /* void  imGUILayer::OnUpdate()
     {*/
     /*   ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetBreadth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/



        //-------------------------
        //// --- 1. Set up IO (Size, DeltaTime) ---
        //ImGuiIO& io = ImGui::GetIO();
        //Application& app = Application::Get();
        //io.DisplaySize = ImVec2(app.GetWindow().GetBreadth(), app.GetWindow().GetHeight());

        //float time = (float)glfwGetTime();
        //io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        //m_time = time;

        //// --- 2. Start New Frames ---
        //ImGui_ImplOpenGL3_NewFrame();


        //ImGui_ImplGlfw_NewFrame();



        //ImGui::NewFrame();

        //// --- 4. Create your UI ---
        //static bool show = true;
        //ImGui::ShowDemoWindow(&show);

        //// --- 5. Render ---


        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());





}