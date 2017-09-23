#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#define SHADER_DATA
#include "shaderData.h"
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <thread>

#include "fastCircleRectangle.h"

int main()
{
	const float speed = 4;
	
	Window window(1280, 720, "Collision");
	
	Mesh mesh;
	Shader rectShader(rectVert, rectFrag);
	Shader circleShader(circleVert, circleFrag);
	
	Transform rectTransform({-2, 0});
	Transform circleTransform({2, 0});
	
	glm::mat4 vp = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f);
	
	glm::vec4 rectColor;
	glm::vec4 circleColor;
	
	double lastTime = 0;
	const double delta = 1.0f/60;
	glfwSetTime(0);
	while(!glfwWindowShouldClose(window.getWindow()))
	{
		glfwPollEvents();
		
		if(glfwGetKey(window.getWindow(), GLFW_KEY_A))rectTransform.getPos() -= glm::vec2(speed * delta, 0);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_D))rectTransform.getPos() += glm::vec2(speed * delta, 0);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_W))rectTransform.getPos() += glm::vec2(0, speed * delta);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_S))rectTransform.getPos() -= glm::vec2(0, speed * delta);
		
		if(glfwGetKey(window.getWindow(), GLFW_KEY_E))rectTransform.getScale() += glm::vec2(delta, 0);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_Q))
		{
			rectTransform.getScale() -= glm::vec2(delta, 0);
			if(rectTransform.getScale().x <0.01f)rectTransform.getScale().x = 0.01f;
		}
		if(glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_SHIFT))rectTransform.getScale() += glm::vec2(0, delta);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_CONTROL))
		{
			rectTransform.getScale() -= glm::vec2(0, delta);
			if(rectTransform.getScale().y <0.01f)rectTransform.getScale().y = 0.01f;
		}
		
		if(glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))circleTransform.getPos() -= glm::vec2(speed * delta, 0);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT))circleTransform.getPos() += glm::vec2(speed * delta, 0);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_UP))circleTransform.getPos() += glm::vec2(0, speed * delta);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))circleTransform.getPos() -= glm::vec2(0, speed * delta);
		
		if(glfwGetKey(window.getWindow(), GLFW_KEY_PAGE_UP))circleTransform.getScale() += glm::vec2(delta, delta);
		if(glfwGetKey(window.getWindow(), GLFW_KEY_PAGE_DOWN))
		{
			circleTransform.getScale() -= glm::vec2(delta, delta);
			if(circleTransform.getScale().x <0.01f)circleTransform.getScale() = glm::vec2(0.01f, 0.01f);
		}
		
		float radius = (circleTransform.getScale().x + circleTransform.getScale().y) / 4;
		if(circleRectCollision(rectTransform.getPos(), rectTransform.getScale(), circleTransform.getPos(), radius))
		{
			rectColor = {0, 1, 0, 1};
			circleColor = {0, 1, 0, 1};
		}
		else
		{
			rectColor = {1, 0, 0, 1};
			circleColor = {0, 0, 1, 1};
		}
		
		window.clear(0, 0, 0, 1);
		rectShader.bind();
		rectShader.uniformMat(0, vp * rectTransform.getModel());
		rectShader.uniform(1, rectColor);
		mesh.draw();
		
		circleShader.bind();
		circleShader.uniformMat(0, vp * circleTransform.getModel());
		circleShader.uniform(1, circleColor);
		mesh.draw();
		
		window.swapBuffers();
		
		std::this_thread::sleep_for(std::chrono::duration<double>(delta + glfwGetTime() - lastTime));
		lastTime = glfwGetTime();
	}
	
	return 0;
}