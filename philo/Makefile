SRCS		= philo.c \
			  utils.c \
			  init.c \
			  main.c

SRCS		:= $(addprefix src/,$(SRCS)) 
OBJS		= ${SRCS:.c=.o}
NAME		= philo
CC			= gcc
MAKE		= make
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -pthread -Iinclude

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
all:			$(NAME)
clean:
				${RM} ${OBJS}
fclean:			clean
				${RM} $(NAME)
re:				fclean all
.PHONY:			all clean fclean re
