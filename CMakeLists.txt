#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(MipMap)

#设置变量用的,这里设置的是c++17
set(CMAKE_CXX_STANDARD 17)

#全局预编译宏
add_definitions (-DDEBUG)

#拷贝资源文件到二进制执行文件目录
file(GLOB ASSETS "./ASSETS")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#添加头文件搜索
include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/include
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui
	#SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/wrapper
)

#链接.lib库dd
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/lib
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui
)

#添加子目录
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)
add_subdirectory(ThirdParty/ImGui)
   
#本工程输出程序及主程序文件名称
add_executable(GLM "main.cpp" "glad.c")


#将.lib库链接到结果文件中（此处是OpenglStudy)
target_link_libraries(GLM glfw3.lib wrapper app fw gui)