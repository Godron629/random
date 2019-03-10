#define PROGRAM_TITLE "Gideon Richter"
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
int rotation_degrees = 0;

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

static void PrintString(void *font, char *str)
{
    int i, len = strlen(str);

    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, *str++);
}

void draw_cube()
{
    glTranslatef(0.0, 0.0, cube_z);
    glRotated(rotation_degrees, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);

    // Far face.
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Top face.
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face.
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right face.
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Front face.
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Left Face.
    glColor3f(0.25, 0.0, 0.7);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // All polygons have been drawn.
    glEnd();
}

void make_area_1()
{
    /* 
        Make "Area 1" in assignment description. 
        Area 1 is to display help information, such as 
        the keys that are used in this program.
    */
    glViewport(
        WINDOW_WIDTH * 0.2,
        WINDOW_HEIGHT * 0.8,
        WINDOW_WIDTH * 0.8,
        WINDOW_HEIGHT * 0.8);

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);

    // Set the text color
    glColor4f(0.6, 1.0, 0.6, 1.00);

    glRasterPos2i(2, 20);
    char msg1[50] = "Press RB to change lookAt";
    PrintString(GLUT_BITMAP_HELVETICA_12, msg1);

    glRasterPos2i(2, 2);
    char msg2[50] = "Press z to push cube";
    PrintString(GLUT_BITMAP_HELVETICA_12, msg2);

    glPopMatrix();
}

void make_area_2()
{
    /*
    Make "Area 2" in assignment description
    Area 2 is used to display the current information 
    about the object, such as its z positions, eyes, etc.
    */
    glViewport(0, 0, WINDOW_WIDTH * 0.2, WINDOW_HEIGHT * 0.8);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);
    glColor4f(0.6, 1.0, 0.6, 1.00);

    // Form the string: "Cube z: z"
    char msg1[10] = "Cube z: ";
    char cube_z_buf[10];
    gcvt(cube_z, 5, cube_z_buf);
    strcat(msg1, cube_z_buf);
    glRasterPos2i(2, 60);
    PrintString(GLUT_BITMAP_HELVETICA_12, msg1);

    // Form the string "Eye Position: x, y, z"
    char msg2[50] = "Eye Position: ";
    char eye_x_buf[5];
    char eye_y_buf[5];
    char eye_z_buf[5];
    gcvt(eye_x, 5, eye_x_buf);
    gcvt(eye_y, 5, eye_y_buf);
    gcvt(eye_z, 5, eye_z_buf);
    strcat(msg2, eye_x_buf);
    strcat(msg2, ", ");
    strcat(msg2, eye_y_buf);
    strcat(msg2, ", ");
    strcat(msg2, eye_z_buf);
    glRasterPos2i(2, 40);
    PrintString(GLUT_BITMAP_HELVETICA_12, msg2);

    // Form the string "Rotation: 0-360"
    char msg3[50] = "Rotation: ";
    char rotation_buf[5];
    sprintf(rotation_buf, "%d", rotation_degrees);
    strcat(msg3, rotation_buf);
    glRasterPos2i(2, 20);
    PrintString(GLUT_BITMAP_HELVETICA_12, msg3);

    glPopMatrix();
}

void cb_render_scene(void)
{
    char buf[80]; // For our strings.

    usleep(40000);

    glMatrixMode(GL_MODELVIEW);
    glViewport(WINDOW_WIDTH * 0.2, 0, WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.8);
    glLoadIdentity();
    gluLookAt(
        eye_x, eye_y, eye_z,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    draw_cube();
    make_area_1();
    make_area_2();

    glutSwapBuffers();

    rotation_degrees = (rotation_degrees + 15) % 360;
}

void cb_resize_screen(int Width, int Height)
{
    // Let's not core dump, no matter what.
    if (Height == 0)
        Height = 1;

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    WINDOW_WIDTH = Width;
    WINDOW_HEIGHT = Height;
}

void MyInit(int Width, int Height)
{
    glEnable(GL_DEPTH_TEST);
    // Color to clear color buffer to.
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // Depth to clear depth buffer to; type of test.
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);

    // Enables Smooth Color Shading; try GL_FLAT for (lack of) fun.
    glShadeModel(GL_SMOOTH);

    // Load up the correct perspective matrix; using a callback directly.
    cb_resize_screen(Width, Height);
}

void key_function(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 113: // q
        // Destroy the window and quit.
        glutDestroyWindow(WINDOW_ID);
        exit(1);
        break;
    case 122:
        // Push the cube forward along the z axis
        cube_z -= cube_z_push_amount;
        eye_z = cube_z - cube_cam_offset;
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
            // If you press the right mouse
            // button and keep it pressed, your
            // lookAt changes to (5, 5, z).
            eye_x = 5.0;
            eye_y = 5.0;
            eye_z = cube_z - cube_cam_offset;
        }
        if (state == GLUT_UP)
        {
            // If you release the right mouse button
            // your lookAt returns to (0, 0, z).
            eye_x = 0.0;
            eye_y = 0.0;
            eye_z = cube_z - cube_cam_offset;
        }
        break;
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
    printf("Press RB to change lookAt\n");
    printf("Press z to push cube\n");

    glutMainLoop();
    return 1;
}
