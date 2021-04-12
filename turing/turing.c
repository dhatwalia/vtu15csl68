#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <unistd.h> // for sleep

#define B '&'

// str stores the original copy of string
char string[100], str[100];
int i = 0, j = 0, k = 0, n = 0, m = 0, l = 0, x = 0, flag = 0;
char var1;

void options();

int stringLength(char *s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

void stringUpper(char *s) {
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] >= 'a' && s[i] <= 'z') {
      s[i] = s[i] - 32;
    }
    ++i;
  }
}

void reshape(int w, int h) {
  GLdouble size;
  GLdouble aspect;

  /* Use the whole window. */
  glViewport(0, 0, w, h);

  /* We are going to do some 2-D orthographic drawing. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  size = (GLdouble)((w >= h) ? w : h) / 2.0;
  if (w <= h) {
    aspect = (GLdouble)h / (GLdouble)w;
    glOrtho(-size, size, -size * aspect, size * aspect, -100000.0, 100000.0);
  } else {
    aspect = (GLdouble)w / (GLdouble)h;
    glOrtho(-size * aspect, size * aspect, -size, size, -100000.0, 100000.0);
  }

  glScaled(aspect, aspect, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void grid() {
  int size = 70;
  int x_pos = -375;
  int y_pos = 135;
  for (int i = 0; i < size * stringLength(string) / 2; i += size) {
    glColor3f(0, 0.3 + 0.5 * (i % 140), 1);
    glBegin(GL_POLYGON);
    glVertex2i(x_pos + i, y_pos);
    glVertex2i(x_pos + size + i, y_pos);
    glVertex2i(x_pos + size + i, y_pos + size);
    glVertex2i(x_pos + i, y_pos + size);
    glEnd();
  }
}

void writer() {
  unsigned int i, j;
  unsigned int count = 0;

  GLfloat x = -350;
  GLfloat y = 155;

  // Draw the strings, according to the current font.
  glColor4f(0, 0, 0, 0);

  // Displaying the message
  glRasterPos2f(x, y);
  for (i = 0; i < stringLength(string) / 2; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    for (j = 0; j < 9; j++)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  }
}

void needle(int position) {
  // Display the pointer needle triangle
  glColor3f(0, 0, 0);
  int size2 = 30;
  int x_pos2 = -350 + position;
  int y_pos2 = 135;
  glBegin(GL_TRIANGLES);
  glVertex2f(x_pos2 + size2 / 2, y_pos2);
  glVertex2f(x_pos2, y_pos2 - size2);
  glVertex2f(x_pos2 + size2, y_pos2 - size2);
  glEnd();

  // Displaying the pointer needle rectangle
  glColor3f(0, 0, 0);
  int size3 = 15;
  int x_pos3 = -350 + size2 / 4 + position;
  int y_pos3 = 135 - size2;
  glBegin(GL_QUADS);
  glVertex2f(x_pos3, y_pos3);
  glVertex2f(x_pos3 + size3, y_pos3);
  glVertex2f(x_pos3 + size3, y_pos3 - size3 * 3);
  glVertex2f(x_pos3, y_pos3 - size3 * 3);
  glEnd();
}

void showTape(int arrow) {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Displaying the grid
  grid();

  // Displaying the content of grid
  writer();

  // Display the pointer needle
  needle(arrow * 70);

  glutSwapBuffers();

  // Delay
  sleep(1);
}

void accept() {
  char text[7] = "ACCEPT";
  glClearColor(1, 1, 1, 1);
  GLfloat x = -350;
  GLfloat y = 0;
  glRasterPos2f(x, y);
  for (int i = 0; i < 6; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  options();
  glutSwapBuffers();
}

void reject() {
  char text[7] = "REJECT";
  glClearColor(1, 1, 1, 1);
  GLfloat x = -350;
  GLfloat y = 0;
  glRasterPos2f(x, y);
  for (int i = 0; i < 6; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  options();
  glutSwapBuffers();
}

int forward(int m) {
  for (k = m; k < n * 2;)
    if (string[k] == B)
      return k;
    else
      k++;
}

int backward(int l) {
  for (k = l; k >= 0;)
    if (string[k] == B)
      return k;
    else
      k--;
}

void checkpal(int i) {
  j = i;
  var1 = string[i];
  i = forward(i);
  i--;
  if (var1 == string[i]) {
    string[i] = B;
    showTape(i);
    string[j] = B;
    showTape(j);

    i--;
    i = backward(i);
    i++;
    for (x = 0; x < n * 2; x++) {
      if (string[x] == B) {
        flag++;
      }
    }
    if (i == (n / 2)) {
      accept();
    } else {
      checkpal(i);
    }
  } else {
    reject();
  }
}

void *currentfont;
// FUNCTION TO SELECT BITMAP FONT
void setFont(void *font) { currentfont = font; }
// FUNCTION TO DRAW BITMAP string at (x,y)
void drawstring(GLfloat x, GLfloat y, char *string) {
  char *c;
  glRasterPos2f(x, y);

  for (c = string; *c != '\0'; *c++) {
    glutBitmapCharacter(currentfont, *c);
  }
}

void title() {
  glLineWidth(3.0);
  glColor3f(0, 0, 0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(-475, -225);
  glVertex2f(-475, 225);
  glVertex2f(475, 225);
  glVertex2f(475, -225);
  glEnd();

  setFont(GLUT_BITMAP_HELVETICA_18);
  glColor3f(0, 0, 1);
  drawstring(-350, 150, "Computer Graphics Laboratory Mini Project");
  glColor3f(0, 0, 1);
  drawstring(-350, 130, "Topic : Turing Machine");

  glColor3f(0, 0, 0);
  drawstring(-350, 50, "Submitted by:");
  drawstring(-350, 30, "1CR15CS047 : Daga Tarun Pavan");
  drawstring(-350, 10, "1CR15CS111 : Prajwal Dhatwalia");

  glColor3f(1, 0, 0);
  drawstring(-350, -70, "Guided by:");
  glColor3f(1, 0, 0);
  drawstring(-350, -90, "Assistant Prof. Kartheek GCR, Dept. of CSE");

  glFlush();
}

void options() {
  glColor3f(0, 0, 0);
  drawstring(-350, -150, "Press <1> : Cover page");
  drawstring(-350, -170, "Press <2> : Run the Turing Machine");
  drawstring(-350, -190, "Press <3> : Exit Progam");
  glFlush();
}

void keys(GLubyte key, GLint x, GLint y) {
  switch (key) {
  case '1':
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    title();
    options();
    glutSwapBuffers();
    glFlush();
    break;

  case '2':
    // Copy oringial string 'str' to 'string'
    for (i = 0; i < n * 2; i++)
      string[i] = str[i];
    i = 0;
    showTape(i);
    checkpal(i);
    break;

  case '3':
    printf("Done\n");
    exit(0);
    break;

  default:
    break;
  }
}

void display() {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  title();
  options();
  glutSwapBuffers();
  glFlush();
}

void main(int argc, char **argv) {
  printf("Enter a word : ");
  scanf("%s", str);
  n = stringLength(str);
  for (i = n; i < n * 2; i++)
    str[i] = B; //$

  stringUpper(str);
  str[n] = B;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1000, 500);
  glutCreateWindow("Turing Machine");
  glutDisplayFunc(display);
  glutKeyboardFunc(keys);
  glutReshapeFunc(reshape);
  glutMainLoop();
}