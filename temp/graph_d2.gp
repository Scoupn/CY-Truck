
	#Crée le graphique

	set terminal pngcairo size 800,600   
	set output 'images/horizontal_d2.png'
	set datafile separator";"
	set title 'Option -d2 : Distance = f(Driver)'
	set xlabel 'Distance (Km)'
	set ylabel 'DRIVERS NAMES'
	set yrange [-0.75:9.75]      
	set style fill solid   
	unset key             
	myBoxWidth = 0.8
	set boxwidth myBoxWidth
	plot 'temp/resultat_d2.txt' using (0.5*$2):0:(0.5*$2):(myBoxWidth/2.):(2):ytic(1) with boxxy lc var
	set output 
	
