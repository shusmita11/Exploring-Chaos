#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <mmsystem.h>
using namespace std;


//************************************** Variables *********************************
const GLint HEIGHT = 780, WIDTH = 1540;

// Bouali
static GLdouble B_new_x = 0.0, B_new_y = 0.0, B_new_z = 0.0;
static GLdouble B_dt = 0.020, B_dx = 0.0, B_dy = 0.0, B_dz = 0.0;
static GLdouble B_a = 0.3, B_s = 1.0;
static GLint B_cnt = 0, B_stop = 0;
GLdouble Blines[1000][3] = { {-0.5, 1.0, -0.9} };

//Halvorsen
static GLdouble H_new_x = 0.0, H_new_y = 0.0, H_new_z = 0.0;
static GLdouble hal_a = 1.89;
static GLdouble H_dt = 0.01, H_dx = 0.0, H_dy = 0.0, H_dz = 0.0;
GLdouble Hlines[1000][3] = { {-1.48, -1.51, 2.04} };
static GLint H_cnt = 0, H_stop = 0;

// Chenlee
static GLdouble CL_dt = 0.01, CL_dx = 0.0, CL_dy = 0.0, CL_dz = 0.0;
static GLdouble CL_new_x = 0.0, CL_new_y = 0.0, CL_new_z = 0.0;
static GLdouble CL_a = 0.2, CL_b = -0.4, CL_c = -0.38;
static GLint CL_cnt = 0, CL_stop = 0;
GLdouble CL_lines[1000][3] = { {-0.2, 0.1, 0.2} };

//lorenz
static GLdouble L_dx = 0.0, L_dy = 0.0, L_dz = 0.0;
static GLdouble L_new_x = 0.0, L_new_y = 0.0, L_new_z = 0.0;
static GLdouble L_a = 10.0, L_b = 8.0 / 3.0, L_p = 28.0;
static GLint L_cnt = 0, L_stop = 0;
GLdouble Llines[1000][3] = { {0.0, 0.1, 0.0} };
GLfloat rotation_angle = 0.0;
GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };
GLfloat light_diffuse[] = { 1.0, 0.0, 1.0, 1.0 };

static char currentAttractor = 'c';

//***********************************************************************

//************************* Functions ***********************************
void CL_display();
void Text(const char* text, int length, float x, float y, float scale);
void B_display();
void H_display();
void L_display();
void Display();
void CL_display();
void Reshape(int w, int h);
void Timer(int);
void Keyboard(unsigned char key, int x, int y);
void B_Init();
void H_Init();
void CL_Init();
void L_Init();
void Init();

//***********************************************************************



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Exploring Chaos");
    glutDisplayFunc(Display);

    glutReshapeFunc(Reshape);
    glutTimerFunc(0, Timer, 0);
    Init();
    glutKeyboardFunc(Keyboard);
    sndPlaySound(TEXT("s2.wav"), SND_ASYNC);
    glutMainLoop();
    return 0;
}

void Text(const char* text, int length, float x, float y, float scale)
{
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scale, scale, scale);
    glRasterPos3i(0, 0, 0);
    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
}

void B_display()
{
    for (int i = 0; i < 1000; i++)
    {
        B_cnt++;
        glLoadIdentity();

        B_dx = (Blines[i][0] * (4 - Blines[i][1]) + B_a * Blines[i][2]) * B_dt;
        B_dy = (-Blines[i][1] * (1 - (Blines[i][0] * Blines[i][0]))) * B_dt;
        B_dz = (-Blines[i][0] * (1.5 - B_s * Blines[i][2]) - 0.05 * Blines[i][2]) * B_dt;

        glLineWidth(1.5);
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 0.4);

        B_new_x = Blines[i][0] + B_dx;
        B_new_y = Blines[i][1] + B_dy;
        B_new_z = Blines[i][2] + B_dz;

        glVertex2d(Blines[i][0], Blines[i][1]);
        glVertex2d(B_new_x, B_new_y);

        Blines[i][0] = B_new_x;
        Blines[i][1] = B_new_y;
        Blines[i][2] = B_new_z;

        glEnd();
    }
}

