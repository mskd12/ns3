#!/usr/bin/gnuplot
#
# Plotting the data of file plotting_data1.dat
#
# AUTHOR: Hagen Wierstorf

reset

# wxt
#set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
# png
set terminal pngcairo size 950,600 enhanced font 'Verdana,10'
set output './lookaround_all_2.png'
# svg
#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \
#fsize '10'
#set output 'plotting_data1.svg'

# color definitions
set border linewidth 0.5
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5 # --- blue

unset key

#set ytics 0.1
set xtics 2
set grid
set xlabel "Look Around Rate"
set ylabel "Throughput"
set key right top
#set tics scale 0.75

set xrange [2:30]
#set yrange [2:8]

plot \
'./la_2/la2.dat' using 1:2 with lines title "2", \
'./la_2/la4.dat' using 1:2 with lines title "4", \
'./la_2/la5.dat' using 1:2 with lines title "5", \
'./la_2/la6.dat' using 1:2 with lines title "6", \
'./la_2/la7.dat' using 1:2 with lines title "7", \
'./la_2/la8.dat' using 1:2 with lines title "8"
#'./la/la-half.dat' using 1:2 with lines title "1/2", \
