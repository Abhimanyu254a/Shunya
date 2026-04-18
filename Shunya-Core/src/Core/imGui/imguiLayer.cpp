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

        io.Fonts->AddFontFromFileTTF("assets/fonts/Quantico/Quantico-Bold.ttf", 18.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Quantico/Quantico-Regular.ttf", 18.0f);

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
        SetDarkThemeColors();

        Application& app = Application::Get();

        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);

        //--------------------------------------------------------

        ImGui_ImplOpenGL3_Init("#version 410");

    }

    void imGUILayer::OnDetch()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void imGUILayer::OnEvent(Event& e)
    {
        if (m_BlockEvents)
        {
            ImGuiIO& io = ImGui::GetIO();

            // Block mouse events if ImGui is using the mouse
            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;

            // Block keyboard events if ImGui is actively using the keyboard (e.g., typing in a text box)
            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        }
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

    }
    void imGUILayer::SetDarkThemeColors() {
        {
            //auto& colors = ImGui::GetStyle().Colors;

            //// Background
            //colors[ImGuiCol_WindowBg] = ImVec4{ 0.05f, 0.07f, 0.12f, 1.0f };

            //// Headers
            //colors[ImGuiCol_Header] = ImVec4{ 0.10f, 0.15f, 0.28f, 1.0f };
            //colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.15f, 0.22f, 0.40f, 1.0f };
            //colors[ImGuiCol_HeaderActive] = ImVec4{ 0.08f, 0.12f, 0.22f, 1.0f };

            //// Buttons
            //colors[ImGuiCol_Button] = ImVec4{ 0.10f, 0.15f, 0.28f, 1.0f };
            //colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.20f, 0.35f, 0.65f, 1.0f };
            //colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.25f, 0.50f, 1.0f };

            //// Frame BG
            //colors[ImGuiCol_FrameBg] = ImVec4{ 0.08f, 0.11f, 0.18f, 1.0f };
            //colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.12f, 0.18f, 0.32f, 1.0f };
            //colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.06f, 0.09f, 0.16f, 1.0f };

            //// Tabs
            //colors[ImGuiCol_Tab] = ImVec4{ 0.07f, 0.10f, 0.18f, 1.0f };
            //colors[ImGuiCol_TabHovered] = ImVec4{ 0.25f, 0.40f, 0.70f, 1.0f };
            //colors[ImGuiCol_TabActive] = ImVec4{ 0.15f, 0.25f, 0.48f, 1.0f };
            //colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.07f, 0.10f, 0.18f, 1.0f };
            //colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.10f, 0.16f, 0.28f, 1.0f };

            //// Title
            //colors[ImGuiCol_TitleBg] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };
            //colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.08f, 0.12f, 0.22f, 1.0f };
            //colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };

            //// Scrollbar
            //colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };
            //colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.15f, 0.25f, 0.48f, 1.0f };
            //colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.25f, 0.40f, 0.70f, 1.0f };
            //colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.10f, 0.18f, 0.35f, 1.0f };

            //// Accent — bright blue highlight
            //colors[ImGuiCol_CheckMark] = ImVec4{ 0.36f, 0.60f, 1.00f, 1.0f };
            //colors[ImGuiCol_SliderGrab] = ImVec4{ 0.25f, 0.45f, 0.85f, 1.0f };
            //colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.36f, 0.60f, 1.00f, 1.0f };

            //// Separator
            //colors[ImGuiCol_Separator] = ImVec4{ 0.12f, 0.20f, 0.38f, 1.0f };
            //colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.25f, 0.45f, 0.80f, 1.0f };
            //colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.36f, 0.60f, 1.00f, 1.0f };

            //// Docking
            //colors[ImGuiCol_DockingPreview] = ImVec4{ 0.25f, 0.45f, 0.85f, 0.7f };
            //colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };  


                ImGui::StyleColorsDark();

                auto& colors = ImGui::GetStyle().Colors;

            // Background - The abyssal midnight sky
            colors[ImGuiCol_WindowBg] = ImVec4{ 0.02f, 0.03f, 0.06f, 1.0f };

            // Headers - Deep stratospheric blue
            colors[ImGuiCol_Header] = ImVec4{ 0.06f, 0.09f, 0.15f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.11f, 0.16f, 0.28f, 1.0f };
            colors[ImGuiCol_HeaderActive] = ImVec4{ 0.04f, 0.06f, 0.12f, 1.0f };

            // Buttons - Corporate obsidian blue
            colors[ImGuiCol_Button] = ImVec4{ 0.06f, 0.09f, 0.15f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.14f, 0.22f, 0.40f, 1.0f };
            colors[ImGuiCol_ButtonActive] = ImVec4{ 0.09f, 0.14f, 0.25f, 1.0f };

            // Frame BG - Subdued twilight
            colors[ImGuiCol_FrameBg] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.08f, 0.12f, 0.20f, 1.0f };
            colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.03f, 0.04f, 0.07f, 1.0f };

            // Tabs - Seamless architectural navigation
            colors[ImGuiCol_Tab] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };
            colors[ImGuiCol_TabHovered] = ImVec4{ 0.14f, 0.22f, 0.40f, 1.0f };
            colors[ImGuiCol_TabActive] = ImVec4{ 0.09f, 0.14f, 0.25f, 1.0f };
            colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.02f, 0.03f, 0.06f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.06f, 0.09f, 0.15f, 1.0f };

            // Title - The zenith boundary
            colors[ImGuiCol_TitleBg] = ImVec4{ 0.01f, 0.02f, 0.04f, 1.0f };
            colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.04f, 0.06f, 0.10f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.01f, 0.02f, 0.04f, 1.0f };

            // Scrollbar - Silent progression
            colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.01f, 0.02f, 0.04f, 1.0f };
            colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.09f, 0.14f, 0.25f, 1.0f };
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.14f, 0.22f, 0.40f, 1.0f };
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.06f, 0.09f, 0.15f, 1.0f };

            // Accent — Bioluminescent starlight highlight
            colors[ImGuiCol_CheckMark] = ImVec4{ 0.20f, 0.50f, 0.90f, 1.0f };
            colors[ImGuiCol_SliderGrab] = ImVec4{ 0.14f, 0.35f, 0.70f, 1.0f };
            colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.20f, 0.50f, 0.90f, 1.0f };

            // Separator - Horizon lines
            colors[ImGuiCol_Separator] = ImVec4{ 0.08f, 0.12f, 0.20f, 1.0f };
            colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.14f, 0.22f, 0.40f, 1.0f };
            colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.20f, 0.50f, 0.90f, 1.0f };

            // Docking - Fluid workspace assimilation
            colors[ImGuiCol_DockingPreview] = ImVec4{ 0.14f, 0.35f, 0.70f, 0.7f };
            colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.01f, 0.02f, 0.04f, 1.0f };
        }

    }
}