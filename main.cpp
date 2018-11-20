//#ifdef __APPLE__
//#include<GLUT/GLUT.h>
//#elseif
#include<gl/glut.h>
//#endif // __APPLE__
#include <Windows.h>
#include <Mmsystem.h>
#include <stack>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <time.h>;

using namespace std;

const float PI = 3.14;
const int treeNum = 4;
float ANGLE = 20, depth = 0;

double lastTime = 0, elapsedTime = 0, lastElapsedTime = 0;

float eyeX, eyeY, eyeZ, lookX, lookY, lookZ,
      upX, upY, upZ, fieldOfView, num = 0,
                                  incr = 0.1;
float lengthScale = 0.75;
float leng1 = 10;
float lineWidth = 5;

struct {
    char f = 'F';
    char k = 'K';
    string F = "D[++M[----X]]^BD[--M[++++X]]BD^B";
    string G = "[+K[----X][--X]^^^LK[----X][--X]^^^^K[----X][--X]]";
} Rules;
string axiom1 = "[F";
string axiom2 = "F";
string str = axiom1;
string strcrown = axiom2;

void push() {
    glPushMatrix();
}

void pop() {
    glPopMatrix();
}

//Rotate
void rotL() {
    glRotatef(ANGLE, 1, 0, 0);
    glRotatef(ANGLE*2, 0, 1, 0);
    glRotatef(ANGLE, 0, 0, 1);
}
void rotLSmaller() {
    glRotatef(1, 1, 0, 0);
    glRotatef(1*2, 0, 1, 0);
    glRotatef(1, 0, 0, 1);
}
void rotR() {
    glRotatef(-ANGLE, 1, 0, 0);
    glRotatef(ANGLE*2, 0, 1, 0);
    glRotatef(-ANGLE, 0, 0, 1);
}
void rotRSmaller() {
    glRotatef(-1, 1, 0, 0);
    glRotatef(4*2, 0, 1, 0);
    glRotatef(-1, 0, 0, 1);
}
void rotXminus90() {
    glRotatef(90, -1, 0, 0);
}
void rotXplus90() {
    glRotatef(90, 1, 0, 0);
}

void DrawLeaf() {
    glPushAttrib(GL_LIGHTING_BIT);
    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambient[4] = { 0.50, 1.0, 0.0 };
    GLfloat specular[4] = { 0.1, 1.0, 0.0 };
    GLfloat diffuse[4] = { 0.50, 1.0, 0.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

    float scale = 2;
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(-1/scale, 0/scale, -3/scale);
    glVertex3f(-1/scale, 4/scale, -3/scale);
    glVertex3f(-1/scale, 6/scale, -3/scale);
    glVertex3f(1/scale, 1/scale, -3/scale);
    glVertex3f(-1/scale, 0/scale, -3/scale);
    glVertex3f(0, 0/scale, 0);
    glEnd();
    glPopAttrib();
}

void DrawLine(float width,float leng, int colorMode) {
    glPushAttrib(GL_LIGHTING_BIT);
    if(colorMode == 0)
        glColor3ub(81, 114, 1);
    else if(colorMode == 1)
        glColor3ub(230, 195, 77);
    else if(colorMode == 2){
        glColor3ub(60, 30, 22);
    }

    GLfloat ambient[4] = {0.55, 0.27, 0.07};
    GLfloat specular[4] = {0.55, 0.27, 0.07};
    GLfloat diffuse[4] = {0.55, 0.27, 0.07};

    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glLineWidth(width*1.5);

    glBegin(GL_LINES);

    glVertex3f(0, 0, 0);
    glVertex3f(0, leng, 0);
    glEnd();

    glTranslatef(0, leng, 0);
	glPopAttrib();
}


void generateBody() {
    string strCurrent = Rules.F;
    cout << strCurrent;
    str += strCurrent;
}


void generateCrown() {
    leng1 = lengthScale*leng1;

    string strCurrent = "";

    for (int i = 0; i < strcrown.length(); i++) {
        char current =  strcrown.at(i);
        if (current == Rules.f || current == Rules.k) {
            strCurrent += Rules.G;
        }
        else
            strCurrent += current;
    }
    strcrown += strCurrent;
    str += strCurrent;
    cout <<  strCurrent << " " << strCurrent.length() << "\n";
}

void draw() {
    stack <char> S;

    for (int i = 0; i < str.length(); i++)
    {
        char current = str.at(i);
        if (current == 'F')
        {
            DrawLine(1.0*lineWidth, leng1, 0);
        }
        else if (current == 'B')
        {
            DrawLine(1.0*lineWidth, leng1, 0);
        }
        else if(current == 'L' || current == 'K')
        {
            DrawLine(0.35*lineWidth, leng1, 0);
        }
        else if(current == 'M')
        {
            DrawLine(0.2*lineWidth, leng1*0.2, 0);
        }
        else if (current == 'H')
        {
            DrawLine(1.0*lineWidth, leng1*0.8, 2);
        }
        else if (current == 'X')
        {
            DrawLeaf();
        }
        else if (current == 'D')
        {
            DrawLine(1.0*lineWidth, 2, 1);
        }
        else if (current == '+')
        {
            rotR();
        }
        else if (current == '-')
        {
            rotL();
        }

        else if (current == '*')
        {
            rotLSmaller();
        }
        else if (current == '^')
        {
            rotRSmaller();
        }
        else if (current == '[')
        {
            push();
            S.push(1);
        }
        else if(current == ']')
        {
            pop();
            S.pop();
        }
        else if(current == 'S')
        {
            rotXminus90();
        }
        else if(current == 'P')
        {
            rotXplus90();
        }
    }
}

void generateTree() {
    string h = "";
    for(int iter = 0; iter < treeNum; iter++ ) {
        for (int i = 0; i < 3; i++) {
            generateBody();
            cout<< "\n";
        }
        int branchNum = 1;
        for (int j = 0; j < 2; j++) {
            generateCrown();
            cout<< "\n";
        }
        leng1 = leng1*1.5;

        string addString ="";

        if(iter%2==0) {
            cout << iter << "Re nhanh\n";
            if(iter == 0)
                addString="][^^^";
            else
                addString="][S" + h + "PB^^^";
        }
        else {
            cout << iter << "tach cay\n";

            if (iter < treeNum - 1) {
                for (int i = 0; i < iter+1; i++)
                    h += "H";
                addString = "][S" + h;
                addString += "PB";
            }
        }

        str += addString ;
        strcrown = axiom2; //tach ve cay lien ke

    }
}

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (fieldOfView, 1.0, 1, 2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //tao view nhin
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);

    glPushAttrib(GL_LIGHTING_BIT);
    glPushMatrix();


    GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shininess[] = { 100.0f };

    glColor3ub(160, 25, 50);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBegin(GL_TRIANGLES);
    glVertex3f(-20,0,-20);
    glVertex3f(20,0,-20);
    glVertex3f(20,0,20);
    glVertex3f(-20,0,20);
    glVertex3f(-20,0,-20);
    glVertex3f(20,0,20);
    glEnd();

    draw();
    glPopMatrix();
    glPopAttrib();

    glutSwapBuffers();
    glutPostRedisplay();
}

