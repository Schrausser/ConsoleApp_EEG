# ConsoleApp_EEG
Console applications for calculating EEG coherence, correlation and focus parameters (see Schrausser, 2000).


## ERC, ERCX

Calculates event related coherence $ERCoh$.

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

Calculates cross correlation $Xcorr$.

Usage:

     XCOR [input] [output] n k
     [input]..... Input File, Format ASCII tab. (eg. data.dat)
     [output].... Output File
     n........... number of cases
     k........... number of variables
	

## FOC

Calculates focus parameter $yf$, where

$$yf = \sum\limits_{i=1}^k{1-\frac{\frac{x_i-x_{min}}{d}}{k-1}},$$
with
$$d=x_{max}-x_{min}$$.

Usage: 

     foc [input] [output] n k
     [input]... Input File, Format ASCII tab. (eg. data.dat)
     [output].. Output File
     n......... number of cases
     k......... number of leads


## DIS

Reading in distance values $d_{ij}$ for $x_i$, $x_j$ and calculates wights $g_{ij}$ defined by

$$g_{ij} = \frac{\frac{1}{d_{ij}}}{\sum\limits_{j=1}^n{\frac{1}{d_{ij}}}}.$$
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

Schrausser, D. G. (2000). *Development of a Parameter to Indicate the Focussation-Level of Cortical Activation.* [DOI: 10.13140/RG.2.2.32114.17601](https://rgdoi.net/10.13140/RG.2.2.32114.17601)
