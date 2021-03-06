#include "cube.hpp"
#include <math.h>
#include <iostream>


//konstruktor
cube :: cube(double width, double height, double depth){
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->hit = false;
	this->movement = false; 	
}

void cube :: draw(){

    glPushMatrix();

    //ako je pritisnuto odgovarajuce dugme vrednost movement=true
    //treba azurirati centre rotacije kocke i centre kocke kako bi se pokret
    //identicno mogao izvoditi u svakom delu scene
    if(movement){
    	Xcenter_of_rotation += increase_X;
    	Ycenter_of_rotation += increase_Y;
    	Zcenter_of_rotation += increase_Z;


    	//glTranslatef(increase_X/translate_for, increase_Y/translate_for, increase_Z/translate_for);
    	Xcenter = Xcenter + increase_X ;
    	Ycenter = Ycenter + increase_Y ;
    	Zcenter = Zcenter + increase_Z ;

    }
    
    //ako smo pritisnuli dugme koje izaziva udarac vrednost promenljive hit=true
    //udarac se sastoji od rotacije kocke oko neke tacke
    //rotacija oko tacke: translacija u tacku + rotacija + vracanje translacije u
    //koordinatni pocetak
    if(hit){
    	glTranslatef(Xcenter_of_rotation , Ycenter_of_rotation + 0.1, Zcenter_of_rotation);
        glRotatef(rotate_for , X_axes, 0, Z_axes);
        glTranslatef(-Xcenter_of_rotation, -Ycenter_of_rotation -0.1, -Zcenter_of_rotation);
        
    }

     	 
    //iscrtavanje koceke
    glTranslatef(global_Xcenter , global_Ycenter, global_Zcenter);
    glRotatef(active_angle , 0, 1, 0);
    glTranslatef(-global_Xcenter, -global_Ycenter, -global_Zcenter);


    glTranslatef(Xcenter, Ycenter, Zcenter);
	glColor3f(R, G, B);

    //igrac staje u gard ako mu je receno da stane u gard ali tek kad savije ruke
    if(guard and rotate_end){
        glScalef(1,0.5,1);   
    }
    
    glScalef(width, height, depth);

    //svaka kocka odbija razlicitu svetlost pa se ovde definisu koeficijenti odbijanja
    GLfloat ambient_coeffs0[] = { (GLfloat)(R*7), (GLfloat)(G*5), (GLfloat)(B*5), 1 };
    GLfloat diffuse_coeffs0[] = { (GLfloat)(R*5), (GLfloat)(G*2), (GLfloat)(B*2), 1 };
    GLfloat specular_coeffs0[] = { 1, 1, 1, 1 };
    GLfloat shininess = 30;

    //primena materijala na kocku koja se iscrtava
    glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient_coeffs0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse_coeffs0);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  specular_coeffs0);
    glMaterialf(GL_FRONT,  GL_SHININESS, shininess);
    
    glutSolidCube(1);

    glLineWidth(0.5);
   
    glPopMatrix();
    

}

//za koliko treba pomeriti kocku
void cube :: cube_set_translate(double increase_X,double increase_Y,double increase_Z){
	this->increase_X = increase_X;
	this->increase_Y = increase_Y;
	this->increase_Z = increase_Z;

}

//postavljanje centra rotacije
void cube :: cube_set_rotate(double Xcenter_of_rotation,double Ycenter_of_rotation, double Zcenter_of_rotation){

	this->Xcenter_of_rotation = Xcenter_of_rotation;
	this->Ycenter_of_rotation = Ycenter_of_rotation;
	this->Zcenter_of_rotation = Zcenter_of_rotation;

}

//postavljanje vrednosti promenljivih koje odredjuju boju
void cube :: cube_set_color(double R, double G, double B){
	this->R = R;
	this->G = G;
	this->B = B;
}

//postavljen dok su neke promenljive bile private, sad su public :(
void cube :: cube_set_center(double Xcenter,double Ycenter,double Zcenter){
	this->Xcenter = Xcenter;
	this->Ycenter = Ycenter;
	this->Zcenter = Zcenter;
}

//postavljanje dimenzija kocke
void cube :: cube_set_value(double width,double height,double depth){
	this->width = width;
	this->height = height;
	this->depth = depth;
}

//destruktor
cube :: ~cube(){};