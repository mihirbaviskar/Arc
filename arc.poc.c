    double sum = average();
    while(sum<(77000)*2){
        sum+=gyro_z();
        printf("%lf\n",sum);
        mrp(0,600,6);
        mrp(1,800,10);
        //19.75in radius
        //77000 is 90
    }
