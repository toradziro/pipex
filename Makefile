NAME =	pipex
HEAD =	pipex.h
SRCS =	pipex.c \
		utils/split.c \
		utils/libft_utils.c \
		utils/error_handle.c \
		utils/pipex_utils.c \
		utils/pipex_utils_2.c

OBJS =	$(SRCS:.c=.o)

SRC_D =	$(SRCS:.c=.d)

CC =	gcc

FLAGS =	-MMD -g -fsanitize=leak

.c.o:
		$(CC) $(FLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)
		rm -f $(SRC_D)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

-include $(SRC_D)