/*dis by Dietmar G. SCHRAUSSER (C) 2000*/

#include <stdio.h>
#include <stdlib.h>


#define SIZE 27 												/*globale feldgroessen def, n=SIZE leads max*/

 									

main(int argc, char *argv[]) 									/*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *outStream;									/*streams*/
       								
   float dis[SIZE][SIZE], wight[SIZE][SIZE], dis_tot=0;   
   int run=1, iLauf=0, jLauf=0;
   
   inStream = fopen (argv[1], "r");  
   outStream = fopen (argv[2], "w");
   
   /*berechnung von gij*/
   while (run <= 4)
   {   
    for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1 ); iLauf++) 			/*jlauf: anzahl der leadsi=argument 4*/ 
    {
   		for (jLauf = 0; jLauf <= (atoi(argv[4]) - 1 ); jLauf++)   	/*ilauf: anzahl der leadsj=argument 4*/
   		{
   			switch(run)
   			{
   				case 1:
   					fscanf(inStream,"%f", &dis[iLauf][jLauf]); 		/*einlesen der distanzwerte von instream*/ 
   					break; 
   				
   				case 2:
   			        if (iLauf != jLauf)
   			        { 
   					dis_tot += 1/dis[iLauf][jLauf];  							/*sum(1/dij)*/
   					}
   					break; 
   				
   				case 3: 
   					if (iLauf != jLauf)
   					{
   					wight[iLauf][jLauf] = (1/dis[iLauf][jLauf])/dis_tot;    	/*gij*/ 
   					printf("wight%i%i\n", iLauf+1, jLauf+1 );
   					}
   					break; 
   					
   				case 4:                                                       /* ausgabe in outstream*/
   					if (iLauf != jLauf)
   					{
   					fprintf(outStream,"d%i%i=%f ",iLauf+1,jLauf+1,dis[iLauf][jLauf]);  								 
   					fprintf(outStream,"g%i%i=%f\n",iLauf+1,jLauf+1,wight[iLauf][jLauf]);
   					}
   					break;
   			}			
   		}
   	 }
   	run++;	
    }
   	
   	fprintf(outStream,"dis_tot=%f",dis_tot);
   	
     	       
   fclose( inStream ); 
   fclose( outStream );
    
   return 0;
                      
}

