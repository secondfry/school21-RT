# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oadhesiv <secondfry+school21@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 17:41:01 by oadhesiv          #+#    #+#              #
#    Updated: 2021/07/18 15:54:33 by oadhesiv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LFT_FUNCTIONS_PART1 = memset bzero memcpy memccpy memmove memchr memcmp \
	strlen strdup strcpy strncpy strcat strncat strlcat strchr strrchr strstr \
	strnstr strcmp strncmp \
	atoi \
	isalpha isdigit isalnum isascii isprint \
	toupper tolower

LFT_FUNCTIONS_PART2 = memalloc memdel \
	strnew strdel strclr striter striteri strmap strmapi strequ strnequ \
	strsub strjoin strtrim strsplit \
	itoa \
	putchar putstr putendl putnbr \
	putchar_fd putstr_fd putendl_fd putnbr_fd

LFT_FUNCTIONS_BONUS = lstnew lstdelone lstdel lstadd lstiter lstmap

LFT_FUNCTIONS_PRSNL = atol ltoa ltoa_static ltoa_hex_static \
	putlong putlong_fd putchar_color putstr_color \
	print_ptr print_memory print_list \
	strrev strtol \
	isspace \
	ptr_check

LFT_FUNCTIONS = $(LFT_FUNCTIONS_PART1)\
				$(LFT_FUNCTIONS_PART2)\
				$(LFT_FUNCTIONS_BONUS)\
				$(LFT_FUNCTIONS_PRSNL)

FUNCTIONS = get_next_line \
	byte_array_new byte_array_resize byte_array_add byte_array_has \
	byte_array_destroy \
	ptr_array_new ptr_array_resize ptr_array_add ptr_array_has

OBJECTS = 	$(patsubst %,objs/ft_%.o,$(LFT_FUNCTIONS)) \
			$(patsubst %,objs/%.o,$(FUNCTIONS))
DEPS =		$(patsubst %,objs/ft_%.d,$(LFT_FUNCTIONS)) \
			$(patsubst %,objs/%.d,$(FUNCTIONS))

OBJ_DIR = ./objs

CFLAGS_ERRORS = -Wall -Wextra -Werror

ifeq ($(DEBUG),1)
	CFLAGS_OPTIMIZATIONS = -funroll-loops
	CFLAGS_DEBUG = -O0 -pg -g -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
else
	CFLAGS_OPTIMIZATIONS = -O3 -funroll-loops -march=native
	CFLAGS_DEBUG =
endif

CFLAGS_DEPENDENCIES = -MMD -MP
CFLAGS_SO = -fPIC -shared
CFLAGS_ASAN = -fsanitize=address
CFLAGS :=	$(CFLAGS_ERRORS) $(CFLAGS_OPTIMIZATIONS) $(CFLAGS_DEPENDENCIES) \
			$(CFLAGS_DEBUG) \
			$(CFLAGS)

NAME = libft.a
DYNN = libft.so

ifeq ($(origin CC), default)
CC = clang
endif

.PHONY: all clean fclean re so

all: $(NAME)

-include $(DEPS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

so: $(DYNN)

$(DYNN): $(OBJECTS)
	$(CC) $(CFLAGS_SO) -o $(DYNN) $(OBJECTS)

objs/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS)
	rm -rfv objs

fclean: clean
	rm -f $(NAME) $(DYNN)

re: fclean all
