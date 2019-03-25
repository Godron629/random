#include "GL/glut.h"
#include <stdio.h>

// Angle rotates only the bottom portion of each UFO.
static int UFO_BOTTOM_ANGLE = 0;

// Polyhedron positions. 
static float POLYHEDRON_XYZ_1[] = {1.0, 1.0, 1.0};
static float POLYHEDRON_XYZ_2[] = {-2.0, 0.0, -2.0};

// UFO 1 and 2 are rotating around the 'Polyhedron positions'
int UFO_1_ANGLE = 0;
int UFO_2_ANGLE = 0;

// State for user controlling UFO 3 in the back right area. 
enum FlyingState
{
    UP_DOWN,
    FORWARD_BACKWARD
};

// Flips ever 20 displays to make UFO 3 fly up/down on repeat.
int REVERSE_FLIGHT = 0;

// UFO 3 position and state that is changed by `move_ufo_3()`
float UFO_3_X = 2.0;
float UFO_3_Y = 2.0;
float UFO_3_Z = -1.0;
int UFO_3_STATE = UP_DOWN;
int UFO_3_MOVE_COUNTER = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Enable two lights and smooth shading model.
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}

void make_ufo_side()
{
    glPushMatrix();
    // Make 6 triangle sides, each angled
    // and rotated around the perimeter.
    int rotation = 60;
    for (int i = 0; i <= 5; i++)
    {
        glPushMatrix();
        glRotatef((GLfloat)rotation, 0.0, 1.0, 0.0);
        glTranslatef(0.0, 0.0, 0.43);
        glRotatef(-45.0, 1.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        glVertex3f(-0.25, 0.0, 0.0);
        glVertex3f(0.25, 0.0, 0.0);
        glVertex3f(0.0, 0.61, 0.0);
        glEnd();

        glPopMatrix();
        rotation += 60;
    }
    // There is no need to create base, we can't see it.
    glPopMatrix();
}

void draw_axes()
{
    // Draw X axis.
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-100, 0.0, 0.0);
    glVertex3f(100, 0.0, 0.0);
    glEnd();
    // Draw Y axis.
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();
    // Draw Z axis.
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
}

void ufo(int s)
{
    // Make a ufo with size s
    // Scale the result to `s`
    glScalef(1.0 * s, (1.0 * s) / 1.5, 1.0 * s);
    // Draw the top
    make_ufo_side();
    // Flip those eggs
    glRotatef(180, 1.0, 0.0, 0.0);
    // Draw the bottom
    glPushMatrix();
    // it is spinning constantly.
    glRotatef(UFO_BOTTOM_ANGLE, 0.0, 1.0, 0.0);
    make_ufo_side();
    glPopMatrix();
}

void move_ufo_3()
{
    // Move ufo 3 (back right) up and down or side to side.
    // When it reaches the extremes of its flight path - it
    // should switch directions.
    if (UFO_3_MOVE_COUNTER == 20)
    {
        // Switch directions and reset counter.
        REVERSE_FLIGHT = REVERSE_FLIGHT == 0 ? 1 : 0;
        UFO_3_MOVE_COUNTER = 0;
    }
    if (UFO_3_STATE == FORWARD_BACKWARD)
    {
        if (REVERSE_FLIGHT)
        {
            // Move closer to viewer.
            UFO_3_Z += 0.05;
        }
        else
        {
            // Move away from viewer.
            UFO_3_Z -= 0.05;
        }
    }
    else if (UFO_3_STATE == UP_DOWN)
    {
        if (REVERSE_FLIGHT)
        {
            // Move up.
            UFO_3_Y += 0.05;
        }
        else
        {
            // Move down.
            UFO_3_Y -= 0.05;
        }
    }
    UFO_3_MOVE_COUNTER += 1;
}

void draw_ufos()
{
    // Back left ufo
    // Is rotating around polyhedron 2.
    glPushMatrix();
    glTranslatef(POLYHEDRON_XYZ_2[0], POLYHEDRON_XYZ_2[1] + 0.5,
                 POLYHEDRON_XYZ_2[2]);
    glRotatef(UFO_1_ANGLE, 0.0, 1.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    ufo(1);
    glPopMatrix();

    // Center ufo
    // Spins by itself.
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    ufo(1);
    glPopMatrix();

    // Back right
    // It is moving up/down or right/left.
    glPushMatrix();
    glTranslatef(UFO_3_X, UFO_3_Y, UFO_3_Z);
    ufo(1);
    glPopMatrix();

    // Front left ufo
    // Spins by itself.
    glPushMatrix();
    glTranslatef(-2.0, 2.0, 1.0);
    ufo(1);
    glPopMatrix();

    // Front right ufo
    // Is rotating around polyhedron 1.
    glPushMatrix();
    glTranslatef(POLYHEDRON_XYZ_1[0], POLYHEDRON_XYZ_1[1] + 0.5,
                 POLYHEDRON_XYZ_1[2]);
    glRotatef(-UFO_2_ANGLE, 0.0, 1.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    ufo(1);
    glPopMatrix();

    // Rotate UFO 1 and 2 for next time.
    // 2 is spinning slower than 1.
    UFO_1_ANGLE = (UFO_1_ANGLE + 2) % 360;
    UFO_2_ANGLE = (UFO_2_ANGLE + 1) % 360;
    UFO_BOTTOM_ANGLE = (UFO_BOTTOM_ANGLE + 2) % 360;

    move_ufo_3();
}

void draw_polyhedron()
{
    // Draw two polyhedron - one in the back left
    // of the viewing area and one in the front right.
    glPushMatrix();
    glTranslatef(POLYHEDRON_XYZ_1[0], POLYHEDRON_XYZ_1[1], POLYHEDRON_XYZ_1[2]);
    glScalef(0.3, 0.3, 0.3);
    glutSolidDodecahedron();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(POLYHEDRON_XYZ_2[0], POLYHEDRON_XYZ_2[1], POLYHEDRON_XYZ_2[2]);
    glScalef(0.3, 0.3, 0.3);
    glutSolidDodecahedron();
    glPopMatrix();
}

void display()
{
    // Light 1 is facing directly at the scene.
    GLfloat light1_position[] = {0.0, 0.0, 5.0, 1.0};
    // Light 2 is facing the scene on the upper left.
    GLfloat light2_position[] = {-5.0, 5.0, 5.0, 1.0};
    // Light 2 has green diffuse colouring.
    GLfloat light2_diffuse[] = {0.0, 1.0, 0.0, 1.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    draw_axes();

    glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light2_diffuse);

    draw_polyhedron();

    draw_ufos();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 102: // "f"
        // Set UFO 3 state to move forward/backward.
        UFO_3_STATE = FORWARD_BACKWARD;
        break;
    case 117: // "u"
        // Set UFO 3 state to move up/down.
        UFO_3_STATE = UP_DOWN;
        break;
    default:
        printf("Not a control key: %d\n", key);
        fflush(stdout);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}