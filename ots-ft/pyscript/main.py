
with open("ThostFtdcUserApiStruct.h") as fp:
    data = fp.readlines()


with open("print.cpp", "w+") as write_fp:
    name = None
    for th, i in enumerate(data):
        if "struct" in i:
            line = i.replace("\n", "").split(" ")[1]
            name = line
            line = """std::cout<<"{0}"<< std::endl;\n""".format(line)
            print(line)
            write_fp.write(line)

        if "TThostFtdc" in i:
            line = i.split("\t")[2].replace("\n", "")
            line = line.replace(";", "")
            line = """std::cout<<"{0}: " <<ptr->{0}<< std::endl;\n""".format(line)
            print(line)
            write_fp.write(line)

        if """};""" in i:
            line = """std::cout<< "{}" <<std::endl;\n""".format(name)
            print(line)
            write_fp.write(line)
            write_fp.write("\n")
            write_fp.write("\n")
            print()
            print()