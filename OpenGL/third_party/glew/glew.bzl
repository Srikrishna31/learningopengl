# load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load ("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def import_glew():
    http_archive(
        name = "glew",
        type = ".zip",
        url = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip",
        sha256 = "2700383d4de2455f06114fbaf872684f15529d4bdc5cdea69b5fb0e9aa7763f1",
        build_file = "//third_party/glew:glew.BUILD"
    )
# def import_glew():
#     new_git_repository(
#         name = "glew",
#         remote = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip",
#         # sha256 = "2700383d4de2455f06114fbaf872684f15529d4bdc5cdea69b5fb0e9aa7763f1",
#         build_file = "glew.BUILD"
#     )
