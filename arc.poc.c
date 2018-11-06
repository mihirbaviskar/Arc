


#include<stdio.h>
#include<math.h>

void turn_degrees(double degrees,double radius);
double speed_left_wheel(double radius);
double get_ratio(double radius);


int main() {
    double r = 10.8;
    printf(" Left: %lf\n Right %lf\n",speed_left_wheel(r), speed_right_wheel(r));
}

double speed_left_wheel(double radius){
    return (radius-3.153)/0.02511;
    
}

double speed_right_wheel(double radius){
    double ratio =  sqrt(24.8499/(radius-2.35752));
    return (speed_left_wheel(radius)*ratio);
    
}

void turn_degrees(double degrees, double radius){
    double sum = average();
    while(sum<(((75000)*1.05)/90)*degrees){
        sum+=gyro_z();
        mrp(0,speed_left_wheel(radius),9);
        mrp(1,speed_right_wheel(radius),15);
        printf("%lf\n",sum);
        //19.75in radius for left:600 & right:800
    }
}

