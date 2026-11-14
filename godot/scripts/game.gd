extends Node2D

# A deliberately authored first level: each section has its own rhythm and mode.
const LEVEL_END := 12200.0
const FLOOR_Y := 590.0
const CEILING_Y := 105.0
const RUN_SPEED := 285.0
const GRAVITY := 1850.0
const JUMP_SPEED := -690.0

var player := Vector2(150, FLOOR_Y - 24)
var velocity := Vector2.ZERO
var camera_x := 0.0
var mode := "CUBE"
var mode_index := 0
var grounded := true
var gravity_sign := 1.0
var jump_lock := false
var dead := false
var won := false
var attempts := 1
var trail: Array[Vector2] = []
var platforms: Array[Rect2] = []
var spikes: Array[Vector2] = []
var gates := [
	{"x": 1850.0, "mode": "SHIP"},
	{"x": 3550.0, "mode": "UFO"},
	{"x": 5250.0, "mode": "BALL"},
	{"x": 6950.0, "mode": "WAVE"},
	{"x": 8650.0, "mode": "ROBOT"},
	{"x": 10350.0, "mode": "SPIDER"}
]
var hud: Label
var progress: ProgressBar
var mode_label: Label
var message: Label

func _ready() -> void:
	_build_level()
	_make_hud()
	queue_redraw()

func _build_level() -> void:
	# Cube intro: spaced pairs and a raised platform, not a random obstacle stream.
	_add_spike(650); _add_spike(1030); _add_spike(1110)
	_add_platform(1320, 500, 260, 28)
	_add_spike(1650)
	# Ship tunnel: ceiling/floor teeth form a readable flight corridor.
	_add_spike(2150, 0); _add_spike(2500, 0); _add_spike(2840, 0)
	_add_spike(3180); _add_spike(3330)
	# UFO: short landing islands with deliberate gaps.
	_add_platform(3850, 480, 180, 24); _add_platform(4230, 410, 190, 24)
	_add_platform(4640, 485, 210, 24); _add_spike(4960)
	# Ball: floor/ceiling alternation and gravity-flip corridor.
	_add_platform(5480, 470, 220, 24); _add_platform(5880, 225, 220, 24)
	_add_platform(6300, 470, 220, 24); _add_spike(6620)
	# Wave: narrow but fair zig-zag channel.
	_add_platform(7160, 390, 420, 22); _add_platform(7160, 170, 420, 22)
	_add_platform(7650, 170, 360, 22); _add_platform(7650, 420, 360, 22)
	_add_platform(8080, 390, 330, 22); _add_platform(8080, 170, 330, 22)
	# Robot: varied jump heights over grouped hazards.
	_add_spike(8950); _add_spike(9320); _add_spike(9400)
	_add_platform(9700, 495, 230, 24); _add_spike(10030)
	# Spider: ceiling/floor switches between separated hazard groups.
	_add_spike(10650); _add_spike(10980, 0); _add_spike(11320)
	_add_platform(11520, 470, 260, 24)

func _add_platform(x: float, y: float, w: float, h: float) -> void:
	platforms.append(Rect2(x, y, w, h))

func _add_spike(x: float, from_floor: int = 1) -> void:
	spikes.append(Vector2(x, float(from_floor)))

func _make_hud() -> void:
	var layer := CanvasLayer.new()
	add_child(layer)
	hud = Label.new()
	hud.position = Vector2(28, 20)
	hud.add_theme_font_size_override("font_size", 24)
	hud.add_theme_color_override("font_color", Color.WHITE)
	layer.add_child(hud)
	mode_label = Label.new()
	mode_label.position = Vector2(28, 55)
	mode_label.add_theme_font_size_override("font_size", 17)
	mode_label.add_theme_color_override("font_color", Color(0.35, 0.9, 1))
	layer.add_child(mode_label)
	progress = ProgressBar.new()
	progress.position = Vector2(28, 91)
	progress.size = Vector2(300, 12)
	progress.show_percentage = false
	layer.add_child(progress)
	message = Label.new()
	message.set_anchors_and_offsets_preset(Control.PRESET_CENTER)
	message.position = Vector2(-250, -60)
	message.size = Vector2(500, 120)
	message.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
	message.add_theme_font_size_override("font_size", 30)
	message.add_theme_color_override("font_color", Color.WHITE)
	layer.add_child(message)

