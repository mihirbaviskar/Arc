
    void turn_degrees(double degrees){
    double sum = average();
    while(sum<(((75000)*1.05)/90)*degrees){
        sum+=gyro_z();
        mrp(0,600,9);
        mrp(1,800,15);
        printf("%lf\n",sum);
        //19.75in
    } 


