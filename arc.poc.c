


#include<stdio.h>
#include<math.h>


double speed_left_wheel(double radius);
double get_ratio(double radius);


int main() {
    double r = 10.8;
    printf(" Left: %lf\n Right %lf\n",speed_left_wheel(r), (speed_left_wheel(r)*get_ratio(r)));
    printf("Ratio %lf", get_ratio(r));
}

void turn_degrees(double degrees){
    double sum = average();
    while(sum<(((75000)*1.05)/90)*degrees){
        sum+=gyro_z();
        mrp(0,600,9);
        mrp(1,800,15);
        printf("%lf\n",sum);
        //19.75in
    } 
double speed_left_wheel(double radius){
    return (radius-3.153)/0.02511;
    
}
double get_ratio(double radius){
    return sqrt(24.8499/(radius-2.35752));
    
}
