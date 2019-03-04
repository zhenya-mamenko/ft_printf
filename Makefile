# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 13:54:51 by emamenko          #+#    #+#              #
#    Updated: 2019/03/03 16:23:18 by emamenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	libftprintf.a

.PHONY:		$(NAME) all clean fclean re

SOURCES	:=	ft_printf.c vaprintf.c \
			\
			formats/string.c formats/integer.c formats/float.c formats/ext.c \
			\
			helpers/atoi_s.c helpers/itoa_base.c helpers/str_funcs.c \
			helpers/pf_funcs.c

OBJECTS	:=	$(SOURCES:.c=.o)
OBJECTS	:=	$(subst formats/,,$(OBJECTS))
OBJECTS	:=	$(subst helpers/,,$(OBJECTS))

all:		$(NAME)

$(NAME):
			gcc -Wall -Wextra -Werror -I. -c $(SOURCES)
			ar rcs $(NAME) $(OBJECTS)

clean:
			rm -f $(OBJECTS)

fclean:		clean
			rm -f $(NAME)

re: 		fclean all

reclean:	re; make clean
