CC = gcc
GL = -lm -lGL -lGLU -lglut
ASS= -lassimp







%.o: %.c
	$(CC)  -c $< -o $@





Cars : $(OBJS)
	$(CC) Modele/opmat.c Controlleur/actions.c Vue/VM_init.c Vue/init.c Vue/ppm.c Modele/Regles.c Vue/HUD.c Modele/physique.c -c;$(CC) main.c actions.o axes.o init.o switch_blend.o switch_light.o VM_init.o ppm.o opmat.o $(GL) -o $@ $(ASS)

 
