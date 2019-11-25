#next up:
Write a class that acts as a C++ wrapper for an NSMutableDictionary
PThread

#Game-related:
Modularized engine:
A) Part maintains the running game world (portable)
	(analogues:  FieldMgr)
B) Part feeds the running game world controller input (platform-specific)
	(analogues:  InputMgr)
C) Part reads the running game world and updates the screen (platform-specific)
	(no analogues; similar functionality in ImgCache, SoundMgr, code strewn
	throughout everything in Atma)
	1) All image/sound data will be loaded here, other Parts will only have
	   references/tokens
	2) Use an internal resolution and scale to the viewport's resolution
	3) React to changes in the viewport's size/status
	X) Functionality:
		a) request draw list from Part A
			1.	Sprite name
			2.	Sprite animation set
			3.	Sprite frame number
			4.	X/Y/W/H
		b) translate Sprite name/set/number into a currently-stored
		   image; if unavailable, ignore this one
		c) blank and draw to screen
D) Part synchronizes the above nonsense (portable)
	(analogues:  EventMgr?)

E) A fucking scripting language that's better than Clab (and ATMA)

Names?
A)	SceneMgr
B)	InputMgr
C)	Renderer
D)	EventMgr
