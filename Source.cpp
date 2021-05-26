#include <stdlib.h>
#include <GL/glut.h>

#include <math.h>


#define PI 3.14
static int body, lshoulder, lelbow, head, rshoulder, lfrontshoulder, rfrontshoulder, relbow, lfemur, lfrontfemur, rfrontfemur, ltibia, rfemur, rtibia = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

// Rotation about vertical direction
void lookRight()
{
    rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
    rotatePoint(up, -PI / 8, eye);
}

// Rotation about horizontal direction

void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 8, eye);
    rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 8, eye);
    rotatePoint(horizontal, -PI / 8, up);
}

// Forward and Backward
void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;
}
void init_projection(void)
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0,
        1.0,
        1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void reset()
{
    double e[] = { 0.0, 0.0, 5.0 };
    double c[] = { 0.0, 0.0, 0.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
}
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'f':
        moveForward();
        break;
    case 'b':
        moveBackword();
        break;
    case 'r':
        reset();
        break;
    case 's':
        lshoulder = (lshoulder + 5) % 180;
        rshoulder = (rshoulder - 5) % 180;
        glutPostRedisplay();
        break;
    case 'S':
        if (lshoulder > 0 & rshoulder < 0)
        {
            lshoulder = (lshoulder + 5) % 180;
            rshoulder = (rshoulder - 5) % 180;
        }
        glutPostRedisplay();
        break;
    case 'd':
        lfrontshoulder = (lfrontshoulder + 15) % 180;
        rfrontshoulder = (rfrontshoulder - 15) % 180;

        glutPostRedisplay();
        break;


    case 'e':
        lfemur = (lfemur + 5) % 90;
        glutPostRedisplay();
        break;
    case 'E':
        //lfemur = (lfemur - 5) % 10;
        if (lfemur > 0)
        {
            lfemur = (lfemur - 5) % 90;
        }
        else
        {
            lfemur = (lfemur - 5) % 10;
        }

        glutPostRedisplay();
        break;
    case 't':
        rfemur = (rfemur - 5) % 90;

        glutPostRedisplay();
        break;
    case 'T':
        if (rfemur < 0)
        {
            rfemur = (rfemur + 5) % 90;
        }

        else
        {
            rfemur = (rfemur + 5) % 10;
        }
        glutPostRedisplay();
        break;
    case 'q':
        lfrontfemur = (lfrontfemur - 5) % 90;

        glutPostRedisplay();
        break;
    case 'Q':
        lfrontfemur = (lfrontfemur + 5) % 80;
        glutPostRedisplay();
        break;
    case 'w':
        rfrontfemur = (rfrontfemur - 5) % 90;
        glutPostRedisplay();
        break;
    case 'W':
        rfrontfemur = (rfrontfemur + 5) % 80;
        glutPostRedisplay();
        break;
    case 'y':
        rtibia = (rtibia + 5) % 90;
        glutPostRedisplay();
        break;
    case 'Y':
        if (rtibia > 0)
            rtibia = (rtibia - 5) % 90;
        glutPostRedisplay();
        break;
    case 'u':
        ltibia = (ltibia + 5) % 90;
        glutPostRedisplay();
        break;
    case 'U':
        if (ltibia > 0)
            ltibia = (ltibia - 5) % 90;
        glutPostRedisplay();
        break;



    case 'h':
        if (rshoulder != 0 & lshoulder != 0)
        {
            relbow = (relbow + 5) % 120;
            lelbow = (lelbow - 5) % 120;
        }
        //rfrontshoulder = (rfrontshoulder - 5) % 180;
        glutPostRedisplay();
        break;
    case 'H':
        if (relbow > 0 & lelbow < 0)
        {
            relbow = (relbow - 5) % 120;
            lelbow = (lelbow + 5) % 120;
        }
        //rfrontshoulder = (rfrontshoulder - 5) % 180;
        glutPostRedisplay();
        break;


        //case 'k':
        //if(lfrontshoulder >0)
        //lelbow = (lelbow - 5) % 120;
        //rfrontshoulder = (rfrontshoulder - 5) % 180;
        //glutPostRedisplay();
        //break;
    }


    glutPostRedisplay();
}

void init_shape(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //body start
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef((GLfloat)body, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 2.0, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    //head
    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glPushMatrix();
    glutWireSphere(0.3, 10.0, 10.0);
    glPopMatrix();
    glPopMatrix();
    //left arm start
    glPushMatrix();
    glTranslatef(0.65, 1.0, 0.0);
    glRotatef((GLfloat)lshoulder, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)lfrontshoulder, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
    // left elbow start
    glTranslatef(0.0, -0.4, 0.0);
    glRotatef((GLfloat)lelbow, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
    //left fingers
      //thumb
    glPushMatrix();
    glTranslatef(0.0, -0.45, 0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f1
    glPushMatrix();
    glTranslatef(0.0, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f2
    glPushMatrix();
    glTranslatef(-0.08, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f3
    glPushMatrix();
    glTranslatef(0.08, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //left arm end
    glPopMatrix();
    //right arm start
    glPushMatrix();
    glTranslatef(-0.65, 1.0, 0.0);
    glRotatef((GLfloat)rshoulder, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rfrontshoulder, 0.0, 1.0, 0.0);

    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
    //right elbow start
    glTranslatef(0.0, -0.4, 0.0);
    glRotatef((GLfloat)relbow, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.8, 0.3);
    glutWireCube(1.0);
    glPopMatrix();
    //right fingers
    //thumb
    glPushMatrix();
    glTranslatef(0.0, -0.45, 0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f1
    glPushMatrix();
    glTranslatef(0.0, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f2
    glPushMatrix();
    glTranslatef(-0.08, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //f3
    glPushMatrix();
    glTranslatef(0.08, -0.45, -0.125);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.04, 0.1, 0.05);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //right arm end
    glPopMatrix();
    //left leg start
    glPushMatrix();
    glTranslatef(0.35, -1.0, 0.0);
    glRotatef((GLfloat)lfemur, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)lfrontfemur, 1.0, 0.0, 0.0);

    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.5, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    //left tibia start
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef((GLfloat)ltibia, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.6, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.2, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    //left feet start
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.3, 0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    //left leg end
    glPopMatrix();
    //right leg start
    glPushMatrix();
    glTranslatef(-0.35, -1.0, 0.0);
    glRotatef((GLfloat)rfemur, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rfrontfemur, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.5, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    //right tibia start
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef((GLfloat)rtibia, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.6, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.2, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    //right feet start
    glTranslatef(0.0, -0.75, 0.0);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(0.3, 0.3, 0.9);
    glutSolidCube(1.0);
    glPopMatrix();
    //right leg end
    glPopMatrix();
    //body end
    glPopMatrix();
    glutSwapBuffers();
}
static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}
static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init_shape();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyBoard);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init_projection();
    glutMainLoop();
    return 0;

}