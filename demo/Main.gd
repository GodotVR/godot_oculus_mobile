extends Spatial

func _ready():
	# Find the interface and initialise
	var arvr_interface = ARVRServer.find_interface("GearVR")
	print("==============================================================")
	if arvr_interface and arvr_interface.initialize():
		get_viewport().arvr = true
		print("Loaded GearVR")
	else:
		print("Failed to enable GearVR")

func _process(delta):
	# Test for escape to close application, space to reset our reference frame
	if (Input.is_key_pressed(KEY_ESCAPE)):
		get_tree().quit()
	elif (Input.is_key_pressed(KEY_SPACE)):
		# Calling center_on_hmd will cause the ARVRServer to adjust all tracking data so the player is centered on the origin point looking forward
		ARVRServer.center_on_hmd(true, true)
