#include <iostream>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#define pi 3.14 
#define UPDATE_TIME 25
//			Class : Ball
class Ball{
private:
	float x,y;
	float radius;
	float direction;
	float red,green,blue;
public:
	Ball();
	Ball(float,float,float,float);
	void setLocation(float,float);
	void setRadius(float);
	void setDirection(float);
	void setColor(float,float,float);
	float getX();
	float getY();
	//float getZ();
	float getR();
	float getDirection();
	float getRed();
	float getGreen();
	float getBlue();
};
Ball::Ball(){
	x=y=0;
	radius=0.2;
	direction=0;
	red=0.0;
	green=1.0;
	blue=0.0;
}
Ball::Ball(float a,float b,float c,float d){
	x=a;
	y=b;
	//z=c;
	radius=c;
	direction=d;
	red=0.0;
	green=1.0;
	blue=0.0;
}
void Ball::setLocation(float a,float b){
	x=a;
	y=b;
}
void Ball::setRadius(float a){
	radius=a;
}
void Ball::setDirection(float a){
	direction=a;
}
void Ball::setColor(float r,float g,float b){
	red=r;
	green=g;
	blue=b;
}
float Ball::getX(){
	return x;
}
float Ball::getY(){
	return y;
}
/*float Ball::getZ(){
	return z;
}*/
float Ball::getR(){
	return radius;
}
float Ball::getDirection(){
	return direction;
}
float Ball::getRed(){
	return red;
}
float Ball::getGreen(){
	return green;
}
float Ball::getBlue(){
	return blue;
}
/*
			Class Ball Ends
*/

std::vector<Ball> v;
Ball b;
void drawBalls(){
	for(int i=0,num=v.size();i<num;++i){
		glColor3f(v[i].getRed(),v[i].getGreen(),v[i].getBlue());
		if(i==0)
  		  	glTranslatef(v[i].getX(), v[i].getY(),0.0);
    	else
    		glTranslatef(v[i].getX()-v[i-1].getX(), v[i].getY()-v[i-1].getY(),0.0);
    	glutSolidSphere(v[i].getR(),100, 100);
    }
}

void update(int value){
	for(int i=0,n=v.size();i<n;++i){
		if((v[i].getX()+0.01*cos(v[i].getDirection())>0.9)||(v[i].getY()+0.01*sin(v[i].getDirection())>0.9)||(v[i].getX()+0.01*cos(v[i].getDirection())<-0.9)||(v[i].getY()+0.01*sin(v[i].getDirection())<-0.9)){
			// Generating 2 new Balls with half demenions
			v[i].setRadius(v[i].getR()/2);
			b=v[i];
			v[i].setDirection(v[i].getDirection()+pi);
			b.setDirection(v[i].getDirection()+pi+1.5);
			v.push_back(b);
		}
		v[i].setLocation(v[i].getX()+0.01*cos(v[i].getDirection()),v[i].getY()+0.01*sin(v[i].getDirection()));
	}
	glutPostRedisplay();
	glutTimerFunc(UPDATE_TIME, update, 0);
}

void initBall(){
	Ball b;
	//red
	b.setLocation(0.0,0.0);
	b.setColor(1.0,0.0,0.0);
	b.setDirection(1.4);
	v.push_back(b);
	//green
	b.setLocation(0.4,0.4);
	b.setColor(0.0,1.0,0.0);
	b.setDirection(2.6);
	v.push_back(b);
	//blue
	b.setDirection(1.3);
	b.setLocation(-0.4,0.4);
	b.setColor(0.0,0.0,1.0);
	v.push_back(b);
	//yellow
	b.setDirection(2.2);
	b.setLocation(0.1,0.1);
	b.setColor(1.0,1.0,0.0);
	v.push_back(b);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    drawBalls();
    glutSwapBuffers();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Ball");
	initBall();
	glutDisplayFunc(display);
	glutTimerFunc(UPDATE_TIME, update, 0);
	glutMainLoop();
	return 0;
}