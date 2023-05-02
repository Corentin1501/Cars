CC = gcc
GL = -lm -lGL -lGLU -lglut
ASS= -lassimp

%.o: %.c
	$(CC)  -c $< -o $@


Cars : $(OBJS)
	$(CC) Controlleur/actions.c Modele/Modele.c Modele/opmat.c Modele/Regles.c Vue/HUD.c Vue/init.c Vue/ppm.c Vue/VM_init.c -c -c;$(CC) main.c actions.o axes.o init.o switch_blend.o switch_light.o VM_init.o ppm.o opmat.o $(GL) -o $@ $(ASS)
