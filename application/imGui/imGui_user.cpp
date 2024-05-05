#include"imGui_user.h"

GUI::GUI()
{
}

GUI::~GUI()
{
}


//***************************��ʼ��********************************
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

	// ΢���ź�����
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc", 18.0f, nullptr,
	io.Fonts->GetGlyphRangesChineseFull());
}

//*************************��ʼѭ��***************************
void GUI::startGUI_up()
{
	//ѭ����ͷ
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
	//ѭ����β
	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls glfwSwapBuffers() etc.)
}


//***************************�����������****************************
void GUI::destroyGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}




//**********************ʵ�ִ���*************************
void GUI::controlPlane()
{
	if (!show_control_plane)
		return;

	ImGui::Begin(u8"�������", &show_control_plane, ImGuiWindowFlags_MenuBar);

	ImGui::Text(u8"���ñ�����ɫ");
	ImGui::ColorEdit4("Color", color);
		glClearColor(color[0], color[1], color[2],color[3]);

	//ImGui::SliderFloat(u8"�����ƶ�������", &f, 0.0f, 1.0f);

	if (ImGui::Button(u8"�л���������������/͸�������"))
	{
		
		onPerspectiveCamera = !onPerspectiveCamera;
	}

	if (ImGui::Button(u8"�л��ƶ���������"))
	{
		onGameCameraControl = !onGameCameraControl;
	}
	ImGui::Text(u8"WASD�ƶ�������м��ƶ�");
	
	
	ImGui::End(); // ��������
}
