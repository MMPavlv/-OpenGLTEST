#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"

#include <iostream>
#include <vector>

#include "Game.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���������
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

float a1 = 0.0f;
float a2 = 0.0f;
float a3 = 0.0f;
float x_shift = 0.0f;
float y_shift = 0.0f;
int rot_type = -1;

int main()
{
	//
	LGE::Game MainGame;

	// glfw: ������������� � ����������������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw: �������� ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: �������� ���� ���������� �� OpenGL-�������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ���������������� ����������� ��������� OpenGL
	glEnable(GL_DEPTH_TEST);

	// �������������� ����� ��������� ���������
	Shader ourShader("vShader.vert", "fShader.frag");

	// �������� ������ (� ������(��)) � ��������� ��������� ���������
	float vertices[] = {
		// ����������        // ���������� ����������
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f
	};

	///////

	LGE::AABBCollider BoxCollider(LGE::ColliderType::AABB, glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f));
	LGE::CylinderCollider UserCollider(LGE::ColliderType::Cylinder, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.5f);
	///////

	// ������� ���������� ����� �������
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f, 1.0f),
		glm::vec3(2.0f, 0.0f, 2.0f),
		glm::vec3(3.0f, 0.0f, 3.0f),
		glm::vec3(4.0f, 0.0f, 4.0f),
		glm::vec3(5.0f,  0.0f, 5.0f),
		glm::vec3(6.0f, 0.0f, 6.0f),
		glm::vec3(7.0f,  0.0f, 7.0f),
		glm::vec3(8.0f,  0.0f, 8.0f),
		glm::vec3(9.0f,  0.0f, 9.0f)
	};

	/////////////////////
	{
	// �������� � �������� �������
	unsigned int texture1, texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// ��������� ���������� ��������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��������� ���������� ���������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �������� �����������, �������� �������� � ������������� ������-�������
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); 
	unsigned char* data = stbi_load("metal.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// ��������� ���������� ��������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��������� ���������� ���������� ��������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// �������� �����������, �������� �������� � ������������� ������-�������
	data = stbi_load("EH5bQU.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	std::cout << ourShader.loadTexture("metal.jpg", GL_RGB) << std::endl;
	std::cout << ourShader.loadTexture("EH5bQU.png", GL_RGBA) << std::endl;
	ourShader.SetTextures();
	}
	/////////////////////

	MainGame.shaders.push_back(ourShader);

	// �������� ������� ������� �������� (��������� ������������ ������� ����� ��������, �� ��� ������������� ������ ��� ��� ������� �����)
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);

	std::vector<LGE::GameObjectPolyhedron> objects;
	std::vector<float> vec(std::begin(vertices), std::end(vertices));
	for(int  i = 0; i < 10; i++)
	{
		auto *lobj = new LGE::GameObjectPolyhedron(LGE::GameObjectType::staticObject, MainGame.globalCounter++, vec, MainGame.shaders.size() - 1, cubePositions[i], 0.0f);
		lobj->setCollider(&BoxCollider);
		MainGame.staticObjects.push_back(lobj);

	}

	auto userobj = LGE::GameObjectPolyhedron(LGE::GameObjectType::userobject, MainGame.globalCounter++, vec, MainGame.shaders.size() - 1, glm::vec3(1.0f, 0.0f, 5.0f), 0.0f);
	userobj.setCollider(&UserCollider);
	MainGame.playObject = &userobj;
	// ���� ����������
	while (!glfwWindowShouldClose(window))
	{
		// ��������� �����
		processInput(window);

		MainGame.x_shift = x_shift;
		MainGame.y_shift = y_shift;
		MainGame.a2 = a2;

		MainGame.placing();
		MainGame.render();
		x_shift = 0.0f;
		y_shift = 0.0f;
		//glfw: ����� ���������� front- � back- �������. ������������ ������� �����/������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
	for (unsigned int i = 0; i < 10; i++)
	{
		//objects[i].Dispose();
	}

	// glfw: ����������, ������������ ���� ���������� ����� GLFW-��c�����
	glfwTerminate();
	return 0;
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ ���� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		y_shift -= 0.05;
	}
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		y_shift += 0.05;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		a2 -= 0.01;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		a2 += 0.01;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		x_shift += 0.05;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		x_shift -= 0.05;
	}
}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ����������, ��� ���� ��������� ������������� ����� �������� ����.
	// �������� ��������, ������ � ������ ����� ����������� ������, ��� �������, �� Retina-��������
	glViewport(0, 0, width, height);
}