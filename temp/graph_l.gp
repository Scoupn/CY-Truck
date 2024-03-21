
	#Créée le graphique
	set terminal pngcairo size 800,600   
	set output 'images/vertical_l.png'
	set datafile separator";"
	set title 'Option -l : Distance = f(Route)'
	set xlabel 'ROUTE ID'
	set ylabel 'Distance (km)'
	set xrange [-0.75:*]
	set yrange [0:*]    
	set style fill solid   
	unset key             
	myBoxWidth = 0.8
	set boxwidth myBoxWidth
	plot 'temp/resultat_l.txt' using 2:xtic(1) with boxes lc rgb '#39A77C'
	set output 
	
