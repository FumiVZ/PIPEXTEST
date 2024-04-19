NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g
CC = cc
BUILD_DIR = build

SRC_LIBFT =	ft_atoi.c \
		ft_itoa.c \
		ft_putendl_fd.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_bzero.c \
		ft_putnbr_fd.c \
		ft_strlcpy.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_putstr_fd.c \
		ft_strlen.c \
		ft_toupper.c \
		ft_isalnum.c \
		ft_memcmp.c \
		ft_split.c \
		ft_strmapi.c \
		ft_isalpha.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strncmp.c \
		ft_isascii.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_strnstr.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_striteri.c \
		ft_strrchr.c \
		ft_isprint.c \
		ft_putchar_fd.c \
		ft_strjoin.c \
		ft_strtrim.c \
		printf/ft_printf.c \
		printf/ft_printf_utils.c \
		ft_lstnew_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c


OBJECTS = $(SRC_LIBFT:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/printf

$(BUILD_DIR)/%.o: %.c libft.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJECTS) 
	ar crs $(NAME) $(OBJECTS) 

re: fclean all

clean: 
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

.PHONY: re all clean fclean