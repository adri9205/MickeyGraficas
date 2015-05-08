#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include "Imageloader.h"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600


using namespace std;
bool active=true;
int opcion=2;
bool pause=false;
bool reset=false;
bool reactive=false;
bool win=false;
GLfloat seg=0.0;
double xM=0, yM=0;
GLfloat mins=0.0;
GLfloat deci=0.0;
GLfloat turns=0.0;
typedef enum {FONDO1,FONDO2,FONDO3,FONDO4,FONDO5};
void draw();
void reshape(int width, int height);
void special_keyboard(int key, int mouseX, int mouseY);
void initRendering();
void keyboard(unsigned char, int, int);
void dibujaCrono();
void mouse(int boton, int state, int x, int y);
void timer(int i);
float y=1.0;
bool loose=false;
double posXvillano[30]={4,7,14,8,15,4,7,16,16,8,4,7,14,8,15};
double posYvillano[30]={9,5,12,-1.5,3,-1,8,13,4,14,9,5,12,-1.5,3};
//GLfloat posXvillano[30]={4,7,14,8,15,4,7,16,16,8,4,7,14,8,15};
//GLfloat posYvillano[30]={9,5,12,-1.5,3,-1,8,13,4,14,9,5,12,-1.5,3};
double mouseX;
double mouseY;
bool estadoMenu=true, estadoNivel1=false,estadoNivel2=false, estadoNivel3=false, estadoNivel4=false, principiante=false, intermedio=false,avanzado=false, puntaje=false;
bool ventanaprincipal=true;
void creacionMenu();
bool adivinaP=false;
const float medida = 1;  // Mitad del tama√ío de cada lado del cubo
bool resume=false;
int angulo=0;
static GLuint texName[80];
const int TEXTURE_COUNT=6;
float z=1.0;
int oportunidades=4;
bool reto=false;
int enemigos=5;
int oportunidadesAvanzados=3;
bool vencido[30]={false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
bool colisionVillano[30]={false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};
int puntos=0;
void outputText(double x,double y,double z,double scale,char *s);
void myTimer(int v);
bool bonus=false;
float x=0;
float x1=2.0;


int main(int argc, char** argv) {

	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(20, 20);
	glEnable(GL_DEPTH_TEST);
	glutCreateWindow("MickeySaveTheWorld");
	initRendering();
	glutDisplayFunc(dibujaCrono);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keyboard);
    glutMouseFunc(mouse);
	glutTimerFunc(25, timer, 0.1);
    glutTimerFunc(5, myTimer, 1);
    creacionMenu();
	glutMainLoop();

	return 0;
}

void onMenu(int opcion) {
	switch(opcion) {
case FONDO1:

	break;
case 2:
    active=true;
    glutPostRedisplay();
	break;
case 3:
   active=false;
    glutPostRedisplay();
	break;

	case 4: // Blanco 3
   active=false;
    reset=true;

    glutPostRedisplay();

	break;
case 5:
exit(0);
	break;
	glutPostRedisplay();
}}

