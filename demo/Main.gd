extends Spatial

onready var ovr_init_config = preload("res://addons/godot_ovrmobile/OvrInitConfig.gdns").new()
onready var ovr_runtime_config = preload("res://addons/godot_ovrmobile/OvrRuntimeConfig.gdns").new()

func _ready():
	# Get the count of available interfaces.
	var interface_count = ARVRServer.get_interface_count()
	print("Interfaces count: ")
	print(interface_count)
	
	# Find the interface and initialise
	var arvr_interface = ARVRServer.find_interface("OVRMobile")
	print("==============================================================")
	if !arvr_interface:
		print("Couldn't find OVR interface")
	else:
		# Configure the interface init parameters.
		ovr_init_config.set_render_target_size_multiplier(1)
		if arvr_interface.initialize():
			get_viewport().arvr = true
			print("Loaded OVRMobile")
		else:
			print("Failed to enable OVRMobile")

var first_time = true
var perform_runtime_config = false

func _process(delta):
	if first_time:
		print("First time processing.")
		first_time = false
	else:
		if !perform_runtime_config:
			ovr_runtime_config.set_clock_levels(1, 1)
			ovr_runtime_config.set_extra_latency_mode(0)
			perform_runtime_config = true
