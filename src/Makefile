OBJ = $(OBJDIR)NRE_Main.o 
OBJDIR = ../obj/

GL = GL
LIB = lib
RENDERER = Renderer
WORLD = World

all : childs $(OBJ)

childs:
	@(cd $(GL) && $(MAKE))
	@(cd $(LIB) && $(MAKE))
	@(cd $(RENDERER) && $(MAKE))
	@(cd $(WORLD) && $(MAKE))

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)