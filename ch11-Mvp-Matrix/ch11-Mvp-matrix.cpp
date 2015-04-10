#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <shader.h>
#include <SOIL/SOIL.h>
#include <glm/gtc/matrix_transform.hpp>

const static GLsizei VertexCount(32);
const static GLsizeiptr VertexSize = sizeof(GLfloat)* VertexCount;
const static GLfloat VertexData[] = { //vertex data
	// Positions          // Colors           // Texture Coords
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // Top Right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Bottom Right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Left
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top Left 
};

const static GLsizei ElementCount(6);
const static GLsizeiptr ElementSize = sizeof(GLuint)* ElementCount;
const static GLuint ElementData[ElementCount] = {
	0, 1, 3,   // First Triangle
	1, 2, 3    // Second Triangle
};

GLuint vbo, vao, ebo, program, color_loc;
Shader triangleShader("Triangle");
GLuint texture1, texture2, tex1_loc, tex2_loc;
GLuint mvp_matrix_loc;

void init_shader()  // initial the shader 
{
	triangleShader.init();
	triangleShader.attach(GL_VERTEX_SHADER, "rectangle.vert");
	triangleShader.attach(GL_FRAGMENT_SHADER, "rectangle.frag");
	triangleShader.link();
	program = triangleShader.program;
	tex1_loc = glGetUniformLocation(program, "tex1");
	tex2_loc = glGetUniformLocation(program, "tex2");
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
}

void init_buffer()
{
	glGenBuffers(1, &vbo); //initial the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void init_vertexArray()
{
	glGenVertexArrays(1, &vao);  //initial the vertex array object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);  //tranform the data to shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)(NULL));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)(NULL + sizeof(GLfloat)* 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 8, (GLvoid*)(NULL + sizeof(GLfloat)* 6));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //�������vao ebo�Ĵ洢���
	glBindVertexArray(0);
}

void init_texture()
{
	int width, height;
	unsigned char*image = SOIL_load_image("../media/texture/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the file" << std::endl;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); //�󶨵�texture0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	image = SOIL_load_image("../media/texture/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (!image)
		std::cout << "Faile to load the file" << std::endl;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); //�󶨵�texture0
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void init()
{
	init_shader();
	init_texture();
	init_buffer();
	init_vertexArray();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //background color
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao);
	glUniform1i(tex1_loc, 0);
	glUniform1i(tex2_loc, 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))
		* glm::rotate(glm::mat4(1.0f), glm::radians(time*50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 proj_matrix = glm::perspective(45.0f, 720.0f / 640.0f, 0.1f, 1000.0f);
	glm::mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
	glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch6-shader-attribute");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}