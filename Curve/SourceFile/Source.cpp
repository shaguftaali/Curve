#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "..\Includes\Shader.h"
#include <iostream>
#include "../Includes/Camera.h"
#include "vector"
#include "../Includes/Maths/Curve.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void processInput(GLFWwindow *window);
void processInput(GLFWwindow *window, vector<Vector3>& controlPoints);
void ConvertVectorToFloatList(vector<Vector3>& controlPoints, vector<float>& floatList);


std::vector<float> vertices;
std::vector<float> controlPointVertices;
vector<int> controlIndices;
// settings
const  int SCR_WIDTH = 800;
const   int SCR_HEIGHT = 800;

float x_mousePosition;
float y_mousePosition;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	glewInit();
	glfwSetCursorPosCallback(window, mouse_callback);
	Shader ourShader("D:/Shagufta/OpenGL_Workspace/Curve/Curve/Shaders/VertexShader.vs", "D:/Shagufta/OpenGL_Workspace/Curve/Curve/Shaders/FragmentShader.fs");

	

	//float vertices[] = {
	//	// front
	//	-20.2, -20.2, -20.5, 
	//	 20.2, -20.2, -20.5, 
	//	 20.2,  20.2, -20.5,  
	//	-20.2,  20.2, -20.5,
	//				   
	//	-20.2, -20.2,  20.5 ,  
	//	 20.2, -20.2,  20.5 ,    
	//	 20.2,  20.2,  20.5 ,    
	//	-20.2,  20.2,  20.5    
	//};

	//float vertices[] = {
	//	// front
	//	-10,   10,   0,
	//	 45,   32.5, 0,
	//	 90,  -20,   0,
	//	
	//};


	Camera camera = Camera(Vector3(0, 0, -100), Vector3(0, 0, 0), 1000, 0.01f, -1*SCR_WIDTH/4, SCR_WIDTH/4, SCR_HEIGHT/4, -1*SCR_HEIGHT/4);
	vector<Vector3> controlPoints;
	controlPoints.push_back(Vector3(10, 10, 0));
	controlPoints.push_back(Vector3(40, 70, 0));
	controlPoints.push_back(Vector3(90, -20, 0));
	//
	 controlPoints.push_back(Vector3(130, 120, 0));
	ConvertVectorToFloatList(controlPoints,controlPointVertices);
	Curve curve = Curve(controlPoints);

	/*std::vector<float> vertices=curve.GetFinalControlPoints(controlPoints,20);*/
	vertices = curve.GetFinalControlPoints(controlPoints, 20);
	

	//unsigned int indices[] = {
	//	//front
	//	0,1,2,
	//	0,2,3,

	//	//back face
	//	4,6,5,
	//	4,7,6

	//};

	//unsigned int indices[] = {
	//	//front
	//	0,1,2
	//	
	//};

	vector<int> indices;
	for(int i=0;i<vertices.size()/3;i++)
	{
		indices.push_back(i);
	}

	
	for (int i = 0; i<controlPointVertices.size()/3; i++)
	{
		controlIndices.push_back(i);
	}

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*300, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float)*vertices.size(),&vertices[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 300, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float)*indices.size(), &indices[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	
	
	unsigned int controlVBO, controlVAO, controlEBO;
	glGenVertexArrays(1, &controlVAO);
	glGenBuffers(1, &controlVBO);
	glGenBuffers(1, &controlEBO);

	glBindVertexArray(controlVAO);

	glBindBuffer(GL_ARRAY_BUFFER, controlVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 300, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*controlPointVertices.size(), &controlPointVertices[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*controlPointVertices.size(), &controlPointVertices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, controlEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 300, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float)*controlIndices.size(), &controlIndices[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*controlIndices.size(), &controlIndices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window, controlPoints);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.setMat4("view", camera.viewMatrix);
		//ourShader.setMat4("view", Matrix4::IdentityMat);
		ourShader.setMat4("projection", camera.projectionMatrix);
		ourShader.setMat4("model",Matrix4::IdentityMat);

		ourShader.use();


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(controlVAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, controlEBO);

		glLineWidth(2);
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_STRIP, controlIndices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void processInput(GLFWwindow *window,vector<Vector3>& controlPoints)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		//controlPoints.push_back(mousePosition);
		int offset=controlPointVertices.size();
		controlPointVertices.push_back(x_mousePosition);
		controlPointVertices.push_back(y_mousePosition);
		controlPointVertices.push_back(0);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*offset,sizeof(float)*3, &controlPointVertices[0]);

		offset=controlIndices.size();
		controlIndices.push_back(offset);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(int)*offset,sizeof(int), &controlIndices[0]);
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout<<"x : "<<xpos<<"  y : "<<ypos<<endl;
	x_mousePosition=xpos;
	y_mousePosition=ypos;

}

void VerticesData(int& VBO, int& VAO, int& EBO )
{
	//VBO, VAO, EBO;
}

void ConvertVectorToFloatList(vector<Vector3>& controlPoints, vector<float>& floatList)
{
	floatList.clear();
	for(int i=0;i<controlPoints.size();i++)
	{
		floatList.push_back(controlPoints[i].x);
		floatList.push_back(controlPoints[i].y);
		floatList.push_back(controlPoints[i].z);
	}
}

//void AddT

