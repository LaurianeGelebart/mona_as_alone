CC			= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL2 -lSDL2_image -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 04

# Fichiers exercice 03
OBJ_TD04_EX03= opengl/opengl.o
EXEC_TD04_EX03= opengl.out


# Regles compilation TD 04

all :


opengl : $(OBJDIR)$(OBJ_TD04_EX03)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD04_EX03) -o $(BINDIR)$(EXEC_TD04_EX03) $(LDFLAGS)


clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
