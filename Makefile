# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 21:49:09 by fbabin            #+#    #+#              #
#    Updated: 2019/10/12 19:38:19 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	server
NAME2			=	client

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra #-fsanitize=address

_SRV			=	main.c server.c client_handler.c reply_handler.c \
					cmds_handler.c utils.c path.c user.c quit.c mkd.c \
					syst.c rmd.c noop.c cdup.c cwd.c pwd.c port.c list.c \
					utils_2.c dele.c pass.c stor.c retr.c eprt.c \
					data_connection.c

_CLIENT			=	main.c client.c client_handler.c utils.c process_cmd.c \
					cquit.c cuser.c cpwd.c clls.c clpwd.c clcd.c ccd.c \
					cmkdir.c crmdir.c cls.c dataserver.c port_handler.c \
					cput.c

SRV_DIR			=	srcs_server
CLIENT_DIR		=	srcs_client

SRV_SRCS		=	$(addprefix $(SRV_DIR)/,$(_SRV))
CLIENT_SRCS		=	$(addprefix $(CLIENT_DIR)/,$(_CLIENT))

SRV_ODIR		=	objs_server
CLIENT_ODIR		=	objs_client
SRV_OBJS		=	$(addprefix $(SRV_ODIR)/,$(_SRV:%.c=%.o))
CLIENT_OBJS		=	$(addprefix $(CLIENT_ODIR)/,$(_CLIENT:%.c=%.o))

LIBFT_DIR		=	libft
_LIBFT			=	libft.a
LIBTF			=	$(LIBFT_DIR)/$(_LIBFT)

INCS_DIR		=	includes
INCS			=	-I $(INCS_DIR) -I $(LIBFT_DIR)/$(INCS_DIR)
HEADER			=	$(INCS_DIR)/ft_p.h $(LIBFT_DIR)/$(INCS_DIR)/libft.h

all: lib $(HEADER) $(NAME) $(NAME2)

$(NAME): $(SRV_ODIR) $(SRV_OBJS) $(SRV_SRCS)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(SRV_OBJS) -L$(LIBFT_DIR) -lft
	@echo "$(NAME) : Done"

$(NAME2): $(CLIENT_ODIR) $(CLIENT_OBJS) $(CLIENT_SRCS)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME2) $(CLIENT_OBJS) -L$(LIBFT_DIR) -lft
	@echo "$(NAME2) : Done"

$(SRV_ODIR):
	@mkdir -p $(SRV_ODIR)

$(CLIENT_ODIR):
	@mkdir -p $(CLIENT_ODIR)

$(SRV_ODIR)/%.o: $(SRV_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

$(CLIENT_ODIR)/%.o: $(CLIENT_DIR)/%.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

lib:
	@make -C $(LIBFT_DIR)

clean:
	@make fclean -C $(LIBFT_DIR)
	@/bin/rm -rf $(SRV_ODIR)
	@echo "$(NAME) clean : Done"
	@/bin/rm -rf $(CLIENT_ODIR)
	@echo "$(NAME2) clean : Done"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(NAME) fclean : Done"
	@/bin/rm -f $(NAME2)
	@echo "$(NAME2) fclean : Done"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
