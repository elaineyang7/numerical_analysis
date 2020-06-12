#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define G 38.925
#define mu1 G*0.6897
#define mu2 G*0.20255
#define x1 -0.0509
#define y1 0.0
#define x2 0.17339
#define y2 0.0
#define n 1

double dist(double p1, double q1, double p2, double q2)
{
    double D;
    
    D=sqrt(pow(p1-p2,2)+pow(q1-q2,2));
    
    return D;
}

double func(int m, double w[])
{
    double A;
    double r=dist(w[1],w[2],0,0);
    double r1=dist(w[1],w[2],x1,y1);
    double r2=dist(w[1],w[2],x2,y2);
    if(m==1)
    {
        A=w[3];
    }
    if(m==2)
    {
        A=w[4];
    }
    if(m==3)
    {
        A=2*n*w[4]+n*n*w[1]-mu1*(w[1]-x1)/pow(r1,3)-mu2*(w[1]-x2)/pow(r2,3);
    }
    if(m==4)
    {
        A=-2*n*w[3]+n*n*w[2]-mu1*w[2]/pow(r1,3)-mu2*w[2]/pow(r2,3);
    }
    
    return (A);
}

main()
{
    FILE *output;
    output=fopen("ex2.txt", "wt");
    
    double a=0.0;
    double b=50.0;
    int N=4000,m=4;
    double t, h, theta_b, z,r;
    double R,V,A,H,E;
    double r1,r2,cJ;
    double w[5], v1[5], v2[5], v3[5], v4[5];
    double k1[5],k2[5],k3[5],k4[5];
    int i, j;
    
    h=(b-a)/(double)(N);
    t=a;
    
    theta_b=atan2(w[2],w[1]);
    
    w[1]=0.7048;
    w[2]=0.0;
    w[3]=0.0;
    w[4]=sqrt((mu1+mu2)/w[1]);
    
    //   fprintf(output, "%f %f %f %f %f\n", t, w[1], w[2], w[3], w[4]);//
    
    for(i=1; i<=N; i++)
    {
        for(j=1; j<=m; j++)
        {
            k1[j]=h*func(j,w);
            v1[j]=w[j]+0.5*k1[j];}
            
       for(j=1;j<=m;j++){
         k2[j]=h*func(j,v1);
         v2[j]=w[j]+0.5*k2[j];}
         
          for(j=1; j<=m; j++)
        { k3[j]=h*func(j, v2);
           v3[j]= w[j]+k3[j];}
        
        for(j=1; j<=m; j++)
        {
            k4[j]=h*func(j,v3);
        }
        
        for(j=1; j<=m; j++)
        {
            w[j]=w[j]+(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6.0;
        }
        
        t=t+h;
        r=dist(w[1],w[2],0,0);
        r1=dist(w[1],w[2],x1,y1);
        r2=dist(w[1],w[2],x2,y2);
            cJ=-w[3]*w[3]-w[4]*w[4]+w[1]*w[1]+w[2]*w[2]+2*mu1/r1+2*mu2/r2;
            fprintf(output, "%f %f %f %f %f %f %f\n", t, w[1], w[2], w[3],w[4],r,cJ);
        }
    fclose(output);
    system("pause");
}
