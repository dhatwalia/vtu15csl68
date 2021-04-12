/*
Aim: Clip a lines using Cohen-Sutherland algorithm

Compile: gcc prog5.c -lGL -lGLU -lglut
*/

#include <GL/glut.h>
#include <stdio.h>

#define true 1
#define false 0

float xmin = 50, ymin = 50, xmax = 100, ymax = 100;
int left = 2, bottom = 1, right = 8, top = 4;
float x_0, y_0, x_1, y_1;

int compute(float x, float y) {
  int code = 0;
  if (x < xmin)
    code |= left;
  else if (x > xmax)
    code |= right;

  if (y < ymin)
    code |= bottom;
  else if (y > ymax)
    code |= top;

  return code;
}

void line_clip() {
  int code0 = compute(x_0, y_0);
  int code1 = compute(x_1, y_1);
  int codeout;
  float m = (y_1 - y_0) / (x_1 - x_0);
  float x, y;
  int done = false, accept = false;
  do {
    m = (y_1 - y_0) / (x_1 - x_0);
    if (!(code0 | code1)) {
      done = true;
      accept = true;
    } else if (code0 & code1) {
      done = true;
    }

    else {
      if (code0)
        codeout = code0;
      else
        codeout = code1;

      if (codeout & top) {
        y = ymax;
        x = x_0 + (ymax - y_0) / m;
      } else if (codeout & bottom) {
        y = ymin;
        x = x_0 + (ymin - y_0) / m;
      } else if (codeout & right) {
        x = xmax;
        y = y_0 + (xmax - x_0) * m;
      } else // left
      {
        x = xmin;
        y = y_0 + (xmin - x_0) * m;
      }

      if (codeout == code0) {
        x_0 = x;
        y_0 = y;
        code0 = compute(x_0, y_0);
      } else {
        x_1 = x;
        y_1 = y;
        code1 = compute(x_1, y_1);
      }
    }
  } while (!done);

  if (accept) {

    glTranslatef(100, 0, 0);

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x_0, y_0);
    glVertex2f(x_1, y_1);
    glEnd();
  }
}

void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // drawing the view volume
  glColor3f(0, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(xmin, ymin);
  glVertex2f(xmax, ymin);
  glVertex2f(xmax, ymax);
  glVertex2f(xmin, ymax);
  glEnd();

  glColor3f(1, 0, 0);
  glBegin(GL_LINES);
  glVertex2f(x_0, y_0);
  glVertex2f(x_1, y_1);
  glEnd();

  line_clip();

  glFlush();
}

void init() {
  gluOrtho2D(0, 400, 0, 400); // resize diagram
}

void main(int argc, char **argv) {
  printf("Initial Coordinate\n");
  printf("x = ");
  scanf("%f", &x_0);
  printf("y = ");
  scanf("%f", &y_0);

  printf("Final Coordinate\n");
  printf("x = ");
  scanf("%f", &x_1);
  printf("y = ");
  scanf("%f", &y_1);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Cohen Sutherland");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
