CC = gcc
GL = -lm -lGL -lGLU -lglut -lSOIL
ASS= -lassimp

%.o: %.c
	$(CC)  -c $< -o $@


Cars : $(OBJS)
	$(CC) Controlleur/actions.c Modele/Modele.c Modele/opmat.c Modele/Regles.c Modele/Car.c Vue/HUD.c Vue/init.c Vue/ppm.c Vue/VM_init.c -c -c;$(CC) main.c Objets/actions.o Objets/axes.o Objets/init.o Objets/switch_blend.o Objets/Car.o Objets/switch_light.o Objets/VM_init.o Objets/ppm.o Objets/opmat.o $(GL) -o $@ $(ASS); mv *.o Objets/

clean:
	rm -rf Cars
