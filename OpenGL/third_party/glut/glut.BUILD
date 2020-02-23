load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["freeglut-code-r1862-trunk/freeglut/freeglut/**"]),
    visibility = ["//visibility:private"]
)

# cc_library(
#     name = "glut",
#     #TODO: Add targets for other platforms
#     srcs = glob(["freeglut-code-r1862-trunk/freeglut/freeglut/*.c",
#                  "freeglut-code-r1862-trunk/freeglut/freeglut/*.h",
#                 "freeglut-code-r1862-trunk/freeglut/freeglut/mswin/*.c",
#                 "freeglut-code-r1862-trunk/freeglut/freeglut/mswin/*.h",
#                 ]),
#     hdrs = glob(["freeglut-code-r1862-trunk/freeglut/freeglut/include/GL/*.h"]),
#     includes = ["freeglut-code-r1862-trunk/freeglut/freeglut/include"],
#     visibility = ["//visibility:public"]
#     # deps = ["header files"],
# )

cmake_external(
    name = "glut",
    generate_crosstool_file = True,
    lib_source = ":all",
    cache_entries = {
        "FREEGLUT_BUILD_STATIC_LIBS" : "OFF",
        "FREEGLUT_BUILD_DEMOS" : "OFF",
        "CMAKE_C_COMPILER" :"/cygdrive/c/PROGRA~2/MIB055~1/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/cl.exe",
        "CMAKE_CXX_COMPILER" :"/cygdrive/c/PROGRA~2/MIB055~1/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/cl.exe",
        # "CMAKE_C_COMPILER" : "/cydgrive/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/",
    },
    lib_name = "freeglutd.lib",
    make_commands = ["MSBuild.exe INSTALL.vcxproj"],
    visibility = ["//visibility:public"]
)

# cmake_external(
#     name = "glut",
#     generate_crosstool_file = True,
#     cache_entries = {
#         "FREEGLUT_BUILD_STATIC_LIBS" : "OFF",
#         "FREEGLUT_BUILD_DEMOS" : "OFF",
#         "CMAKE_C_COMPILER" : "/cygdrive/c/PROGRA~2/MIB055~1/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/cl.exe",
#         "CMAKE_CXX_COMPILER" : "/cygdrive/c/PROGRA~2/MIB055~1/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/cl.exe",
#         # "CMAKE_C_COMPILER" : "/cydgrive/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.24.28314/bin/HostX64/x64/",
#     },
#     cmake_options = ["-G \"NMake Makefiles\""],
#     #lib_name = "freeglutd.lib",
#     lib_source = ":all",
#     make_commands = [
#         "nmake ",
#         "nmake install"
#     ],
#     static_libraries = ["freeglutd.lib"],
#     visibility = ["//visibility:public"],
# )