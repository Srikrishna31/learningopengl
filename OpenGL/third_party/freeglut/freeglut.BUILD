load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["freeglut-3.2.1/**"]),
    visibility = ["//visibility:private"]
)

cmake_external(
    name = "libglut",
    generate_crosstool_file = True,
    cache_entries = {
        "FREEGLUT_BUILD_STATIC_LIBS" : "ON",
        "FREEGLUT_BUILD_DEMOS" : "OFF",
    },
    cmake_options = select({ 
        "@bazel_tools//src/conditions:linux_x86_64" : ["-G \"Unix Makefiles\""],
        "@bazel_tools//src/conditions:windows" : ["-G \"NMake Makefiles\""]
    }),
    lib_source = ":all",
    make_commands = select({
        "@bazel_tools//src/conditions:linux_x86_64": [
                                                        "make",
                                                        "make install"
                                                        ],
        "@bazel_tools//src/conditions:windows" : [
                                                        "nmake", 
                                                        "nmake install"
                                                    ]
    }),
    visibility = ["//visibility:public"],
)
