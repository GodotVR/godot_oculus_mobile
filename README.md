# Oculus Mobile SDK GDNative plugin for Godot

*WIP* This is an unfinished work in progress repository, it requires a few unsubmitted changes in the core of Godot. Check back here soon when we're a little further along!

This repository contains the source code for the Oculus Mobile SDK plugin for Godot.
See demo project as an example for how to use the plugin

This is an Android only plugin that only works on suitable Oculus Mobile devices (e.g: GearVR, Oculus Go and Quest)!
Currently only the HMD is handled!

Make sure to use this module against the latest master of Godot, it uses a few improvements that will only be available in Godot 3.2 and later.

License
-------
Please check the Oculus Mobile SDK for license information in relation to the Oculus Mobile SDK used in this project.
The rest of this project is released under a MIT license.

Compiling
---------
In order to compile this plugin you first need to download the Oculus Mobile SDK from the Oculus developer website. Place this within the ```ovr_sdk_mobile``` subfolder.

You will also need the Android NDK (Make sure it's in your PATH variable) and JDK.

After cloning this repository make sure to initialise the submodules with `git submodule init`
When you've pulled a newer version make sure to run `git submodule update`

Now run:
```
cd jni
ndk-build
```

After it has successfully build, copy the contents on the newly created ```libs\``` folder into ```demo\addons\godot_ovr```.

Todos
-----

* Find out how we resume/halt, this likely requires changes in Godot itself.
* See about using VrAppFramework as we doubled up a few things
* Get this to work on Oculus Go and Quest
* Make additions for Gear VR + instruction so on OSIG
* Create binary version to distribute
* Change build system (scons/gradle/???) and move files into more sensible folders
* Investigate MultiView support (possibly requires driver solution in Godot): https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-multiview/
* Investigate foveated rendering support: https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/

