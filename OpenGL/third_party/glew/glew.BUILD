# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "glew",
    srcs = glob(["glew-2.1.0/src/*.c"]),
    hdrs = glob(["glew-2.1.0/include/GL/*.h"]),
    includes = ["glew-2.1.0/include/"],
    visibility = ["//visibility:public"]
    # deps = ["header files"],
)