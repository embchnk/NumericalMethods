set term png
set logscale x
set out "png/resultexc22.png"
set xlabel "iteracja"
set ylabel ""
plot "dat/exc2_21.100000.dat" u 1:2 w l lt 2 lw 1 t 'w_1',\
  	 "dat/exc2_21.200000.dat" u 1:2 w l lt 3 lw 1 t 'w_2',\
     "dat/exc2_21.300000.dat" u 1:2 w l lt 4 lw 1 t 'w_3',\
     "dat/exc2_21.400000.dat" u 1:2 w l lt 5 lw 1 t 'w_4',\
     "dat/exc2_21.500000.dat" u 1:2 w l lt 6 lw 1 t 'w_5',\
     "dat/exc2_21.600000.dat" u 1:2 w l lt 7 lw 1 t 'w_6',\
     "dat/exc2_21.700000.dat" u 1:2 w l lt 8 lw 1 t 'w_7',\
     "dat/exc2_21.800000.dat" u 1:2 w l lt 9 lw 1 t 'w_8',\
     "dat/exc2_21.900000.dat" u 1:2 w l lt 1 lw 1 t 'w_9',

reset
set out "png/resultpot22.png"
plot "dat/pot2_21.900000.dat" u 1:2:3 w image

reset
set out "png/resultden22.png"
plot "dat/den2_21.900000.dat" u 1:2:3 w image
