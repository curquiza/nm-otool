class Display:

    OK        = '\033[92m'
    WARNING   = '\033[93m'
    FAIL      = '\033[91m'
    END       = '\033[0m'
    BOLD      = '\033[1m'
    UNDERLINE = '\033[4m'

    def print_failure(str):
        print(Display.FAIL + str + Display.END)

    def print_warning(str):
        print(Display.WARNING + str + Display.END)

    def print_success(str):
        print(Display.OK + str + Display.END)

    def print_title(title):
        if (len(title) > 75):
            print('{:<80}'.format(title[0:75] + '...'), end='', flush=True)
        else:
            print('{:<80}'.format(title), end='', flush=True)

    def print_subtitle(subtitle):
        print(f'  > {subtitle}', flush=True)
