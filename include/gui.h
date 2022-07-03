#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class GUI {
private:
  
  auto set_solidness(float transparency) -> void {
    ImGuiStyle& style = ImGui::GetStyle();
    const auto before = style.Colors[ImGuiCol_WindowBg];
    const auto after = ImVec4(before.x, before.y, before.z, transparency);
    style.Colors[ImGuiCol_WindowBg] = after;
  }
  
  auto transparent() -> void {
    set_solidness(0.50f);
  }
  
  auto solid() -> void {
    set_solidness(1.00f);
  }

  auto basic_colors() -> void {
    ImGuiStyle& style = ImGui::GetStyle();
    // Set background colors of window and child to 3x 16 and 3x 24 respectively
    style.Colors[ImGuiCol_WindowBg] = ImColor(16,16,16);
    style.Colors[ImGuiCol_ChildBg] = ImColor(24,24,24);
  }

public:
  auto init (GLFWwindow* window, const std::string& glsl_version) -> void {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
    ImGui::StyleColorsDark();
    basic_colors();
  };

  auto new_frame() -> void {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }
  
  
  auto update () -> void {
    
    {
      ImGui::Begin("Helloooo", 0, ImGuiWindowFlags_NoTitleBar);
      ImGui::BeginChild("scrolling", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
      for (int n = 0; n < 100; n++)
        ImGui::Text("%04d: Some text", n);
      ImGui::EndChild();
      ImGui::End();
    }
    
  };

  auto render() -> void {
    // Render dear imgui into screen
    ImGui::Render();
	  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  };

  auto shutdown() -> void {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  };
};