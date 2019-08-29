OBJ = $(OBJDIR)NRE_GL.o 
OBJDIR = ../../obj/GL/


all : childs $(OBJ)

childs:

$(OBJDIR)%.o :  %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)