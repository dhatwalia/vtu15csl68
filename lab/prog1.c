/*
Aim: Implement Brenham’s line drawing algorithm for all types of slope.

Compile: gcc prog1.c -lGL -lGLU -lglut
*/

#include <GL/glut.h>
#include <stdio.h>

int x1, x2, y11, y2;

void draw_pixel(int x, int y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
  int dx, dy, i, e; // e is  decision parameter
  int incx, incy, inc1, inc2, x, y;
  dx = x2 - x1;
  dy = y2 - y1;
  if (dx < 0)
    dx = -1 * dx;
  if (dy < 0)
    dy = -1 * dy;
  incx = 1;
  if (x2 < x1)
    incx = -1;
  incy = 1;
  if (y2 - y1)
    incy = -1;
  x = x1;
  y = y1;
  if (dx > dy) {
    draw_pixel(x, y);
    e = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;
    for (i = 0; i < dx; i++) {
      if (e >= 0) {
        y += incy;
        e += inc1;
      } else
        e += inc2;
      x += incx;
      draw_pixel(x, y);
    }
  } else // when dx > dy is false
  {
    draw_pixel(x, y);
    e = 2 * dx - dy;
    inc1 = 2 * (dx - dy);
    inc2 = 2 * dx;
    for (i = 0; i < dy; i++) {
      if (e >= 0) {
        x += incx;
        e += inc1;
      } else
        e += inc2;
      y += incy;
      draw_pixel(x, y);
    }
  }
}

void display() {
  glColor3f(1, 0, 0);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  draw_line(x1, x2, y11, y2);
  glFlush();
}

void init() {
  gluOrtho2D(0, 500, 0, 500); // resize diagram
}

void main(int argc, char **argv) {
  printf("Initial coordinate\n");
  printf("x : ");
  scanf("%d", &x1);
  printf("y : ");
  scanf("%d", &y11);

  printf("Final coordinate\n");
  printf("x : ");
  scanf("%d", &x2);
  printf("y : ");
  scanf("%d", &y2);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Line");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
