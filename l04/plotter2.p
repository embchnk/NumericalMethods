set terminal pngcairo color rounded size 1200, 800

#-------------------------------------------------------------------------------
# Zad 1.
#-------------------------------------------------------------------------------
# Plik z1_prof.dat powinien zawierać następujące kolumny:
#
# [y] [psi(0,0)] [psi(2,0)] [zeta(0,0)] [zeta(2,0)] [u(2,y)]
#
# plik z1_map.dat powinien zawierać następujące kolumny:
# [x] [y] [psi(x,y)] [zeta(x,y)]
#-------------------------------------------------------------------------------

reset

set xlabel "y (pkt. siatki)"
set grid

set ylabel "{/Symbol y}"
set output "png/psi.png"
plot    "dat/z1_prof.dat" u 1:2 w l lw 2 lc "green" t "{/Symbol y}_{0,j}",\
        "" u 1:3 w l lw 2 dt 2 lc "red" t "{/Symbol y}_{2,j}"

set ylabel "{/Symbol z}"
set output "png/zeta.png"
plot    "dat/z1_prof.dat" u 1:4 w l lw 2 lc "green" t "{/Symbol z}_{0,j}",\
        "" u 1:5 w l lw 2 dt 2 lc "red" t "{/Symbol z}_{2,j}"

set ylabel "u"  
set output "png/velocity.png"
plot    "dat/z1_prof.dat" u 1:6 w l lw 2 lc "green" notitle

reset
set palette rgbformulae 22,13,-31

set xrange[0:400]
set yrange[0:200]
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
set output "png/z1_psi.png"
splot "dat/z1_map.dat" u 1:2:3 w pm3d lc "black" lt 1

#-------------------------------------------------------------------------------
# Zad 2.
#-------------------------------------------------------------------------------
# Plik z1_prof.dat powinien zawierać następujące kolumny:
#
# [y] [psi(0,0)] [psi(2,0)] [zeta(0,0)] [zeta(2,0)] [u(2,y)]
#
#-------------------------------------------------------------------------------

reset
set palette rgbformulae 22,13,-31

set xrange[0:400]
set yrange[0:200]
unset xlabel
unset ylabel

set size ratio 0.5
set contour both
unset ztics
unset key
set view 0,0
set cntrparam bspline
set cntrparam levels 20
set cntrlabel onecolor


set output "png/z2_Qm10_psi.png"
splot "dat/z2_Qm10_map.dat" u 1:2:3 w pm3d lc "black" lt 1

set output "png/z2_Qm100_psi.png"
splot "dat/z2_Qm100_map.dat" u 1:2:3 w pm3d lc "black" lt 1

set output "png/z2_Qm500_psi.png"
splot "dat/z2_Qm500_map.dat" u 1:2:3 w pm3d lc "black" lt 1

set output "png/z2_Qm1000_psi.png"
splot "dat/z2_Qm1000_map.dat" u 1:2:3 w pm3d lc "black" lt 1

set cntrparam levels 50
set output "png/z2_Qm1000_zeta.png"
splot "dat/z2_Qm1000_map.dat" u 1:2:4 w pm3d lc "black" lt 1