void animate()
{
    //chuyen dong gio thoi
    if (lastTime == 0)
        lastTime = timeGetTime();

    elapsedTime = timeGetTime()-lastTime;

    // thay doi goc
    float numR = (float) rand()/RAND_MAX;


    if (ANGLE > 21.5) {
        if (numR < 0.5) {
            incr = -0.15;
        }
        else {
            incr = -0.1;
        }
    }
    else if (ANGLE < 18.5) {
        if (numR > 0.5) {
            incr = 0.15;
        }
        else {
            incr = 0.1;
        }
    }
    ANGLE += incr;


    if(elapsedTime-lastElapsedTime > 2000) {
        lastElapsedTime = elapsedTime;
    }
    elapsedTime = elapsedTime/5000;
    float t = (sin((elapsedTime*PI-PI/2))+1)/2;

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 113:			// q - Exit the program
            exit(0);
            break;
        case 119:			// w - Reset the camera
            fieldOfView = 45;
            eyeX = 150;
            eyeY = 100;
            eyeZ = 150;
            lookX = 0;
            lookY = 50;
            lookZ = 0;
            break;
        case 122:			// z - Zoom in
            fieldOfView -= 5;
            glutPostRedisplay();
            break;
        case 120:			// x - Zoom out
            fieldOfView += 5;
            glutPostRedisplay();
            break;
    }
}

void arrowKeyboard(int key, int x, int y){
    {
        switch(key){
        case GLUT_KEY_UP:
            lookY+=6.0;
            break;
        case GLUT_KEY_DOWN:
            lookY-=6.0;
            break;
        case GLUT_KEY_LEFT:
            lookX-=6.0;
            break;
        case GLUT_KEY_RIGHT:
            lookX+=6.0;
            break;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1280, 900);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Cay tre L System");

    fieldOfView = 40;
    eyeX = 250;
    eyeY = 100;
    eyeZ = 100;
    lookX = 0;
    lookY = 50;
    lookZ = 0;
    srand (time(NULL));
    num = (float) rand()/RAND_MAX;

    GLfloat lightP[4] = {2.0f, 5.0f, 5.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightP);

    GLfloat lightA[4] = {0.0f, 0.6f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightA);

    GLfloat lightS[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightS);

    GLfloat lightD[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightD);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightD);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKeyboard);
    glutIdleFunc(animate);

    glEnable(GL_DEPTH_TEST);
    if(str == axiom1)
        generateTree();

    glutMainLoop();
    return 0;
}
