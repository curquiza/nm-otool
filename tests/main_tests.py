import sys
import subprocess
from input_cmds import INPUT_CMDS as ic_test_tab
from subprocess_parser import SubprocessParser
from display import Display as display

def test_processing(ic_test):
    try:
        output = subprocess.check_output(ic_test['cmd'], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        spp = SubprocessParser(exc.returncode, exc.output, ic_test)
        return spp.print_result_when_exception()
    else:
        spp = SubprocessParser(0, output, ic_test)
        return spp.print_result()

def tests_loop(tests_tab):
    failed_tests_count = 0
    for ic_test in tests_tab:
        display.print_title(ic_test['cmd'])
        ret = test_processing(ic_test)
        failed_tests_count += (0 if ret else 1)
    return 0 if failed_tests_count == 0 else 1

def main():
    return tests_loop(ic_test_tab)

if __name__== "__main__":
    sys.exit(main())
