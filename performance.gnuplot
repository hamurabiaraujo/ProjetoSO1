set encoding iso_8859_1
set grid
set key top left
set title "14/08/2014:Quinta-feira - Tempo total de execução: 300s"
set xlabel 'Tamanho do vetor'
set ylabel 'Tempo (segundos)'

# set label "string" at x,y
# para facilitar colocar o y = y+50
# curva do quicksort
set label "1%" at 2500,150
set label "10%" at 5000,250
set label "25%" at 7500,300
set label "30%" at 10000,450

#curva do bublesort
set label "3%" at 2500,250
set label "11%" at 5000,500
set label "21%" at 7500,650
set label "43%" at 10000,850

# Primeira curva
plot 'saida.txt' using 1:2 notitle with linespoints ls 1 lt 8
rep 'saida.txt' using 1:2:3:4 t 'QuickSort' with yerrorbars ls 1 lt 8

# Segunda curva
rep 'saida2.txt' using 1:2 notitle with linespoints ls 2 lt 6
rep 'saida2.txt' using 1:2:3:4 t 'Bublesort' with yerrorbars ls 2 lt 6


set terminal png
set output 'grafico.png'

replot
