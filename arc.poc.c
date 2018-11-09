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
    printf("%lf",z/1000);
    return (z/1000);
}

/*double speed_left_wheel(double radius){
    return (radius-3.153)/0.02511;

}*/

double speed_wheel(double radius){
    double ratio =(-6.358/(radius+6.74076))+1.041;
    return (SPEEDC*ratio);  
}

void turn_degrees_arc(double degrees , double radius, int direction){
    printf("%lf\n",degrees);
    double sum = average();
    if(direction == 0){
        while(sum < ((75000*1.048)/90)*degrees){
            sum+=gyro_z();
            mrp(0,speed_wheel(radius),9);
            mrp(1,SPEEDC,15);
            printf("%lf\n",sum);
            //19.75in radius for left:600 & right:800
        }
    }
    else{
        while(sum > (((7500*1.048))*degrees)*-1){
            sum+=gyro_z();
            mrp(0,SPEEDC,15);
            mrp(1,speed_wheel(radius),9);
            //printf("%lf\n",sum);
            //19.75in radius for left:600 & right:800
        }
    }


}

