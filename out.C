/*OUT by Dietmar G. SCHRAUSSER (C) 2000*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stats.h" /*header mit statistk prozeduren (zb fisher Z) stats.h (c) by schrausser*/

#define SIZE1 20 /*globale feldgroessen def, k=20 spalten*/
#define SIZE2 100 /*globale feldgroessen def, n=100 zeilen max*/

void _err_msg (char *PszProgName); /*prozedur fehlermeldung und usage instruktion*/
void _head(void); /*prozedur für kopfzeilen*/

char dbuffer [9],tbuffer [9];/*buffer fuer time und date*/

main(int argc, char *argv[]) /*main übernimmt n argumente im vektor argv*/
{   
   FILE *inStream, *logStream;/*streams*/
   float feld[SIZE1][SIZE2], FZc=0, out=0;
   int iLauf=0, jLauf=1;
     
   if (argc != 6)/*was wenn keine oder zuwenig, zuviel argumente?*/
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
   
   /*def von input und outputdatei:*/
   
   
   inStream = fopen( argv[1], "r" );
   /*outStream = fopen( argv[2], "w" );*/ 
   logStream = fopen( "out.rep", "a+" ); 
     
   if (inStream == NULL)/*was wenn keine datendatei*/
	{
   		printf("ERROR, check file %s!\n", argv[1]);
   		_err_msg(argv[0]);
		fprintf(logStream,"fehlt\n");
	}
   
   _head();
   
   /*einlesen der werte*/
   for (jLauf = 1; jLauf <= atoi(argv[2]); jLauf++) /*jlauf: anzahl der zeilen = argument 2*/ 
   {
   		for (iLauf = 0; iLauf <= (atoi(argv[3]) - 1); iLauf++) /*ilauf: anzahl der spalten=argument 3*/
   		{
   			fscanf(inStream,"%f", &feld[iLauf][jLauf]);  /*einlesen der werte x pro zeile j und spalte i von instream*/
			/*printf("%f__", feld[iLauf][jLauf]); */ 
   			/*fprintf(logStream,"%f\t",Fi_Z(feld[iLauf][jLauf]));  ausgabe in outstream */
		}	
    
   /*fprintf(logStream,"\n");  zeilnvorschub in logstream*/ 
   }   
    /*ausgeben der werte in out.rep*/ 

	for (iLauf = 0; iLauf <= (atoi(argv[3]) - 1); iLauf++) /*ilauf: anzahl der spalten=argument 3*/
    {
   		for (jLauf = (atoi(argv[4]) + 1); jLauf <= atoi(argv[5]); jLauf++) /*jlauf: anzahl der blockzeilen = argument 4 / 5*/ 
        {
		FZc += Fi_Z (feld[iLauf][jLauf]); /* fisher z tranformierung und summierung von x*/
		}
	out = FZc / (atoi(argv[5])-atoi(argv[4])); /*mittelung*/
    fprintf(logStream,"%f\t",out); /* ausgabe in logstream*/ 
	FZc = 0;
	}
	
   fprintf(logStream,"\n"); /* zeilnvorschub in logstream*/ 
   printf("\nwriting file:\nout.rep\n");/*bildschirmausgabe*/     
   fclose( inStream ); 
   /*fclose( outStream );*/
   fclose( logStream ); 
   return 0;
}

/*allgemeine fehlerroutine*/
void _err_msg(char *pszProgName)
{
	printf("-----------------------------------------------------------\n");
	printf("Usage: out [input] [n] [k] [start] [end] \n ");
	printf(" [input].... Input File, Format ASCII tab. (i.e. coh.asc)\n");
	printf("  [n]........ number of values / cases /rows\n");
	printf("  [k]........ number of variables / columns \n");
    printf("  [start].... number of block start value \n");
	printf("  [end]...... number of block end value\n");
	printf("-----------------------------------------------------------\n");
	printf("OUT by d.schrausser\n");
    printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

void _head(void)
{
   printf("\nOUT by d.schrausser\n");						/*titelzeile bildschirmausgabe*/
   printf("compiled on %s @ %s\n", __DATE__, __TIME__);
   printf("computing out:"); 
}
