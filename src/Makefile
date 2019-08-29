OBJ = $(OBJDIR)NRE_Main.o 
OBJDIR = ../obj/

GL = GL
RENDERER = Renderer

all : childs $(OBJ)

childs:
	@(cd $(GL) && $(MAKE))
	@(cd $(RENDERER) && $(MAKE))

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)