load("//third_party/assimp:assimp.bzl", "import_assimp")
load("//third_party/glew:glew.bzl", "import_glew")
load("//third_party/freeglutd:freeglutd.bzl", "import_freeglut")
load("//third_party/glm:glm.bzl", "import_glm")

def import_dependencies():
    import_assimp()
    import_glew()
    import_freeglut()
    import_glm()
