OBJ = $(OBJDIR)NRE_World.o 
OBJDIR = ../../obj/World/


all : childs $(OBJ)

childs:

$(OBJDIR)%.o :  %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)