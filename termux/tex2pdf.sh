#!/bin/bash

ERROR="Too few arguments : no file name specified"
[[ $# -eq 0 ]] && echo $ERROR && exit # no args? ... print error and exit

# check that the file exists
#if [ -f $1.tex ] 
#then
# if it exists then latex it twice, dvips, then ps2pdf, then remove all the unneeded files
texfot latex $1.tex
#latex $1.tex
dvips $1.dvi -q* -o  $1.ps
ps2pdf $1.ps
termux-open $1.pdf

# these lines can be appended to delete other files, such as *.out
#rm *.aux
#rm *.log
#rm *.ps
#rm *.dvi
#rm *.toc
#rm *.lof
#else
# otherwise give this output line with a list of available tex files
#echo the file doesnt exist butthead! Choose one of these:
#ls *.tex
#fi
