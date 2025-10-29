#include "SNY-PCH.h"
#include "Core/Core.h"
#include "Core/Layer.h"
#include "Application.h"
#include "All_Event.h"

#include "imgui.h"
#include "imguiLayer.h"
#include "Core/imgui_opengl_Render.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/imgui_impl_glfw.h"




GLFWgamepadstate gamepad;
#define MAP_BUTTON(KEY_NO, BUTTON_NO, _UNUSED)          do { io.AddKeyEvent(KEY_NO, gamepad.buttons[BUTTON_NO] != 0); } while (0)
#define MAP_ANALOG(KEY_NO, AXIS_NO, _UNUSED, V0, V1)    do { float v = gamepad.axes[AXIS_NO]; v = (v - V0) / (V1 - V0); io.AddKeyAnalogEvent(KEY_NO, v > 0.10f, Saturate(v)); } while (0)



namespace Shunya
{

    static inline float Saturate(float v) { return v < 0.0f ? 0.0f : v  > 1.0f ? 1.0f : v; }

    imGUILayer::imGUILayer()
        :Layer("imGUI_Layer") {
    }

    imGUILayer::~imGUILayer() {}

    //void imGUILayer::OnAttach() { 
    //	ImGui::CreateContext();
 //       ImGui::SetCurrentContext(ImGui::GetCurrentContext());
    //	

 //       ImGuiIO& io = ImGui::GetIO();
 //       //GLFWgamepadstate gamepad;


 //       io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
 //       Application& app = Application::Get();
 //       io.DisplaySize = ImVec2(app.GetWindow().GetBreadth(),app.GetWindow().GetHeight());

 //       MAP_BUTTON(ImGuiKey_GamepadStart, GLFW_GAMEPAD_BUTTON_START, 7);
 //       MAP_BUTTON(ImGuiKey_GamepadBack, GLFW_GAMEPAD_BUTTON_BACK, 6);
 //       MAP_BUTTON(ImGuiKey_GamepadFaceLeft, GLFW_GAMEPAD_BUTTON_X, 2);     // Xbox X, PS Square
 //       MAP_BUTTON(ImGuiKey_GamepadFaceRight, GLFW_GAMEPAD_BUTTON_B, 1);     // Xbox B, PS Circle
 //       MAP_BUTTON(ImGuiKey_GamepadFaceUp, GLFW_GAMEPAD_BUTTON_Y, 3);     // Xbox Y, PS Triangle
 //       MAP_BUTTON(ImGuiKey_GamepadFaceDown, GLFW_GAMEPAD_BUTTON_A, 0);     // Xbox A, PS Cross
 //       MAP_BUTTON(ImGuiKey_GamepadDpadLeft, GLFW_GAMEPAD_BUTTON_DPAD_LEFT, 13);
 //       MAP_BUTTON(ImGuiKey_GamepadDpadRight, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, 11);
 //       MAP_BUTTON(ImGuiKey_GamepadDpadUp, GLFW_GAMEPAD_BUTTON_DPAD_UP, 10);
 //       MAP_BUTTON(ImGuiKey_GamepadDpadDown, GLFW_GAMEPAD_BUTTON_DPAD_DOWN, 12);
 //       MAP_BUTTON(ImGuiKey_GamepadL1, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, 4);
 //       MAP_BUTTON(ImGuiKey_GamepadR1, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, 5);
 //       MAP_ANALOG(ImGuiKey_GamepadL2, GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, 4, -0.75f, +1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadR2, GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, 5, -0.75f, +1.0f);
 //       MAP_BUTTON(ImGuiKey_GamepadL3, GLFW_GAMEPAD_BUTTON_LEFT_THUMB, 8);
 //       MAP_BUTTON(ImGuiKey_GamepadR3, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, 9);
 //       MAP_ANALOG(ImGuiKey_GamepadLStickLeft, GLFW_GAMEPAD_AXIS_LEFT_X, 0, -0.25f, -1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadLStickRight, GLFW_GAMEPAD_AXIS_LEFT_X, 0, +0.25f, +1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadLStickUp, GLFW_GAMEPAD_AXIS_LEFT_Y, 1, -0.25f, -1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadLStickDown, GLFW_GAMEPAD_AXIS_LEFT_Y, 1, +0.25f, +1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadRStickLeft, GLFW_GAMEPAD_AXIS_RIGHT_X, 2, -0.25f, -1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadRStickRight, GLFW_GAMEPAD_AXIS_RIGHT_X, 2, +0.25f, +1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadRStickUp, GLFW_GAMEPAD_AXIS_RIGHT_Y, 3, -0.25f, -1.0f);
 //       MAP_ANALOG(ImGuiKey_GamepadRStickDown, GLFW_GAMEPAD_AXIS_RIGHT_Y, 3, +0.25f, +1.0f);
 //       
 //       
 //       ImGui_ImplOpenGL3_Init("version 410");
 //       ImGui::StyleColorsDark();
    //}
    void imGUILayer::OnAttach()
    {
        // --- 1. Create Context and Set Flags ---
        ImGui::CreateContext();
        /*ImGui::SetCurrentContext(ImGui::GetCurrentContext());*/
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
        // Add other flags here (docking, viewports, etc.)
        // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // --- 2. Get the Native Window ---

        Application& app = Application::Get();




        // --- 3. Initialize Backends ---
        /*ImGui_ImplGlfw_InitForOpenGL(window, true);*/
        ImGui_ImplOpenGL3_Init("#version 410");

        // --- 4. Set Style ---
        ImGui::StyleColorsDark();

        // ALL The MAP_BUTTON AND MAP_ANALOG CALLS MUST BE DELETED FROM HERE
    }
    void imGUILayer::OnDetch()
    {
    }



