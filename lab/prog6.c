/*
Aim: To draw a simple shaded scene consisting of a tea pot on a table. Define
suitably the position and properties of the light source along with the
properties of the surfaces of the solid object used in the scene.

Compile: gcc prog6.c -lGL -lGLU -lglut
*/

#include <GL/glut.h>

void wall(double thickness) {
  glPushMatrix();
  glTranslated(0.5, 0.5 * thickness, 0.5);
  glScaled(1.0, thickness, 1.0);
  glutSolidCube(1.0);
  glPopMatrix();
}
void tableleg(double thick, double len) {
  glPushMatrix();
  glTranslated(0, len / 2, 0);
  glScaled(thick, len, thick);
  glutSolidCube(1.0);
  glPopMatrix();
}
void table(double topwid, double topthick, double legthick, double leglen) {
  glPushMatrix();
  glTranslated(0, leglen, 0);
  glScaled(topwid, topthick, topwid);
  glutSolidCube(1.0);
  glPopMatrix();

  double dist = 0.95 * topwid / 2.0 - legthick / 2.0;

  glPushMatrix();
  glTranslated(dist, 0, dist);
  tableleg(legthick, leglen);

  glTranslated(0, 0, -2 * dist);
  tableleg(legthick, leglen);

  glTranslated(-2 * dist, 0, 2 * dist);
  tableleg(legthick, leglen);

  glTranslated(0, 0, -2 * dist);
  tableleg(legthick, leglen);
  glPopMatrix();
}

void display() {

  GLfloat mat_amb[] = {1.111f, 0.1f, 0.7f, 1.0f};
  GLfloat mat_diff[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat mat_spec[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat mat_shine[] = {50.0f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shine);

  GLfloat lightintensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat lightposition[] = {2.0f, 6.0f, 3.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightintensity);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-64 / 48.0, 64 / 48.0, -1, 1, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(2.3, 1.3, 2.0, 0.0, 0.25, 0.0, 0.0, 1.0, 0.0);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glTranslated(0.4, 0.4, 0.37);
  glutSolidTeapot(0.089);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0.4, 0, 0.4);
  table(0.6, 0.07, 0.06, 0.3);
  glPopMatrix();

  glPushMatrix();
  glRotated(90, 0, 0, 1);
  wall(0.02);
  glPopMatrix();

  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  wall(0.02);
  glPopMatrix();

  glPushMatrix();
  glRotated(0, 0, 1, 0);
  wall(0.02);
  glPopMatrix();

  glFlush();
}

void main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(640, 480);
  glutCreateWindow("Teapot");
  glutDisplayFunc(display);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, 640, 480);
  glutMainLoop();
}
