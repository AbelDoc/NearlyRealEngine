OBJ = $(OBJDIR)NRE_Shader.o 
OBJDIR = ../../../../obj/Renderer/Program/Shader/


all : childs $(OBJ)

childs:

$(OBJDIR)%.o :  %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)