    void  imGUILayer::OnUpdate()
    {
        // --- 1. Set up IO (Size, DeltaTime) ---
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetBreadth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        // --- 2. Start New Frames ---
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // --- 3. Poll Gamepad State (This is where the logic belongs) ---
        GLFWgamepadstate gamepad;
        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &gamepad))
        {
            // Copy all your MAP_BUTTON and MAP_ANALOG macros here
            MAP_BUTTON(ImGuiKey_GamepadStart, GLFW_GAMEPAD_BUTTON_START, 7);
            MAP_BUTTON(ImGuiKey_GamepadBack, GLFW_GAMEPAD_BUTTON_BACK, 6);
            MAP_BUTTON(ImGuiKey_GamepadFaceLeft, GLFW_GAMEPAD_BUTTON_X, 2);
            MAP_BUTTON(ImGuiKey_GamepadFaceRight, GLFW_GAMEPAD_BUTTON_B, 1);
            MAP_BUTTON(ImGuiKey_GamepadFaceUp, GLFW_GAMEPAD_BUTTON_Y, 3);
            MAP_BUTTON(ImGuiKey_GamepadFaceDown, GLFW_GAMEPAD_BUTTON_A, 0);
            MAP_BUTTON(ImGuiKey_GamepadDpadLeft, GLFW_GAMEPAD_BUTTON_DPAD_LEFT, 13);
            MAP_BUTTON(ImGuiKey_GamepadDpadRight, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, 11);
            MAP_BUTTON(ImGuiKey_GamepadDpadUp, GLFW_GAMEPAD_BUTTON_DPAD_UP, 10);
            MAP_BUTTON(ImGuiKey_GamepadDpadDown, GLFW_GAMEPAD_BUTTON_DPAD_DOWN, 12);
            MAP_BUTTON(ImGuiKey_GamepadL1, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, 4);
            MAP_BUTTON(ImGuiKey_GamepadR1, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, 5);
            MAP_ANALOG(ImGuiKey_GamepadL2, GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, 4, -0.75f, +1.0f);
            MAP_ANALOG(ImGuiKey_GamepadR2, GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, 5, -0.75f, +1.0f);
            MAP_BUTTON(ImGuiKey_GamepadL3, GLFW_GAMEPAD_BUTTON_LEFT_THUMB, 8);
            MAP_BUTTON(ImGuiKey_GamepadR3, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, 9);
            MAP_ANALOG(ImGuiKey_GamepadLStickLeft, GLFW_GAMEPAD_AXIS_LEFT_X, 0, -0.25f, -1.0f);
            MAP_ANALOG(ImGuiKey_GamepadLStickRight, GLFW_GAMEPAD_AXIS_LEFT_X, 0, +0.25f, +1.0f);
            MAP_ANALOG(ImGuiKey_GamepadLStickUp, GLFW_GAMEPAD_AXIS_LEFT_Y, 1, -0.25f, -1.0f);
            MAP_ANALOG(ImGuiKey_GamepadLStickDown, GLFW_GAMEPAD_AXIS_LEFT_Y, 1, +0.25f, +1.0f);
            MAP_ANALOG(ImGuiKey_GamepadRStickLeft, GLFW_GAMEPAD_AXIS_RIGHT_X, 2, -0.25f, -1.0f);
            MAP_ANALOG(ImGuiKey_GamepadRStickRight, GLFW_GAMEPAD_AXIS_RIGHT_X, 2, +0.25f, +1.0f);
            MAP_ANALOG(ImGuiKey_GamepadRStickUp, GLFW_GAMEPAD_AXIS_RIGHT_Y, 3, -0.25f, -1.0f);
            MAP_ANALOG(ImGuiKey_GamepadRStickDown, GLFW_GAMEPAD_AXIS_RIGHT_Y, 3, +0.25f, +1.0f);
        }

        // --- 4. Create your UI ---
        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        // --- 5. Render ---
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    //----------------------------------------
    //void  imGUILayer::OnUpdate()
    //{
 //       ImGuiIO& io = ImGui::GetIO();
 //       float time = (float)glfwGetTime();
 //       io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
 //       m_time = time;
 //       
 //       ImGui_ImplOpenGL3_NewFrame();

 //       ImGui::NewFrame();

 //       static bool show = true;
 //       ImGui::ShowDemoWindow(&show);

 //       ImGui::Render();
 //       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //}
    //-----------------------------------------------------

    void imGUILayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseMovedEvent>(SHUNYA_BIND(imGUILayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(SHUNYA_BIND(imGUILayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(SHUNYA_BIND(imGUILayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<MouseButtonRelasedEvent>(SHUNYA_BIND(imGUILayer::OnMouseButtonRelasedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(SHUNYA_BIND(imGUILayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(SHUNYA_BIND(imGUILayer::OnWindowResizeEvent));
        dispatcher.Dispatch<KeyPressedEvent>(SHUNYA_BIND(imGUILayer::OnKeyPressedEvent));

    }

    bool imGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {

        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }



    bool imGUILayer::OnMouseScrolledEvent(MouseScrolledEvent& e) 
    {
        

        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.Get_X();
        io.MouseWheel += e.Get_Y();
        return false;
        


    }
    bool imGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.m_MouseButtonEvent()] = true;

        return false;

    }
    bool imGUILayer::OnMouseButtonRelasedEvent(MouseButtonRelasedEvent& e)
    {

        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.m_MouseButtonEvent()] = false;

        return false;
    }



    bool imGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e) 
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()];
        return false;

    }
    bool imGUILayer::OnKeyPressedEvent(KeyPressedEvent& e) {

        ImGuiIO& io = ImGui::GetIO();
        io.KeysData[e.GetKeyCode()];
        
        return false;
    }
    bool imGUILayer::OnWindowResizeEvent(WindowResizeEvent& e) {
        
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetBreadth(), e.GetLength());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetBreadth(), e.GetLength());
        return false;

    }
}