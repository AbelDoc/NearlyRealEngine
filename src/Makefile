OBJ = $(OBJDIR)NRE_Main.o 
OBJDIR = ../obj/

RENDERER = Renderer

all : childs $(OBJ)

childs:
	@(cd $(RENDERER) && $(MAKE))

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)