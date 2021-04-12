/*
This is mini project for Computer Graphics(15CS62) course
        Prajwal Dhatwalia
        1CR15CS111
        6B, CSE
        2017 to 2018
*/
#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h>

#define delay 40000
#define cell 100
#define nucleus 20
#define size_x 4
#define size_y 20

int round(const float a) { return int(a + 0.5); }

void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry) {
  int Rx2 = Rx * Rx;
  int Ry2 = Ry * Ry;
  int twoRx2 = 2 * Rx2;
  int twoRy2 = 2 * Ry2;
  int p;
  int x = 0;
  int y = Ry;
  int px = 0;
  int py = twoRx2 * y;

  glBegin(GL_POLYGON);
  /* Plot the initial point in each quadrant. */
  glVertex2i(xCenter + x, yCenter + y);
  glVertex2i(xCenter - x, yCenter + y);
  glVertex2i(xCenter + x, yCenter - y);
  glVertex2i(xCenter - x, yCenter - y);

  /* Region 1 */
  p = round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
  while (px < py) {
    x++;
    px += twoRy2;
    if (p < 0)
      p += Ry2 + px;
    else {
      y--;
      py -= twoRx2;
      p += Ry2 + px - py;
    }
    glVertex2i(xCenter + x, yCenter + y);
    glVertex2i(xCenter - x, yCenter + y);
    glVertex2i(xCenter + x, yCenter - y);
    glVertex2i(xCenter - x, yCenter - y);
  }

  /* Region 2 */
  p = round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
  while (y > 0) {
    y--;
    py -= twoRx2;
    if (p > 0)
      p += Rx2 - py;
    else {
      x++;
      px += twoRy2;
      p += Rx2 - py + px;
    }
    glVertex2i(xCenter + x, yCenter + y);
    glVertex2i(xCenter - x, yCenter + y);
    glVertex2i(xCenter + x, yCenter - y);
    glVertex2i(xCenter - x, yCenter - y);
  }
  glEnd();
}

void chromosome(int x, int y) {
  glColor3f(0, 0, 0);
  glBegin(GL_POLYGON);
  glVertex2i(x, y);
  glVertex2i(x + size_x, y);
  glVertex2i(x + size_x, y + size_y);
  glVertex2i(x, y + size_y);
  glVertex2i(x, y);
  glEnd();
}

void step1(float r, float g, float b) {
  glColor3f(r, g, b);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  ellipseMidpoint(250, 250, cell, cell);

  glColor3f(r, b, g);
  ellipseMidpoint(250, 250, nucleus, nucleus);

  chromosome(250 - nucleus * 2, 250 - nucleus * 2);
  chromosome(250 - nucleus * 2, 250 + nucleus * 2);
  chromosome(250 + nucleus * 2, 250 - nucleus * 2);
  chromosome(250 + nucleus * 2, 250 + nucleus * 2);

  // Delay
  usleep(delay);
  glFlush();
}

void step2(float r, float g, float b) {
  int i;

  for (i = 0; i < nucleus / 2; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250, 250, cell, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250, 250, nucleus + i, nucleus);

    chromosome(250 - nucleus * 2, 250 - nucleus * 2);
    chromosome(250 - nucleus * 2, 250 + nucleus * 2);
    chromosome(250 + nucleus * 2, 250 - nucleus * 2);
    chromosome(250 + nucleus * 2, 250 + nucleus * 2);

    // Delay
    usleep(delay * 2);

    glFlush();
  }

  for (i = 0; i < nucleus / 2; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250, 250, cell, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250 + i, 250, nucleus + 10 - i, nucleus);
    ellipseMidpoint(250 - i, 250, nucleus + 10 - i, nucleus);

    chromosome(250 - nucleus * 2, 250 - nucleus * 2);
    chromosome(250 - nucleus * 2, 250 + nucleus * 2);
    chromosome(250 + nucleus * 2, 250 - nucleus * 2);
    chromosome(250 + nucleus * 2, 250 + nucleus * 2);

    // Delay
    usleep(delay * 2);

    glFlush();
  }

  for (i = 0; i < nucleus / 2; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250, 250, cell, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250 + nucleus / 2 + 3 * i, 250, nucleus, nucleus);
    ellipseMidpoint(250 - nucleus / 2 - 3 * i, 250, nucleus, nucleus);

    chromosome(250 - nucleus * 2 - 3 * i, 250 - nucleus * 2);
    chromosome(250 - nucleus * 2 - 3 * i, 250 + nucleus * 2);
    chromosome(250 + nucleus * 2 + 3 * i, 250 - nucleus * 2);
    chromosome(250 + nucleus * 2 + 3 * i, 250 + nucleus * 2);

    // Delay
    usleep(delay * 2);

    glFlush();
  }
}

void step3(float r, float g, float b) {
  int i;

  for (i = 0; i < cell / 2; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250, 250, cell + i, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250 + 2 * nucleus, 250, nucleus, nucleus);
    ellipseMidpoint(250 - 2 * nucleus, 250, nucleus, nucleus);

    chromosome(250 - nucleus * 3.5, 250 - nucleus * 2);
    chromosome(250 - nucleus * 3.5, 250 + nucleus * 2);
    chromosome(250 + nucleus * 3.5, 250 - nucleus * 2);
    chromosome(250 + nucleus * 3.5, 250 + nucleus * 2);

    // Delay
    usleep(delay);

    glFlush();
  }

  for (i = 0; i < cell / 2; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250 + i, 250, cell + 50 - i, cell);
    ellipseMidpoint(250 - i, 250, cell + 50 - i, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250 + 2 * nucleus, 250, nucleus, nucleus);
    ellipseMidpoint(250 - 2 * nucleus, 250, nucleus, nucleus);

    chromosome(250 - nucleus * 3.5, 250 - nucleus * 2);
    chromosome(250 - nucleus * 3.5, 250 + nucleus * 2);
    chromosome(250 + nucleus * 3.5, 250 - nucleus * 2);
    chromosome(250 + nucleus * 3.5, 250 + nucleus * 2);

    // Delay
    usleep(delay);

    glFlush();
  }
}

void step4(float r, float g, float b) {
  int i;

  for (i = 0; i < 70; i++) {
    glColor3f(r, g, b);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    ellipseMidpoint(250 + cell / 2 + i, 250, cell, cell);
    ellipseMidpoint(250 - cell / 2 - i, 250, cell, cell);

    glColor3f(r, b, g);
    ellipseMidpoint(250 + 2 * nucleus + i, 250, nucleus, nucleus);
    ellipseMidpoint(250 - 2 * nucleus - i, 250, nucleus, nucleus);

    chromosome(250 - nucleus * 3.5 - i, 250 - nucleus * 2);
    chromosome(250 - nucleus * 3.5 - i, 250 + nucleus * 2);
    chromosome(250 + nucleus * 3.5 + i, 250 - nucleus * 2);
    chromosome(250 + nucleus * 3.5 + i, 250 + nucleus * 2);

    // Delay
    usleep(delay);

    glFlush();
  }
}

void display() {
  // Prophase
  step1(0, 0, 0.5);

  // Metaphase
  step2(0, 0, 0.5);

  // Anaphase
  step3(0, 0, 0.5);

  // Telophase
  step4(0, 0, 0.5);
}

void init() {
  gluOrtho2D(0, 500, 0, 500); // resize diagram
  glColor3f(1, 1, 1);
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void scan_menu(int id) {
  if (id == 1)
    glutDisplayFunc(display);
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
  glutAddMenuEntry("Start", 1);
  glutAddMenuEntry("Quit", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();

  return 0;
}
