#pragma once //ֻ�ܱ���һ�Σ����������ļ��ظ����������

//ע�⣬glad �ļ������� glfw Ӧ��֮ǰ����
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "../wrapper/checkError.h"

//GLM
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//���������ַ������
#define GLM_ENABLE_EXPERIMENTAL//����ʵ���Թ���
#include<glm/gtx/string_cast.hpp>

//****imgui****
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"