void H_display()
{
    for (int i = 0; i < 1000; i++)
    {
        H_cnt++;
        if (H_cnt == 100000)
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        //cnt++;
        glLoadIdentity();

        H_dx = (-hal_a * Hlines[i][0] - 4 * Hlines[i][1] - 4 * Hlines[i][2] - Hlines[i][1] * Hlines[i][1]) * H_dt;
        H_dy = (-hal_a * Hlines[i][1] - 4 * Hlines[i][2] - 4 * Hlines[i][0] - Hlines[i][2] * Hlines[i][2]) * H_dt;
        H_dz = (-hal_a * Hlines[i][2] - 4 * Hlines[i][0] - 4 * Hlines[i][1] - Hlines[i][0] * Hlines[i][0]) * H_dt;
        glLineWidth(1.5);
        glBegin(GL_POINTS);
        glColor3f(0.5, 1.0, 1.0);

        H_new_x = Hlines[i][0] + H_dx;
        H_new_y = Hlines[i][1] + H_dy;
        H_new_z = Hlines[i][2] + H_dz;

        glVertex2d(Hlines[i][0], Hlines[i][1]);
        glVertex2d(H_new_x, H_new_y);

        Hlines[i][0] = H_new_x;
        Hlines[i][1] = H_new_y;
        Hlines[i][2] = H_new_z;

        glEnd();

    }
}

void L_display()
{
    glLoadIdentity();

    //gluLookAt(0.0, 0.0, 125.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotation_angle, 0.0, 0.0, 1.0);

    for (int i = 0; i < 1000; i++)
    {
        if (L_cnt == 20000)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            L_cnt = 0;
        }
        L_cnt++;
        GLdouble dt = 0.007;
        L_dx = (L_a * (Llines[i][1] - Llines[i][0])) * dt;
        L_dy = ((Llines[i][0] * (L_p - Llines[i][2])) - Llines[i][1]) * dt;
        L_dz = ((Llines[i][0] * Llines[i][1]) - (L_b * Llines[i][2])) * dt;

        L_new_x = Llines[i][0] + L_dx;
        L_new_y = Llines[i][1] + L_dy;
        L_new_z = Llines[i][2] + L_dz;

        glBegin(GL_POINTS);
        glLineWidth(10);
        glColor3d(0.6, 0.2, 0.6);
        glVertex2d(Llines[i][0], Llines[i][1]);
        glVertex2d(L_new_x, L_new_y);

        glEnd();

        Llines[i][0] = L_new_x;
        Llines[i][1] = L_new_y;
        Llines[i][2] = L_new_z;
    }

    glutSwapBuffers();
    rotation_angle += 0.08;
}


void Display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (currentAttractor == 'b')
        gluOrtho2D(-15.0, 15.0, -10.0, 20.0);

    else if (currentAttractor == 'h')
        gluOrtho2D(-25.0, 25.0, -25.0, 25.0);

    else if (currentAttractor == 'c')
        gluOrtho2D(-15.0, 15.0, -10.0, 20.0);

    else if (currentAttractor == 'l')
    {
        gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (currentAttractor == 'b')
    {
        glPushMatrix();

        string text = "B O U A L I  A T T R A C T O R";
        Text(text.data(), text.size(), -14.3, 18.2, 0.0);
        glPopMatrix();

        B_display();
    }

    else if (currentAttractor == 'h')
    {
        glPushMatrix();
        string text = "H A L V O R S E N  A T T R A C T O R";
        Text(text.data(), text.size(), -23.8, 22.2, 0.0);
        glPopMatrix();

        H_display();
    }

    else if (currentAttractor == 'c')
    {
        glPushMatrix();
        string text = "C H E N - L E E  A T T R A C T O R";
        Text(text.data(), text.size(), -3.0, -9.0, 0.0);
        glPopMatrix();

        CL_display();
    }

    else if (currentAttractor == 'l')
    {
        glPushMatrix();
        string text = "L O R E N Z  A T T R A C T O R";
        Text(text.data(), text.size(), -47.2, 44.2, 0.0);
        glPopMatrix();
        glScalef(0.5f, 0.5f, 1.0);
        glLoadIdentity();

        L_display();
    }
    glutSwapBuffers();
}


