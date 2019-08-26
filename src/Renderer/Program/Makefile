OBJ = $(OBJDIR)NRE_Program.o 
OBJDIR = ../../../obj/Renderer/Program/

SHADER = Shader

all : childs $(OBJ)

childs:
	@(cd $(SHADER) && $(MAKE))

$(OBJDIR)%.o :  %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)