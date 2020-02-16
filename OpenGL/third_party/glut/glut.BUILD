# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "glut",
    #TODO: Add targets for other platforms
    srcs = glob(["freeglut-code-r1862-trunk/freeglut/freeglut/*.c",
                 "freeglut-code-r1862-trunk/freeglut/freeglut/*.h",
                "freeglut-code-r1862-trunk/freeglut/freeglut/mswin/*.c",
                "freeglut-code-r1862-trunk/freeglut/freeglut/mswin/*.h",
                ]),
    hdrs = glob(["freeglut-code-r1862-trunk/freeglut/freeglut/include/GL/*.h"]),
    includes = ["freeglut-code-r1862-trunk/freeglut/freeglut/include"],
    visibility = ["//visibility:public"]
    # deps = ["header files"],
)