# Oculus Mobile SDK GDNative plugin for Godot

*WIP* This is an unfinished work in progress repository, it requires a few unsubmitted changes in the core of Godot. Check back here soon when we're a little further along!

This repository contains the source code for the Oculus Mobile SDK plugin for Godot.
See demo project as an example for how to use the plugin

This is an Android only plugin that only works on suitable Oculus Mobile devices (e.g: GearVR, Oculus Go)!
Currently only the HMD is handled!

License
-------
Please check the Oculus Mobile SDK for license information in relation to the Oculus Mobile SDK used in this project.
The rest of this project is released under a MIT license.

Compiling
---------
In order to compile this plugin you first need to download the Oculus Mobile SDK from the Oculus developer website.
You will also need the Android NDK (Make sure it's in your PATH variable) and JDK.

After cloning this repository make sure to initialise the submodules with `git submodule init`
When you've pulled a newer version make sure to run `git submodule update`

For now you will need to edit the `jni/android.mk` file to correct some paths. Still working on making that switchable

Now run:
```
ndk-build
```

After it has successfully build, copy the contents on the newly created Libs\ folder into demo\addons\godot_gearvr
