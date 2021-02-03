load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

filegroup(
    name = "all",
    srcs = glob(["freeglut-3.2.1/**"]),
    visibility = ["//visibility:private"]
)

# cc_library(
#     name = "freeglut",
#     #TODO: Add targets for other platforms
#     srcs = glob(["freeglut-3.2.1/src/*.h",
#                 "freeglut-3.2.1/src/fg_callbacks.c",
#                 "freeglut-3.2.1/src/fg_cursor.c",
#                 "freeglut-3.2.1/src/fg_display.c",
#                 "freeglut-3.2.1/src/fg_ext.c",
#                 "freeglut-3.2.1/src/fg_font_data.c",
#                 "freeglut-3.2.1/src/fg_gamemode.c",
#                 "freeglut-3.2.1/src/fg_geometry.c",
#                 "freeglut-3.2.1/src/fg_gl2.c",
#                 "freeglut-3.2.1/src/fg_gl2.h",
#                 "freeglut-3.2.1/src/fg_init.c",
#                 "freeglut-3.2.1/src/fg_init.h",
#                 "freeglut-3.2.1/src/fg_internal.h",
#                 "freeglut-3.2.1/src/fg_input_devices.c",
#                 "freeglut-3.2.1/src/fg_joystick.c",
#                 "freeglut-3.2.1/src/fg_main.c",
#                 "freeglut-3.2.1/src/fg_misc.c",
#                 "freeglut-3.2.1/src/fg_overlay.c",
#                 "freeglut-3.2.1/src/fg_spaceball.c",
#                 "freeglut-3.2.1/src/fg_state.c",
#                 "freeglut-3.2.1/src/fg_stroke_mono_roman.c",
#                 "freeglut-3.2.1/src/fg_stroke_roman.c",
#                 "freeglut-3.2.1/src/fg_structure.c",
#                 "freeglut-3.2.1/src/fg_teapot.c",
#                 "freeglut-3.2.1/src/fg_teapot_data.h",
#                 "freeglut-3.2.1/src/fg_videoresize.c",
#                 "freeglut-3.2.1/src/fg_window.c",
#                 "freeglut-3.2.1/src/fg_font.c",
#                 "freeglut-3.2.1/src/fg_menu.c",
#                 "freeglut-3.2.1/src/mswin/*.c",
#                 "freeglut-3.2.1/src/mswin/*.h",
#                 "freeglut-3.2.1/src/util/*.h",
#                 "freeglut-3.2.1/src/util/*.c",
#                 ]),
#     hdrs = glob(["freeglut-3.2.1/include/GL/*.h"]),
#     includes = ["freeglut-3.2.1/include"],
#     visibility = ["//visibility:public"]
#     # deps = ["header files"],
# )


# cmake_external(
#     name = "glut",
#     generate_crosstool_file = True,
#     lib_source = ":all",
#     cache_entries = {
#         "FREEGLUT_BUILD_STATIC_LIBS" : "OFF",
#         "FREEGLUT_BUILD_DEMOS" : "OFF",
#     },
#     lib_name = "freeglutd.lib",
#     make_commands = ["MSBuild.exe INSTALL.vcxproj"],
#     visibility = ["//visibility:public"]
# )

cmake_external(
    name = "libglut",
    generate_crosstool_file = True,
    cache_entries = {
        "FREEGLUT_BUILD_STATIC_LIBS" : "ON",
        "FREEGLUT_BUILD_DEMOS" : "OFF",
    },
    #cmake_options = ["-G \"NMake Makefiles\""],
    # cmake_options = ["-G \"Unix Makefiles\""],
    # lib_name = "freeglutd",
    lib_source = ":all",
    # make_commands = [
    #     "nmake ",
    #     "nmake install"
    # ],
    make_commands = [
        "make",
        "make install"
    ],
    # static_libraries = ["freeglutd.lib"],
    # out_include_dir = "include/freeglut",
    visibility = ["//visibility:public"],
)
