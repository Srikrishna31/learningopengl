load ("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def import_freeglut():
    http_archive(
        name = "freeglutd",
        type = "tar.gz",
        url = "https://sourceforge.net/projects/freeglut/files/latest/download",
        build_file = "//third_party/freeglutd:freeglutd.BUILD"
    )
