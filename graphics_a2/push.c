#define PROGRAM_TITLE "Assignment 2 Gideon Richter Graphics 3710"
#define DISPLAY_INFO "Assignment 2 Gideon Richter Graphics 3710"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.
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


static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

void cb_render_scene(void)
{
   char buf[80]; // For our strings.

   usleep(40000);

   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);

   // Reset to 0,0,0; no rotation, no scaling.
   glLoadIdentity(); 

   // Install camera eye
   gluLookAt(
      eye_x, eye_y, eye_z, 
      0.0, 0.0, 0.0, 
      0.0, 1.0, 0.0
   );
   // Move the cube a little bit away from us
   glTranslatef(0.0, 0.0, cube_z);

   // Rotate the cube 
   glRotated(rotation_degrees, 0.0, 1.0, 0.0);

   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glBegin(GL_QUADS); 

      // Far face. 
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Top face. 
      glColor3f(1.0, 0.0, 0.0);
      glVertex3f( 1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f( 1.0f,  1.0f,  1.0f);

      // Bottom face. 
      glColor3f(0.0, 1.0, 0.0);
      glVertex3f( 1.0f,  -1.0f, -1.0f);
      glVertex3f(-1.0f,  -1.0f, -1.0f);
      glVertex3f(-1.0f,  -1.0f,  1.0f);
      glVertex3f( 1.0f,  -1.0f,  1.0f);
      
      // Right face.   
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f( 1.0f, -1.0f, -1.0f); 
      glVertex3f( 1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);

      // Front face.   
      glColor3f(0.5, 0.5, 0.5);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f( 1.0f,  1.0f,  1.0f); 
      glVertex3f(-1.0f,  1.0f,  1.0f);
      
      // Left Face.  
      glColor3f(0.25, 0.0, 0.7);
      glVertex3f(-1.0f, -1.0f, -1.0f); 
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      
   // All polygons have been drawn.
   glEnd();

   // Move back to the origin
   glLoadIdentity();

   // We need to change the projection matrix for the text rendering.  
   glMatrixMode(GL_PROJECTION);

   // But we like our current view too; so we save it here.
   glPushMatrix();

   // Display a string
   // Now we set up a new projection for the text.
   glLoadIdentity();
   glOrtho(0,WINDOW_WIDTH,0,WINDOW_HEIGHT,-1.0,1.0);
   glColor4f(0.6,1.0,0.6,1.00);
   sprintf(buf,"%s", DISPLAY_INFO); // Print the string into a buffer
   glRasterPos2i(2,2);                         // Set the coordinate
   PrintString(GLUT_BITMAP_HELVETICA_12, buf);  // Display the string.

   
   // To ease, simply translate up.  Note we're working in screen
   // pixels in this projection.
   glTranslatef(6.0f, WINDOW_HEIGHT - 14, 0.0f);

   // Done with this special projection matrix.  Throw it away.
   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   // We start with GL_DECAL mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

   // All done drawing.  Let's show it.
   glutSwapBuffers();

   rotation_degrees += 15.0;
}

void cb_resize_screen(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   WINDOW_WIDTH  = Width;
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
   cb_resize_screen(Width,Height);
}

void key_function(unsigned char key, int x, int y) {
   switch(key) {
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
   printf ("Pressing key: %d.\n", key);
}

void mouse_function(int button, int state, int x, int y) {
   switch(button) {
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {
            // If you press the right mouse
            // button and keep it pressed, your 
            // lookAt changes to (5, 5, z).
            eye_x = 5.0; 
            eye_y = 5.0; 
            eye_z = cube_z - cube_cam_offset;
         }
         if (state == GLUT_UP) {
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

int main(int argc, char **argv) {
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

   glutMainLoop(); 
   return 1; 
}

