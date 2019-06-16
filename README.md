# Oculus Mobile Godot plugin

***`<WIP>`***<br> 
This is a work in progress which requires a few unsubmitted changes ([PR #29824](https://github.com/godotengine/godot/pull/29824)) 
in the core of Godot, and has a few remaining issues.<br>
Check back here soon when we're a little further along!<br>
***`</WIP>`***

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
- Download and setup the [latest version](https://developer.android.com/studio/#command-tools) of the **Android SDK**.
- Add the Android SDK **cmake** binaries directory to the environment path. The directory can be found under 
`<android_sdk_location>/cmake/<cmake_version>/bin`.  
- Download and setup the [latest version](https://developer.android.com/ndk/downloads) of the **Android NDK**.
- Set the environment variable `ANDROID_NDK_HOME` to the Android NDK location. 

#### Godot headers
By default the project is configured to checkout the [godot_headers](https://github.com/GodotNativeTools/godot_headers) 
repo as a submodule under the `godot_headers` directory.
You can edit the `GODOT_HEADERS_DIR` cmake variable in the `CMakeLists.txt` build file if you'd like to provide a 
different source for the Godot headers.<br>
**Note**: At the moment, the [godot_headers](https://github.com/GodotNativeTools/godot_headers) repo does not have the 
necessary dependencies to build this plugin. As such you'll need to update your Godot fork to patch in the missing 
dependencies:
- Clone the [Godot](https://github.com/godotengine/godot) repo, and patch in [PR #29824](https://github.com/godotengine/godot/pull/29824)
- Open the [`platform/android/java/AndroidManifest.xml`](https://github.com/godotengine/godot/blob/master/platform/android/java/AndroidManifest.xml)
and add the following meta-data entry above the `org.godotengine.godot.Godot` activity entry:
  - `<meta-data android:name="com.samsung.android.vr.application.mode" android:value="vr_only"/>`
- Rebuild the Godot Android shared libraries
  - **Optional**: build the export templates for your Godot fork by following [these instructions](https://docs.godotengine.org/en/latest/development/compiling/compiling_for_android.html#building-the-export-templates)
- Update the `GODOT_HEADERS_DIR` cmake variable in the `CMakeLists.txt` build file to point to the location of the 
updated headers (e.g: `<godot_fork_root_dir>/modules/gdnative/include`)

#### Oculus Mobile SDK
- Download the [latest version](https://developer.oculus.com/downloads/package/oculus-mobile-sdk/) of the Oculus Mobile 
SDK into a sub-directory of the `ovr_sdk_mobile` directory. It's recommended to use the SDK version as the sub-directory 
name (e.g: `ovr_sdk_mobile/1.23.0/` for version 1.23.0 of the Oculus Mobile SDK).
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
When exporting the project apk, make sure that `Xr Mode` under the Android export `Graphics` section is set to 
`Oculus Mobile VR`.