void creacionMenu(void) {
	int menuFondo, menuDibujo;
    menuDibujo = glutCreateMenu(onMenu);
   glutAddMenuEntry("Adriana Cortés ", 0);
	glutAddMenuEntry("Javier Yépiz", 0);

	menuFondo = glutCreateMenu(onMenu);

    glutAddSubMenu("Autores", menuDibujo);
    glutAddMenuEntry("Iniciar",2);
	glutAddMenuEntry("Pause",3);
	glutAddMenuEntry("Reset",4);
	glutAddMenuEntry("Salir",5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void myTimer(int v)
{
    if (active){
    x=x+.5;
    x1=x1-.5;
    if(x>=2){
        x=0;
    }
    if(x1<=0){
        x1=2.0;
    }}


    glutPostRedisplay();
    glutTimerFunc(500, myTimer, 1);

}

void timer(int extra)
{

if (active)
{
   deci+=1.0;
   if (deci==56){
    deci=0.0;
    seg+=6.0;
    if(seg == 360.0)
    {
	seg = 0.0;
	mins += 6.0;
	if(mins == 360.0)
	{
		mins = 0.0;}
    }}

     if (estadoNivel1){

            if (ventanaprincipal){

                    for (int i=0; i<5;i++){
                            if (!vencido[i]){
                            if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                           if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }

                            if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                            if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){
                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }}


                    }

           if (xM==10&&yM==12){
            ventanaprincipal=false;
            adivinaP=true;
           }

            }

    }
    if(estadoNivel2){
            if (ventanaprincipal){
                    for (int i=5; i<10;i++){
                            if (!vencido[i]){

    if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                           if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }

                            if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                            if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){
                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                       }


                    }

            }
            if (xM==10&&yM==12){
            ventanaprincipal=false;
            adivinaP=true;
           }

    }
    if(estadoNivel3){
            if (ventanaprincipal){
                    for (int i=10; i<15;i++){
                            if (!vencido[i]){
                            if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                           if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+.125)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }

                            if((xM<=(posXvillano[i]+x+.25))&&(xM>=(posXvillano[i]+x-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){

                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                            if((xM<=(posXvillano[i]+x1+.25))&&(xM>=(posXvillano[i]+x1-.25))){

                                if((yM<=posYvillano[i]+1)&&(xM>=posXvillano[i])){
                                    colisionVillano[i]=true;
                                    reto=true;
                                    ventanaprincipal=false;
                                }
                            }
                            }


                    }

            }
            if (xM==10&&yM==12){
            ventanaprincipal=false;
            adivinaP=true;
           }

    }

    }

else {
if (reset){
    seg=0.0;
    mins=0.0;
    deci=0.0;
    turns=0;

    reset=false;
    active=false;
    if (principiante){
        for (int i=0; i<5; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
    }
    else if (intermedio){
        for (int i=5; i<10; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
    }
    else if (avanzado){
        for (int i=10; i<15; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
    }
    ventanaprincipal=true;
    xM=0;
    yM=0;
}

}
glutPostRedisplay();
glutTimerFunc(25, timer, 0.1);


}

void setX(double x)
{
    mouseX=x;
}

void setY(double y)
{
    mouseY=y;
}
void game(){
    if (estadoMenu){


            oportunidades=4;
            puntos=0;
            win=false;
            loose=false;
            xM=0;
            yM=0;
            PlaySound("rAZc0XKApn0.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    if (mouseX>=6.36&&mouseX<=12.28)
        {

            if (mouseY>=9&&mouseY<=11){
                    principiante=true;
                    estadoNivel1=true;
                    estadoMenu=false;
                    intermedio=false;
                    avanzado=false;
                    active=true;

            }
            else if (mouseY>=6&&mouseY<=8){
                    active=true;
                    intermedio=true;
                    estadoNivel1=true;
                    estadoMenu=false;
                    principiante=false;
                    avanzado=false;

            }
            else if (mouseY>=4&&mouseY<=5){
                    active=true;
                    avanzado=true;
                    estadoNivel1=true;
                    estadoMenu=false;
                    principiante=false;
                    intermedio=false;



            }
            else if (mouseY>0&&mouseY<=2){
                puntaje=true;
                estadoMenu=false;
            }
        }
    }

                if (adivinaP){
                        if(estadoNivel1){
                        if (mouseY<=5&&mouseY>=4){
                        if (mouseX<=6.5&&mouseX>=3.5){
                            estadoNivel2=true;
                            estadoNivel1=false;
                            for (int i=0; i<5; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
                            puntos+=50;
                            xM=0;
                            yM=0;
                            oportunidades=3;
                            adivinaP=false;
                            ventanaprincipal=true;
                        }
                        else{
                              oportunidades--;
                              if (oportunidades==0){
                                adivinaP=false;
                                loose=true;

                              }

                        }

                }

        }

        if(estadoNivel2){
                if (mouseY<=5&&mouseY>=4){
                        if (mouseX<=16.5&&mouseX>=13.5){
                            for (int i=5; i<10; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
                            puntos+=50;
                            adivinaP=false;
                            estadoNivel2=false;
                            estadoNivel3=true;
                            oportunidades=4;
                            xM=0;
                            yM=0;
                            ventanaprincipal=true;

                        }
                        else{
                              oportunidades--;
                              if (oportunidades==0){
                              adivinaP=false;
                             loose=true;

                              }

                        }

                }

        }
         if(estadoNivel3){
                if (mouseY<=5&&mouseY>=4){
                        if (mouseX<=11.5&&mouseX>=8.5){
                            for (int i=10; i<15; i++){
                                vencido[i]=false;
                                colisionVillano[i]=false;
                            }
                            puntos+=50;
                            oportunidades=4;
                            adivinaP=false;
                            estadoNivel3=false;
                            win=true;

                        }
                        else{
                              oportunidades--;
                              if (oportunidades==0){
                                    adivinaP=false;
                                loose=true;

                              }

                        }

                }

        }

        }


        if (reto){
                        if(!vencido[0]&&colisionVillano[0]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){
                                        vencido[0]=true;
                                        colisionVillano[0]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[1]&&colisionVillano[1]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=3.5&&mouseX<=6.5){

                                        vencido[1]=true;
                                        colisionVillano[1]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){

                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[2]&&colisionVillano[2]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[2]=true;
                                        colisionVillano[2]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;

                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){

                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }
                        }
                        if(!vencido[3]&&colisionVillano[3]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){

                                        vencido[3]=true;
                                        colisionVillano[3]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){

                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[4]&&colisionVillano[4]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[4]=true;
                                        colisionVillano[4]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }

                        if(!vencido[5]&&colisionVillano[5]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){
                                        vencido[5]=true;
                                        colisionVillano[5]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            //loose=true;
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[6]&&colisionVillano[6]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=3.5&&mouseX<=6.5){

                                        vencido[6]=true;
                                        colisionVillano[6]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[7]&&colisionVillano[7]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[7]=true;
                                        colisionVillano[7]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;

                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }
                        }
                        if(!vencido[8]&&colisionVillano[8]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){

                                        vencido[8]=true;
                                        colisionVillano[8]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            //loose=true;
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[9]&&colisionVillano[9]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[9]=true;
                                        colisionVillano[9]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }

                        if(!vencido[10]&&colisionVillano[10]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){
                                        vencido[10]=true;
                                        colisionVillano[10]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[11]&&colisionVillano[11]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=3.5&&mouseX<=6.5){

                                        vencido[11]=true;
                                        colisionVillano[11]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[12]&&colisionVillano[12]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[12]=true;
                                        colisionVillano[12]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;

                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }
                        }
                        if(!vencido[13]&&colisionVillano[13]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=13.5&&mouseX<=16.5){

                                        vencido[13]=true;
                                        colisionVillano[13]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }
                        if(!vencido[14]&&colisionVillano[14]){
                                if (mouseY>=4&&mouseY<=5){
                                    if (mouseX>=8.5&&mouseX<=11.5){

                                        vencido[14]=true;
                                        colisionVillano[14]=false;
                                        puntos+=25;
                                        reto=false;
                                        ventanaprincipal=true;
                                    }
                                    else{
                                        oportunidades--;
                                        if (oportunidades<=0){
                                            reto=false;
                                            loose=true;
                                        }

                                    }
                                }

                        }





                }
}


void mouse(int boton, int state, int xGLUT, int yGLUT)
{
    double x=(double)xGLUT/50;
    double y =(int)(WINDOW_HEIGHT - yGLUT)/30;
    //cout<<x<<","<<y<<endl;

    if(boton==GLUT_LEFT_BUTTON)
    {

        if (state==GLUT_DOWN){
        setX(x);
        setY(y);
        game();

        glutPostRedisplay();
        }
}

}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'i':
        case 'I':
    active=true;
    glutPostRedisplay();
    break;
   case 'd':
        case 'D':
    active=false;
    glutPostRedisplay();
    break;
    case 'r':
        case 'R':
    active=false;
    reset=true;

    glutPostRedisplay();
    break;
    case 'o':
        case 'O':
            opcion = 1;
            reshape(WINDOW_WIDTH,WINDOW_HEIGHT);
            glutPostRedisplay();
            break;
        case 'p':
        case 'P':
            opcion = 2;
            reshape(WINDOW_WIDTH,WINDOW_HEIGHT);
            glutPostRedisplay();
            break;

            case 'm':
        case 'M':
            if(loose){
            loose=false;
            estadoMenu=true;
            ventanaprincipal=true;
            }
            if(puntaje){
                puntaje=false;
                estadoMenu=true;
                ventanaprincipal=true;
            }
            if(win){
                win=false;
                estadoMenu=true;
                ventanaprincipal=true;
            }
            glutPostRedisplay();
            break;

      	case 27:
         	exit(0);
         	break;
   }
}
char buff2[100];
void special_keyboard(int key, int mouseX, int mouseY)
{
    if (active){

switch (key)
{
case GLUT_KEY_UP:
    if(yM < 20)
        {
            yM += .5;
        }

glutPostRedisplay();
break;
case GLUT_KEY_DOWN:
 if(yM > -2)
        {
           // if(GetAsyncKeyState(VK_DOWN))
            yM -= .5;
        }
        glutPostRedisplay();
break;
case GLUT_KEY_RIGHT:
    if(xM < 20)
        {
            xM += .5;
        }

glutPostRedisplay();
break;
case GLUT_KEY_LEFT:
    if(xM > 0)
        {
            xM -= .5;
        }


glutPostRedisplay();
break;
default:
break;
}}
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{

    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data

}
void initRendering()
{

    GLuint i=0;
    GLfloat ambientLight[] = {12.0f, 12.0, 12.0f, 12.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    GLfloat directedLight[] = {3.0f, 3.0f, 3.0f, 3.0f};
    GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(80, texName); //Make room for our texture
    Image* image;
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/menuprincipal3.bmp");loadTexture(image,i++);//0
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/jardin.bmp");loadTexture(image,i++);//1
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/j.bmp");loadTexture(image,i++);//2
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/night.bmp");loadTexture(image,i++);//3
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/castle.bmp");loadTexture(image,i++);//4
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/mick.bmp");loadTexture(image,i++);//5
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/winner.bmp");loadTexture(image,i++);//6
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/wall.bmp");loadTexture(image,i++);//7
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/loose.bmp");loadTexture(image,i++);//8
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/instrucciones.bmp");loadTexture(image,i++);//9

    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/bambi.bmp");loadTexture(image,i++);//10
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/beatyandbeast.bmp");loadTexture(image,i++);//11
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/cars.bmp");loadTexture(image,i++);//12
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/christmas.bmp");loadTexture(image,i++);//13
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/dalmatas.bmp");loadTexture(image,i++);//14
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/damayvagabundo.bmp");loadTexture(image,i++);//15
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/frozen.bmp");loadTexture(image,i++);//16
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/lionking.bmp");loadTexture(image,i++);//17
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/mickeypluto.bmp");loadTexture(image,i++);//18
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/moon.bmp");loadTexture(image,i++);//19
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/swanprincess.bmp");loadTexture(image,i++);//20
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/selva.bmp");loadTexture(image,i++);//21
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/selva.bmp");loadTexture(image,i++);//22
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/selva.bmp");loadTexture(image,i++);//23
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/pluto.bmp");loadTexture(image,i++);//24
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/minnie.bmp");loadTexture(image,i++);//25
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/goofy1.bmp");loadTexture(image,i++);//26
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/red.bmp");loadTexture(image,i++);//27
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/nemo.bmp");loadTexture(image,i++);//28
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/olaf.bmp");loadTexture(image,i++);//29
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/peterpan.bmp");loadTexture(image,i++);//30

    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/christmas2.bmp");loadTexture(image,i++);//31
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/swanprincess2.bmp");loadTexture(image,i++);//32 peterpan2
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/peterpan2.bmp");loadTexture(image,i++);//33
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/beatyandbeast2.bmp");loadTexture(image,i++);//34
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/damayvagabundo2.bmp");loadTexture(image,i++);//35
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/cars2.bmp");loadTexture(image,i++);//36
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/dalmatas2.bmp");loadTexture(image,i++);//37
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/bambi2.bmp");loadTexture(image,i++);//38
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/frozen2.bmp");loadTexture(image,i++);//39
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/moon2.bmp");loadTexture(image,i++);//40
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/lionking2.bmp");loadTexture(image,i++);//41
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/selva2.bmp");loadTexture(image,i++);//42
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/nemo2.bmp");loadTexture(image,i++);//43
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/olaf2.bmp");loadTexture(image,i++);//44
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/mickeypluto2.bmp");loadTexture(image,i++);//45

    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/frozen3.bmp");loadTexture(image,i++);//46
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/moon3.bmp");loadTexture(image,i++);//47
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/dalmatas3.bmp");loadTexture(image,i++);//48
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/bambi3.bmp");loadTexture(image,i++);//49
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/beatyandbeast3.bmp");loadTexture(image,i++);//50
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/damayvagabundo3.bmp");loadTexture(image,i++);//51
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/cars3.bmp");loadTexture(image,i++);//52
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/lionking3.bmp");loadTexture(image,i++);//53
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/christmas3.bmp");loadTexture(image,i++);//54
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/mickeypluto3.bmp");loadTexture(image,i++);//55
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/swanprincess3.bmp");loadTexture(image,i++);//56 peterpan2
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/nemo3.bmp");loadTexture(image,i++);//57
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/olaf3.bmp");loadTexture(image,i++);//58
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/peterpan3.bmp");loadTexture(image,i++);//59
    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/selva3.bmp");loadTexture(image,i++);//60

    image = loadBMP("C:/Users/AdriiiiiCS/Documents/ProyectoGraficas/white.bmp");loadTexture(image,i++);//61
    delete image;

}


void outputText(double x,double y,double z,double scale,char *s)
{
   int i;
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);
   for (i=0;i<strlen(s);i++)
   glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
   glPopMatrix();
}

void dibujaVillano() {

    for (int i=0; i<5; i++){

           if(estadoNivel1){

            if (!vencido[i]){
                    glBindTexture(GL_TEXTURE_2D, texName[27]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

                     glPushMatrix();

                     if (i%2==0){
                     glTranslatef(posXvillano[i]+x,posYvillano[i],0);}
                     else{
                        glTranslatef(posXvillano[i]+x1,posYvillano[i],0);
                     }

                     glPushMatrix();
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                   // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y

                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, texName[0]);


                    //glTranslatef(posXvillano[i]+1+x, posYvillano[i]+2.5, 0);
                    if (i%2==0){
                     glTranslatef(posXvillano[i]+x+1,posYvillano[i]+2.5,0);}
                     else{
                        glTranslatef(posXvillano[i]+x1+1,posYvillano[i]+2.5,0);
                     }
                    glScaled(.5,.5,0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();

            }
            glBindTexture(GL_TEXTURE_2D, texName[17]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

                     glPushMatrix();

//amigo mickey
                        glTranslatef(10,12,0);
                     glPushMatrix();
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                   // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y

           }
           else if(estadoNivel2){


                if (!vencido[i+5]){
                        glBindTexture(GL_TEXTURE_2D, texName[27]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glPushMatrix();

                     if (i%2==0){
                     glTranslatef(posXvillano[i+5]+x,posYvillano[i+5],0);}
                     else{
                        glTranslatef(posXvillano[i+5]+x1,posYvillano[i+5],0);
                     }
                     glPushMatrix();
                    // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                   // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, texName[0]);

                    //glTranslatef(posXvillano[i]+1+x, posYvillano[i]+2.5, 0);

                    if (i%2==0){
                     glTranslatef(posXvillano[i+5]+x+1,posYvillano[i+5]+2.5,0);}
                     else{
                        glTranslatef(posXvillano[i+5]+x1+1,posYvillano[i+5]+2.5,0);
                     }
                    glScaled(.5,.5,0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();

            }

                glBindTexture(GL_TEXTURE_2D, texName[20]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

                     glPushMatrix();


                        glTranslatef(10,12,0);


                     glPushMatrix();
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                   // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
           }
           else if(estadoNivel3){
                if (!vencido[i+10]){
                        glBindTexture(GL_TEXTURE_2D, texName[27]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glPushMatrix();

                     if (i%2==0){
                     glTranslatef(posXvillano[i+10]+x,posYvillano[i+10],0);}
                     else{
                        glTranslatef(posXvillano[i+10]+x1,posYvillano[i+10],0);
                     }
                     glPushMatrix();
                     //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();
                    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
                    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
                    glPushMatrix();
                    glBindTexture(GL_TEXTURE_2D, texName[0]);

                    //glTranslatef(posXvillano[i]+1+x, posYvillano[i]+2.5, 0);
                    if (i%2==0){
                     glTranslatef(posXvillano[i+10]+x+1,posYvillano[i+10]+2.5,0);}
                     else{
                        glTranslatef(posXvillano[i+10]+x1+1,posYvillano[i+10]+2.5,0);
                     }
                    glScaled(.5,.5,0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();

            }

           glBindTexture(GL_TEXTURE_2D, texName[20]);
                     glEnable(GL_TEXTURE_GEN_S);//lo hace en x
                    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
                    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

                     glPushMatrix();


                        glTranslatef(10,12,0);


                     glPushMatrix();
                    glTranslatef(1, 3, 0);
                    glScaled(.5,.5,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                    //glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPushMatrix();
                   // glBindTexture(GL_TEXTURE_2D, texName[27]);
                    glTranslatef(1.5, 3.5, 0);
                    glScaled(.25,.25,0);
                    glColor3f(0.0,0.0,0.0);
                    glutSolidSphere(1,20,16);
                    glPopMatrix();
                    glPopMatrix();

    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y

           }

    }
}
void dibujaCrono() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable (GL_DEPTH);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);

    char b3[100];
    if (estadoMenu){

    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();

    }
    else if (win){
    glBindTexture(GL_TEXTURE_2D, texName[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 0, -.0005);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();
    sprintf(b3,  "%2d", (int) puntos);
    outputText(18.0,2.5,0,0.006, b3);


    }
    else if (loose){
    glBindTexture(GL_TEXTURE_2D, texName[8]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();


    }

    else
    {

    if (estadoNivel1){
    if (ventanaprincipal){
    glColor3ub(0,0,255);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(20, 0, -.0005);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();

    for (int i=1; i<=oportunidades;i++){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[4]);
    glTranslatef(15+i, 19, 0);
    glScaled(1,2,0);
    glutSolidTeapot(0.35);
    glPopMatrix();

    }

    //Dibuja mickey principal
    glPushMatrix();
    glTranslatef(xM,yM,0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1, 3, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPopMatrix();

    glColor3ub(255,0,255);
    sprintf(b3,  "Puntaje:%2d", (int) puntos);
    outputText(0.0,18,0,0.006+.00025, b3);
    dibujaVillano();

    //Cuerpo del mickey principal
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTranslatef(xM+1, yM+2.5, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
//wall
    glBindTexture(GL_TEXTURE_2D, texName[7]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glPushMatrix();
    glTranslatef(0, 11, 0);
    glScaled(2,10,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 15, 0);
    glScaled(10,4,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
   // glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(4, 2, 0);
    glScaled(2,12,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(9, 15, 0);
    glScaled(2,12,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(15, 4, 0);
    glScaled(12,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(17, 10, 0);
    glScaled(7,2,0);
    glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y



                }
                else if (adivinaP){

    glBindTexture(GL_TEXTURE_2D, texName[26]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
    glBindTexture(GL_TEXTURE_2D, texName[1]);

    sprintf(b3,  "%s", "Goofy");
    outputText(4.0,5,0,0.006, b3);
    sprintf(b3,  "%s", "Pinocho");
    outputText(8.5,5,0,0.006, b3);
    sprintf(b3,  "%s", "Donald");
    outputText(14.0,5,0,0.006, b3);
                }

                else if (reto){

glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
    glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y

    if (principiante){
            if (!vencido[0]&&colisionVillano[0]){
    //sprintf(b3,  "%s", "3+2");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[10]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "11");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "5");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[1]&&colisionVillano[1]){
    //sprintf(b3,  "%s", "9-4");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[11]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "5");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[2]&&colisionVillano[2]){
    //sprintf(b3,  "%s", "7/1");
    //outputText(10.0,13,0,0.01, b3);
     glBindTexture(GL_TEXTURE_2D, texName[12]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "1");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "7");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[3]&&colisionVillano[3]){
    glBindTexture(GL_TEXTURE_2D, texName[14]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   // sprintf(b3,  "%s", "2x2");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "9");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[4]&&colisionVillano[4]){
    //sprintf(b3,  "%s", "7+3");
    //outputText(10.0,13,0,0.01, b3);
     glBindTexture(GL_TEXTURE_2D, texName[15]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "9");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "10");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "8");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (intermedio){
    if (!vencido[0]&&colisionVillano[0]){
    glBindTexture(GL_TEXTURE_2D, texName[31]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "30+20");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "110");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "100");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "50");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[1]&&colisionVillano[1]){
    glBindTexture(GL_TEXTURE_2D, texName[32]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "90-45");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "45");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "60");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "44");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[2]&&colisionVillano[2]){
    glBindTexture(GL_TEXTURE_2D, texName[33]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "20/5");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "1");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "2");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[3]&&colisionVillano[3]){
    glBindTexture(GL_TEXTURE_2D, texName[34]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "20x20");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "900");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "600");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "400");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[4]&&colisionVillano[4]){
    glBindTexture(GL_TEXTURE_2D, texName[35]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "70+3");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "37");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "73");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "88");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (avanzado){
    if (!vencido[0]&&colisionVillano[0]){

    glBindTexture(GL_TEXTURE_2D, texName[46]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   // sprintf(b3,  "%s", "150+225");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "345");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "255");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "375");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[1]&&colisionVillano[1]){
    glBindTexture(GL_TEXTURE_2D, texName[47]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "990-44");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "946");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "926");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "911");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[2]&&colisionVillano[2]){
    glBindTexture(GL_TEXTURE_2D, texName[48]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "144/12");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "22");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "12");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "77");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[3]&&colisionVillano[3]){
    glBindTexture(GL_TEXTURE_2D, texName[49]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "24x24");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "536");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "516");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "576");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[4]&&colisionVillano[4]){
    glBindTexture(GL_TEXTURE_2D, texName[50]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "700+333");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "933");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "1033");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "833");
    outputText(14.0,5,0,0.008, b3);}
    }
        }
    }
    else if (estadoNivel2){
            if (ventanaprincipal){

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glPushMatrix();
    glTranslatef(10, -7, 0);
    glScaled(200,20,20);
    glutSolidCube(1.0);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 3, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 3, -.0005);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();

    //Dibuja mickey principal
    glPushMatrix();
    glTranslatef(xM,yM,0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1, 3, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPopMatrix();




    sprintf(b3,  "Puntaje:%2d", (int) puntos);
    outputText(0.0,18,0,0.006, b3);

    dibujaVillano();
    //Cuerpo del mickey principal
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTranslatef(xM+1, yM+2.5, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
      glPushMatrix();
    //glRotatef(z,0,0,0);
    for (int i=1; i<=oportunidades;i++){

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texName[4]);

    glTranslatef(15+i, 19, 0);
    glScaled(1,2,0);
 //   glColor3f(0.0,1.0,0.0);
    //glutSolidCube(1.0);
    glutSolidTeapot(0.5);

    glPopMatrix();

    }
    glPopMatrix();
    //wall
    glBindTexture(GL_TEXTURE_2D, texName[7]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(0, 5, 0);
    glScaled(10,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(5, 9, 0);
    glScaled(2,10,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(8, 13, 0);
    glScaled(8,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(18, 3, 0);
    glScaled(8,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(13, 5, 0);
    glScaled(2,6,0);
    glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y


    }
    else if (adivinaP){
    glBindTexture(GL_TEXTURE_2D, texName[25]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();

glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
  // glBindTexture(GL_TEXTURE_2D, texName[1]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

  glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y

    glBindTexture(GL_TEXTURE_2D, texName[1]);
    sprintf(b3,  "%s", "Daisy");
    outputText(4.0,5,0,0.006, b3);
    sprintf(b3,  "%s", "Tribilin");
    outputText(8.5,5,0,0.006, b3);
    sprintf(b3,  "%s", "Minnie");
    outputText(14.0,5,0,0.006, b3);
                }
    else if (reto){
glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    if (principiante){
            if (!vencido[5]&&colisionVillano[5]){
    glBindTexture(GL_TEXTURE_2D, texName[16]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "3+4");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "11");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "7");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[6]&&colisionVillano[6]){
   // sprintf(b3,  "%s", "6-4");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[19]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "2");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[7]&&colisionVillano[7]){
    //sprintf(b3,  "%s", "8/2");
    //outputText(10.0,13,0,0.01, b3);
     glBindTexture(GL_TEXTURE_2D, texName[17]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "1");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "3");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[8]&&colisionVillano[8]){
    glBindTexture(GL_TEXTURE_2D, texName[13]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();

   // sprintf(b3,  "%s", "9x9");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "90");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "66");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "81");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[9]&&colisionVillano[9]){
    glBindTexture(GL_TEXTURE_2D, texName[18]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();

   // sprintf(b3,  "%s", "6+3");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "10");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "9");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "11");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (intermedio){
    if (!vencido[5]&&colisionVillano[5]){
    glBindTexture(GL_TEXTURE_2D, texName[36]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "33+22");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "110");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "100");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "55");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[6]&&colisionVillano[6]){
    glBindTexture(GL_TEXTURE_2D, texName[37]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "80-45");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "35");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "60");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "44");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[7]&&colisionVillano[7]){
    glBindTexture(GL_TEXTURE_2D, texName[38]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "45/5");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "4");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "9");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[8]&&colisionVillano[8]){
    glBindTexture(GL_TEXTURE_2D, texName[39]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "30x20");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "900");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "60");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "600");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[9]&&colisionVillano[9]){
    glBindTexture(GL_TEXTURE_2D, texName[40]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "70+31");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "37");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "101");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "88");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (avanzado){
    if (!vencido[5]&&colisionVillano[5]){
    glBindTexture(GL_TEXTURE_2D, texName[51]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "250+225");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "345");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "255");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "475");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[6]&&colisionVillano[6]){
    glBindTexture(GL_TEXTURE_2D, texName[52]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "890-44");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "846");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "926");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "911");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[7]&&colisionVillano[7]){
    glBindTexture(GL_TEXTURE_2D, texName[53]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "120/60");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "66");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "2");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "77");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[8]&&colisionVillano[8]){
    glBindTexture(GL_TEXTURE_2D, texName[54]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "13x13");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "246");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "516");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "169");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[9]&&colisionVillano[9]){
    glBindTexture(GL_TEXTURE_2D, texName[55]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   // sprintf(b3,  "%s", "800+633");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "9333");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "1433");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "1833");
    outputText(14.0,5,0,0.008, b3);}
    }
        }

    }
    else if (estadoNivel3){
            if (ventanaprincipal){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 0, -.0005);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();


    //Dibuja mickey principal
    glPushMatrix();
    glTranslatef(xM,yM,0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1, 3, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[5]);
    glTranslatef(1.5, 3.5, 0);
    glScaled(.25,.25,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();
    glPopMatrix();

    sprintf(b3,  "Puntaje:%2d", (int) puntos);
    outputText(0.0,18,0,0.006, b3);
    dibujaVillano();
    //Cuerpo del mickey principal
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTranslatef(xM+1, yM+2.5, 0);
    glScaled(.5,.5,0);
    glutSolidSphere(1,20,16);
    glPopMatrix();

     for (int i=1; i<=oportunidades;i++){

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, texName[4]);

    glTranslatef(15+i, 19, 0);
    glScaled(1,2,0);
 //   glColor3f(0.0,1.0,0.0);
    //glutSolidCube(1.0);
    glutSolidTeapot(0.5);

    glPopMatrix();

    }
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texName[7]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    //glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    //glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

    glPushMatrix();
   // glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(0, 11, 0);
    glScaled(2,10,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(3, 15, 0);
    glScaled(10,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(4, 2, 0);
    glScaled(2,12,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(9, 15, 0);
    glScaled(2,12,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(15, 4, 0);
    glScaled(12,2,0);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texName[3]);
    glTranslatef(17, 10, 0);
    glScaled(7,2,0);
    glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y


    }
   else if (adivinaP){
  glBindTexture(GL_TEXTURE_2D, texName[24]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
   // glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();
   glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
    glBindTexture(GL_TEXTURE_2D, texName[1]);

    sprintf(b3,  "%s", "Peter");
    outputText(4.0,5,0,0.006, b3);
    sprintf(b3,  "%s", "Pluto");
    outputText(8.5,5,0,0.006, b3);
    sprintf(b3,  "%s", "Lucas");
    outputText(14.0,5,0,0.006, b3);
                }

                else if (reto){

glBindTexture(GL_TEXTURE_2D, texName[61]);
    glEnable(GL_TEXTURE_GEN_S);//lo hace en x
    glEnable(GL_TEXTURE_GEN_T);//mapea en y de forma automatica
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glPushMatrix();
    glTranslatef(10, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15, 5, -.00125);
    glScaled(3,2,0);
    //glBindTexture(GL_TEXTURE_2D, texName[2]);
    glutSolidCube(1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);//generador de vertices en x
    glDisable(GL_TEXTURE_GEN_T);//generador de vertices en y
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    if (principiante){
            if (!vencido[10]&&colisionVillano[10]){
    glBindTexture(GL_TEXTURE_2D, texName[28]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();

   // sprintf(b3,  "%s", "3+5");
   // outputText(10.0,13,0,0.01, b3);
   glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "11");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "8");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[11]&&colisionVillano[11]){
       glBindTexture(GL_TEXTURE_2D, texName[29]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "9-6");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "3");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[12]&&colisionVillano[12]){
    glBindTexture(GL_TEXTURE_2D, texName[30]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "10/5");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "1");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "2");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[13]&&colisionVillano[13]){
    glBindTexture(GL_TEXTURE_2D, texName[21]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "3x3");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "3");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "6");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "9");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[14]&&colisionVillano[14]){
    glBindTexture(GL_TEXTURE_2D, texName[20]);
   glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "7+3");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "9");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "10");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "8");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (intermedio){
    if (!vencido[10]&&colisionVillano[10]){
    glBindTexture(GL_TEXTURE_2D, texName[41]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "50+20");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "110");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "100");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "70");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[11]&&colisionVillano[11]){
   glBindTexture(GL_TEXTURE_2D, texName[42]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   // sprintf(b3,  "%s", "99-45");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "54");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "60");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "44");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[12]&&colisionVillano[12]){
    glBindTexture(GL_TEXTURE_2D, texName[43]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "100/5");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "1");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "4");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "20");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[13]&&colisionVillano[13]){
    glBindTexture(GL_TEXTURE_2D, texName[44]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "10x20");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "90");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "60");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "200");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[14]&&colisionVillano[14]){
    glBindTexture(GL_TEXTURE_2D, texName[45]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "66+3");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "37");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "69");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "88");
    outputText(14.0,5,0,0.008, b3);}

    }
    else if (avanzado){
    if (!vencido[10]&&colisionVillano[10]){
    glBindTexture(GL_TEXTURE_2D, texName[56]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "784+78");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "345");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "255");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "872");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[11]&&colisionVillano[11]){
    glBindTexture(GL_TEXTURE_2D, texName[57]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "642-132");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "510");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "926");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "911");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[12]&&colisionVillano[12]){
    glBindTexture(GL_TEXTURE_2D, texName[58]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "144/12");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "22");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "12");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "77");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[13]&&colisionVillano[13]){
    glBindTexture(GL_TEXTURE_2D, texName[59]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
    //sprintf(b3,  "%s", "24x24");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "536");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "516");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "576");
    outputText(14.0,5,0,0.008, b3);}
    if (!vencido[14]&&colisionVillano[14]){
   glBindTexture(GL_TEXTURE_2D, texName[60]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(2, 7, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(18, 7, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(18, 18, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(2, 18, 0);
    glEnd();
   // sprintf(b3,  "%s", "700+333");
    //outputText(10.0,13,0,0.01, b3);
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    sprintf(b3,  "%s", "933");
    outputText(4.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "1033");
    outputText(9.0,5,0,0.008, b3);
    sprintf(b3,  "%s", "833");
    outputText(14.0,5,0,0.008, b3);}

    }
        }


    }
    else if (puntaje){
            glBindTexture(GL_TEXTURE_2D, texName[9]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
  //  glVertex3f(-10.0f, -10.0f, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1.0f, 0.0f);
   // glVertex3f(10.0f, -10.0f, 0);
    glVertex3f(20, 0, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(20, 20, 0);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 20, 0);
    glEnd();

    }
    }
	glutSwapBuffers();
}


void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (opcion == 1){
    glOrtho(0, 20, 0, 20, 1, 20);}
    else{
      glFrustum(0, 20, 0, 20, 3, 40);
    }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 3, 0, 0, 0, 0.0, 1.0, 0.0);

}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}




