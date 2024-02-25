/*FOC by Dietmar G. SCHRAUSSER (C) 2000*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 64 												/*globale feldgroessen def, n=64 leads max*/

void _err_msg (char *PszProgName); 								/*prozedur fehlermeldung und usage instruktion*/
void _head(struct _iobuf *stream);                               /*prozedur für kopfzeilen*/

char dbuffer [9],tbuffer [9];									/*buffer fuer time und date*/

main(int argc, char *argv[]) 									/*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *outStream,*logStream;						/*streams*/
       								
   float feld[SIZE],xValue = 0, xMax = -100, xMin=100, yf = 0;   
   int iLauf=0, jLauf=1;
     
   if (argc != 5)												/*was wenn keine oder zuwenig, zuviel argumente?*/
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
   
   /*def von input und outputdatei:
   argument 1:input; argument 2:output*/
   
   inStream = fopen( argv[1], "r" );
   outStream = fopen( argv[2], "w" ); 
   logStream = fopen( "foc.rep", "a+" ); 
   
   
   if (inStream == NULL)										/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[1]);
   		_err_msg(argv[0]);
	}
   
   _head(logStream);
   
   /*berechnung von yf*/
      
   for (jLauf = 1; jLauf <= atoi(argv[3]); jLauf++) 			/*jlauf: anzahl der fälle=argument 3*/ 
   {
   		for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1); iLauf++)   	/*ilauf: anzahl der leads=argument 4*/
   		{
   			fscanf(inStream,"%f", &feld[iLauf]);  					/*einlesen der werte x pro lead von instream*/
   		}	
   
   		for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1); iLauf++)
   		{
   			if (feld[iLauf] <= -100) feld[iLauf]= -100;					/*ERS auf -100*/
			if (xMax < feld[iLauf]) xMax = feld[iLauf];				/*find xmax*/
			if (xMin > feld[iLauf]) xMin = feld[iLauf];				/*find xmin*/
   		}
   		for (iLauf = 0 ;iLauf <= (atoi(argv[4]) - 1); iLauf++)
   		{
   			if(xMax > -100) 
				xValue += 1 - ( (feld[iLauf] - xMin) / (xMax - xMin) );               /*berechnung und summierung von 1-((xi-min)/(xmax-min))*/
			else 
				xValue += 0;										/*wenn max=0 +0*/
   		}
		
   		yf = xValue / ( atoi(argv[4]) - 1 ); 						/*berechnung von yf=x/n-1*/
   		printf("case%i\n", jLauf);  								/*bildschirmausgabe*/
   
		fprintf(outStream,"%f\n",yf);  								/* ausgabe in outstream*/ 
		fprintf(logStream,"case%i: xmax=%f yf=%f\n",jLauf,xMax,yf); /* ausgabe in logstream*/ 
		xValue = 0;
		xMax = -100, xMin = 100;										/*reset von 1-xi/xmax, xMax, xMin*/
    
   }
  
   printf("\nwriting file:\nfoc.rep\n%s",argv[2]);						/*bildschirmausgabe*/     
   fclose( inStream ); 
   fclose( outStream );
   fclose( logStream ); 
   return 0;
                      
}

/*allgemeine fehlerroutine*/

void _err_msg(char *pszProgName)
{
	printf("-----------------------------------------------------------\n");
	printf("Usage: foc [input] [output] n k\n ");
	printf(" [input]... Input File, Format ASCII tab. (eg. data.dat)\n");
	printf("  [output].. Output File\n");
	printf("   n........ number of cases\n");
	printf("   k........ number of leads\n");
	printf("-----------------------------------------------------------\n");
	printf("FOC by d.schrausser\n");
    printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	


void _head(struct _iobuf *logStream)

{
   printf("FOC by d.schrausser\n");						/*titelzeile bildschirmausgabe*/
   printf("compiled on %s @ %s\n\n", __DATE__, __TIME__);
   printf("computing yf:\n"); 
   fprintf(logStream,"\n************************************\n");	/*titelzeile in logstream*/ 
   fprintf(logStream,"Report: FOC \n");
   _strdate( dbuffer );
   fprintf(logStream,"%s ", dbuffer);
   _strtime( tbuffer );
   fprintf(logStream,"%s\n", tbuffer);
   fprintf(logStream,"------------------------------------\n");
}
