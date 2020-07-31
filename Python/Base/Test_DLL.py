import ctypes
from ctypes import c_int, c_float
import os


# test architecture
# 4 if 32-bit, 8 if 64-bit
# if ctypes.sizeof(ctypes.c_void_p) == 4:
#     print("32-Bit")
# else:
#     print("64-Bit")

# add dll path
# it is chnages in 3.8, used to ensure consistency
os.add_dll_directory("C:/WINDOWS/system32")
os.add_dll_directory("D:/Anaconda/Library/mingw-w64/bin")  # TODO: it should not use Anaconda

# import dll file
lib_tracer  = ctypes.CDLL(os.path.join(os.getcwd(), "Tracer.dll"))
# lib_test    = ctypes.CDLL(os.path.join(os.getcwd(), "Test.dll"))

# call dll function
# lib_test.Test_printHelloWorld()
lib_tracer.RayTracer_info()
