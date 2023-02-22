# ConsoleApp_EEG
Console applications for calculating EEG coherence, correlation and focus parameters (see Schrausser, 2000).


## ERC, ERCX

Calculates event related coherence ERCoh.

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

Calculates cross correlation Xcorr.

Usage:

     XCOR [input] [output] n k
     [input]..... Input File, Format ASCII tab. (eg. data.dat)
     [output].... Output File
     n........... number of cases
     k........... number of variables
	

## FOC

Calculates focus parameter yf, where

     yf = (∑[i,k]1-((xi-xmin)/d))/(k-1),
     with
     d=(xmax-xmin)

Usage: 

     foc [input] [output] n k
     [input]... Input File, Format ASCII tab. (eg. data.dat)
     [output].. Output File
     n......... number of cases
     k......... number of leads


## DIS

Reading in distance values ​​dij for xi, xj and calculates wights gij defined as

     gij = (1/dij)/∑[j,n](1/dij)

Usage:

     DIS [input] [output] n k
     [input]... Input File, Format ASCII tab. 
     [output].. Output File
     n......... number of cases
     k......... number of leads

## FLOC

Calculates spatial focus parameter yloc, where

     yloc = ( ∑[i,k] ∑[j,k-1](1/Gi)(1-((xi-xmin)/d)wGij) )/(k-2),
     with
     Gi = ∑[j,k-1]gij
     wGij = gij(1-((xj-xmin)/d))


Usage: 

     FLOC [input] [output] n k [distance]
     [input]..... Input File, Format ASCII tab. (eg. data.dat)
     [output].... Output File
     n........... number of cases
     k........... number of lead
     [distance].. Distance Matrix File

## OUT

Generates output file.

Usage: 

     out [input] [n] [k] [start] [end] 
     [input].... Input File, Format ASCII tab. (i.e. coh.asc)
     [n]........ number of values / cases /rows
     [k]........ number of variables / columns 
     [start].... number of block start value 
     [end]...... number of block end value


## References

Schrausser, D. G. (2000). *Development of a Parameter to Indicate the Focussation-Level of Cortical Activation.* https://www.academia.edu/97287277
