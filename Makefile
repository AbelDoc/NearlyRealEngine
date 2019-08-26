export CXX = g++.exe
export LD = g++.exe

export CFLAGS = -pedantic -Wno-virtual-move-assign -Wall -Wextra -Wfatal-errors -Wfloat-equal -Wstrict-overflow -Wshadow -Wconversion -Wunreachable-code -Wuninitialized -Winit-self -Werror -fstrict-overflow -std=c++17
export LDFLAGS = -static -static-libgcc -static-libstdc++

export INC = -I"C:\lib\MinGW64_7.3\include" -I"C:\lib\Glew\include" -I"C:\Users\abell\Documents\GitHub\NRE-Utility\src" -I"C:\Users\abell\Documents\GitHub\NRE-Math\src" -I"C:\Users\abell\Documents\GitHub\NRE-System\src" -I"C:\Users\abell\Documents\GitHub\NRE-IO\src" 
export LIB = "-lmingw32" "-lNRE-System" "C:\lib\Glew\lib\libglew32.dll.a" "-lOpenGL32" "-lPsapi" "-lgdi32" "-lNRE-Math" 
export LIBDIR = -L"C:\lib\MinGW64_7.3\lib" -L"C:/lib/WindowsKits/10/Lib/10.0.17763.0/um/x64" -L"C:/lib/NRE" -L"C:/lib/NRE/Windows" -L"C:/lib/Glew/lib" 

OBJDIR = obj/
BIN = bin/
SRC = src
OBJ = $(OBJDIR)NRE_Main.o $(OBJDIR)Renderer/Program/NRE_Program.o $(OBJDIR)Renderer/Program/Shader/NRE_Shader.o 
OUT = NearlyRealEngine

all : childs out

childs :
	@(cd $(SRC) && $(MAKE))

out : $(OBJ)
	@$(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LDFLAGS) $(LIB)
	@echo "Jobs done."

clean : 
	@echo "Clear of obj/"
	@rm -r obj
	@mkdir obj
	@mkdir obj/Renderer/
	@mkdir obj/Renderer/Program/
	@mkdir obj/Renderer/Program/Shader/
	@echo "obj-Tree creation done."
	@echo "Clean done."
