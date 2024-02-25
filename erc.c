/*ERC by Dietmar G. SCHRAUSSER (C) 2000*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stats.h" /*header mit statistk prozeduren (zb fisher Z) stats.h (c) by schrausser*/

#define SIZE1 20 /*globale feldgroessen def, n=20 coh positionen max*/
#define SIZE2 100 /*globale feldgroessen def, n=100 coh werte max*/

void _err_msg (char *PszProgName); /*prozedur fehlermeldung und usage instruktion*/
void _head(struct _iobuf *stream); /*prozedur für kopfzeilen*/

char dbuffer [9],tbuffer [9];/*buffer fuer time und date*/

main(int argc, char *argv[]) /*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *outStream,*logStream;/*streams*/
   float feld[SIZE1][SIZE2], cR=0, cA=0, FZcR=0, FZcA=0, erc=0;
   int iLauf=0, jLauf=1;
   char *typ;
     
   if (argc != 10)/*was wenn keine oder zuwenig, zuviel argumente?*/
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
   
   /*def von input und outputdatei:
   argument 1:input; argument 2:output*/
   
   switch (atoi(argv[9]))
   {	   
   case 0:
	typ = "w";
   break;
   case 1:
	typ = "a+";
   break;
   }

   inStream = fopen( argv[1], "r" );
   outStream = fopen( argv[2], typ ); 
   logStream = fopen( "ERC.rep", "a+" ); 
     
   if (inStream == NULL)/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[1]);
   		_err_msg(argv[0]);
	}
   
   _head(logStream);
   
   /*einlesen der coh werte*/
   for (jLauf = 1; jLauf <= atoi(argv[3]); jLauf++) /*jlauf: anzahl der coherenz werte = argument 3*/ 
   {
   		for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1); iLauf++) /*ilauf: anzahl der coh-positionen=argument 4*/
   		{
   			fscanf(inStream,"%f", &feld[iLauf][jLauf]);  /*einlesen der werte x pro fall j und coh pos i von instream*/
			/*printf("%f__", feld[iLauf][jLauf]); */ 
   			/*fprintf(outStream,"%f\n",&feld[iLauf][jLauf]);*/ /* ausgabe in outstream*/ 
		}	
     }   

   /*berechnung von erc*/			
   for (iLauf = 0; iLauf <= (atoi(argv[4]) - 1); iLauf++)/*ilauf: anzahl der coh-positionen=argument 4*/
   {
	   printf("coh%i\n", iLauf + 1 );/* bildschirmausgabe*/
	   fprintf(logStream,"Coh%i: ", iLauf + 1); /* logfile ausgabe*/

	   	for (jLauf = atoi(argv[5]); jLauf <= atoi(argv[6]); jLauf++)/*jlauf: anzahl der werte im ref intervall=argumente 5-6*/ 
		{
           FZcR += Fi_Z (feld[iLauf][jLauf]); /* fisher z tranformierung von cR*/
		}
	
	   	FZcR = FZcR / (atoi(argv[6]) - atoi(argv[5]));/*mittelung aller z transf coh werte in R*/
	   	cR = r_Fi_Z (FZcR);/*retranformierung von FZcR*/
        
	   	for (jLauf = atoi(argv[7]); jLauf <= atoi(argv[8]); jLauf++)/*jlauf: anzahl der werte im act intervall=argumente 7-8*/ 
		{
          	FZcA += Fi_Z (feld[iLauf][jLauf]); /* fisher z tranformierung von cA*/
		}
        
		if (atoi(argv[7]) != atoi(argv[8]))	 /*wenn mehr als 2 intervallargumente coh...*/
	    	FZcA = FZcA / (atoi(argv[8]) - atoi(argv[7]));   /*mittelung aller z transf coh werte in A*/
		
		cA = r_Fi_Z (FZcA);	/*retranformierung von FZcA*/
        erc = (cA - cR) / cR; /*berechnzng von ERC*/
				  
		fprintf(logStream,"R=%f (Z=%f); A=%f (Z=%f);  ERC=%f\n", cR, FZcR, cA, FZcA, erc);/* logfile ausgabe*/	
		fprintf(outStream,"%f\t", erc); /* outfile ausgabe*/
		
		FZcA = 0, cA = 0, FZcR = 0, cR = 0, erc=0; /*rücksetzen der variablen*/
	}
  
   fprintf(outStream,"\n"); /* outfile return*/
   printf("\nwriting file:\nERC.rep\n%s",argv[2]);/*bildschirmausgabe*/     
   fclose( inStream ); 
   fclose( outStream );
   fclose( logStream ); 
   return 0;
}

/*allgemeine fehlerroutine*/
void _err_msg(char *pszProgName)
{
	printf("-----------------------------------------------------------\n");
	printf("Usage: ERC [input] [output] [nCoh] [nX] [refs] [refe] [acts] [acte] [typ]\n ");
	printf(" [input].... Input File, Format ASCII tab. (i.e. coh.asc)\n");
	printf("  [output]... Output File\n");
	printf("  [nCOH]..... number of coherence values \n");
	printf("  [nX]....... number of channel combinations\n");
    printf("  [refs]..... number of reference start value \n");
	printf("  [refe]..... number of reference end value\n");
	printf("  [acts]..... number of active start value\n");
    printf("  [acte]..... number of active end value\n");
    printf("  [typ]...... type of output (0) individual (1) append\n");
	printf("-----------------------------------------------------------\n");
	printf("ERC by d.schrausser\n");
    printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

void _head(struct _iobuf *logStream)
{
   printf("ERC by d.schrausser\n");						/*titelzeile bildschirmausgabe*/
   printf("compiled on %s @ %s\n\n", __DATE__, __TIME__);
   printf("computing ERC:\n"); 
   fprintf(logStream,"\n************************************\n");/*titelzeile in logstream*/ 
   fprintf(logStream,"Report: ERC \n");
   _strdate( dbuffer );
   fprintf(logStream,"%s ", dbuffer);
   _strtime( tbuffer );
   fprintf(logStream,"%s\n", tbuffer);
   fprintf(logStream,"------------------------------------\n");
}
