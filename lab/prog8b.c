/*
Aim: Develop a menu driven program to animate a flag using Bezier Curve
algorithm

Compile: gcc prog8b.c -lGL -lGLU -lglut -lm
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int i, k, u;
int flag;
void beziercoeff(int n, float *c) {
  for (k = 0; k <= n; k++) {
    c[k] = 1;
    for (i = n; i >= k + 1; i--) {
      c[k] *= i;
    }
    for (i = n - k; i >= 1; i--) {
      c[k] /= i;
    }
  }
}

void init() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 100, 0, 100);
  glMatrixMode(GL_MODELVIEW);
}

void draw(int cp[][2]) {
  float blend, u, x, y;
  int n = 3;
  float c[4];
  beziercoeff(n, c);

  glLineWidth(100.0);
  glBegin(GL_LINE_STRIP);
  for (u = 0; u <= 1; u += 0.01) {
    x = 0, y = 0;
    for (k = 0; k <= n; k++) {
      blend = c[k] * pow(u, k) * pow(1 - u, n - k);
      x += cp[k][0] * blend;
      y += cp[k][1] * blend;
    }
    glVertex2f(x, y);
  }

  glEnd();
}

void flagu() {
  int x = 0, y = 0, i, j, k;
  for (i = 0; i < 100000; i++) {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.25, 0.25);
    int cp[4][2] = {{10, 10},
                    {20 + x - 25, 20 + y - 25},
                    {30 - x + 25, 25 - y + 25},
                    {40, 30}};
    draw(cp);

    glColor3f(1, 1, 1);
    int cp1[4][2] = {{10, 9},
                     {21 + x - 25, 19 + y - 25},
                     {31 - x + 25, 24 - y + 25},
                     {41, 29}};
    draw(cp1);

    glColor3f(0, 1, 0);
    int cp2[4][2] = {{10, 8},
                     {22 + x - 25, 18 + y - 25},
                     {32 - x + 25, 23 - y + 25},
                     {42, 28}};
    draw(cp2);
    if (x == 90) {
      x = y = 0;
    }
    x++;
    y++;
    glFlush();
    for (j = 0; j < 1000; j++)
      for (k = 0; k < 5000; k++)
        ;
  }
}
void scan_menu(int id) {
  if (id == 1)
    flag = 1;
  else if (id == 2)
    flag = 2;
  else
    exit(0);
  glutPostRedisplay();
}
void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if (flag == 1) {
    glColor3f(0, 1, 0);
    int cp2[4][2] = {{12, 10}, {22, 48}, {32, 5}, {42, 50}};
    draw(cp2);
  } else if (flag == 2) {
    flagu();
  }

  glFlush();
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Bezier");
  init();
  glutDisplayFunc(display);
  glutCreateMenu(scan_menu);
  glutAddMenuEntry("Curve", 1);
  glutAddMenuEntry("flag", 2);
  glutAddMenuEntry("exit", 0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;
}
