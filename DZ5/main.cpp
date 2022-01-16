#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include "CircleRenderer.h"
#include "LineRenderer.h"

int Factorial(int x)
{
	if (x > 1)
		return x * Factorial(x - 1);
	else
		return 1;
}

int BinomialCoefficiant(int n, int k)
{
	return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

class BezierCurve
{
    public:


        void RegisterPoint(float x, float y)
        {
            points.push_back({ x,y });
        }

        void ClearPoints()
        {
            points.clear();
        }

        void makeCurve(float i)
        {
            // sum(i=0 to 3)(1-t)^n*Pi, 3* osim prva 2
           for(float t = 0; t <= 1.0; t += i){
            points.push_back((1-t)*(1-t)*(1-t)*T0 + 3*(1-t)*(1-t)*t*T1 + 3*(1-t)*t*t*T2 + t*t*t*T3);
        }

        std::vector<glm::vec2> GetCurve(){
            return points;
        }

	public:
        std::vector<glm::vec2> points;
        glm::vec2 T0,T1,T2,T3;


        BezierCurve(glm::vec2 T0, glm::vec2 T1, glm::vec2 T2, glm::vec2 T3): T0(T0), T1(T1), T2(T2), T3(T3) {}
};



//minGW: g++ main.cpp -o out -lglfw3 -lopengl32 glad/glad.c LineRenderer.cpp CircleRenderer.cpp
int main ()
{
	GLFWwindow* window;

	if (!glfwInit())
    {
		std::cout << "Error : could not initilize GLFW";
    }

	int width = 1000;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(width, width * 9/16, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Error : could not create window";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Error : could not initilize Glad";

	glfwSwapInterval(1);

	InitCircleRendering(32);
	InitLineRendering();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


    bezier.makeCurve(0.001);

    while (!glfwWindowShouldClose(window)) {
    	
	    glClear(GL_COLOR_BUFFER_BIT);

        RenderCircle(bezier.T0, 5);
        RenderCircle(bezier.T1, 5);
        RenderCircle(bezier.T2, 5);
        RenderCircle(bezier.T3, 5);

        RenderLine(bezier.GetCurve());

        glfwSwapBuffers(window);

    }

	return 0;
}
