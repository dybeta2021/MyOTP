with open("ThostFtdcUserApiStruct.h") as fp:
    data = fp.readlines()

with open("spdlog_ctp.h", "w+") as write_fp:
    ptr_name = None
    str = None
    var_str = ""
    for th, i in enumerate(data):
        if "struct" in i:
            line = i.replace("\n", "").split(" ")[1]
            str = """SPDLOG_TRACE("{0},""".format(line)
            var_str = ""
            ptr_name = "p" + line.replace("CThostFtdc", "")
            print(ptr_name)

        if "TThostFtdc" in i:
            line = i.split("\t")[2].replace("\n", "")
            line = line.replace(";", "")

            str += "{0}:".format(line) + "{},"
            var_str += ",{0}->{1}".format(ptr_name, line)
            print(str)
            print(var_str)

        if """};""" in i:
            line = str[:-1] + """" """ + var_str + ");\n"
            write_fp.write(line)
            write_fp.write("\n")

