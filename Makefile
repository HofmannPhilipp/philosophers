NAME = philo
CC = gcc
CFLAGS = -Werror -Wextra -Wall -I./include
DEBUG_FLAGS = -Werror -Wextra -Wall -I./include -fsanitize=address -g
SRC_DIR = ./src
VPATH = $(SRC_DIR) $(SRC_DIR)/utils $(SRC_DIR)/simulation
SRCS =	main.c utils.c init.c ft_atol.c eat.c parse.c getters.c setters.c \
		simulation.c philo_routine.c monitor_routine.c simulation_utils.c \
		mutex_utils.c
OBJS_DIR = objects
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@echo "Creating $(OBJS_DIR) directory"
	@mkdir -p $(OBJS_DIR)

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug