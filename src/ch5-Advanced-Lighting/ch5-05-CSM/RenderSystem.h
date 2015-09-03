#ifndef OGLRENDERSYSTEM_H
#define OGLRENDERSYSTEM_H

#include "ogl/App.h"
#include "ogl/camera.h"

#include "cube.h"
#include "plane.h"

namespace byhj
{

class RenderSystem : public ogl::App
{
public:
	RenderSystem() {}
	~RenderSystem() {}

	///////////////////////// Window and Render //////////////////////////////////
	void v_InitInfo();
	void v_Init();
	void v_Render();
	void v_Shutdown();

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void v_Movement(GLFWwindow *window);
	void v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void v_MouseCallback(GLFWwindow* window, double xpos, double ypos);
	void v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


private:
	void update();

	byhj::Cube   m_Cube;
	byhj::Plane  m_Plane;
	ogl::Camera m_Camera;
};


}

#endif