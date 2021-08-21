MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)

ifeq ($(DEBUG),1)
	CFLAGS_OPTIMIZATIONS = -funroll-loops
	CFLAGS_DEBUG = -O0 -pg -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
	SWIFTFLAGS_OPTIMIZATIONS = -Onone
	SWIFTFLAGS_DEBUG = -g
else
	CFLAGS_OPTIMIZATIONS = -O3 -funroll-loops -march=native
	CFLAGS_DEBUG =
	SWIFTFLAGS_OPTIMIZATIONS = -O
	SWIFTFLAGS_DEBUG =
endif

CFLAGS += $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_DEBUG)
SWIFTFLAGS += $(SWIFTFLAGS_OPTIMIZATIONS) $(SWIFTFLAGS_DEBUG)

NAME=libmlx.dylib

INC=-I.

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(SWIFTFLAGS) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

%.o: %.swift
	swiftc $(SWIFTFLAGS) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(SWIFTFLAGS) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
	rm -fv $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~

fclean: clean
	rm -fv $(NAME)

re: fclean all
