/*
Aim: Draw a color cube and allow the user to move the camera suitably to
experiment with perspective viewing.

Compile: gcc prog4.c -lGL -lGLU -lglut
*/
#include <GL/glut.h>
#include <stdio.h>

float v[8][3] = {{1, 1, 1},  {1, -1, 1},  {-1, -1, 1},  {-1, 1, 1},
                 {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}};
float theta[3] = {0, 0, 0};
float viewer[] = {0, 0, 5};
int axis = 1;

void spin() {
  theta[axis] += 1; // speed of spinning

  if (theta[axis] > 360) {
    theta[axis] -= 360;
  }

  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    axis = 0;
  else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    axis = 1;
  else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    axis = 2;
}

void polygon(int a, int b, int c, int d) {
  glBegin(GL_POLYGON);
  glVertex3fv(v[a]);
  glVertex3fv(v[b]);
  glVertex3fv(v[c]);
  glVertex3fv(v[d]);
  glEnd();
}

void cube() {
  glColor3f(1, 0, 0);
  polygon(4, 5, 6, 7);

  glColor3f(0, 0, 1);
  polygon(0, 4, 7, 3);

  glColor3f(0, 1, 1);
  polygon(1, 5, 6, 2);

  glColor3f(1, 1, 0);
  polygon(0, 4, 5, 1);

  glColor3f(1, 0, 1);
  polygon(3, 7, 6, 2);

  glColor3f(0, 1, 0);
  polygon(0, 1, 2, 3);
}

void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
  glRotatef(theta[0], 1, 0, 0);
  glRotatef(theta[1], 0, 1, 0);
  glRotatef(theta[2], 0, 0, 1);
  cube();
  glutSwapBuffers();
  glFlush();
}

void init() {
  glMatrixMode(GL_PROJECTION);
  glFrustum(-2, 2, -2, 2, 2, 10);
  glMatrixMode(GL_MODELVIEW);
}

void keys(unsigned char key, int x, int y) {
  if (key == 'x')
    viewer[0] -= 1;
  else if (key == 'X')
    viewer[0] += 1;
  else if (key == 'y')
    viewer[1] -= 1;
  else if (key == 'Y')
    viewer[1] += 1;
  else if (key == 'z')
    viewer[2] -= 1;
  else if (key == 'Z')
    viewer[2] += 1;
}

void main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Cuboid");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(spin);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keys);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
}
