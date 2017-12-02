Results_hw5.pdf : Results_hw5.tex figura.png 
	pdflatex Results_hw5.tex

figura.png : Plots.py Datos_Ajuste.txt
	python Plots.py

Datos_Ajuste.txt : CurvaRotacion.x
	./CurvaRotacion.x

CurvaRotacion.x : CurvaRotacion.c RadialVelocities_2.dat
	cc CurvaRotacion.c -o CurvaRotacion.x -lm 

RadialVelocities_2.dat : RadialVelocities.dat
	sed '1d' RadialVelocities.dat > RadialVelocities_2.dat





