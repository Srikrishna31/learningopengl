load ("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def import_glm():
    http_archive(
        name = "glm",
        type = ".zip",
        url = "https://github.com/g-truc/glm/archive/stable.zip",
        sha256 = "6b092b47d1727ef5e3adb2191350da82df57d10b3203187cc506c535a1cf64fb",
        build_file = "//third_party/glm:glm.BUILD"
    )
