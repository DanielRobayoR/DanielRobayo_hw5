Results_hw5.pdf : Results_hw5.tex figura.png 
	pdflatex Results_hw5.tex

figura.png : Plots.py Datos_Ajuste.txt
	python Plots.py

Datos_Ajuste.txt : CurvaRotacion.x
	./CurvaRotacion.x

CurvaRotacion.x : CurvaRotacion.c
	cc CurvaRotacion.c -o CurvaRotacion.x -lm 




