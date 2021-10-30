#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"


int i, timer;
double q = 1;
double p = 0;
double x = 0;
double y = 0;
double z = 0;
double x1 = 0;
double y1 = 0;
double z1 = 0;
/*double colors[4][3] = { {0.0,0.0,0.0},
						{1.0,1.0,1.0},
						{0.0,0.0,1.0},
						{1.0,0.0,0.0},
};*/

void Simulation(int value) // функция вызывается каждые 20 мс, изменение параметров сцены
{
	glutPostRedisplay(); // уфункция отмечает, что окно нуждается в перерисовке
	//таймер
	/* timer += 20;
	if (timer >= 1000) {
		if (i < 3) {
			i++;
		}
		else
			i=0;
		timer = 0;
	} */
	glutTimerFunc(20, Simulation, 0); // функция вызывается каждые 20 мс
}

void Reshape(int w, int h) // фун-ия при изменении размеров окна
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); // устанавливаем новую область просмотра, равную всей области экрана
	glMatrixMode(GL_PROJECTION); // устанавливаем матрицу проекции с правильным аспектом
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
}

void Display(void) //функция для перерисовки окна
{
	// чистим буфер цвета
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру и ее положение
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	timer += 20;
	if (timer >= 20) 
	{
		if (q < 1.5) 
		{
			q += 0.02;
		}
		else
		{
			if (p > -0.5)
			{
				p -= 0.02;
			}
			else {
				q = 1; p = 0;
			}
		}

		timer = 0;
	}


	glScalef(q+p, q+p, q+p);

	//
	timer += 20;
	if (timer >= 20)
	{
		if (x < 1)
			x += 0.05;
		else
		{
			if (y < 1)
				y += 0.05;
			else
			{
				if (z < 1)
					z += 0.05;
				else
				{
					if (x1 < 1)
						x1 += 0.05;
					else
					{
						if (y1 < 1)
							y1 += 0.05;
						else
						{
							if (z1 < 1)
								z1 += 0.05;
							else
							{
								x = 0; y = 0; z = 0; x1 = 0; y1 = 0; z1 = 0;
							}
						}
					}
				}
			}
		}
	}
	// выводим объект - чайник (красный (1,0,0))
	glColor3f(x-x1 ,y-y1 ,z-z1 );


	glutWireTeapot(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
}

/*// функция обработи нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);	//пишет в консоль код клавиши
	
	//смена при нажатии
	if ((unsigned int)key) {
		if (i < 3) {
			i++;
		}
		else
			i = 0;
	}												
}*/

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// четверка цветов, двойная буферизация, буфер глубины, ин-ия для каждого пикселя

	// создание окна
	glutInitWindowPosition(200, 200); // верхний левый угол окна
	glutInitWindowSize(700, 600); // размер окна
	glutCreateWindow("LR_1"); // создаем окно
	
	glutDisplayFunc(Display); // функция для перерисовки окна
	glutReshapeFunc(Reshape); //функция при изменении разверов окна
	glutTimerFunc(20, Simulation, 0); // Функция, которая будет вызвана через 20 секунд
	//glutKeyboardFunc(KeyboardFunc); // функция, которая вызывается при нажатии на клавишу

	glutMainLoop(); // основной цикл обработки сообщений ОС
	return;
}