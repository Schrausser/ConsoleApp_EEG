/*xCOR by Dietmar G. SCHRAUSSER (C) 2000*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stats.h"
 
#define SIZE1 50 /*globale feldgroessen def, k=SIZE=vnar max*/ 
#define SIZE2 200 /*globale feldgroessen def, n=SIZE=n max*/ 

void _err_msg (char *PszProgName); /*prozedur fehlermeldung und usage instruktion*/
void _head(struct _iobuf *stream); /*prozedur für kopfzeilen*/

char dbuffer [9],tbuffer [9];
 
main(int argc, char *argv[]) /*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *outStream, *logStream;/*streams*/
       								
   float feld[SIZE1][SIZE2]; 
   double sumx=0, sumy=0, sxsum=0, sysum=0, mx=0, my=0, sx=0, sy=0, cov=0, corr=0;
   double tr=0, pr=0;
   int  nLauf=0, kLauf=0, Lauf=0, i;
   
   if (argc != 5)/*was wenn keine oder zuwenig, zuviel argumente?*/
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
   
   inStream = fopen (argv[1], "r");  
   outStream = fopen (argv[2], "w");
   logStream = fopen( "xcor.rep", "a+" );
   
   if (inStream == NULL)/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[1]);
   		_err_msg(argv[0]);
	} 
   
   
   _head(logStream);
   
     
   /*einlesen der werte*/
   for (nLauf = 1; nLauf <= atoi(argv[3]); nLauf++)/*nlauf: anzahl der fälle=argument 3*/ 
   {
   		for (kLauf = 0; kLauf <= (atoi(argv[4]) - 1); kLauf++)/*klauf: anzahl der leads=argument 4*/
   		{													   	
   		    
   			fscanf(inStream,"%f", &feld[kLauf][nLauf]);/*einlesen der werte x pro lead von instream*/ 
   		}
   	}
   
   	/*berechnen aller r kombinationen*/
   	for (Lauf = 1; Lauf <= (atoi(argv[4]) - 1); Lauf++)/*lauf: geht k-1 mal*/ 
   	{
    	for (kLauf = 0; kLauf <= (atoi(argv[4]) - (Lauf +1)); kLauf++)/*klauf: anzahl der variablen=argument 4*/
   		{													   	 
   			for (i=1; i <=2; i++)/*2 laeufe zur summierung für s und cov*/
			{
				for (nLauf = 1; nLauf <= atoi(argv[3]); nLauf++)/*nlauf: anzahl der fälle=argument 3*/ 
   				{
   					switch(i)
					{
					case 1:/*summen berechnung*/ 	
						sumx += feld[kLauf][nLauf];
						sumy += feld[kLauf+Lauf][nLauf];
					break;
					
					case 2:/*s, cov berechnung*/
						sxsum += (pow (feld[kLauf][nLauf] - mx, 2));
						sysum += (pow (feld[kLauf+Lauf][nLauf] - my, 2));
						cov += ((feld[kLauf][nLauf] - mx) * (feld[kLauf+Lauf][nLauf] - my));
						
					break;

					}
				}
				/*berechnung der mittelwerte*/
				mx = sumx / atoi(argv[3]); 
				my = sumy / atoi(argv[3]);
				/*fprintf(logStream,"sum %i = %.2f\n", kLauf+1, sumx);
				fprintf(logStream,"sum %i = %.2f\n", (kLauf+Lauf)+1, sumy);
				fprintf(logStream,"mean %i = %.2f\n", kLauf+1, mx);
				fprintf(logStream,"mean %i = %.2f\n", (kLauf+Lauf)+1, my);*/
				sumx=0; sumy=0;
			}
			/*berechnung von r*/
			sx = sqrt(sxsum / atoi(argv[3]));
			sy = sqrt(sysum / atoi(argv[3]));
			/*fprintf(logStream,"std %i = %.2f\n", kLauf+1, sx);
			fprintf(logStream,"std %i = %.2f\n", (kLauf+Lauf)+1, sy);*/
			sxsum=0, sysum=0; 
			cov = cov /atoi(argv[3]);
			corr = cov / (sx * sy);	cov=0;
			/*fprintf(logStream,"r = %.2f\n", corr);*/
			
			/*berechnung von t und p*/
			tr = t_r(corr, atoi(argv[3]));
			/*fprintf(logStream,"t = %.2f\n", tr);*/
			pr = p_val_t(tr, atoi(argv[3])); pr = pr * 2; /*2 seitiges sig niveau*/
			if (pr <= 0) pr = 0.001;
			
			/*ausgabe der werte*/
			fprintf(outStream,"%f\t%f\t%f\n",corr, tr, pr);
			fprintf(logStream,"Pearson correlation %i with %i ( r = %.2f, p < %.3f )\n", kLauf+1, (kLauf+Lauf)+1, corr, pr);
		}	
		/*resets*/
		sumx=0; mx=0; sx=0; sxsum=0; sumy=0; my=0; sy=0; sysum=0; cov=0; corr=0; tr=0; pr=0;	
   		
   	}
   		
   printf("\nwriting file:\nxcor.rep\n%s",argv[2]);	/*bildschirmausgabe*/     
   fclose( inStream ); 
   fclose( outStream );
   fclose( logStream );
   return 0;	
 
}

/*allgemeine fehlerroutine*/

void _err_msg(char *pszProgName)
{
	printf("-----------------------------------------------------------\n");
	printf("Usage: xcor [input] [output] n k\n ");
	printf(" [input]..... Input File, Format ASCII tab. (eg. data.dat)\n");
	printf("  [output].... Output File\n");
	printf("   n.......... number of cases\n");
	printf("   k.......... number of variables\n");
	printf("-----------------------------------------------------------\n");
	printf("xCOR by d.schrausser\n");
    printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

/*titelzeile bildschirmausgabe, Logfile*/

void _head(struct _iobuf *logStream)

{
   printf("xCOR by d.schrausser\n");						
   printf("compiled on %s @ %s\n\n", __DATE__, __TIME__);
   printf("computing...\n"); 
   fprintf(logStream,"\n************************************\n");	
   fprintf(logStream,"Report: xCOR \n");
   _strdate( dbuffer );
   fprintf(logStream,"%s ", dbuffer);
   _strtime( tbuffer );
   fprintf(logStream,"%s\n", tbuffer);
   fprintf(logStream,"------------------------------------\n");
}
