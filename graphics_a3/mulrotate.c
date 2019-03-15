#define PROGRAM_TITLE "Assignment 2 Gideon Richter Graphics 3710"
#define DISPLAY_INFO "Assignment 2 Gideon Richter Graphics 3710"

#include <stdlib.h> // Useful for the following includes.
#include <stdio.h>
#include <string.h> // For spring operations.
#include <unistd.h> // sleep

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

int WINDOW_ID;
int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 400;

// Increasing by 15deg each display
float rotation_degrees = 0.0;

// Camera eye coordinates
float eye_x = 0.0;
float eye_y = 0.0;
float eye_z = 5.0;

// Current cube z location
float cube_z = 0.0;

// Push amount on z keypress
float cube_z_push_amount = 2.0;

// How far back we are from the cube
float cube_cam_offset = 5.0;

int sphere_rotation = 0;
int cube_rotation = 0;
int pyramid_rotation = 0;

int rotate_sphere = 1;
int rotate_cube = 1;
int rotate_pyramid = 1;

void draw_triangle()
{
    /* 
    Draw a triangle at the origin
    */
    glBegin(GL_TRIANGLES);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}

void draw_cube(int size)
{
    glutSolidCube(size);
}

void cb_render_scene(void)
{
    usleep(40000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        eye_x, eye_y, eye_z,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 3.0);
    if (rotate_cube)
    {
        cube_rotation += 15;
    }
    glRotated(cube_rotation, 0.0, 1.0, 0.0);
    draw_cube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -3);
    if (rotate_pyramid)
    {
        pyramid_rotation += 15;
    }
    glRotated(pyramid_rotation, 0.0, 1.0, 0.0);
    draw_triangle();
    glPopMatrix();

    glPushMatrix();
    if (rotate_sphere)
    {
        sphere_rotation += 15;
    }
    glRotatef(sphere_rotation, 0.0, 0.0, 1.0);
    glTranslatef(2.0, 0.0, 0.0);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
    draw_axis();
    glColor3f(0.0, 1.0, 0.0);

    glutSwapBuffers();
}

void draw_axis()
{
    glBegin(GL_LINES);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
}

void cb_resize_screen(int Width, int Height)
{
    // Let's not core dump, no matter what.
    if (Height == 0)
        Height = 1;

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    WINDOW_WIDTH = Width;
    WINDOW_HEIGHT = Height;
}

void MyInit(int Width, int Height)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    cb_resize_screen(Width, Height);
}

void key_function(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 113: // q
        rotate_cube = 0;
        rotate_sphere = 0;
        rotate_pyramid = 0;
        break;
    case 32: // space
        rotate_cube = 1;
        rotate_sphere = 1;
        rotate_pyramid = 1;
        break;
    case 122: // z
        rotate_cube = 1;
        rotate_sphere = 1;
        rotate_pyramid = 0;
        break;
    case 97: // a
        rotate_cube = 0;
        rotate_sphere = 1;
        rotate_pyramid = 1;
        break;
    default:
        break;
    }
    printf("Pressing key: %d.\n", key);
}

void mouse_function(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            // If you press the right mouse button
            // the eye changes to (5, 5, 5)
            eye_x = 5.0;
            eye_y = 5.0;
            eye_z = 5.0;
        }
        if (state == GLUT_UP)
        {
            // If you release the button
            // your lookat returns to its
            // default setting.
            eye_x = 0.0;
            eye_y = 0.0;
            eye_z = 5.0;
        }
        break;
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            // If you press the left mouse button
            // the eye changes to (-5, 5, 5)
            eye_x = -5.0;
            eye_y = 5.0;
            eye_z = 5.0;
        }
        if (state == GLUT_UP)
        {
            // If you release the button
            // your lookat returns to its
            // default setting.
            eye_x = 0.0;
            eye_y = 0.0;
            eye_z = 5.0;
        }
    default:
        printf("No action for other mouse functions.\n");
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    WINDOW_ID = glutCreateWindow(PROGRAM_TITLE);

    // Register callback functions
    glutDisplayFunc(&cb_render_scene);
    glutIdleFunc(&cb_render_scene);
    glutReshapeFunc(&cb_resize_screen);
    glutKeyboardFunc(&key_function);
    glutMouseFunc(&mouse_function);

    MyInit(WINDOW_WIDTH, WINDOW_HEIGHT);

    printf("\n%s\n\n", PROGRAM_TITLE);
    printf("Press z to spin cube and sphere\n");
    printf("Press a to spin pyramid and sphere\n");
    printf("Press space to spin all\n");
    printf("Press q to stop all\n");

    glutMainLoop();
    return 1;
}
