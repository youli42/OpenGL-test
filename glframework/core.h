#pragma once //只能编译一次，解决下面的文件重复编译的问题

//注意，glad 文件必须在 glfw 应用之前引用
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "../wrapper/checkError.h"

//GLM
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//将矩阵变成字符串输出
#define GLM_ENABLE_EXPERIMENTAL//启用实验性功能
#include<glm/gtx/string_cast.hpp>

//****imgui****
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"