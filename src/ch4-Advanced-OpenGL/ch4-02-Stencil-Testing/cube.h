#ifndef CUBE_H
#define CUBE_H

#include "ogl/Shader.h"
#include "ogl/Utility.h"

#include <glfw/glfw3.h>

namespace byhj
{

	class Cube
	{
	public:
		Cube(): color_prog(0), cube_prog(0), vao(0), vbo(0), CubeShader("Cube Shader") {}
		~Cube() {}

	public:
		void Init();
		void Render(const const ogl::MvpMatrix &matrix);
		void RenderColor(const const ogl::MvpMatrix &matrix);
		void Shutdown();
	
	private:
		void init_shader();
		void init_buffer();
		void init_vertexArray();
		void init_texture();

		GLuint vao, vbo;
		GLuint color_prog, cube_prog;
		GLuint texture, tex_loc;
		GLuint model_loc, view_loc, proj_loc;
		GLuint color_model_loc, color_view_loc, color_proj_loc; 

		ogl::Shader CubeShader;		
		ogl::Shader ColorShader;
	};

}

#endif