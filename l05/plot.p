set terminal pngcairo color rounded size 1200, 800
reset 
set xrange[0:300]
set yrange[0:90]
unset xlabel
unset ylabel
set size ratio 0.3023
unset ztics
unset key
set cbrange[0:]

set title "Plama it = 0"
set output "png/z1_it0.png"
plot "dat/z1_it0.dat" u 1:2:3 w image

set title "Plama it = 300"
set output "png/z1_it300.png"
plot "dat/z1_it300.dat" u 1:2:3 w image

set title "Plama it = 600"
set output "png/z1_it600.png"
plot "dat/z1_it600.dat" u 1:2:3 w image

set title "Plama it = 900"
set output "png/z1_it900.png"
plot "dat/z1_it900.dat" u 1:2:3 w image

set title "Plama it = 1200"
set output "png/z1_it1200.png"
plot "dat/z1_it1200.dat" u 1:2:3 w image

set title "Plama it = 1500"
set output "png/z1_it1500.png"
plot "dat/z1_it1500.dat" u 1:2:3 w image

reset
set grid

set xlabel "t"
set ylabel "<x>"
set title "Wartosc oczekiwana polozenia"

set output "png/z1_Ex.png"
plot "dat/z1_integrals.dat" u 1:3 w l lw 2 notitle