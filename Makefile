NAME = ft_nm

FLAG = -Wall -Wextra -Werror
CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
		utils.c \
		utils_options.c \
		sort.c \
		check_file_size.c \
		magic64_init.c \
		magic64_main.c \
		print_symb_output.c \
		clean.c \
		main.c)

OBJ_DIR = objs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

H_DIR = include
INCL = -I$(H_DIR) -I$(LIBFT_H)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INCL) -c $< -o $@
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

run_test:
	python3 tests/main_tests.py

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

re : fclean all

re_with_lib: fclean_all all
