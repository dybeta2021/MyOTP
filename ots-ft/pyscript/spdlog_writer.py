with open("ThostFtdcUserApiStruct.h") as fp:
    data = fp.readlines()

with open("spdlog_writer.h", "w+") as write_fp:
    name = None
    str = None
    for th, i in enumerate(data):
        if "struct" in i:
            line = i.replace("\n", "").split(" ")[1]
            name = line

            # std::ostream& operator<<(std::ostream& os, const some_class& c)
            line = """std::ostream& operator<<(std::ostream& os, const {0}& c)\n""".format(name)
            write_fp.write(line)

            line = """{\n"""
            write_fp.write(line)

            str = "return os"

        if "TThostFtdc" in i:
            line = i.split("\t")[2].replace("\n", "")
            line = line.replace(";", "")

            str_add = """<<"{0}:"<< c.{0},""".format(line)
            str += str_add
            # write_fp.write(str)

        if """};""" in i:
            str += """;\n"""
            write_fp.write(str)

            line = "};\n\n"
            write_fp.write(line)
