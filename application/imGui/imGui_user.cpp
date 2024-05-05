#include"imGui_user.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}


//***************************初始化********************************
void GUI::setGuiInit(GLFWwindow* windows, bool test)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(windows, test);// Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	// 微软雅黑字体
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr,
	io.Fonts->GetGlyphRangesChineseFull());
}

//*************************开始循环***************************
void GUI::startGUI_up()
{
	//循环开头
	// (Your code calls glfwPollEvents())
	// ...
	// Start the Dear ImGui frame

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // Show demo window! :)
	controlPlane();
}

void GUI::startGUI_end()
{
	//循环结尾
	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls glfwSwapBuffers() etc.)
}


//***************************结束清除程序****************************
void GUI::destroyGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}




//**********************实现窗口*************************
void GUI::controlPlane()
{
	if (!show_control_plane)
		return;

	ImGui::Begin(u8"控制面板", &show_control_plane, ImGuiWindowFlags_MenuBar);

	ImGui::Text(u8"设置背景颜色");
	ImGui::ColorEdit4("Color", color);
		glClearColor(color[0], color[1], color[2],color[3]);

	//ImGui::SliderFloat(u8"设置移动灵敏度", &f, 0.0f, 1.0f);

	if (ImGui::Button(u8"切换摄像机（正交相机/透视相机）"))
	{
		
		onPerspectiveCamera = !onPerspectiveCamera;
	}

	if (ImGui::Button(u8"切换移动控制类型"))
	{
		onGameCameraControl = !onGameCameraControl;
	}
	ImGui::Text(u8"WASD移动和鼠标中键移动");
	
	
	ImGui::End(); // 结束窗口
}
