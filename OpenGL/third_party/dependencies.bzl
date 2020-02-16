load("//third_party/glew:glew.bzl", "import_glew")
load("//third_party/glut:glut.bzl", "import_glut")
load("//third_party/glm:glm.bzl", "import_glm")

def import_dependencies():
    import_glew()
    import_glut()
    import_glm()