func _unhandled_input(event: InputEvent) -> void:
	var pressed := (event is InputEventScreenTouch and event.pressed) or (event is InputEventMouseButton and event.pressed) or (event is InputEventKey and event.pressed and event.keycode in [KEY_SPACE, KEY_UP, KEY_W])
	if not pressed:
		return
	if dead or won:
		_restart()
	else:
		_action_pressed = true

var _action_pressed := false
var _action_held := false

func _input(event: InputEvent) -> void:
	if event is InputEventScreenTouch:
		_action_held = event.pressed
	elif event is InputEventMouseButton:
		_action_held = event.pressed
	elif event is InputEventKey and event.keycode in [KEY_SPACE, KEY_UP, KEY_W]:
		_action_held = event.pressed

func _physics_process(delta: float) -> void:
	if dead or won:
		queue_redraw()
		return
	var old_x := player.x
	player.x += RUN_SPEED * delta
	camera_x = maxf(0.0, player.x - 330.0)

	for gate in gates:
		if old_x < gate.x and player.x >= gate.x:
			mode = gate.mode
			mode_index += 1
			gravity_sign = 1.0
			velocity.y = 0
			grounded = false

	_apply_mode(delta)
	_resolve_surfaces(old_x)
	_check_spikes()
	if player.y > 790 or player.y < -100:
		_die()
	if player.x >= LEVEL_END:
		won = true
		message.text = "LEVEL COMPLETE!\nTap to play again"
	_update_hud()
	queue_redraw()
	_action_pressed = false

func _apply_mode(delta: float) -> void:
	match mode:
		"CUBE", "ROBOT":
			velocity.y += GRAVITY * gravity_sign * delta
			if _action_pressed and grounded:
				velocity.y = (JUMP_SPEED * (0.82 if mode == "ROBOT" else 1.0)) * gravity_sign
				grounded = false
		"SHIP":
			velocity.y += (GRAVITY - (3100.0 if _action_held else 0.0)) * delta
			velocity.y = clampf(velocity.y, -560, 620)
		"UFO":
			velocity.y += GRAVITY * delta
			if _action_pressed:
				velocity.y = -590.0
		"BALL":
			velocity.y += GRAVITY * gravity_sign * delta
			if _action_pressed and grounded:
				gravity_sign *= -1.0
				velocity.y = 0
				grounded = false
		"WAVE":
			velocity.y = (-430.0 if _action_held else 430.0)
		"SPIDER":
			velocity.y += GRAVITY * gravity_sign * delta
			if _action_pressed:
				gravity_sign *= -1.0
				velocity.y = 0
				grounded = false
	player.y += velocity.y * delta

func _resolve_surfaces(old_x: float) -> void:
	grounded = false
	var half := 20.0
	if mode == "WAVE":
		if player.y < 188 or player.y > 372:
			_die()
		return
	if gravity_sign > 0 and player.y + half >= FLOOR_Y:
		player.y = FLOOR_Y - half
		velocity.y = 0
		grounded = true
	elif gravity_sign < 0 and player.y - half <= CEILING_Y:
		player.y = CEILING_Y + half
		velocity.y = 0
		grounded = true
	for p in platforms:
		if player.x + 18 > p.position.x and player.x - 18 < p.end.x:
			if gravity_sign > 0 and old_x < p.end.x and player.y + half >= p.position.y and player.y < p.position.y:
				player.y = p.position.y - half
				velocity.y = 0
				grounded = true
			elif gravity_sign < 0 and player.y - half <= p.end.y and player.y > p.end.y:
				player.y = p.end.y + half
				velocity.y = 0
				grounded = true

func _check_spikes() -> void:
	for s in spikes:
		var spike_y := FLOOR_Y if s.y > 0 else CEILING_Y
		if absf(player.x - s.x) < 31 and absf(player.y - spike_y) < 57:
			_die()
			return

func _die() -> void:
	dead = true
	message.text = "CRASHED!\nTap to retry"

func _restart() -> void:
	attempts += 1
	player = Vector2(150, FLOOR_Y - 24)
	velocity = Vector2.ZERO
	camera_x = 0
	mode = "CUBE"
	mode_index = 0
	gravity_sign = 1
	grounded = true
	dead = false
	won = false
	message.text = ""
	_update_hud()