void CL_display()
{
    for (int i = 0; i < 1000; i++)
    {
        CL_cnt++;
        glLoadIdentity();

        CL_dx = (CL_a * CL_lines[i][0] - CL_lines[i][1] * CL_lines[i][2]) * CL_dt;
        CL_dy = (CL_b * CL_lines[i][1] - CL_lines[i][0] * CL_lines[i][2]) * CL_dt;
        CL_dz = (CL_c * CL_lines[i][2] + CL_lines[i][0] * (CL_lines[i][1] / 3.0)) * CL_dt;

        glLineWidth(1.5);
        glBegin(GL_POINTS);

        glColor3f(0.7, 1.0, 0.7);

        CL_new_x = CL_lines[i][0] + CL_dx;
        CL_new_y = CL_lines[i][1] + CL_dy;
        CL_new_z = CL_lines[i][2] + CL_dz;

        glVertex2d(CL_lines[i][0], CL_lines[i][1]);
        glVertex2d(CL_new_x, CL_new_y);

        CL_lines[i][0] = CL_new_x;
        CL_lines[i][1] = CL_new_y;
        CL_lines[i][2] = CL_new_z;

    }
    glEnd();
    glFlush();
}
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Timer(int)
{
    if (currentAttractor == 'b')
        B_stop += 1;
    else if (currentAttractor == 'h')
        H_stop += 1;

    else if (currentAttractor == 'c')
        CL_stop += 1;

    else if (currentAttractor == 'l')
        L_stop += 1;

    if (B_stop == 1000000 || CL_stop == 1000000 || H_stop == 1000000 || L_stop == 1000000)
        return;

    glutPostRedisplay();
    glutTimerFunc(10, Timer, B_stop);
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'B':
    case 'b':
        if (currentAttractor != 'b')
        {
            currentAttractor = 'b';
            B_Init();
            B_cnt = 0;
            B_stop = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
        break;
    case 'H':
    case 'h':
        if (currentAttractor != 'h')
        {
            currentAttractor = 'h';
            H_Init();
            H_cnt = 0;
            H_stop = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
        break;

    case 'C':
    case 'c':
        if (currentAttractor != 'c')
        {
            currentAttractor = 'c';
            CL_Init();
            CL_cnt = 0;
            CL_stop = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
        break;

    case 'L':
    case 'l':
        if (currentAttractor != 'l')
        {
            currentAttractor = 'l';
            L_Init();
            L_cnt = 0;
            L_stop = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glutPostRedisplay();
        }
        break;
    }
}

void B_Init()
{
    Blines[0][0] = -0.5;
    Blines[0][1] = 1.0;
    Blines[0][2] = -0.9;

    B_new_x = 0.0, B_new_y = 0.0, B_new_z = 0.0;

    for (int i = 1; i < 1000; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            Blines[i][0] = Blines[i - 1][0];
            Blines[i][1] = Blines[i - 1][1];
            Blines[i][2] = Blines[i - 1][2];
        }
    }
}

void H_Init()
{
    Hlines[0][0] = -1.48;
    Hlines[0][1] = -1.51;
    Hlines[0][2] = 2.04;
    H_new_x = 0.0, H_new_y = 0.0, H_new_z = 0.0;

    for (int i = 1; i < 1000; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            Hlines[i][0] = Hlines[i - 1][0] + 0.1;
            Hlines[i][1] = Hlines[i - 1][1];
            Hlines[i][2] = Hlines[i - 1][2];
        }
    }
}

void CL_Init()
{
    CL_lines[0][0] = -1.48;
    CL_lines[0][0] = -1.51;
    CL_lines[0][0] = 2.04;
    for (int i = 1; i < 1000; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            CL_lines[i][0] = CL_lines[i - 1][0] - 0.1;
            CL_lines[i][1] = CL_lines[i - 1][1] + 0.2;
            CL_lines[i][2] = CL_lines[i - 1][2];
        }
    }
}

void L_Init()
{
    Llines[0][0] = 0.0;
    Llines[0][1] = 0.1;
    Llines[0][2] = 0.0;

    for (int i = 1; i < 1000; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            Llines[i][0] = Llines[i - 1][0];
            Llines[i][1] = Llines[i - 1][1];
            Llines[i][2] = Llines[i - 1][2] + 0.2;
        }
    }

}

void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    B_Init();
    H_Init();
    L_Init();
    CL_Init();
}




