
#include<SDL.h>
#ifdef __WIN32__
 #include <Windows.h>
#endif


#include <GL/GL.h>
#include <GL/GLU.h>
#include <stdio.h>
#include <iostream>

#include "Texture.h"
//#include <glut.h>

//SDL freeks
#define main main


const GLsizei  windowWidth = 640;
const GLsizei windowHeight = 480;

GLfloat cubeRotateX = 45;
GLfloat cubeRotateY = 45;
//char *keys = NULL;

Texture *texture=NULL;

GLvoid establishProjectionMatrix(GLsizei width,GLsizei height){
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
}

GLvoid initGL(GLsizei width,GLsizei height){
	establishProjectionMatrix(width,height);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable(GL_PERSPECTIVE_CORRECTION_HINT);

	glEnable(GL_TEXTURE_2D);

	texture = new Texture("data/box.tga","Box texture");

}

GLvoid displayFPS(SDL_Window* window){
	static long lastTime = SDL_GetTicks();
	static long loops=0;
	static GLfloat fps = 0.0f;

	int newTime = SDL_GetTicks();

	if(newTime - lastTime>100){
		float newFPS = (float)loops/float(newTime-lastTime)*1000.0f;

		fps = (fps+newFPS)/2.0f;

		char title[80];
		sprintf(title,"window %.2f",fps);
				
		SDL_SetWindowTitle(window,title);

		lastTime = newTime;
		loops = 0;
	}

	loops++;
}
///

GLvoid drawScene(SDL_Window* window){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0,0,-5.0f);
	glRotatef(cubeRotateX,1,0,0);
	glRotatef(cubeRotateY,0,1,0);

	glColor3f(1.0f,1.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D, texture->texID);

	glBegin(GL_QUADS);
		
		//Top face
		glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f,1.0f,-1.0f);		
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,1.0f,1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,1.0f,1.0f);

		//Bottom face
		
		glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f,-1.0f,-1.0f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,-1.0f,1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,-1.0f,1.0f);

		//Front face
		
		glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f,1.0f,1.0f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f,1.0f,1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,-1.0f,1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,-1.0f,1.0f);
		
		//Back face
		
		glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,-1.0f,-1.0f);
		
		//Left face
		
		glTexCoord2f(1.0f,1.0f);glVertex3f(-1.0f,1.0f,1.0f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(-1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(-1.0f,-1.0f,1.0f);
		
		//Right face
		
		glTexCoord2f(1.0f,1.0f);glVertex3f(1.0f,1.0f,1.0f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(1.0f,1.0f,-1.0f);
		glTexCoord2f(0.0f,0.0f);glVertex3f(1.0f,-1.0f,-1.0f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(1.0f,-1.0f,1.0f);
		
	glEnd();

	glFlush();

	SDL_GL_SwapWindow(window);
	SDL_UpdateWindowSurface(window);

	displayFPS(window);

}

GLvoid checkKeys(const Uint8 *state){

	const GLfloat speed = 7.0f;

	if (state[SDL_SCANCODE_RETURN]) {
    printf("<RETURN> is pressed.\n");
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		cubeRotateY += speed;
	}
	if (state[SDL_SCANCODE_LEFT]) {
		cubeRotateY -= speed;
	}
	if (state[SDL_SCANCODE_UP]) {
		cubeRotateX -= speed;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		cubeRotateX += speed;;
	}

	/*switch(evnt->key.keysym.sym){
	
	case SDLK_LEFT: cubeRotateY -=speed;break;
	case SDLK_RIGHT: cubeRotateY +=speed;break;
	case SDLK_UP: cubeRotateX +=speed;break;
	case SDLK_DOWN: cubeRotateX -=speed;break;
	}*/


}

//GLvoid timerLoop(int value){

	//glutPostRedisplay();
	//glutTimerFunc(1,timerLoop,0);
//}

int main(int argc,char **argv){
		

	if(SDL_Init(SDL_INIT_VIDEO)<0){
		//error
	}

	SDL_Window* window = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          windowWidth, windowHeight,
                          //SDL_WINDOW_FULLSCREEN | 
						  SDL_WINDOW_OPENGL);

	if(window==NULL){
		//error
	}


	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	initGL(windowWidth,windowHeight);

	//состояния клавиатуры
	const Uint8 *state = NULL;

	int done = 0;

	while(!done){

		drawScene(window);

		SDL_Event evnt;	
		while(SDL_PollEvent(&evnt)){
			if(evnt.type == SDL_QUIT){
				done = 1;
			}

			state = SDL_GetKeyboardState(NULL);
			checkKeys(state);
			//std::cout<<SDL_GetScancodeFromKey(evnt.key.keysym.sym)<<std::endl;
			//std::cout<<evnt.key.keysym.scancode<<std::endl;
		}

		
		
	}
	SDL_Quit();

	/*glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);

	int windowID = glutCreateWindow("cube");
	glutReshapeWindow(windowWidth,windowHeight);

	initGL(windowWidth,windowHeight);

	glutDisplayFunc(drawScene);
	glutTimerFunc(1,timerLoop,0);

	glutMainLoop();*/
	return 0;
}