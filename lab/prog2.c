/*
Aim: Create and rotate a triangle about the origin and a fixed point.

Compile: gcc prog2.c -lGL -lGLU -lglut -lm
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define pi 3.142857143

float m = 0, n = 0;
float h, k;
float angle;

void draw_triangle(float a[3][3]) {
  glBegin(GL_LINE_LOOP);
  glVertex2i(a[0][0], a[1][0]); // x1 y1
  glVertex2i(a[0][1], a[1][1]); // x2 y2
  glVertex2i(a[0][2], a[1][2]); // x3 y3
  glEnd();
}

void multiply(float a[3][3], float b[3][3], float c[3][3]) {
  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 3; j++) {
      c[i][j] = 0;
      for (int k = 0; k < 3; k++) {
        c[i][j] += b[i][k] * a[k][j];
      }
    }
  }
}

void display() {
  glColor3f(0, 0, 0);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Triangle at initial position
  float t[3][3] = {{150, 250, 350}, {200, 400, 200}, {1, 1, 1}};
  draw_triangle(t);

  // Triangle after rotation about origin
  m = 0;
  n = 0;
  float r[3][3] = {
      {cos(angle), -sin(angle), m}, {sin(angle), cos(angle), n}, {0, 0, 1}};
  float f[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  multiply(t, r, f);
  glColor3f(1, 0, 1);
  draw_triangle(f);

  // Triangle rotated about fixed position
  m = -h * (cos(angle) - 1) + k * (sin(angle));
  n = -k * (cos(angle) - 1) - h * (sin(angle));
  r[0][2] = m;
  r[1][2] = n;
  multiply(t, r, f);
  glColor3f(1, 0, 0);
  draw_triangle(f);

  glFlush();
}

void init() {
  gluOrtho2D(-500, 1000, -500, 1000); // resize diagram
}

void main(int argc, char **argv) {
  printf("Enter the angle of rotation (degrees) : ");
  scanf("%f", &angle);
  angle = angle * pi / 180;

  printf("Enter h : ");
  scanf("%f", &h);

  printf("Enter k : ");
  scanf("%f", &k);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Line");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
