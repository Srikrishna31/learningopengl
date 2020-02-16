
# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "glexperiments",
    srcs = [
            "include/DefaultRenderer.h",
            "include/ISceneRenderer.h",
            "include/RectangularMeshRenderer.h",
            "include/ShaderManager.h",
            "include/SnowmanRenderer.h",
            "include/stdafx.h",
            "include/TriangleRenderer.h",
            "include/TriangleShaderRenderer.h",

            "src/DefaultRenderer.cpp",
            "src/GLExperiments.cpp",
            "src/RectangularMeshRenderer.cpp",
            "src/ShaderManager.cpp",
            "src/SnowmanRenderer.cpp",
            "src/TriangleRenderer.cpp",
            "src/TriangleShaderRenderer.cpp"
    ],
    includes = ["include"],
    deps = ["@glew"],
)
