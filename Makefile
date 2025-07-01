NAME = philosophers

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

SRC_DIR = src

LIB_DIR = lib

LIBFT = $(LIB_DIR)/libft.a

SRCS = \
	main.c \
	utilits_main.c \
	threads_utilits.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@clear
	@echo "✅ ${NAME} is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_DIR)

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(ARGS)
helgrind: $(NAME)
	$(VALGRIND) --tool=helgrind ./$(NAME) $(ARGS)

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all
