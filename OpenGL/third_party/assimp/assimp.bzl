load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def import_assimp():
    http_archive(
        name = "assimp",
        type = "zip",
        url = "https://github.com/assimp/assimp/archive/v5.0.1.zip",
        build_file = "//third_party/assimp:assimp.BUILD",
    )
