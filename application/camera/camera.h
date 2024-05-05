#pragma once
#include"../../glframework/core.h"

class Camera
{
public:
	//每帧实时计算并存储到Camera中：
	glm::vec3 mPosition{ 0.0f,0.0f,1.0f };//eye参数
	glm::vec3 mUp{ 0.0f,1.0f,0.0f };//up向量
	glm::vec3 mRight{ 1.0f,0.0f,0.0f };//

public:
	Camera(glm::vec3 Position, glm::vec3 Up, glm::vec3 Right);
	~Camera();

	glm::mat4 getViewMatrix();

	virtual glm::mat4 getProjectionMatrix();
	virtual void scale(float deltaScale);//获取鼠标滚轮
};

