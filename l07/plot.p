set term png size 800, 600
set out "png/resul1.png"
plot "dat/t0.dat" u 1:2 w l lt 1 lw 1 t 't = 0',\
		 "dat/t0.dat" u 1:3 w l lt 1 dt 3 lw 1 t 't_teoria = 0',\
     "dat/t25.dat" u 1:2 w l lt 2 lw 1 t 't = 0.25',\
     "dat/t25.dat" u 1:3 w l lt 2 dt 3 lw 1 t 't_teoria = 0.25',\
     "dat/t50.dat" u 1:2 w l lt 3 lw 1 t 't = 0.5',\
     "dat/t50.dat" u 1:3 w l lt 3 dt 3 lw 1 t 't_teoria = 0.5',\
     "dat/t75.dat" u 1:2 w l lt 4 lw 1 t 't = 0.75',\
     "dat/t75.dat" u 1:3 w l lt 4 dt 3 lw 1 t 't_teoria = 0.75',\
     "dat/t100.dat" u 1:2 w l lt 5 lw 1 t 't = 1',\
     "dat/t100.dat" u 1:3 w l lt 5 dt 3 lw 1 t 't_teoria = 1',\
     "dat/t125.dat" u 1:2 w l lt 6 lw 1 t 't = 1.25',\
     "dat/t125.dat" u 1:3 w l lt 6 dt 3 lw 1 t 't_teoria = 1.25',\
     "dat/t150.dat" u 1:2 w l lt 7 lw 1 t 't = 1.50',\
     "dat/t150.dat" u 1:3 w l lt 7 dt 3 lw 1 t 't_teoria = 1.50',\
     "dat/t175.dat" u 1:2 w l lt 8 lw 1 t 't = 1.75',\
     "dat/t175.dat" u 1:3 w l lt 8 dt 3 lw 1 t 't_teoria = 1.75',\
     "dat/t200.dat" u 1:2 w l lt 8 lw 0.1 t 't = 2',\
     "dat/t200.dat" u 1:3 w l lt 8 dt 3 lw 0.1 t 't_teoria = 2'

set out "png/zad2b.png"
plot "dat/zad2b.dat" u 1:2 w l lt 1 lw 1 t 'x = 0',\
		 "dat/zad2b.dat" u 1:3 w l lt 2 lw 1 t 'x = 1'

reset
set out "png/zad2.png"
plot "dat/zad2.dat" u 1:2:3 w image

reset
set out "png/zad2c.png"
plot "dat/zad2c.dat" u 1:2:3 w image

reset
set out "png/zad32.png"
plot "dat/beta2.dat" u 1:2:3 w image

reset
set out "png/zad310.png"
plot "dat/beta10.dat" u 1:2:3 w image

reset
set out "png/zad330.png"
plot "dat/beta30.dat" u 1:2:3 w image