OBJ = $(OBJDIR)NRE_Main.o 
OBJDIR = ../obj/


all : childs $(OBJ)

childs:

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)