# Oculus Mobile Godot plugin

**Note:**<br> 
This plugin is in **beta**.<br>
Testing needs to be complete before it's deemed stable and ready for use.<br>
If you'd like to contribute to the testing process, follow the instructions below to setup and use the plugin, 
and report any issues you encounter. Thanks!<br>

This repository contains the source code for the Oculus Mobile Godot plugin.
See demo project as an example for how to use the plugin.

This is an Android only plugin that is only supported on the following Oculus Mobile devices:
- Oculus Quest
- Oculus Go

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
  - If using Android Studio, download version **3.5** or higher.
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
(version **1.25.0** or higher) of the Oculus Mobile SDK into the 
`ovr_sdk_mobile` directory (create the directory if it doesn't exist).
- If needed, update the `OVR_ROOT_DIR` cmake variable in the the `CMakeLists.txt` build file to point to the Oculus Mobile SDK 
containing folder.

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
When exporting the project apk in Godot, the following Android export 
`Graphics` options should be set:
- `Xr Mode` must be set to `Oculus Mobile VR`.
- `Degrees of Freedom`:
  - If deploying only on Oculus Quest, this must be set to `6DOF`
  - If deploying on Oculus Go, or on Oculus Go and Oculus Quest, 
  this must be set to `3DOF and 6DOF`

GDScript Oculus VrApi access
------------
This plugin exposes parts of the Oculus VrApi via GDNative script classes. The actual exported functions
can be found in [src/config/](src/config/).

Here is an example of how to use these classes inside GDScript:
```
onready var ovrTrackingTransform = preload("res://addons/godot_ovrmobile/OvrTrackingTransform.gdns").new()
onready var ovrGuardianSystem = preload("res://addons/godot_ovrmobile/OvrGuardianSystem.gdns").new()

func _process(delta):
	print("GetTrackingSpace: " , ovrTrackingTransform.get_tracking_space())

	print("GetBoundaryVisible: ", ovrGuardianSystem.get_boundary_visible())
	print("GetBoundaryOrientedBoundingBox: ", ovrGuardianSystem.get_boundary_oriented_bounding_box())
```

There is also a OvrUtility GDNative script class that exposes some utility functions to configure the 
compositor and query information:
```
onready var ovrUtilities = preload("res://addons/godot_ovrmobile/OvrUtilities.gdns").new()

func do_something():
  # Query the current IPD; return value is in m
  print("Current IPD is: %.1fmm" % (ovrUtilities.get_ipd() * 1000.0))

  # set a color multiply (also useful for fade to black)
  ovrUtilities.set_default_layer_color_scale(Color(1.0, 0.3, 0.4, 1.0));
```

