# ConsoleApp_EEG
Console applications for calculating EEG *coherence*, *correlation* and *focus parameters* (c.f. Schrausser, 2000).


## ERC, ERCX

Calculates event related coherence $ERC$.

Usage:

     ERC [input] [output] [nCoh] [nX] [refs] [refe] [acts] [acte] [typ]
     [input].... Input File, Format ASCII tab. (e.g. coh.asc)
     [output]... Output File
     [nCOH]..... number of coherence values 
     [nX]....... number of channel combinations
     [refs]..... number of reference start value 
     [refe]..... number of reference end value
     [acts]..... number of active start value
     [acte]..... number of active end value
     [typ]...... type of output (0) individual (1) append


## XCOR

Calculates cross correlation $xCOR$.

Usage:

     XCOR [input] [output] n k
     [input]..... Input File, Format ASCII tab. (e.g. data.dat)
     [output].... Output File
     n........... number of cases
     k........... number of variables
	

## FOC

Calculates focus parameter $yf$, where

$$yf = \sum\limits_{i=1}^k{1-\frac{\frac{x_i-x_{min}}{d}}{k-1}},$$

with

$$d=x_{max}-x_{min}.$$

Usage: 

     foc [input] [output] n k
     [input]... Input File, Format ASCII tab. (e.g. data.dat)
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

Calculates *spatial* focus parameter $yloc$, where

$$yloc = \frac{\sum\limits_{i=1}^{k} {\sum\limits_{j=1}^{k-1}{\frac{1}{G_i}⋅\bigl[(1-\frac{x_i-x_{min}}{d})⋅w_{G_{ij}}\bigr]}}}{k-2},$$

with

$${G_i} = \sum\limits_{j=1}^{k-1}{g_{ij}},$$

$$w_{G_{ij}} = g_{ij}⋅\Bigl(1-\frac{x_j-x_{min}}{d}\Bigr).$$

Usage: 

     FLOC [input] [output] n k [distance]
     [input]..... Input File, Format ASCII tab. (e.g. data.dat)
     [output].... Output File
     n........... number of cases
     k........... number of leads
     [distance].. Distance Matrix File

## OUT

Generates *output* file.

Usage: 

     out [input] [n] [k] [start] [end] 
     [input].... Input File, Format ASCII tab. (e.g. coh.asc)
     [n]........ number of values / cases /rows
     [k]........ number of variables / columns 
     [start].... number of block start value 
     [end]...... number of block end value


## References

Schrausser, D. G. (2000). *Development of a Parameter to Indicate the Focussation-Level of Cortical Activation*. https://doi.org/10.13140/RG.2.2.32114.17601.
