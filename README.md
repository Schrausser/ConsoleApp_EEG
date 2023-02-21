# ConsoleApp_EEG
Console applications for calculating EEG parameters.


## ERC, ERCX

Calculates event related coherence.

Usage:

     ERC [input] [output] [nCoh] [nX] [refs] [refe] [acts] [acte] [typ]
     [input].... Input File, Format ASCII tab. (i.e. coh.asc)
     [output]... Output File
     [nCOH]..... number of coherence values 
     [nX]....... number of channel combinations
     [refs]..... number of reference start value 
     [refe]..... number of reference end value
     [acts]..... number of active start value
     [acte]..... number of active end value
     [typ]...... type of output (0) individual (1) append


## XCOR

Calculates cross correlation.

     XCOR [input] [output] n k
     [input]..... Input File, Format ASCII tab. (eg. data.dat)
     [output].... Output File
     n.......... number of cases
     k.......... number of variables
	

## FOC

Calculates foc parameter.

     foc [input] [output] n k
     [input]... Input File, Format ASCII tab. (eg. data.dat)
     [output].. Output File
     n........ number of cases
     k........ number of leads


## FLOC

Calculates floc parameter.

Usage: 

      FLOC [input] [output] n k [distance]
      [input]..... Input File, Format ASCII tab. (eg. data.dat)
      [output].... Output File
      n.......... number of cases
      k.......... number of lead
      [distance].. Distance Matrix File

## DIS

Reading in distance values ​​calculates gij and creates output file.

Usage:

     DIS [input] [output] n k
     [input]... Input File, Format ASCII tab. 
     [output].. Output File
     n........ number of cases
     k........ number of leads

## OUT

Generates output file.

Usage: 

      out [input] [n] [k] [start] [end] 
      [input].... Input File, Format ASCII tab. (i.e. coh.asc)
      [n]........ number of values / cases /rows
      [k]........ number of variables / columns 
      [start].... number of block start value 
      [end]...... number of block end value


