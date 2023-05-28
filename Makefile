CC  = gcc
GL  = -lm -lGL -lGLU -lglut 
ASS = -lassimp
IA  = -ltensorflow

%.o: %.c
	$(CC)  -c $< -o $@


Cars : $(OBJS)
	$(CC) Controlleur/*.c Modele/*.c Vue/*.c -c -c; mv *.o Objets/ ; 
	$(CC) main.c Objets/physique.o Objets/actions.o Objets/axes.o Objets/Car.o Objets/HUD.o Objets/IA.o Objets/init.o Objets/lumiere.o Objets/Modele.o Objets/ppm.o Objets/Regles.o Objets/switch_blend.o Objets/switch_light.o Objets/VM_init.o $(GL) -o $@ $(ASS) ;

clean:
	rm -rf Cars
