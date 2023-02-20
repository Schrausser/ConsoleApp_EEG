/*FLOC by Dietmar G. SCHRAUSSER (C) 2000*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define SIZE 30 												/*globale feldgroessen def, n=SIZE=leads max*/

void _err_msg (char *PszProgName); 								/*prozedur fehlermeldung und usage instruktion*/
void _head(struct _iobuf *stream);                               /*prozedur für kopfzeilen*/

char dbuffer [9],tbuffer [9];
 
main(int argc, char *argv[]) 									/*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *outStream, *disStream, *logStream; 			/*streams*/
       								
   float dis[SIZE][SIZE]; 
   float wight[SIZE][SIZE];
   float feld[SIZE], locA=0, xValue=0; 
   float xMax = -100, xMin=100;
   float yf = 0, yloc = 0, loc_max=0, dis_tot=0;   
   int run=1, iLauf=0, jLauf=0, kLauf=0;
   
   if (argc != 6)												/*was wenn keine oder zuwenig, zuviel argumente?*/
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
   
   inStream = fopen (argv[1], "r");  
   outStream = fopen (argv[2], "w");
   disStream = fopen( argv[5], "r" );
   logStream = fopen( "floc.rep", "a+" );
   
   if (inStream == NULL)										/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[1]);
   		_err_msg(argv[0]);
	} 
   
   if (disStream == NULL)										/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[5]);
   		_err_msg(argv[0]);
	}
   
   _head(logStream);
   
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
   					fscanf(disStream,"%f", &dis[iLauf][jLauf]); 		/*einlesen der disdanzwerte von instream*/ 
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
   					printf("wight:%i%i\n", iLauf+1, jLauf+1 );
   					}
   					break; 
   					
   				case 4:                                                       /* ausgabe in outstream*/
   					if (iLauf != jLauf)
   					{
   					fprintf(logStream,"d%i%i=%f ",iLauf+1,jLauf+1,dis[iLauf][jLauf]);  								 
   					fprintf(logStream,"g%i%i=%f\n",iLauf+1,jLauf+1,wight[iLauf][jLauf]);
   					}
   					break;
   			}			
   		}
   	 }
   	run++;	
    }
   	
   	run=1;
   	fprintf(logStream,"\ndis_tot=%f\n\n",dis_tot);
    
    /*berechnung von yf, yloc*/
   printf("\ncomputing yf, yloc:\n");
      
   for (kLauf = 1; kLauf <= atoi(argv[3]); kLauf++) 				/*klauf: anzahl der fälle=argument 3*/ 
   {
   while (run <= 4)
   {
   		for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1); iLauf++)
   		{													   	/*ilauf: anzahl der leads=argument 4*/
   		    switch(run)
   			{
   		    	case 1:
   				fscanf(inStream,"%f", &feld[iLauf]);  				/*einlesen der werte x pro lead von instream*/ 
   				break; 
   		
   			    case 2:
                if (feld[iLauf] <= -100) feld[iLauf]= -100;					/*ERS auf -100*/
				if (xMax < feld[iLauf]) xMax = feld[iLauf];	       /*find xmax*/
				if (xMin > feld[iLauf]) xMin = feld[iLauf];       /*find xmin*/
				break;
   		    
   		    	case 3:
   				if(xMax > -100) 
					xValue += 1 - ( (feld[iLauf] - xMin) / (xMax - xMin) );          /*berechnung und summierung von 1-((xi-min)/(xmax-min))*/
				else 
					xValue += 0;
				break;											   /*wenn max=0 +0*/
   			
   			    
   			    case 4:
   			    for (jLauf = 0; jLauf <= (atoi(argv[4]) - 1 ); jLauf++)   	/*jlauf: anzahl der leads=argument 4*/
   				{	
   			     if (iLauf != jLauf)
   			     {
   			     locA += ( ((1-((feld[iLauf]-xMin)/(xMax-xMin)))  * (wight[iLauf][jLauf] * ((1-((feld[jLauf]-xMin)/(xMax-xMin)))))) );
   			     loc_max += wight[iLauf][jLauf]; 					/*maximaler floc 0 sum aller gewichte zu xi*/ 
   			     }
   			    }
   			    locA = locA / loc_max ;
   			    break;
   			 }
   		yloc += locA ;
   		locA = 0;
   		loc_max = 0;                   /*berechnung von yloc */
   		
   		}
	run++;    
	}	    
   	yf = xValue / ( atoi(argv[4]) - 1 ); 						/*berechnung von yf=x/n-1*/
    yloc = yloc / ( atoi(argv[4]) - 2 );
   		
   	printf("case:%i\n", kLauf);  								/*bildschirmausgabe*/
   
	fprintf(outStream,"%f %f\n",yf, yloc);										/* ausgabe in outstream*/ 
	fprintf(logStream,"case%i: xmax=%f yf=%f yloc=%f\n",kLauf,xMax,yf,yloc); 	/* ausgabe in logstream*/ 
	
	xValue = 0;
	xMax = -100, xMin = 100; 
	yf = 0; 
	yloc = 0;
	locA = 0;
	loc_max = 0;
	run = 1; 													/*reset */
    
   }
  
   printf("\nwriting file:\nfloc.rep\n%s",argv[2]);						/*bildschirmausgabe*/     
   fclose( inStream ); 
   fclose( outStream );
   fclose( logStream );
   fclose( disStream ); 
   
   return 0;	
 
}

/*allgemeine fehlerroutine*/

void _err_msg(char *pszProgName)
{
	printf("-----------------------------------------------------------\n");
	printf("Usage: FLOC [input] [output] n k [disdance]\n ");
	printf(" [input]..... Input File, Format ASCII tab. (eg. data.dat)\n");
	printf("  [output].... Output File\n");
	printf("  [disdance].. Disdance Matrix File\n");
	printf("   n.......... number of cases\n");
	printf("   k.......... number of leads\n");
	printf("-----------------------------------------------------------\n");
	printf("FLOC by d.schrausser\n");
    printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

/*titelzeile bildschirmausgabe, Logfile*/

void _head(struct _iobuf *logStream)

{
   printf("FLOC by d.schrausser\n");						
   printf("compiled on %s @ %s\n\n", __DATE__, __TIME__);
   printf("computing wights:\n"); 
   fprintf(logStream,"\n************************************\n");	
   fprintf(logStream,"Report: FLOC \n");
   _strdate( dbuffer );
   fprintf(logStream,"%s ", dbuffer);
   _strtime( tbuffer );
   fprintf(logStream,"%s\n", tbuffer);
   fprintf(logStream,"------------------------------------\n");
}
