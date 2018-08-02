set xlabel 'Dias'
set ylabel 'População
set yrange [0:5200]
set grid
set key center right
set term png
set output 'graph.png'

plot 'output_1.dat' using 1:2 title 'A<N<K' w p pt 6 ps 1 lc rgb "blue", \
     'output_2.dat' using 2 title 'K<N' w p pt 6 ps 1 lc rgb "red", \
     'output_3.dat' using 2 title 'N<A' w p pt 6 ps 1 lc rgb "green"
