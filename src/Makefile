OBJ = $(OBJDIR)NRE_Main.o 
OBJDIR = ../obj/

GL = GL
LIB = lib
RENDERER = Renderer

all : childs $(OBJ)

childs:
	@(cd $(GL) && $(MAKE))
	@(cd $(LIB) && $(MAKE))
	@(cd $(RENDERER) && $(MAKE))

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)