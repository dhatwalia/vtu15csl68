/*
Aim: Develop a menu driven program to fill the polygon using scan line algorithm

Compile: gcc prog9.c -lGL -lGLU -lglut
*/
#include <GL/glut.h>
#include <stdio.h>

float slope;

void draw_pixel(int x, int y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void edge_detect(float x1, float y1, float x2, float y2, int le[], int re[]) {
  float temp;
  int x, y, i;
  if (y2 < y1) {
    // swap y1 and y2
    temp = y2;
    y2 = y1;
    y1 = temp;
    // swap x1 and x2
    temp = x2;
    x2 = x1;
    x1 = temp;
  }

  if (y2 != y1)
    slope = (x2 - x1) / (y2 - y1);
  else
    slope = x2 - x1;
  x = x1;

  for (i = y1; i < y2; i++) {
    if (x < (float)le[i])
      le[i] = (int)x;

    if (x > (float)re[i]) {
      re[i] = (int)x;
      x += slope;
    }
  }

  for (y = 0; y < 500; y++) {
    if (le[y] <= re[y])
      for (i = (int)le[y]; i < (int)re[y]; i++) {
        draw_pixel(i, y);
      }
  }
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3,
              float x4, float y4) {
  int le[500], re[500], i;
  for (i = 0; i < 500; i++) {
    le[i] = 500;
    re[i] = 0;
  }
  edge_detect(x1, y1, x2, y2, le, re);
  edge_detect(x2, y2, x3, y3, le, re);
  edge_detect(x3, y3, x4, y4, le, re);
  edge_detect(x4, y4, x1, y1, le, re);
}

void display() {
  float x1 = 200, y1 = 200, x2 = 100, y2 = 300, x3 = 200, y3 = 400, x4 = 300,
        y4 = 300;

  glColor3f(1, 0, 0);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
  glFlush();
}

void init() {
  gluOrtho2D(0, 500, 0, 500); // resize diagram
}

void create_polygon() {
  glColor3f(1, 0, 0);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_LOOP);
  glVertex2f(200, 200);
  glVertex2f(100, 300);
  glVertex2f(200, 400);
  glVertex2f(300, 300);
  glEnd();
  glFlush();
}

void scan_menu(int id) {
  if (id == 1)
    glutDisplayFunc(display);
  else if (id == 2)
    glutDisplayFunc(create_polygon);
  else
    exit(0);
  glutPostRedisplay();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Line");
  init();

  glutCreateMenu(scan_menu);
  glutAddMenuEntry("Fill Colour", 1);
  glutAddMenuEntry("No Color", 2);
  glutAddMenuEntry("Quit", 3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();

  return 0;
}
