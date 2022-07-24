with open("ThostFtdcUserApiStruct.h") as fp:
    data = fp.readlines()

with open("spdlog_print.h", "w+") as write_fp:
    ptr_name = None
    var_end = None
    for th, i in enumerate(data):
        if "struct" in i:
            line = i.replace("\n", "").split(" ")[1]
            str = """SPDLOG_TRACE("{0}");\n""".format(line)
            var_str = ""
            ptr_name = "p" + line.replace("CThostFtdc", "")
            write_fp.write(str)
            var_end = str

        if "TThostFtdc" in i:
            line = i.split("\t")[2].replace("\n", "")
            line = line.replace(";", "")

            str = "SPDLOG_TRACE(" + "\"" +  line + ":{}\", "
            var_str = "{0}->{1}".format(ptr_name, line)
            str += var_str
            str += ");"

            # str = """ "{0}:" """.format(line)

            # str = """SPDLOG_TRACE(""" + str + var_str + """);\n"""

            str += "\n"
            write_fp.write(str)

        if """};""" in i:
            write_fp.write(var_end)
            write_fp.write("\n")

