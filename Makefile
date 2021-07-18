# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 13:58:56 by oadhesiv          #+#    #+#              #
#    Updated: 2021/07/18 19:33:25 by oadhesiv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/zsh

NAME = RTv1
SRCS_DIR = ./srcs
INCLUDES_DIR = ./includes
OBJS_DIR = ./objs

LIB = libft.a
LIB_DIR = ./libft

SRC_FILES =	main.c \
			matrix_factory_1.c matrix_factory_2.c \
			matrix_utils.c \
			vector_1.c vector_2.c \
			quaternion.c \
			clear_mlx.c init_mlx.c init_mlx_2.c \
			init_rtv.c init_rtv_scene_lights.c init_rtv_scene_objects.c \
			loop_hook_flow.c \
			loop_hook_invalidate.c loop_hook_events.c loop_hook_render_debug.c \
			loop_hook_redraw.c \
			raytrace.c raytrace_light.c normal.c \
			color.c \
			intersection.c intersection_sphere.c intersection_plane.c intersection_cylinder.c intersection_cone.c \
			intersection_common.c \
			parser.c parser_level.c parser_level_process.c \
			parser_parse_1.c parser_parse_2.c \
			validator.c validator_light.c \
			validator_light_directional.c validator_light_point.c \
			validator_cone.c validator_cylinder.c validator_plane.c \
			validator_sphere.c \
			graceful.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

ifeq ($(OS),Windows_NT)
# huh lol
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		ifeq ($(origin CC), default)
			CC = clang
		endif

		MLX = libmlx.a
		MLX_DIR = ./minilibx-linux
		CFLAGS_PLATFORM = -D MLX_LINUX
		LDFLAGS += -lX11 -lXext -lm -pthread
	endif
	ifeq ($(UNAME_S),Darwin)
		ifeq ($(origin CC), default)
			CC = clang
		endif

		UNAME_R := $(shell uname -r | cut -d. -f1)
		VER := $(shell test $(UNAME_R) -ge 17 && echo 'new' || echo 'old')
		ifeq ($(VER),new)
			MLX = libmlx.dylib
			MLX_DIR = ./minilibx_mms_20200219
			CFLAGS_PLATFORM = -D MLX_MACOS_METAL
		endif
		ifeq ($(VER),old)
			MLX = libmlx.a
			MLX_DIR = ./minilibx_macos
			CFLAGS_PLATFORM = -D MLX_MACOS
			LDFLAGS += -framework OpenGL -framework AppKit
		endif
	endif
endif

CFLAGS_ERRORS = -Wall -Wextra -Werror -Wno-incompatible-pointer-types-discards-qualifiers

ifeq ($(DEBUG),1)
	CFLAGS_OPTIMIZATIONS = -funroll-loops
	CFLAGS_DEBUG = -O0 -pg -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
else
	CFLAGS_OPTIMIZATIONS = -O3 -funroll-loops -march=native
	CFLAGS_DEBUG =
endif

CFLAGS_DEPENDENCIES = -MMD -MP
CFLAGS_INCLUDES = -I$(INCLUDES_DIR) -I$(LIB_DIR) -I$(MLX_DIR)
CFLAGS_ASAN = -fsanitize=address

CFLAGS_FINAL =	$(CFLAGS_ERRORS) $(CFLAGS_OPTIMIZATIONS) \
				$(CFLAGS_DEPENDENCIES) $(CFLAGS_INCLUDES) \
				$(CFLAGS_PLATFORM) $(CFLAGS_DEBUG) $(CFLAGS_INTERNAL) \
				$(CFLAGS)

LDFLAGS += -L$(LIB_DIR) -lft -L$(MLX_DIR) -lmlx

LDFLAGS_ASAN = -fsanitize=address

DEFAULT = "\033[0;0m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"
BLUE = "\033[0;34m"
CYAN = "\033[0;36m"

.PHONY: all clean clean_libs clean_self fclean fclean_libs fclean_self debug debug_all asan asan_all re prepare_ubuntu

all:
	@echo $(CYAN) "Making libft" $(DEFAULT)
	@echo -n $(BLUE)
	CC="$(CC)" DEBUG="$(DEBUG)" $(MAKE) -C $(LIB_DIR)
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Making minilibx" $(DEFAULT)
	@echo -n $(BLUE)
	CC="$(CC)" DEBUG="$(DEBUG)" $(MAKE) -C $(MLX_DIR)
	cp $(MLX_DIR)/$(MLX) $(MLX)
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Making RTv1" $(DEFAULT)
	@echo -n $(GREEN)
	$(MAKE) $(NAME)
	@echo -n $(DEFAULT)

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS_FINAL) -c -o $@ $<

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(LIB_DIR)/$(LIB) $(MLX_DIR)/$(MLX)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean: clean_libs clean_self

clean_libs:
	@echo $(CYAN) "Cleaning libft" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(LIB_DIR) clean
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Cleaning minilibx" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(MLX_DIR) clean
	@echo -n $(DEFAULT)

clean_self:
	@echo $(CYAN) "Cleaning RTv1" $(DEFAULT)
	@echo -n $(GREEN)
	rm -rfv $(OBJS_DIR)
	@echo -n $(DEFAULT)

fclean: fclean_libs fclean_self

fclean_libs: clean_libs
	@echo $(CYAN) "Purging libft" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(LIB_DIR) fclean
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Purging minilibx" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(MLX_DIR) fclean
	rm -rfv $(MLX)
	@echo -n $(DEFAULT)

fclean_self: clean_self
	@echo $(CYAN) "Purging RTv1" $(DEFAULT)
	@echo -n $(GREEN)
	rm -rfv $(NAME)
	@echo -n $(DEFAULT)

debug: clean_self
	DEBUG="1" $(MAKE) all

debug_wsl:
	@echo "Don't forget to run on Windows host:"
	@echo '"C:\\Program Files\\VcXsrv\\vcxsrv.exe" :0 -ac -terminate -lesspointer -multiwindow -clipboard -wgl -dpi auto'
	@echo "Press any key to continue..."
	@read
	$(MAKE) debug

debug_all: clean_self clean_libs
	DEBUG="1" $(MAKE) all

asan: clean_self
	DEBUG="1" CFLAGS_INTERNAL="$(CFLAGS_ASAN)" LDFLAGS="$(LDFLAGS_ASAN)" \
	$(MAKE) all

asan_all: clean_self clean_libs
	DEBUG="1" CFLAGS_INTERNAL="$(CFLAGS_ASAN)" LDFLAGS="$(LDFLAGS_ASAN)" \
	$(MAKE) all

re: fclean all

prepare_ubuntu:
	sudo apt update
	sudo apt install zsh clang lldb libx11-dev libxext-dev libbsd-dev gdb -y