func _update_hud() -> void:
	hud.text = "DYNAMIC DASH     ATTEMPT %02d" % attempts
	mode_label.text = "MODE: " + mode
	progress.value = clampf(player.x / LEVEL_END * 100.0, 0, 100)

func _draw() -> void:
	var screen_w := 1280.0
	# Layered moving grid gives the level a coherent visual identity.
	for i in range(-1, 18):
		var gx := i * 100.0 - fmod(camera_x * 0.22, 100.0)
		draw_line(Vector2(gx, 0), Vector2(gx, 720), Color(0.12, 0.19, 0.32, 0.35), 1)
	for y in range(0, 720, 80):
		draw_line(Vector2(0, y), Vector2(1280, y), Color(0.12, 0.19, 0.32, 0.25), 1)
	# Track rails.
	draw_rect(Rect2(0, FLOOR_Y, 1280, 130), Color(0.055, 0.075, 0.15))
	draw_line(Vector2(0, FLOOR_Y), Vector2(1280, FLOOR_Y), Color(0.15, 0.85, 1), 4)
	draw_line(Vector2(0, CEILING_Y), Vector2(1280, CEILING_Y), Color(0.15, 0.85, 1, 0.55), 3)
	# Platforms and authored spike groups.
	for p in platforms:
		var r := Rect2(p.position.x - camera_x, p.position.y, p.size.x, p.size.y)
		if r.end.x > -100 and r.position.x < screen_w + 100:
			draw_rect(r, Color(0.11, 0.3, 0.48))
			draw_rect(Rect2(r.position, Vector2(r.size.x, 5)), Color(0.2, 0.9, 1))
	for s in spikes:
		var x := s.x - camera_x
		if x < -50 or x > screen_w + 50: continue
		var y := FLOOR_Y if s.y > 0 else CEILING_Y
		var pts := PackedVector2Array([Vector2(x - 25, y), Vector2(x, y - 48 if s.y > 0 else y + 48), Vector2(x + 25, y)])
		draw_colored_polygon(pts, Color(1, 0.27, 0.48))
		draw_polyline(pts, Color(1, 0.75, 0.82), 2)
	# Mode portals.
	for gate in gates:
		var x := gate.x - camera_x
		if x > -50 and x < screen_w + 50:
			draw_circle(Vector2(x, 340), 38, Color(0.45, 0.22, 0.95, 0.22))
			draw_arc(Vector2(x, 340), 38, 0, TAU, 48, Color(0.5, 0.65, 1), 4)
	# Player with a distinct shape for each mode.
	var pos := Vector2(player.x - camera_x, player.y)
	var col := Color(0.2, 0.95, 1)
	match mode:
		"CUBE", "ROBOT":
			draw_rect(Rect2(pos - Vector2(19, 19), Vector2(38, 38)), col)
			draw_rect(Rect2(pos - Vector2(9, 8), Vector2(6, 6)), Color(0.03, 0.05, 0.12))
			draw_rect(Rect2(pos + Vector2(5, -8), Vector2(6, 6)), Color(0.03, 0.05, 0.12))
		"SHIP":
			draw_colored_polygon(PackedVector2Array([pos + Vector2(24, 0), pos + Vector2(-18, -15), pos + Vector2(-10, 0), pos + Vector2(-18, 15)]), col)
		"UFO":
			draw_circle(pos, 19, col); draw_rect(Rect2(pos - Vector2(22, 3), Vector2(44, 8)), Color(0.8, 0.95, 1))
		"BALL":
			draw_circle(pos, 20, col); draw_arc(pos, 13, 0, PI, 24, Color(0.03, 0.05, 0.12), 4)
		"WAVE":
			draw_line(pos + Vector2(-20, 17), pos, col, 9); draw_line(pos, pos + Vector2(20, -17), col, 9)
		"SPIDER":
			draw_circle(pos, 15, col)
			for a in range(4):
				var side := -1 if a < 2 else 1
				var yy := -12 if a % 2 == 0 else 12
				draw_line(pos + Vector2(side * 10, yy), pos + Vector2(side * 25, yy + (8 if a % 2 == 0 else -8)), col, 4)
	if dead or won:
		draw_rect(Rect2(0, 0, 1280, 720), Color(0.01, 0.015, 0.04, 0.55))
