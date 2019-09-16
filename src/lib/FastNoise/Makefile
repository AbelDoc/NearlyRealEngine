OBJ = $(OBJDIR)FastNoise.o 
OBJDIR = ../../../obj/lib/FastNoise/

all : $(OBJ)

$(OBJDIR)%.o :  %.cpp %.h
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)