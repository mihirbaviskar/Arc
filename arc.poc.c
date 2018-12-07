#include <kipr/botball.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SPEEDC 800
#define LEFT 0
#define RIGHT 1

int average();
void turn_degrees_arc(double,double,int);
double speed_wheel(double radius);
//double speed_right_wheel(double radius);

int main()
{
    //printf("Left:%lf\n",speed_wheel(12));
    turn_degrees_arc(90,12,RIGHT);
    /*printf("Left:%lf\n",speed_wheel(12));
    printf("Ratio%lf\n", sqrt(29.7836/(12+1.99308)));*/
    //int x,y,z = 0;
    /*
    while (1) {

        x = gyro_x();
        y = gyro_y();
        z = gyro_z();
        console_clear();
        printf("x: %i      |   y: %i        |   z: %i      |\n",x,y,z);
        msleep(100);
    }*/
    return 0;
}

int average(){
    double z;
    int counter;
    for(counter=0; counter<=1000; counter++){
        z+=gyro_z();
        //printf("counter:%i  |  %lf\n",counter,z);
    }
    printf("%lf\n",z/1000);
    return (z/1000);
}

double speed_wheel(double radius){
    double ratio =(-6.4/((radius/2.54)+6.30))+1.041;// - 6.358  6.74076
    return (SPEEDC*ratio);  
}
double speed_wheel2(double radius) {
    double ratio =((-23.0757/(radius+20.6761))-(0.00229346*radius)+(1.22057));
    return (SPEEDC*ratio);
    printf("/t RATIO: %lf\n",ratio);
}

void turn_degrees_arc(double degrees , double radius, int direction){
    cmpc(RIGHT);
    printf("%lf\n",degrees);
//    double sum = 2*average();
    double bias = average(); 
    double sum = 0;
    double real_gyro= 0;
    double counter = 0;
    double last_gyro = 0;
    
    if(direction == 0){
        while(sum <= ((75000*1.12)/90)*degrees){
            mrp(0,speed_wheel2(radius),9);//speed_wheel(radius)*(1/LIMITER),9);
            mrp(1,800,15);
            //printf("%lf\n",sum);
            //printf("%lf\n",sum-last_gyro);
            last_gyro = sum;
            counter++;
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
            //19.75in radius for left:600 & right:800
        }
    }
    else{
        while(sum <= (((75000*1.05)/90)*degrees)){
            mrp(0,SPEEDC,15);
            mrp(1,speed_wheel2(radius)*LIMITER,9);
            //printf("%lf\n",sum);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
            //19.75in radius for left:600 & right:800
        }
        
    }   
	printf("Bias:%lf\n",bias);
        printf("Average Gyro Turn%lf\n",(sum/counter));
        printf("\t GMPC:%i\n",(gmpc(RIGHT)));

}



/* ------------------
(sum / 75000*1.12)
0  ———————————————— 1
sum=0    sum1/75000*1.12
rmax = 6
rmin = 3
diff = 3
radius = rmax
radius = rmax - ( sum1/75000*1.12 ) * diff

radius = rmax - ( sum1/75000*1.12 ) * 3

--------------------- */



void turn_degrees_arc_ellipse(double degrees , double rstart, double rend, int direction){
    cmpc(RIGHT);
    printf("%lf\n",degrees);
    double bias = average(); 
    double sum = 0;
    double real_gyro= 0;
    double counter = 0;
    double last_gyro = 0;
    double radius = rstart;
    double diff = rstart - rend;
    double degrees_turned;
    if(direction == 0){
        while(sum <= ((120000*1.12)/90)*degrees){
            mrp(0,speed_wheel2(radius),9);
            mrp(1,SPEEDC,15);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
            //radius = rmax - diff*(sum/(((75000*1.12)/90)*degrees));
	    //radius  = rmax - (sqrt(((45*percent*percent)/9)+4)*diff-2);
	    degrees_turned = sum/(120000*1.12)*3.14159/180;
	    radius  = sqrt(((pow(rend,4)*pow(tan(degrees_turned),2)+pow(rstart,4))/(pow(rstart,2)+pow(rend,2)*pow(tan(degrees_turned),2))));

            //19.75in radius for left:600 & right:800
        }
    }
    else{
        while(sum <= (((120000*1.05)/90)*degrees)){
            mrp(0,SPEEDC,15);
            mrp(1,speed_wheel2(radius)*LIMITER,9);
            real_gyro = gyro_z()-bias;
            sum+=real_gyro;
	    degrees_turned = -sum/(120000*1.05)*3.14159/180;
	    //radius  = sqrt(((percent-1)*(percent-1)*(rstart*rstart-rend*rend))+rend*rend);
	    radius  = sqrt(((pow(rend,4)*pow(tan(degrees_turned),2)+pow(rstart,4))/(pow(rstart,2)+pow(rend,2)*pow(tan(degrees_turned),2))));

            //19.75in radius for left:600 & right:800
        }
        
    }   
        printf("Bias:%lf\n",bias);
        printf("Average Gyro Turn%lf\n",(sum/counter));
        printf("\t GMPC:%i\n",(gmpc(RIGHT)));

}


