load ("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def import_glut():
    http_archive(
        name = "glut",
        type = ".zip",
        url = "https://sourceforge.net/code-snapshots/svn/f/fr/freeglut/code/freeglut-code-r1862-trunk.zip",
        sha256 = "15776d8e1e99844b333b7b3e404797a64cadca57d02be3d631068f5a6e434a49",
        build_file = "//third_party/glut:glut.BUILD"
    )
