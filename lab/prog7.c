/*
Aim: Design, develop and implement recursively subdivide a tetrahedron to form
3D sierpinski gasket. The number of recursive steps is to be specified by the
user.

Compile: gcc prog7.c -lGL -lGLU -lglut
*/

#include <GL/glut.h>
#include <stdio.h>

float v[][3] = {{0, 0, 1}, {0, 1, -1}, {1, -1, -1}, {-1, -1, -1}};
int n = 0;

void triangle(float *a, float *b, float *c) {
  glBegin(GL_TRIANGLES);
  glVertex3fv(a);
  glVertex3fv(b);
  glVertex3fv(c);
  glEnd();
}

void dt(float *a, float *b, float *c, int n) {
  int i;
  float v1[3], v2[3], v3[3];
  if (n > 0) {
    for (i = 0; i < 3; i++) {
      v1[i] = (a[i] + b[i]) / 2;
      v2[i] = (b[i] + c[i]) / 2;
      v3[i] = (a[i] + c[i]) / 2;
    }
    dt(a, v1, v3, n - 1);
    dt(v1, b, v2, n - 1);
    dt(v2, v3, c, n - 1);
  } else
    triangle(a, b, c);
}

void tetrahedron(int n) {
  glColor3f(1, 0, 0);
  dt(v[1], v[0], v[3], n);

  glColor3f(0, 1, 0);
  dt(v[1], v[0], v[2], n);

  glColor3f(0, 0, 1);
  dt(v[0], v[2], v[3], n);

  glColor3f(0, 0, 0);
  dt(v[1], v[2], v[3], n);
}

void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // drawing the view volume
  glColor3f(1, 0, 0);
  dt(v[0], v[1], v[2], n);

  glColor3f(0, 1, 0);
  dt(v[0], v[2], v[3], n);

  glColor3f(0, 0, 1);
  dt(v[0], v[3], v[1], n);

  glFlush();
}

void init() {
  glMatrixMode(GL_PROJECTION);
  glOrtho(-2, 2, -2, 2, -5, 5);
  glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv) {
  printf("No. of sub-divisions : ");
  scanf("%d", &n);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Some Russian name");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
