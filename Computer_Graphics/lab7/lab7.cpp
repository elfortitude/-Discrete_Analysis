#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <vector>
#include <math.h>


// compile: g++ -std=c++11 main.cpp -o main -lglut -lGL -lGLU -lglfw
using namespace std;
using namespace glm;

#define PI		3.14159265359
#define TWOPI	PI*2

GLFWwindow *window;
int w, h;
double mouseX, mouseY;

vector<double> knots;		// Вектор узлов
vector<dvec2> control;		// контрольные точки вектора
float cRadius = 0.013f;		// радиус контрольной точки(для захвата мышкой)
int selected = -1;			// индекс захваченной точки
bool movePoint = false;		// точка перемещается
bool showPoints = true;		// показывается контрольная точка
bool showColours = true;	// показывать цвета
bool niceLines = true;		// видимые линии
bool sRevolution = false;	//

int k = 4;					// B-spline порядок
double uinc = 0.001;		// Апроксимация
double vinc = PI/16;

bool rotating = false;		// вращается
float yangle = 0.f;			// угол вращения вокруг y
float zangle = 0.f;			// угол вращения вокруг z
float rotSpeed = 100.f;		// скорость вращения
float scale = 1.f;			// параметр масштабирования
float zoomSpeed = 0.02f;

// Возращаем индекс отрезка в котором лежит точка
int delta(double u) {
	int m = control.size();
	for (int i = 0; i <= m + k - 1; i++) {
		if (u >= knots[i] && u < knots[i + 1])
			return i;
	}
	return -1;
}

// Генерирует точку на сплайне алгоритмом де Бура

dvec2 bspline(double u, int d) {

	dvec2 *c = new dvec2[control.size()];
	for (int i = 0; i <= k - 1; ++i) {
		c[i] = control[d - i];
	}

	for (int r = k; r >= 2; --r) {
		int i = d;
		for (int s = 0; s <= r - 2; ++s) {
			double u_i = knots[i];
			double u_ir1 = knots[i + r - 1];
			double omega = (u - u_i) / (u_ir1 - u_i);
			c[s] = omega * c[s] + (1.0 - omega) * c[s + 1];
			i--;
		}
	}

	dvec2 result = c[0];
	delete[] c;
	return result;
}

// vec2 getBezierPoint( vec2* points, int numPoints, float t ) {
//     vec2* tmp = new vec2[numPoints];
//     memcpy(tmp, points, numPoints * sizeof(vec2));
//     int i = numPoints - 1;
//     while (i > 0) {
//         for (int k = 0; k < i; k++)
//             tmp[k] = tmp[k] + t * ( tmp[k+1] - tmp[k] );
//         i--;
//     }
//     vec2 answer = tmp[0];
//     delete[] tmp;
//     return answer;
// }


// переодичый
void generateKnots() {
	knots.clear();

	for (int i = 0; i < k; i++)
		knots.push_back(0.0);

	int middle = control.size() - k;
	for (int i = 0; i < middle; i++)
		knots.push_back(double(i+1) / (middle+1));

	for (int i = 0; i < k; i++)
		knots.push_back(1);
}

// Функция отрисовки
void render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Задаем значения для инициализации в библиотеке
	if (niceLines && !sRevolution) {
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_BLEND);
	}

	// Добляем к матрице модели масштабирование и повороты вокруг осей z и y
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(scale, scale, scale);			// scale by factor
	glRotatef(yangle, 0.0f, 1.0f, 0.0f);	// rotate by y angle
	glRotatef(zangle, 0.0f, 0.0f, 1.0f);	// rotate by z angle

	// Задаем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 10);

	// Отрисовываем контрольные точки в виде квадратиков
	if (showPoints) {
		glBegin(GL_QUADS);

		for (int i = 0; i < control.size(); i++) {
			float pr = 1.f;
			float pg = 1.f;
			float pb = 1.f;
			if (selected == i) {
				pg = 0.f;
				pb = 0.f;
			}

			glColor3f(pr, pg, pb);
			glVertex3f(control[i].x + cRadius, control[i].y + cRadius, 0);
			glColor3f(pr, pg, pb);
			glVertex3f(control[i].x + cRadius, control[i].y - cRadius, 0);
			glColor3f(pr, pg, pb);
			glVertex3f(control[i].x - cRadius, control[i].y - cRadius, 0);
			glColor3f(pr, pg, pb);
			glVertex3f(control[i].x - cRadius, control[i].y + cRadius, 0);
		}

		glEnd();
	}

	// Отрисовываем кривую
	glLineWidth(3.5);
	glBegin(GL_LINE_STRIP);

	// Обновляем вектор узлов в зависимости от контрольных точек
	generateKnots();

	// Генерируем B-spline
	// Иттерация
	for (double u = knots[k-1] + uinc; u <= knots[control.size()]; u += uinc) {
		// Получаем индекс дельта отрезка в равномерном векторе узлов
		int d = delta(u);

		// генерируем цвета и ершины
		if (control.size() >= d) {
			float cr = 1;
			float cg = 1;
			float cb = 1;
			// цвет
			if (showColours) {
				cr = 0.5 * (sin(101 * u) + 1);
				cg = 0.5 + 0.25 * (cos(11 * u) + 1);
				cb = 0.5 * (sin(71 * u) + 1);
			}
			glColor3f(cr, cg, cb);

			// отрисовываем
			dvec2 point = bspline(u, d);
			/*if (!sRevolution)*/
			glVertex3f(point.x, point.y, 0);
		}
	}

	glEnd();
}

