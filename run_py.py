import ctypes
import sys

clib = ctypes.CDLL("so_files/allFunctions.so")
clib.connect()


len_argv = len(sys.argv)

for arg in range(1, len_argv):
    clib.getArgumentsFromInput((sys.argv[arg]))




