# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 21:49:09 by fbabin            #+#    #+#              #
#    Updated: 2019/08/11 22:04:21 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	server

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra

_SRV			=	server.c

SRV_DIR			=	srcs_srv

SRV_SRCS		=	$(addprefix $(SRV_DIR)/,$(_SRV))

SRV_ODIR		=	objs_srv
SRV_OBJS		=	$(addprefix $(SRV_ODIR)/,$(_SRV:%.c=%.o))

PRINTF_DIR		=	ft_printf
_PRINTF			=	libftprintf.a
PRINTF			=	$(PRINTF_DIR)/$(_PRINTF)

INCS_DIR		=	includes
INCS			=	-I $(INCS_DIR) -I $(PRINTF_DIR)/$(INCS_DIR)
HEADER			=	$(INCS_DIR)/ft_p.h \
					$(PRINTF_DIR)/$(INCS_DIR)/ft_printf.h

all: lib $(HEADER) $(NAME)

$(NAME): $(SRV_ODIR) $(SRV_OBJS) $(SRV_SRCS)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) -L$(PRINTF_DIR) -lftprintf $(SRV_OBJS)
	@echo "$(NAME) : Done"

$(SRV_ODIR):
	@mkdir -p $(SRV_ODIR)

$(SRV_ODIR)/%.o: $(SRV_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

lib:
	@make -C $(PRINTF_DIR)

clean:
	@make fclean -C $(PRINTF_DIR)
	@/bin/rm -rf $(SRV_ODIR)
	@echo "$(NAME) clean : Done"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) fclean : Done"

re:
	@make fclean
	@make

.PHONY: all clean fclean re