// Обработка нажатий клавиатуры
void keyboard (GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Настройка аппроксимация

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
		uinc *= 0.9;

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
		uinc *= 1.1;

	// Скрыть точки

	if (key == GLFW_KEY_HOME && action == GLFW_PRESS)
		showPoints = !showPoints;

	if (key == GLFW_KEY_END && action == GLFW_PRESS)
		niceLines = !niceLines;

	// Скрыть цвет

	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
		showColours = !showColours;

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		scale = 1.f;
		yangle = 0.f;
		zangle = 0.f;
	}

	// Стриание
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
		control.clear();
		uinc = 0.001;
		showPoints = true;
		sRevolution = false;
		scale = 1.f;
		yangle = 0.f;
		zangle = 0.f;
	}
}

// Обработка нажатий мыши
void mouseClick (GLFWwindow *sender, int button, int action, int mods) {

    if (action == GLFW_PRESS) {
		selected = -1;
		double x = (2 * mouseX / w) - 1;
		double y = (-2 * mouseY / h) + 1;

		// Выбор точки для перемещения
		for (int i = 0; i < control.size(); i++) {
			if (abs(control[i].x - x) <= cRadius && abs(control[i].y - y) <= cRadius) {
				selected = i;
				cout << "Selected point: " << selected << endl;
				movePoint = true;
			}
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && selected == -1) {
			// Создание новой контрольной точки
			control.push_back(vec2(x, y));
		}

		else if (button == GLFW_MOUSE_BUTTON_RIGHT && selected >= 0) {
			// Удаление старой контрольной точки
			control.erase(control.begin() + selected);
			cout << "Deleted point: " << selected << endl;
			selected = -1;
		}

		else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
			glfwGetCursorPos(window, &mouseX, &mouseY);
			rotating = true;
		}
    }

	if (action == GLFW_RELEASE) {
		movePoint = false;
		rotating = false;
	}
}

// Обработка координат мыши

void mousePos(GLFWwindow *sender, double x, double y) {
	// Вращение
	if (rotating) {
		yangle += rotSpeed * float(x - mouseX) / float(w);
		zangle += rotSpeed * float(y - mouseY) / float(h);
	}

	mouseX = x;
	mouseY = y;

	// перемещение выбранной точки
	if (movePoint && selected >= 0) {
		double newx = (2 * mouseX / w) - 1;
		double newy = (-2 * mouseY / h) + 1;
		control[selected] = vec2(newx, newy);
	}
}


void mouseScroll(GLFWwindow *sender, double x, double y) {
	// Масштабирование
	scale += zoomSpeed * y;
}


int main () {
	// Инициализация GLFW
	if (!glfwInit()) return 1;

	// Создание окна
	window = glfwCreateWindow (800, 800, "Lab7 Var13", NULL, NULL);
	if (!window) return 1;
	glfwMakeContextCurrent (window);

	// Функции обратного вызова
	glfwSetKeyCallback (window, keyboard);
	glfwSetMouseButtonCallback (window, mouseClick);
	glfwSetCursorPosCallback (window, mousePos);
	glfwSetScrollCallback(window, mouseScroll);

	// Игровой цикл
	while (!glfwWindowShouldClose (window)) {
		glfwGetFramebufferSize (window, &w, &h);
		glViewport (0, 0, w, h);

		render ();

		glfwSwapBuffers (window);
		glfwPollEvents();
	}

	// очистка окна и выход
	glfwDestroyWindow (window);
	glfwTerminate();
	return 0;
}