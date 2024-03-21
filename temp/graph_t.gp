
	#Créée le graphique
	set terminal pngcairo size 800,600   
	set output 'images/graph_t.png'
	set datafile separator";"
	set title 'Option -t : Nb routes = f(Towns)'
	set xlabel 'TOWN NAMES'
	set ylabel 'NB ROUTES'
	set style data histograms
	set xtics border in scale 0,0 mirror rotate by -45 autojustify
	set xrange [*:*]
	set yrange [0:3500]    
	set style fill solid               
	myBoxWidth = 2
	set boxwidth myBoxWidth
	plot 'temp/resultat_t.txt' using 2:xtic(1) title 'Total routes' lc rgb '#19DE91', '' u 3 title 'First town' lc rgb '#39A77C'
	
