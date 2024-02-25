/*STATS.H by Dietmar G. SCHRAUSSER (C) 2000*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
 
double pval, zval, euler=2.718281828182;
                                        
/*berechnung von fishers Z aus r*/
double Fi_Z (double r) 									
{   
   double FiZ; 		
   FiZ=0.5*log((1+r)/(1-r));
   return FiZ;   								
} 

/*berechnung von r aus fishers Z*/
double r_Fi_Z (double FiZ)
{
  double r;
  r=(pow(euler,(FiZ*2))- 1)/(pow(euler,(FiZ*2))+1);
  return r;
} 

/*berechnung von p aus z*/
double p_value(double zwert)
{
  double qw=fabsl(zwert);
  pval= qw*(0.0000380036+qw*(0.0000488906+qw*0.000005383));
  pval=1+qw*(0.049867347+qw*(0.021141006+qw*(0.0032776263+pval)));
  pval=0.5*pow(pval,-16);
  if(zwert<0)
  {
   pval=1-pval;
  }
  return pval;
} 

/*berechnung von p aus student t und n*/
double p_val_t(double tx, int n)/*übernimmt twert(tx) und n*/
{
 	double fx,w1,w2,w3,w4,ww,xx,yy,zz,n1,i,ij,nn1,nn2=1;
	
 	if(n/2 != floor(n/2))
    { 
      n=n+1;
    }
 	n1 = n, n = 1, w4 = tx, tx =pow(tx,2);
 	w1 = n1/(n1+1*tx), w2 = sqrt(1-w1);
 	nn1 =2*floor(n1/2)-n1+2;
 	pval = 1-w2, w3 = w1*w2/2;
 	for(i = nn1; i < n1; i = i + 2)
      {
      ij = i;
      if(n1 <= i || fabs(2/i*w3)<(0.00001*pval))
        {
         goto e;
        }
      pval = pval-2/i*w3, w3 = w3*w1*(nn2/i+1);
      }
	e:
  	pval = pval/2, n = n1, tx = w4;
  	if(tx < 0)
    {
      pval = 1-pval;
    }
   	xx = pval, yy = -5;
  	if(xx == 0) {goto g;}
    fx = (fabs(xx)), fx = log10(fx), yy = fx + yy;
   	if(fx >= 0)
   	{
     fx = floor(fx);
   	}
 	else
   	{
     fx = -1*(floor(fabs(fx)));
   	}
	zz = fx, fx = yy;
  	if(fx >= 0)
   	{
     fx = floor(fx);
   	}
 	else
   	{
     fx = -1*(floor(fabs(fx)));
   	}
  	yy = zz-fx-1;
    if(yy >= 19) {goto g;}
    if(yy < 0)
    { 
      xx = 0;
      goto g;
    }
  	if(zz >= 90)
    {
      xx = 1e-20,fx = zz, zz = zz-20;
    }
   	ww = fabs(xx*pow(10,-zz )), ww = floor(ww*pow(10,yy)+0.5);
   	ww = ww*(pow(10,zz))*(pow(10,-yy));
  	if(fx >= 90)
    {
      ww = 1e20;
    }
    if(xx >= 0)
    { 
      xx = ww;
    }
  	else
    {
      xx = ww * -1;
    }
    g:
  	pval = xx;
  	pval =fabs(pval);
	return pval;
}

/*berechnung von McNemar Chi*/
double mn_chi(long chib, long chic)
{
	double a,b, chi;        
    a = pow((chib - chic),2);
	b = (chic + chib);
    chi = a / b;
    return chi;
}    
    
/*berechnung von student t aus r*/
double t_r(double r, int n)
{
 	double t;
 	t=r*(sqrt(n-2))/(sqrt(1-pow(r,2)));
	t=fabs(t);
 	return t;
}
