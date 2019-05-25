
def file_content(file_name):
    with open (file_name, "r") as myfile:
        str = myfile.read()
    myfile.close()
    return str
