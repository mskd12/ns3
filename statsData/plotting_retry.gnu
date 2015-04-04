#!/usr/bin/gnuplot
#
# Plotting the data of file plotting_data1.dat
#
# AUTHOR: Krishna Deepak

reset

# wxt
#set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
# png
set terminal pngcairo size 950,600 enhanced font 'Verdana,10'
set output 'retry.png'
# svg
#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \
#fsize '10'
#set output 'plotting_data1.svg'

# color definitions
set border linewidth 0.5
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5 # --- blue
set palette model RGB defined ( 0 'red', 1 'green' )

unset key

#set ytics 0.005
set xtics 2
set grid
set xlabel "LookAround Rate"
set ylabel "Retry rate(avg.)"
set key right top
#set tics scale 0.75

#set xrange [-105:105]
#set yrange [0:0.025]

plot \
'./retry1.dat' using 1:2 with lines title "1", \
'./retry2.dat' using 1:2 with lines title "2", \
'./retry4.dat' using 1:2 with lines title "4", \
'./retry6.dat' using 1:2 with lines title "6", \
'./retry7.dat' using 1:2 with lines title "7", \
'./retry8.dat' using 1:2 with lines title "8"
