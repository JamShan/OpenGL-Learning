#include "OGLRenderSystem.h"

const static glm::vec3 g_LightPos(1.5f, 0.5f, 0.0f);

namespace byhj
{
	void OGLRenderSystem::v_InitInfo()
	{
		windowInfo.title += ": Point";
	}

	void OGLRenderSystem::v_Init()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND); //�������
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Point.Init();
		m_Camera.SetPos( glm::vec3(0.0f, 1.0f, 3.0f) );
	}

	void OGLRenderSystem::v_Render()
	{
		static const float bgColor[4] = {0.2f, 0.3f, 0.4f, 1.0f};
		glClearBufferfv(GL_COLOR, 0, bgColor);
		static const float one = 1.0f;
		glClearBufferfv(GL_DEPTH, 0, &one);

		update();

		static const byhj::MvpMatrix &matrix;
		matrix.view  = m_Camera.GetViewMatrix();
		matrix.proj  = glm::perspective(glm::radians(m_Camera.GetZoom() ), GetAspect(), 0.1f, 1000.0f);
		matrix.model = glm::mat4(1.0f);

		glEnable(GL_PROGRAM_POINT_SIZE);
		glEnable(GL_POINT_SPRITE);

		m_Point.Render(matrix);

	}

	void OGLRenderSystem::v_Shutdown()
	{
		m_Point.Shutdown();
	}

	/////////////////////////////////Key and Mouse//////////////////////////////////
	void OGLRenderSystem::v_Movement(GLFWwindow *Triangle)
	{
		m_Camera.movement(Triangle);
	}
	void OGLRenderSystem::v_KeyCallback(GLFWwindow* Triangle, int key, int scancode, int action, int mode)
	{
		m_Camera.key_callback(Triangle, key, scancode, action, mode);
	}

	void OGLRenderSystem::v_MouseCallback(GLFWwindow* Triangle, double xpos, double ypos)
	{
		m_Camera.mouse_callback(Triangle, xpos, ypos);
	}

	void OGLRenderSystem::v_ScrollCallback(GLFWwindow* Triangle, double xoffset, double yoffset)
	{
		m_Camera.scroll_callback(Triangle, xoffset, yoffset);
	}

	void OGLRenderSystem::update()
	{
		static GLfloat lastFrame = static_cast<float>( glfwGetTime() );
		GLfloat currentFrame = static_cast<float>( glfwGetTime() );
		GLfloat deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		m_Camera.update(deltaTime);
	}

}