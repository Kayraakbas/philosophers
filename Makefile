NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -pthread
RM = rm -f

SRC_PATH = ./
SRCS_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

SRC = 	philo.c

SRCS_SRC = philo_utils.c \
		   ft_atoll.c \
		   ft_isdigit.c \
		   arg_check_utils.c \
		   monitor_thread_utils.c \
		   philo_state_utils.c \
		   safety_utils.c \

MAIN_SRCS = $(addprefix $(SRC_PATH), $(SRC))
UTILS_SRCS = $(addprefix $(SRCS_PATH), $(SRCS_SRC))
ALL_SRCS = $(MAIN_SRCS) $(UTILS_SRCS)

OBJ = $(SRC:.c=.o)
SRCS_OBJ = $(SRCS_SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ)) $(addprefix $(OBJ_PATH), $(SRCS_OBJ))

INC = -I $(INC_PATH)

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "🔷 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@echo "🔷 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@echo "✅ Building $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LDFLAGS)

clean:
	@echo "🧹Cleaning object files..."
	@rm -rf $(OBJ_PATH)
	@echo "✅ Cleaning completed!"

fclean: clean
	@echo "🧹 Full cleaning is in progress..."
	@rm -f $(NAME)
	@echo "✅ Full cleaning completed!"

re: fclean all

.PHONY: all clean fclean re