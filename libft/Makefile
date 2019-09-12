# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 17:49:24 by fbabin            #+#    #+#              #
#    Updated: 2019/08/14 21:54:55 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra -Ofast

_MEM			=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
					ft_memmove.c ft_memchr.c ft_memcmp.c \
					ft_memalloc.c ft_memdel.c ft_memalloc2.c ft_memdup.c \
					ft_char2alloc.c ft_int2alloc.c \

_STR			=	ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
					ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
					ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
					ft_strnew.c ft_strdel.c ft_strclr.c \
					ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
					ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
					ft_strtrim.c ft_strsplit.c ft_strreplace.c ft_split.c \
					ft_strcat.c ft_strmjoin.c ft_strspn.c ft_strcspn.c \
					ft_strbspn.c ft_strbcspn.c ft_strchrindex.c \
					ft_charinset.c ft_strjoinclr.c ft_strnjoinclr.c

_ARRAY			=	ft_join.c ft_quicksort.c ft_mergesort.c ft_array_dump.c \

_LST			=	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
					ft_lstiter.c ft_lstmap.c ft_lstcreate.c ft_lstpushback.c \
					ft_lstpushfront.c ft_lstsize.c ft_lstlast.c ft_lstclear.c \
					ft_lstatpos.c ft_lstreverse.c ft_lstfind.c \
					ft_lstremoveif.c ft_lstmerge.c ft_lstdump.c ft_lstsort.c \

_BTREE			=	ft_btreecreate.c ft_btreepush.c ft_btreeprefix.c \
					ft_btreeinfix.c ft_btreepostfix.c

_CONVERT		=	ft_atoi.c ft_itoa.c ft_itoa_base.c \
					ft_ftoa.c ft_ltoa.c ft_ltoa_base.c ft_lltoa.c \
					ft_llutoa.c ft_lltoa_base.c ft_llutoa_base.c \
					ft_atol.c ft_atoll.c ft_atollu.c ft_long_atoi.c

_UTILS			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c \
					ft_isspace.c ft_getopt.c ft_free2.c \
					ft_iswp.c  ft_tabsize.c ft_abs.c ft_swap.c

_IO				=	ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c get_next_line.c sget_next_line.c \

_FT_PRINTF		=	ft_printf.c padding.c xtract.c handler_wc.c \
					handler_ws.c handler_num.c handler_fnk.c utils.c \
					utils2.c utils3.c \

MEM_DIR			=	srcs/mem
STR_DIR			=	srcs/str
ARRAY_DIR		=	srcs/array
LST_DIR			=	srcs/lst
BTREE_DIR		=	srcs/btree
CONVERT_DIR		=	srcs/convert
IO_DIR			=	srcs/io
UTILS_DIR		=	srcs/utils
FT_PRINTF_DIR	=	srcs/ft_printf
MEM				=	$(addprefix $(MEM_DIR)/, $(_MEM))
STR				=	$(addprefix $(STR_DIR)/, $(_STR))
ARRAY			=	$(addprefix $(ARRAY_DIR)/, $(_ARRAY))
LST				=	$(addprefix $(LST_DIR)/, $(_LST))
BTREE			=	$(addprefix $(BTREE_DIR)/, $(_BTREE))
CONVERT			=	$(addprefix $(CONVERT_DIR)/, $(_CONVERT))
UTILS			=	$(addprefix $(UTILS_DIR)/, $(_UTILS))
IO				=	$(addprefix $(IO_DIR)/, $(_IO))
FT_PRINTF		=	$(addprefix $(FT_PRINTF_DIR)/, $(_FT_PRINTF))

LIBS			= $(MEM) $(STR) $(ARRAY) $(LST) $(BTREE) $(CONVERT) $(UTILS) $(IO) $(FT_PRINTF)
OBJS			= $(LIBS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)
		@echo "$(NAME) : Done"

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I includes/

clean:
		@/bin/rm -f $(OBJS)
		@echo "libft clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "libft fclean : $(_GREEN)Done$(_END)"

re: fclean all

.PHONY: all clean fclean re
