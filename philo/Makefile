NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

SRC_DIR = src

SRCS = \
	main.c \
	utilits_main.c \
	simulation.c \
	simulation_utils.c \
	ft_error.c \
	monitor.c \
	lib_func.c \
	philo_verifications.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@clear
	@echo "✅ ${NAME} is compiled."

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(ARGS)
helgrind: $(NAME)
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

clean:
	@rm -f $(OBJS)
	@clear
	@echo "🗑️ Objects removed."

fclean: clean
	@rm -f $(NAME)
	@clear
	@echo "🗑️ Program and objects removed."

re: fclean all
