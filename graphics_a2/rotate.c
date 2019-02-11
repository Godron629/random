#define PROGRAM_TITLE "Assignment 2 Graphics 3710"
#define DISPLAY_INFO "Assignment 2 Graphics 3710"

#include <stdlib.h>  // Useful for the following includes.
#include <stdio.h>    
#include <string.h>  // For spring operations.

#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.

// Some global variables.
// Window IDs, window width and height.
int Window_ID;
int Window_Width = 600;
int Window_Height = 400;

// Cube position and rotation speed variables.
float rotation_degrees = 0.0;
float X_Rot = 0.0; 
float Y_Rot = 0.0;
float X_Speed = 0.0f;  // the rotation.
float Y_Speed = 0.0f;
float Z_Off   =-10.0f;

float cx = 0.0; 
float cy = 0.0; 
float cz = 0.0;

float rotation_vector_x = 0.0;
float rotation_vector_y = 0.0;
float rotation_vector_z = 0.0;

//////////////////////////////////////////////////////////
// String rendering routine; leverages on GLUT routine. //
//////////////////////////////////////////////////////////
static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

/////////////////////////////////////////////////////////
// Routine which actually does the drawing             //
/////////////////////////////////////////////////////////
void CallBackRenderScene(void)
{
   char buf[80]; // For our strings.
   
   // Need to manipulate the ModelView matrix to move our model around.
   glMatrixMode(GL_MODELVIEW);

   // Reset to 0,0,0; no rotation, no scaling.
   glLoadIdentity(); 

   // Move the object back from the screen.
   glTranslatef(0.0f,0.0f, Z_Off);

   // Rotate the calculated amount.
   glTranslatef(-cx, -cy, -cz);
   glRotatef(rotation_degrees, rotation_vector_x, rotation_vector_y, rotation_vector_z);
   glRotatef(rotation_degrees, rotation_vector_x, rotation_vector_y, rotation_vector_z);
   glTranslated(cx, cy, cz);

   // Clear the color and depth buffers.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // OK, let's start drawing our planer quads.
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
   glOrtho(0,Window_Width,0,Window_Height,-1.0,1.0);
   glColor4f(0.6,1.0,0.6,1.00);
   sprintf(buf,"%s", DISPLAY_INFO); // Print the string into a buffer
   glRasterPos2i(2,2);                         // Set the coordinate
   PrintString(GLUT_BITMAP_HELVETICA_12, buf);  // Display the string.

   
   // To ease, simply translate up.  Note we're working in screen
   // pixels in this projection.
   glTranslatef(6.0f, Window_Height - 14, 0.0f);

   // Done with this special projection matrix.  Throw it away.
   glPopMatrix();
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

   // We start with GL_DECAL mode.
   glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

   // All done drawing.  Let's show it.
   glutSwapBuffers();

   // Now let's do the motion calculations.
   X_Rot+=X_Speed; 
   Y_Rot+=Y_Speed; 
}

/////////////////////////////////////////////////////////////
// Callback Function called when a special key is pressed. //
/////////////////////////////////////////////////////////////
void CallBackSpecialKeyPressed(int key, int x, int y)
{
   switch (key) {
   case GLUT_KEY_PAGE_UP: // move the cube into the distance.
      Z_Off -= 0.05f;
      break;
   case GLUT_KEY_PAGE_DOWN: // move the cube closer.
      Z_Off += 0.05f;
      break;
   case GLUT_KEY_UP: // decrease x rotation speed;
      X_Speed -= 0.01f;
      break;
   case GLUT_KEY_DOWN: // increase x rotation speed;
      X_Speed += 0.01f;
      break;
   case GLUT_KEY_LEFT: // decrease y rotation speed;
      Y_Speed -= 0.01f;
      break;
   case GLUT_KEY_RIGHT: // increase y rotation speed;
      Y_Speed += 0.01f;
      break;
   default:
      printf ("SKP: No action for %d.\n", key);
      break;
    }
}

///////////////////////////////////////////////////////////////
// Callback routine executed whenever the window is resized. //
//////////////////////////////////////////////////////////////
void CallBackResizeScene(int Width, int Height)
{
   // Let's not core dump, no matter what.
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

////////////////////////////////////////////////////////
//   Setup your program before passing the control    //
//   to the main OpenGL event loop.                   //
////////////////////////////////////////////////////////
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
   CallBackResizeScene(Width,Height);
}

void myCBKey(unsigned char key, int x, int y) {
   /* 
   If 'a' if pressed, move the sphere away from the camera. 
   If 'z' is pressed, move the sphere toward the camera. 
   */
   switch(key) {
      case 113: // q
	      // Destroy the window and quit.
	      glutDestroyWindow(Window_ID);
	      exit(1);
         break; 
      default: 
         printf ("SKP: No action for %d.\n", key);
         break;
   }
}

void mouse_function(int button, int state, int x, int y) {
   switch(button) {
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {
            // Each time when you click the right mouse button, 
            // the cube will rotation 15deg at its centre. 
            rotation_degrees += 15.0;
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

   glutInitWindowSize(Window_Width, Window_Height);
   Window_ID = glutCreateWindow(PROGRAM_TITLE);

   // Register and install the callback function to do the drawing. 
   glutDisplayFunc(&CallBackRenderScene);
   // If there's nothing to do, draw.
   glutIdleFunc(&CallBackRenderScene);

   glutReshapeFunc(&CallBackResizeScene);

   // Register and install the callback function for keys
   glutKeyboardFunc(&myCBKey);
   glutSpecialFunc(&CallBackSpecialKeyPressed);
   glutMouseFunc(&mouse_function);

   MyInit(Window_Width, Window_Height);

   float p1x = atof(argv[1]);
   float p1y = atof(argv[2]);
   float p1z = atof(argv[3]);

   float p2x = atof(argv[4]);
   float p2y = atof(argv[5]);
   float p2z = atof(argv[6]);

   rotation_vector_x = (p2x - p1x);
   rotation_vector_y = (p2y - p1y);
   rotation_vector_z = (p2z - p1z);
   
   cx = atof(argv[7]); 
   cy = atof(argv[8]);
   cz = atof(argv[9]);


   // Print out a bit of help dialog.
   printf("\n%s\n\n", PROGRAM_TITLE);
   printf("Print out some helpful information here.\n");
   printf("When you program, you can also use\n");
   printf("printf to do debugging.\n\n");

   glutMainLoop(); 
   return 1; 
}

