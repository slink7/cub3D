# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scambier <scambier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 16:14:03 by scambier          #+#    #+#              #
#    Updated: 2025/11/22 19:30:12 by scambier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# === Config Variables === #

COMPILER = cc

NAME = cub3D

SOURCE_DIRECTORY = sources

SOURCES =\
	main.c\

CFLAGS = -Wall -Werror -Wextra -g3

LFLAGS =

HEADERS =\
	-I./\
	-Iinclude/\

LIBRARIES = \
	libft/libft.a\

OBJECT_DIRECTORY = objects



# === Auto Variables === #

ACTUAL_SOURCES = $(addprefix $(SOURCE_DIRECTORY)/, $(SOURCES))

OBJECTS = $(patsubst $(SOURCE_DIRECTORY)/%.c, $(OBJECT_DIRECTORY)/%.o, $(ACTUAL_SOURCES))

LFLAGS += $(addprefix -L, $(dir $(LIBRARIES))) $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIBRARIES))))

HEADERS += $(addprefix -I, $(dir $(LIBRARIES)))



# === Targets === #

all: $(NAME)

$(OBJECT_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c
	mkdir -p $(dir $@)
	$(COMPILER) -o $@ -c $< $(CFLAGS) $(HEADERS) 

%.a:
	make -C $(dir $@)

$(NAME): $(OBJECTS) $(LIBRARIES)
	$(COMPILER) -o $(NAME) $(OBJECTS) $(LFLAGS) 

clean:
	rm -rf $(OBJECT_DIRECTORY) || true

fclean: clean
	rm -rf $(NAME) || true

re: fclean all

.PHONY: all clean fclean re 
