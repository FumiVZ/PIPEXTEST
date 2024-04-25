NAME = pipex
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
BUILD_DIR = build

SRC =	code/pipex.c \
		code/error.c \
		code/child.c \
		code/free.c \
		code/command.c \
		code/utils.c \
		code/list.c

HEADER = header/child.h  header/error.h header/error_msg.h header/pipex.h header/struct.h

LIBFT = libft.a
LIB_PATH = libft

OBJECTS = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(LIBFT) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/code
	mkdir -p $(BUILD_DIR)/bonus

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB_PATH)/$(LIBFT)

$(BUILD_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LIB_PATH)

$(LIBFT):
	$(MAKE) -C $(LIB_PATH) 

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re 
