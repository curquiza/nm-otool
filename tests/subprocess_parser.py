import signal
from utils import file_content
from display import Display as display

output_folder = './tests/output'

class SubprocessParser:

    def __init__(self, code, output, ic_test):
        self.code               = code
        self.output             = output
        self.expect_error       = ic_test['error']
        self.expected_output    = file_content(output_folder + '/' + ic_test['output']).encode('ascii')

    def output_is_valid(self):
        return (self.expected_output == self.output)

    def code_return_is_valid(self):
        return ((self.expect_error == False and self.code == 0)
                or (self.expect_error == True and self.code != 0))

    def check_validity(self):
        return (self.output_is_valid() and self.code_return_is_valid())

    def print_failure_reasons(self):
        if (self.output_is_valid() == False):
            display.print_subtitle('output does not match')
        if (self.code_return_is_valid() == False):
            if (self.expect_error != 0):
                display.print_subtitle('error expected, but your return code is 0')
            else:
                display.print_subtitle('no error expected, but your return code is not 0')

    def print_result(self):
        if (self.check_validity() == False):
            display.print_failure("KO")
            self.print_failure_reasons()
            return False
        display.print_success("OK")
        return True

    def print_result_when_exception(self):
        if self.code == -signal.SIGSEGV:
            display.print_failure('SEGFAULT')
            return False
        elif self.code == -signal.SIGABRT:
            display.print_failure('SIGABORT')
            return False
        elif self.code < 0 :
            display.print_failure('Signal caught (' + str(self.code) + ')')
            return False
        elif self.code == 1 or self.code == 255:
            return self.print_result()
        else:
            display.print_failure('Returned a wrong exit code (' + str(self.code) + ')')
            return False
