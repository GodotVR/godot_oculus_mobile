# Oculus Mobile Godot plugin

**Note:**<br>
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
- Please check the [Oculus Mobile SDK license](https://developer.oculus.com/licenses) for information
about the Oculus Mobile SDK used in this project.

Setup
-----
After cloning this repository make sure to initialise the submodules with `git submodule update --init --recursive`.
When you've pulled a newer version make sure to run `git submodule update --init --recursive`.<br>
The project uses `gradle` as its primary build system, which you can configure by following the setup instructions
for the **Android SDK & NDK**.

#### Android SDK & NDK
- Download and setup the [Android SDK](https://developer.android.com/studio/#command-tools).
  - If using Android Studio, download version **3.6.1** or higher.
  - If using the [command line tools](https://developer.android.com/studio/#command-tools),
  download revision **26.1.1** or higher.
  - To ensure you have the latest version, check [SDK Manager](https://developer.android.com/studio/intro/update.html#sdk-manager) for updates.
  - Set the environment variable `ANDROID_HOME` to the Android SDK location.
- Follow the instructions [here](https://developer.android.com/studio/projects/install-ndk#specific-version) and install version **21.0.6113669** of the NDK.

#### Godot libraries
- Checkout the [godot-cpp](https://github.com/GodotNativeTools/godot-cpp) repo as a submodule by running the following command: `git submodule update --init --recursive`.
  - The [godot-cpp](https://github.com/GodotNativeTools/godot-cpp) repo will checkout under the `plugin/libs/godot-cpp` directory.
- Navigate to the `plugin/libs/godot-cpp` directory and follow [these steps](https://github.com/GodotNativeTools/godot-cpp/tree/master#compiling-the-cpp-bindings-library) to generate the cpp bindings.

#### Oculus Mobile SDK
- Download the [latest version](https://developer.oculus.com/downloads/package/oculus-mobile-sdk/)
(**Oculus Mobile SDK 14.0** (1.31.0) or higher) of the Oculus Mobile SDK and extract it into the
`plugin/libs/ovr_sdk_mobile` directory (create the directory if it doesn't exist).
- If needed, update the `OVR_ROOT_DIR` cmake variable in the the `plugin/CMakeLists.txt` build file to point to the Oculus Mobile SDK
containing folder.

Build
-----
#### Generate plugin AAR files
In the project root directory:
 - Run `./gradlew :generatePluginBinary` to generate the plugin AAR files.
 - Once the build successfully completes, the AAR files can be found in the `build/outputs/pluginBin` directory.

**Note:** A release version of the plugin AAR file will be made available for each version update in the [release section](https://github.com/GodotVR/godot_oculus_mobile/releases).

##### Generate shared libraries ( Advanced - For maintainers only )
In the project root directory:
 - Run `./gradlew :generateSharedLibs` to generate the plugin shared libraries.
 - Once the build successfully completes, the shared libraries can be found in the `build/outputs/sharedLibs` directory.

Deployment
----------
**Note:**  
Version `2.0.0` (and higher) of the plugin requires the use of [Android custom build templates](https://docs.godotengine.org/en/3.2/getting_started/workflow/export/android_custom_build.html) ([setup instructions](https://docs.godotengine.org/en/3.2/getting_started/workflow/export/android_custom_build.html#set-up-the-custom-build-environment)).  
Deployment instructions for version `1.0.0` of the plugin can be found [here](https://github.com/GodotVR/godot_oculus_mobile/tree/1.0.0#deployment).

In the editor `FileSystem` pane, make sure the plugin AAR file is added to the `res://android/plugins` directory.  
When exporting the project apk in Godot, the following Android export options should be set:
- `Xr Features`
  - `Xr Mode` must be set to `Oculus Mobile VR`.
  - `Degrees of Freedom`:
    - If deploying only on Oculus Quest, this must be set to `6DOF`
    - If deploying on Oculus Go, or on Oculus Go and Oculus Quest,
    this must be set to `3DOF and 6DOF`
  - `Hand Tracking`: This is only supported on the **Oculus Quest**
    - Select `None` if your app doesn't need hand tracking
    - Select `Optional` if your app can use hand tracking, but doesn't require it (i.e: also works with controllers).
    - Select `Required` if your app only uses hand tracking.
- `Custom Template`
  - `Use Custom Build` must be enabled.
  - `Plugins` list must contain `OVRMobile`. This enables the `OVRMobile` plugin for the project.

GDScript Oculus VrApi access
------------
This plugin exposes parts of the Oculus VrApi via GDNative script classes.

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
compositor or query information:
```
onready var ovrUtilities = preload("res://addons/godot_ovrmobile/OvrUtilities.gdns").new()

func do_something():
  # Query the current IPD; return value is in m
  print("Current IPD is: %.1fmm" % (ovrUtilities.get_ipd() * 1000.0))

  # set a color multiply (also useful for fade to black)
  ovrUtilities.set_default_layer_color_scale(Color(1.0, 0.3, 0.4, 1.0));

  # query controller acceleration/velocities; return value is Vector3
  print(ovrUtilities.get_controller_angular_velocity(1)); # parameter is the controller_id (either 1 or 2)
  print(ovrUtilities.get_controller_linear_velocity(1));
  print(ovrUtilities.get_controller_angular_acceleration(1));
  print(ovrUtilities.get_controller_linear_acceleration(1));

  # the same is available for the head:
  print(ovrUtilities.get_head_angular_velocity());
  print(ovrUtilities.get_head_linear_velocity());
  print(ovrUtilities.get_head_angular_acceleration());
  print(ovrUtilities.get_head_linear_acceleration());
```

Performance settings are in the OvrPerformance GDNative script class:
```
onready var ovrPerformance = preload("res://addons/godot_ovrmobile/OvrPerformance.gdns").new()

func change_performance_settings():
    # enable the extra latency mode: this gives some performance headroom at the cost
    # of one more frame of latency
  	ovrPerformance.set_extra_latency_mode(1); 
		
    # set fixed foveation level
    # for details see https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
		ovrPerformance.set_foveation_level(4); 

    # if you want dynamic foveation make sure to set the maximum desired foveation with the previous function
    # before you enable dynamic foveation
		ovrPerformance.set_enable_dynamic_foveation(true);
```

Hand Tracking (experimental)
------------
The hand tracking API is still in a very early state and might change in future updates. It is contained in `OvrHandTracking.gdns`. To see an example
on how it can be used check the example setup in [demo/addons/godot_ovrmobile/example_scenes/ARVROriginWithHandTracking.gd](demo/addons/godot_ovrmobile/example_scenes/ARVROriginWithHandTracking.gd) and the associated scene file.
To test this in the demo replace the ARVROriginWithInitiAndMovement scene reference with the provided ARVROriginWithHandTracking.tscn.

To enable hand tracking, make sure to follow the **Deployment/Hand Tracking** steps above.


Advanced GDScript Oculus VrApi access
------------
In addition to the official API above there is the experimental `OvrVrApiProxy.gdns`
class that exposes partially the low level property setters/getters from the VrApi.h.
This API is to be considered temporary and might be removed in future releases of the plugin. If possible it is recommended to use the offical API described above.
The functions inside the API rely on enum values so there is an convenience class `OvrVrApiTypes.gd` that contains the enum values.
In the example below you can see a sample usage of the API. For details of the different enum values and query options
please check the VrApi.h file from the oculus mobile sdk.
```
onready var ovr_vr_api_proxy = preload("res://addons/godot_ovrmobile/OvrVrApiProxy.gdns").new();
onready var ovr_types = preload("res://addons/godot_ovrmobile/OvrVrApiTypes.gd").new();

func test_property_access():
	print("Testing vrapi access:")
	print("System property:")
	print("  vrapi_get_system_property_int(VRAPI_SYS_PROP_DEVICE_TYPE) = ", ovr_vr_api_proxy.vrapi_get_system_property_int(ovr_types.OvrSystemProperty.VRAPI_SYS_PROP_DEVICE_TYPE));
	print("  vrapi_get_system_property_int(VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH) = ", ovr_vr_api_proxy.vrapi_get_system_property_int(ovr_types.OvrSystemProperty.VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH));
	
	print("Property:")
	print("  vrapi_get_property_int(VRAPI_DEVICE_EMULATION_MODE) = ", ovr_vr_api_proxy.vrapi_get_property_int(ovr_types.OvrProperty.VRAPI_DEVICE_EMULATION_MODE));
	print("  vrapi_get_property_int(VRAPI_ACTIVE_INPUT_DEVICE_ID) = ", ovr_vr_api_proxy.vrapi_get_property_int(ovr_types.OvrProperty.VRAPI_ACTIVE_INPUT_DEVICE_ID));
	print("  vrapi_get_property_int(VRAPI_FOVEATION_LEVEL) = ", ovr_vr_api_proxy.vrapi_get_property_int(ovr_types.OvrProperty.VRAPI_FOVEATION_LEVEL));
	ovr_vr_api_proxy.vrapi_set_property_int(ovr_types.OvrProperty.VRAPI_FOVEATION_LEVEL, 3);
	print("  vrapi_get_property_int(VRAPI_FOVEATION_LEVEL) = ", ovr_vr_api_proxy.vrapi_get_property_int(ovr_types.OvrProperty.VRAPI_FOVEATION_LEVEL));
	
	print("System Status:")
	print("  vrapi_get_system_status_int(VRAPI_SYS_STATUS_MOUNTED) = ", ovr_vr_api_proxy.vrapi_get_system_status_int(ovr_types.OvrSystemStatus.VRAPI_SYS_STATUS_MOUNTED));
	print("  vrapi_get_system_status_int(VRAPI_SYS_STATUS_RENDER_LATENCY_MILLISECONDS) = ", ovr_vr_api_proxy.vrapi_get_system_status_int(ovr_types.OvrSystemStatus.VRAPI_SYS_STATUS_RENDER_LATENCY_MILLISECONDS));
	print("  vrapi_get_system_status_int(VRAPI_SYS_STATUS_FRONT_BUFFER_SRGB) = ", ovr_vr_api_proxy.vrapi_get_system_status_int(ovr_types.OvrSystemStatus.VRAPI_SYS_STATUS_FRONT_BUFFER_SRGB));
	
```
