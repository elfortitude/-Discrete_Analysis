#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

int X_COORD;
int Y_COORD;
const float ITERATIONS = 0.00005;
int x_off;
int y_off;
float a;

float x_from_polar(float r, float f){
  return r*cos(f);
}

float y_from_polar(float r, float f){
  return r*sin(f);
}

float r_function(float f){
  return a*sin(2*f);
}

void drawgrid(float SERIF_OFFSET, float SERIF_DISTANCE) {
    glBegin(GL_LINES);
        //задаем цвета
        glColor3f(0.0, 0.0, 0.0);

        //рисуем координатные оси
        //горизонталь
        glVertex2f(0.0, Y_COORD / 2);
        glVertex2f(X_COORD, Y_COORD / 2);

        glVertex2f(X_COORD, Y_COORD / 2);
        glVertex2f(X_COORD * 0.97, 0.53 * Y_COORD);

        glVertex2f(X_COORD, Y_COORD / 2);
        glVertex2f(X_COORD * 0.97, 0.47 * Y_COORD);

        //засечки по горизонтали
        int p = X_COORD / 2;
        for(int i = X_COORD / 2; i < X_COORD; i += SERIF_DISTANCE, p -= SERIF_DISTANCE) {
            glVertex2f(i, Y_COORD / 2);
            glVertex2f(i, Y_COORD / 2 + SERIF_OFFSET);

            glVertex2f(p, Y_COORD / 2);
            glVertex2f(p, Y_COORD / 2 + SERIF_OFFSET);

        }
        //вертикаль
        int t = Y_COORD / 2;
        glVertex2f(X_COORD / 2, Y_COORD);
        glVertex2f(X_COORD / 2, 0.0);

        glVertex2f(X_COORD / 2, Y_COORD);
        glVertex2f(X_COORD * 0.53, 0.97 * Y_COORD);

        glVertex2f(X_COORD / 2, Y_COORD);
        glVertex2f(X_COORD * 0.47, 0.97 * Y_COORD);

        //засечки по вертикали
        for(int i = Y_COORD / 2; i < Y_COORD; i += SERIF_DISTANCE, t -= SERIF_DISTANCE) {
            glVertex2f(X_COORD / 2, i);
            glVertex2f(Y_COORD / 2 + SERIF_OFFSET, i);

            glVertex2f(X_COORD / 2, t);
            glVertex2f(Y_COORD / 2 + SERIF_OFFSET, t);
        }
    glEnd();

   char cText[5] = {0};
   int iStrLength = 0;

   for (int iCurX = -X_COORD/2 + 1; iCurX < X_COORD/2; iCurX++)
   {
       sprintf(cText, "%i", iCurX);
       iStrLength = (int) strlen(cText);

       glPushMatrix();
       glTranslatef(iCurX + X_COORD/2, 0.25 + Y_COORD/2, 0.5);
       glScalef(0.002, 0.002, 1);

       for (int iCurChar = 0; iCurChar < iStrLength; iCurChar++)
       {
           glutStrokeCharacter(GLUT_STROKE_ROMAN, cText[iCurChar]);
       }
       glPopMatrix();
   }
   for (int iCurX = -Y_COORD/2 + 1; iCurX < Y_COORD/2; iCurX++)
   {
       if(!iCurX){
         continue;
       }
       sprintf(cText, "%i", iCurX);
       iStrLength = (int) strlen(cText);

       glPushMatrix();
       glTranslatef(0.25 + X_COORD/2, iCurX + Y_COORD/2, 0.5);
       glScalef(0.002, 0.002, 1);

       for (int iCurChar = 0; iCurChar < iStrLength; iCurChar++)
       {
           glutStrokeCharacter(GLUT_STROKE_ROMAN, cText[iCurChar]);
       }
       glPopMatrix();
   }

   glPushMatrix();
   glTranslatef(-1 + X_COORD/2, Y_COORD - 1, 0.5);
   glScalef(0.004, 0.004, 1);

   glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');

   glPopMatrix();

   glPushMatrix();

   glTranslatef(X_COORD - 1, Y_COORD/2 - 1, 0.5);
   glScalef(0.004, 0.004, 1);

   glutStrokeCharacter(GLUT_STROKE_ROMAN, 'X');

   glPopMatrix();

}

void drawfunc() {
    //рисуем график
    glBegin(GL_POINTS);
        glColor3f(0.8, 0.0, 0.8);
        for(float f = 0; f <= M_PI * 2; f += M_PI * ITERATIONS) {
            //перерасчитываем координаты
            glVertex2f(x_off + x_from_polar(r_function(f), f), y_off + y_from_polar(r_function(f), f));
        }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawgrid(0.25, 1);
    drawfunc();

    glutSwapBuffers();

    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter a: ";
    cin >> a;
    if(a < 0){
      std::cout << "Wrong a! Exit!" << '\n';
      return 0;
    }
    
    X_COORD = max(2, 4*int(a));
    Y_COORD = max(2, 4*int(a));
    x_off = X_COORD / 2;
    y_off = Y_COORD / 2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(500, 200);
    glutCreateWindow("Lab1 Var13");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //пространство координат
    glOrtho(0.0, X_COORD, 0.0, Y_COORD, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
return 0;
}