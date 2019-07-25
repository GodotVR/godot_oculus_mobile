# Oculus Mobile Godot plugin

**Note:**<br> 
This plugin is in **alpha** state.<br>
Testing and resolution of remaining issues need to be complete before it's deemed stable and ready for use.<br>
If you'd like to contribute to the testing process, follow the instructions below to setup and use the plugin, 
and report any issues you encounter. Thanks!<br>

This repository contains the source code for the Oculus Mobile Godot plugin.
See demo project as an example for how to use the plugin.

This is an Android only plugin that is only supported on the following Oculus Mobile devices:
- Oculus Quest
- Oculus Go
- GearVR

The use of this plugin require Godot 3.2 or later.

License
-------
- This project is released under a MIT license.
- Please check the [Oculus Mobile SDK license](https://developer.oculus.com/licenses/mobile-3.2.1/) for information 
about the Oculus Mobile SDK used in this project.

Setup
-----
After cloning this repository make sure to initialise the submodules with `git submodule init`.
When you've pulled a newer version make sure to run `git submodule update`.<br>
The project uses `cmake` as its primary build system, which you can configure by following the setup instructions
for the **Android SDK & NDK**.

#### Android SDK & NDK
- Download and setup the [Android SDK](https://developer.android.com/studio/#command-tools).
  - If using Android Studio, download version **3.4** or higher.
  - If using the [command line tools](https://developer.android.com/studio/#command-tools), 
  download revision **26.1.1** or higher. 
  - To ensure you have the latest version, check [SDK Manager](https://developer.android.com/studio/intro/update.html#sdk-manager) for updates.  
- Add the Android SDK **cmake** binaries directory to the environment path. The directory can be found under 
`<android_sdk_location>/cmake/<cmake_version>/bin`.
  - Ensure that `cmake_version` is greater or equal to version `3.6.0`.   
- Download and setup the [latest version](https://developer.android.com/ndk/downloads) 
(version **r20** or higher) of the **Android NDK**.
- Set the environment variable `ANDROID_NDK_HOME` to the Android NDK location. 

#### Godot headers
By default the project is configured to checkout the [godot_headers](https://github.com/GodotNativeTools/godot_headers) 
repo as a submodule under the `godot_headers` directory when you run 
the `git submodule init` and `git submodule update` commands.<br>
You can edit the `GODOT_HEADERS_DIR` cmake variable in the `CMakeLists.txt` 
build file if you'd like to provide a different source for the Godot headers.<br>

#### Oculus Mobile SDK
- Download the [latest version](https://developer.oculus.com/downloads/package/oculus-mobile-sdk/)
(version **1.23.0** or higher) of the Oculus Mobile 
SDK into a sub-directory of the `ovr_sdk_mobile` directory. It's recommended to use the SDK version as the sub-directory 
name (e.g: `ovr_sdk_mobile/1.23.0/` for version **1.23.0** of the Oculus Mobile SDK).
- Update the `OVR_ROOT_DIR` cmake variable in the the `CMakeLists.txt` build file to point to the Oculus Mobile SDK 
root directory.

Build
---------
**Note**: Ensure you're using the **Android SDK**'s version of `cmake`.<br><br>
In the project root directory:
 - Navigate to the `build` directory: `cd build`
 - Run:
```
cmake -GNinja ..
cmake --build .
```

Once the build successfully completes, the plugin and its dependencies shared libraries can be found in the 
default output location: `demo/addons/godot_ovrmobile/libs/<arch>`

Deployment
------------
When exporting the project apk in Godot, make sure that `Xr Mode` under the Android export `Graphics` section is set to 
`Oculus Mobile VR`.