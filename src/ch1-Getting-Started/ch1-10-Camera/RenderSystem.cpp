#include <GL/glew.h>
#include "RenderSystem.h"

namespace byhj
{

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::v_InitInfo()
{
	windowInfo.title += "Cube";
}

void RenderSystem::v_Init()
{
	glEnable(GL_DEPTH_TEST);
	m_Cube.Init();
	m_Camera.SetPos( glm::vec3(0.0f, 0.0f, 3.0f) );

}

void RenderSystem::v_Render()
{
	static const float bgColor[4] = { 0.2f, 0.4f, 0.5f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, bgColor);
	static const float one = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &one);

	update();

	static ogl::MvpMatrix matrix;
	static float aspect = GetAspect();
	float zoom   = m_Camera.GetZoom();
	matrix.view  = m_Camera.GetViewMatrix();
	matrix.proj  = glm::perspective(glm::radians(zoom), aspect, 0.1f, 1000.0f);
	matrix.model = glm::mat4(1.0f);

	m_Cube.Render(matrix);

}


void RenderSystem::v_Shutdown()
{
	m_Cube.Shutdown();
}

/////////////////////////////////Key and Mouse//////////////////////////////////

void RenderSystem::v_Movement(GLFWwindow *window)
{
	m_Camera.movement(window);
}
void RenderSystem::v_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	m_Camera.key_callback(window, key, scancode, action, mode);
}

void RenderSystem::v_MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_Camera.mouse_callback(window, xpos, ypos);
}

void RenderSystem::v_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_Camera.scroll_callback(window, xoffset, yoffset);
}

void RenderSystem::update()
{
	static GLfloat lastFrame = static_cast<float> ( glfwGetTime() );
	GLfloat currentFrame = static_cast<float> ( glfwGetTime() );
	GLfloat deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	m_Camera.update(deltaTime);
}

}
