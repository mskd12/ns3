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
set output './cornerCase-2-6-2.png'
# svg
#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \
#fsize '10'
#set output 'plotting_data1.svg'

# color definitions
set border linewidth 0.5
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5 # --- blue
set palette model RGB defined ( 0 'red', 1 'green' )

unset key

set ytics 1
#set xtics 8
set grid
set xlabel "Time"
set ylabel "Rate"
set tics scale 0.75

#set xrange [-105:105]
set yrange [0:8]

plot '../temp' using 1:2:3 with points palette
