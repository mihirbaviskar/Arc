#include <kipr/botball.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SPEEDC 800//820.68
#define LEFT 0
#define RIGHT 1
#define LIMITER 0.9525
//defines-----------------------------------------------------------------------------------

//end of gobal varaibles -===-=-=-=-=-=-==--=-=-=--------------------------=-=-=-=-=-=-=-=-=
double average();
void turn_degrees_arc(double,double,int);
double speed_wheel(double radius);
struct Wheel {
    double type;
    double speed;
    double ticks;
};
void tester();
void intialize();
void turn_degrees_arc_ellipse(double degrees , double rstart, double rend, int direction);
void turn_degrees_arc_ellipse2(double degrees , double rstart, double rend, int direction);
//double speed_right_wheel(double radius);
struct Wheel wheel1;
struct Wheel wheel2;
int main()
{
                            /*printf("Left:%lf\n",speed_wheel(12));
                            mrp(0,900,7500);
                            mrp(1,900*LIMITER,7500);
                            bmd(0);
                            bmd(1);
                            turn_degrees_arc(180,25,RIGHT);
                            printf("Left:%lf\n",speed_wheel(12));
                            printf("Ratio%lf\n", sqrt(29.7836/(12+1.99308)));
                            int x,y,z = 0; */
    turn_degrees_arc(90 , 5, LEFT);
    return 0;
}

double average(){
    double z, counter;
    for(counter=0; counter<=1000; counter++){
        z+=gyro_z();
    }
    printf("Average: %lf\n",z/1000);
    return (z/1000);
}
double speed_wheel(double radius) {
    double ratio =((-15.4162/((radius)+16.633))+(0.000165389*radius)+(1.02294));
    return (SPEEDC*ratio);
    printf("/t RATIO: %lf\n",ratio);
    printf("/t speed of other wheel: %lf\n",SPEEDC*ratio);
}
//-------------------------------------------NORMAL_ARC--------------------------------     !!!!
void turn_degrees_arc(double degrees , double radius, int direction){
    double bias = average(); 
    double sum = 0;
    double angle = (direction == 0) ? (((120000*1.03)/90)*degrees) : ((((120000*1.05)/90)*degrees)*-1);
    wheel1.type = (direction == 0) ? 0 : 1;
    wheel2.type = (direction == 0) ? 1 : 0;
    if ((direction == 0)) {
        while(sum <= angle){
            mrp(wheel1.type,speed_wheel(radius),9); //speed_wheel(radius)*(1/LIMITER),9);
            mrp(wheel2.type,SPEEDC,15);
            sum+=(gyro_z()-bias);
        }
    } 
    else {
    	while(sum >= angle){
            mrp(wheel1.type,speed_wheel(radius),9); //speed_wheel(radius)*(1/LIMITER),9);
            mrp(wheel2.type,SPEEDC,15);
            sum+=(gyro_z()-bias);
        }
    }
    	printf("Sum%lf\n",sum);
	printf("Bias:%lf\n",bias);
        printf("\t GMPC:%i\n",(gmpc(RIGHT)));

}

//**********************************************ARC_ELLIPSE******
void turn_degrees_arc_ellipse(double degrees , double rstart, double rend, int direction){
    cmpc(RIGHT);
    printf("%lf\n",degrees);
    double bias = average(); 
    double sum = 0;
    double real_gyro= 0;
    double radius = rstart;
    double radians_turned;
    double dist1 = 3;
    double dist2 = 7;
    double angle = (direction == 0) ? (((120000*1.03)/90)*degrees) : ((((120000*1.05)/90)*degrees)*-1);
    if (direction == 0) {
        while(sum <= angle){
            mrp(0,speed_wheel(radius),dist1);
            mrp(1,SPEEDC,dist2);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
	    	radians_turned = (sum/(120000))*3.14159/2;
	    	radius  = sqrt(((pow(rstart,4)*pow(tan(radians_turned),2)+pow(rstart,4))/(pow(rstart,2)+pow(rend,2)*pow(tan(radians_turned),2))));
            /*if((sum*90)/(120000)>=45){
                dist1 = (((((120000)/90)*degrees)/sum)*1.6)+3;
                dist2=8.5;
            }*/
        }
    } else {
        while(sum >= angle){
            mrp(0,SPEEDC,15);
            mrp(1,speed_wheel(radius)*LIMITER,9);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
	    radians_turned = -sum/(120000*1.05)*3.14159/180;
	    //radius  = sqrt(((percent-1)*(percent-1)*(rstart*rstart-rend*rend))+rend*rend);
	    radius  = sqrt(((pow(rstart,4)*pow(tan(radians_turned),2)+pow(rstart,4))/(pow(rstart,2)+pow(rend,2)*pow(tan(radians_turned),2))));

            //19.75in radius for left:600 & right:800
        
    }   
}
        printf("RSTART:%lf\n",rstart);
        printf("REND:%lf\n",rend);
        printf("\t GMPC:%i\n",(gmpc(RIGHT)));

}



//**************ELLIPSE IDEA THAT PROBABLY WONT WORK AND IS NOT VERY MATHEMATICAL*********
void turn_degrees_arc_ellipse2(double degrees , double rstart, double rend, int direction){
    cmpc(RIGHT);
    printf("%lf\n",degrees);
    double bias = average(); 
    double sum = 0;
    double real_gyro= 0;
    double radius = rstart;
    int degrees_turned;
    double mod;
    double multiplier=0.99;
    printf("%lf\n",multiplier);
    if(direction == 0){
        while(sum <= ((120000*1.12)/90)*degrees){
            mrp(0,SPEEDC*multiplier,9);
            mrp(1,SPEEDC,15);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
            degrees_turned = (-sum*90)/(120000*1.05);
            mod = degrees_turned % 10;
            printf("%lf\n",multiplier);
            if (mod == 0) {
            	multiplier = multiplier-0.01;
            }
			//printf("DEGREES:%lf RADIUS%lf\n",(sum*90)/(120000*1.12),radius);
            //19.75in radius for left:600 & right:800
        }
    }
    else{
        while(sum >= (((120000*1.05)/90)*degrees)*-1){
            mrp(0,SPEEDC,15);
            mrp(1,speed_wheel(radius)*LIMITER,9);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
	    degrees_turned = -sum/(120000*1.05)*3.14159/180;
	    //radius  = sqrt(((percent-1)*(percent-1)*(rstart*rstart-rend*rend))+rend*rend);
	    radius  = sqrt(((pow(rend,4)*pow(tan(degrees_turned),2)+pow(rstart,4))/(pow(rstart,2)+pow(rend,2)*pow(tan(degrees_turned),2))));

            //19.75in radius for left:600 & right:800
        }
        
    }   
        printf("RSTART:%lf\n",rstart);
        printf("REND:%lf\n",rend);
        printf("\t GMPC:%i\n",(gmpc(RIGHT)));

}
//TEster--------------------------------------------------------------------------------------
void tester () {
    while (1) {
		
        int x = gyro_x();
        int y = gyro_y();
        int z = gyro_z();
        console_clear();
        printf("x: %i      |   y: %i        |   z: %i      |\n",x,y,z);
        msleep(100);
     }
}
// class & struct fun ^w^ ----------------------------------------------------------------------
struct bot {
    struct wheelbot {
        int LEFT = 0;
        int RIGHT = 1;
        double ticks;
    };
    double speed;
    char name[6] = {"A","r","c","B","o","t"};
};
