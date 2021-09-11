# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 13:58:56 by oadhesiv          #+#    #+#              #
#    Updated: 2021/09/11 23:00:30 by oadhesiv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/zsh

NAME = RT
SRCS_DIR = ./srcs
INCLUDES_DIR = ./includes
OBJS_DIR = ./objs

LIB = libft.a
LIB_DIR = ./lib/libft

IMGUI = cimgui.dylib
IMGUI_DIR = ./lib/cimgui

STB_DIR = ./lib/stb

FILES_INIT :=	init_rtv.c init_rtv_scene_lights.c init_rtv_scene_objects.c \
				texture.c stb.c
FILES_INIT := $(addprefix init_rtv/, $(FILES_INIT))

FILES_INTERSECTION :=	intersection.c intersection_common.c \
						intersection_sphere.c intersection_plane.c \
						intersection_cylinder.c intersection_cone.c 
FILES_INTERSECTION :=	$(addprefix intersection/, $(FILES_INTERSECTION))

FILES_LOOP :=	loop_hook_flow.c loop_hook_invalidate.c \
				loop_hook_redraw.c loop_hook_common.c loop_sdl.c
FILES_LOOP := $(addprefix loop/, $(FILES_LOOP))

FILES_IMGUI :=	controls.c imgui_init.c windows.c window_controls.c \
				window_controls_spheres.c window_controls_spheres_checkbox.c
FILES_IMGUI := $(addprefix imgui/, $(FILES_IMGUI))

FILES_SDL :=	init_sdl.c sdl_events.c sdl_gl_attributes.c sdl_clear_texture.c
FILES_SDL := $(addprefix sdl/, $(FILES_SDL))

FILES_PARSER :=	parser.c parser_level.c parser_level_process.c \
				parser_parse_1.c parser_parse_2.c parser_cleanup.c
FILES_PARSER :=	$(addprefix parser/, $(FILES_PARSER))

FILES_VALIDATOR :=	validator_1.c validator_2.c validator_light.c \
					validator_light_directional.c validator_light_point.c \
					validator_cone.c validator_cylinder.c validator_plane.c \
					validator_sphere.c validator_camera.c
FILES_VALIDATOR :=	$(addprefix validator/, $(FILES_VALIDATOR))

FILES_RAYTRACE :=	raytrace_texture.c \
					raytrace_color_plane.c raytrace_color_sphere.c \
					raytrace_perlin.c
FILES_RAYTRACE :=	$(addprefix raytrace/, $(FILES_RAYTRACE))

SRC_FILES =	main.c \
			matrix_factory_1.c matrix_factory_2.c \
			matrix_utils.c \
			vector_1.c vector_2.c vector_3.c \
			quaternion.c \
			raytrace.c raytrace_light.c normal.c \
			color.c \
			graceful.c \
			$(FILES_INIT) $(FILES_INTERSECTION) $(FILES_LOOP) $(FILES_PARSER) \
			$(FILES_VALIDATOR) $(FILES_SDL) $(FILES_IMGUI) $(FILES_RAYTRACE)

SRC_DIRS = $(sort $(dir $(SRC_FILES)))
OBJS_DIRS = $(addprefix $(OBJS_DIR)/, $(SRC_DIRS))
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

ifeq ($(origin CC), default)
	CC = clang
endif
ifeq ($(origin CXX), default)
	CXX = clang++
endif

CFLAGS_ERRORS = -Wall -Wextra -Werror

ifeq ($(DEBUG),1)
	CFLAGS_OPTIMIZATIONS = -funroll-loops
	CFLAGS_DEBUG = -O0 -pg -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
else
	CFLAGS_OPTIMIZATIONS = -O3 -funroll-loops
	CFLAGS_DEBUG =

	UNAME_P := $(shell uname -p)
	ifneq ($(filter arm%,$(UNAME_P)),)
		CFLAGS_OPTIMIZATIONS +=
	else
		CFLAGS_OPTIMIZATIONS += -march=native
	endif
endif

CFLAGS_DEPENDENCIES = -MMD -MP

# Project
CFLAGS_INCLUDES += -I$(INCLUDES_DIR)
# libft
CFLAGS_INCLUDES += -I$(LIB_DIR)
# ImGui
CFLAGS_INCLUDES += -I$(IMGUI_DIR) -I$(IMGUI_DIR)/generator/output
# ImGui SDL Backend
CFLAGS_INCLUDES += `sdl2-config --cflags`
# stb
CFLAGS_INCLUDES += -I$(STB_DIR)

CFLAGS_ASAN = -fsanitize=address

CFLAGS_FINAL =	$(CFLAGS_ERRORS) $(CFLAGS_OPTIMIZATIONS) \
				$(CFLAGS_DEPENDENCIES) $(CFLAGS_INCLUDES) \
				$(CFLAGS_PLATFORM) $(CFLAGS_DEBUG) $(CFLAGS_INTERNAL) \
				$(CFLAGS)

# libft
LDFLAGS += -L$(LIB_DIR) -lft
# ImGui
LDFLAGS += cimgui.dylib
# ImGui SDL Backend
LDFLAGS += `sdl2-config --libs`
# ImGui OpenGL3 Backend
LDFLAGS += -framework OpenGL

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

	@echo $(CYAN) "Making ImGui" $(DEFAULT)
	@echo -n $(BLUE)
	CC="$(CC)" DEBUG="$(DEBUG)" $(MAKE) -C $(IMGUI_DIR)
	cp $(IMGUI_DIR)/$(IMGUI) $(IMGUI)
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Making RT" $(DEFAULT)
	@echo -n $(GREEN)
	$(MAKE) $(NAME)
	@echo -n $(DEFAULT)

	$(MAKE) -f Makefile.server
	$(MAKE) -f Makefile.client

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIRS)
	$(CC) $(CFLAGS_FINAL) -c -o $@ $<

$(OBJS_DIRS):
	mkdir -p $@

$(NAME): $(OBJS) $(LIB_DIR)/$(LIB) $(MLX_DIR)/$(MLX) $(IMGUI_DIR)/$(IMGUI)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean: clean_libs clean_self
	$(MAKE) -f Makefile.server clean
	$(MAKE) -f Makefile.client clean

clean_libs:
	@echo $(CYAN) "Cleaning libft" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(LIB_DIR) clean
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Cleaning ImGui" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(IMGUI_DIR) clean
	@echo -n $(DEFAULT)

clean_self:
	@echo $(CYAN) "Cleaning RT" $(DEFAULT)
	@echo -n $(GREEN)
	rm -rfv $(OBJS_DIR)
	@echo -n $(DEFAULT)

fclean: fclean_libs fclean_self
	$(MAKE) -f Makefile.server fclean
	$(MAKE) -f Makefile.client fclean

fclean_libs: clean_libs
	@echo $(CYAN) "Purging libft" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(LIB_DIR) fclean
	@echo -n $(DEFAULT)

	@echo $(CYAN) "Purging ImGui" $(DEFAULT)
	@echo -n $(BLUE)
	$(MAKE) -C $(IMGUI_DIR) fclean
	rm -rfv $(IMGUI)
	@echo -n $(DEFAULT)

fclean_self: clean_self
	@echo $(CYAN) "Purging RT" $(DEFAULT)
	@echo -n $(GREEN)
	rm -rfv $(NAME)
	@echo -n $(DEFAULT)

debug_init: clean_self debug

debug:
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

prepare_mac:
	brew install czmq sdl2
