#!python
import os, subprocess, platform

# This will be re-implemented in the future, for now use jni/Android.mk !!

# Local dependency paths
# godot_glad_path = ARGUMENTS.get("headers", "glad")
#godot_headers_path = ARGUMENTS.get("headers", "godot_headers/")
#gearvr_path = ARGUMENTS.get("gearvr", os.getenv("GEARVR_PATH", "../../ovr_sdk_mobile_1.9.0/"))
android_ndk_path = ARGUMENTS.get("android-ndk-path", os.getenv("ANDROID_NDK_ROOT"))
"""
# default to release build, add target=debug to build debug build
target = ARGUMENTS.get("target", "release")

# this really only is supported on android...
#platform = ARGUMENTS.get("platform", "android")

# This makes sure to keep the session environment variables on windows, 
# that way you can run scons in a vs 2017 prompt and it will find all the required tools
#env = Environment()

bits = '64'
if 'bits' in env:
    bits = env['bits']

#if ARGUMENTS.get("use_llvm", "no") == "yes":
#    env["CXX"] = "clang++"

def add_sources(sources, directory):
    for file in os.listdir(directory):
        if file.endswith('.c'):
            sources.append(directory + '/' + file)
        elif file.endswith('.cpp'):
            sources.append(directory + '/' + file)
"""
# Not proud of it
cmd = 'ndk-build' + ' NDK_LIBS_OUT=./demo/bin'
os.system(cmd)
"""

# have to figure out what to do here....
#if platform == "android":

# add our gearvr library
env.Append(CPPPATH=[gearvr_path + 'VrApi/Include'])
target_path = 'demo/bin/arm64/godot_gearvr'
if bits == '64':
    env.Append(LIBPATH=[oculus_path + 'VrApi/Libs/Android/arm64-v8a/' + target])
else:
    env.Append(LIBPATH=[oculus_path + 'VrApi/Libs/Android/armeabi-v7a/' + target])
    target_path = 'demo/bin/arm32/godot_gearvr'

env.Append(LIBS=['libvrapi'])

# and our stuff
env.Append(CPPPATH=['.', godot_headers_path])

sources = []
add_sources(sources, "src")
# sources.append(godot_glad_path + "/glad.c")

library = env.SharedLibrary(target=target_path, source=sources)
Default(library)
"""
