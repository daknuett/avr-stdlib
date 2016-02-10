#!/usr/bin/python3.5

class _Getch:
	"""Gets a single character from standard input.  Does not echo to the
	screen.
	Mainly from http://code.activestate.com/recipes/134892/
	But I did strip away all that windows stuff."""
	def __init__(self):
		self.impl = _GetchUnix()

	def __call__(self): 
		return self.impl()


class _GetchUnix:
	def __init__(self):
		import tty, sys

	def __call__(self):
		import sys, tty, termios
		fd = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd)
		try:
			tty.setraw(sys.stdin.fileno())
			ch = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
		if(ord(ch) == 3 or ord(ch) == 4):
			raise KeyboardInterrupt(ch)
		return ch

