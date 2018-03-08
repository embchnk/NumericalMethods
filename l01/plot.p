set term png
set out "result1.png"
set xlabel "dt"
set ylabel "blad"
plot "result1.dat" u 1:2 w l lt 1 lw 1 t 'exc1',\
		 "result2.dat" u 1:2 w l lt 10 lw 1 t 'exc2',\

set term png
set out "result4.png"
set xlabel "t"
set ylabel "u(t)"
plot "result4.dat" u 1:2 w l lt 1 lw 1 t 'u2p',\
		 ""						 u 1:3 w l lt 10 lw 1 t 'exc1',

set term png
set out "result5.png"
set xlabel "t"
set ylabel "u(t)"
plot "result5.dat" u 1:2 w l lt 1 lw 1 t 'exc5',\
 		 ""						 u 1:4 w l lt 12 lw 1 t 'teor.',\
		 ""						 u 1:3 w l axes x1y2 lt 10 lw 1 t 'dt(t)',
