
	#Créée le graphique
	set terminal pngcairo size 1100,900  
	set output 'images/graph_s.png'
	set datafile separator";"
	set title 'Option -s : Distance = f(Route)'
	set xlabel 'ROUTE ID'
	set ylabel 'DISTANCE (Km)'
	set style data line
	set xtics rotate by -45 autojustify
	set xrange [*:*]
	set yrange [0:1000]
	plot 'temp/resultat_s.csv' using 1:4:xtic(2) with lines lc rgb '#39A77C' title 'Distance average', 'temp/resultat_s.csv' using 1:3 with lines lc rgb '#19DE91' title 'Distance Max/Min', 'temp/resultat_s.csv' using 1:5 with lines lc rgb '#19DE91' notitle, 'temp/resultat_s.csv' using 1:3:5 with filledcurves lc rgb '#19DE91' fs transparent solid 0.5 notitle
	
