LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

################################################################################
#################################### RULES #####################################
################################################################################

all : $(LIBFT)
	printf "\033[1;33m%s\033[0m\n" "FT_NM"
	@make -C nm

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

run_test:
	@python3.7 tests/main_tests.py

clean :
	@make -C nm clean

fclean : clean
	@make -C nm fclean

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

re : fclean all

re_with_lib: fclean_all all
