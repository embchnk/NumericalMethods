set terminal pngcairo enhanced color rounded size 1200,800

#-------------------------
# Zad 1.
#-------------------------
reset
set xrange[1:200]
set yrange[1:100]
unset xlabel
unset ylabel

set size ratio 0.5      # ustalanie proporcji wykresu (szerokosc jest 2x wieksza od wysokosci)
set contour both
unset ztics
unset key
set view 0,0
set cntrparam bspline
set cntrparam levels 20
set cntrlabel onecolor
set output "png/z1_sol.png"
splot "dat/dane.dat" u 1:2:3 w pm3d lc "black" lt 1

reset
set xlabel "Numer iteracji"
set ylabel "Calka dzialania"
set output "png/z1_action.png"
set log x
set mxtics
set grid xtics ytics mxtics mytics
plot "dat/dane2.dat" u 1:2 w lines notitle

#-------------------------
# Zad 2.
#-------------------------
reset
set xrange[1:200]
set yrange[1:100]
unset xlabel
unset ylabel

set size ratio 0.5      # ustalanie proporcji wykresu (szerokosc jest 2x wieksza od wysokosci)
set contour both
unset ztics
unset key
set view 0,0
set cntrparam bspline
set cntrparam levels 40
set cntrlabel onecolor
set output "png/z2_sol.png"
splot "dat/dane3.dat" u 1:2:3 w pm3d lc "black" lt 1

reset
set xlabel "Numer iteracji"
set ylabel "Calka dzialania"
set output "png/z2_action.png"
set log x
set mxtics
set grid xtics ytics mxtics mytics
plot "dat/dane4.dat" u 1:2 w lines notitle
