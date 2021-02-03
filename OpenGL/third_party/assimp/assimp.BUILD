load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["assimp-5.0.1/**"]),
    visibility = ["//visibility:private"]
)

cmake_external(
    name = "libassimp",
    generate_crosstool_file = True,
    cache_entries = {
        "BUILD_SHARED_LIBS" : "OFF",
        "ASSIMP_BUILD_ZLIB" : "ON",
        "ASSIMP_BUILD_TESTS" : "OFF",
        "ASSIMP_BUILD_ASSIMP_TOOLS" : "ON"
    },
    cmake_options = select({
        "@bazel_tools//src/conditions:linux_x86_64" : ["-G \"Unix Makefiles\""],
        "@bazel_tools//src/conditions:windows" : ["-G \"NMake Makefiles\""]
    }),
    lib_source = ":all",
    static_libraries = ["libassimp.a", "libIrrXML.a", "libzlibstatic.a"],
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