#!/usr/bin/python3.5
import sys,threading
import getch
from miniTTY_serialIO import *
import time

class Screen(object):
	def __init__(self,height = 23, width = 80):
		height -= 2
		width -= 2
		self.output = [ " " * int((width / 2) - 1) for i in range(height)]
		self.inpt = [ " " * int(width / 2) for i in range(height)]
		self.output_cursor = [0,0]
		self.input_cursor = [0,0]
		self.output_width = int(width / 2) - 1
		self.input_width = int(width / 2)
		self.height = height
		self.width = width

	def _output_putc(self,row,col,char):
		self.output[row] = self.output[row][:col] + char + self.output[row][col + 1:]
	def _input_putc(self,row,col,char):
		self.inpt[row] = self.inpt[row][:col] + char + self.inpt[row][col + 1:]

	def output_putc(self,char):
		if(char == "\r"):
			self.output_cursor[1] = 0
		elif(char == "\n"):
			self.output_newline()
		elif(char == "\b" or ord(char) == 127):
			self.output_del_char()
		elif(char == "\f"):
			self.output = [ " " * int((self.width / 2) - 1) for i in range(self.height)]
			self.output_cursor = [0,0]
		else:
			self._output_putc(self.output_cursor[0],self.output_cursor[1],char)
			if(self.output_cursor[1] + 1 >= self.output_width):
				self.output_newline()
			else:
				self.output_cursor[1] += 1
	def input_putc(self,char):
		if(char == "\r"):
			# XXX on input we (usually do not enter a \r => change this to \n"
#			self.input_cursor[1] = 0
			self.input_newline()
		elif(char == "\n"):
			self.input_newline()
		elif(char == "\f"):
			self.inpt = [ " " * int(self.width / 2) for i in range(self.height)]
			self.input_cursor = [0,0]
		elif(char == "\b" or ord(char) == 127):
			self.input_del_char()
		else:
			self._input_putc(self.input_cursor[0],self.input_cursor[1],char)
			if(self.input_cursor[1] + 1 >= self.input_width):
				self.input_newline()
			else:
				self.input_cursor[1] += 1

	def output_newline(self):
		if(self.output_cursor[0] + 1 >= self.height):
			self._shift_screen(self.output)
		else:
			self.output_cursor[0] += 1
			self.output_cursor[1] = 0
	def input_newline(self):
		if(self.input_cursor[0] + 1 >= self.height):
			self._shift_screen(self.inpt)
		else:
			self.input_cursor[0] += 1
			self.input_cursor[1] = 0
	def _shift_screen(self,obj):
		if(obj == self.output):
			self.output.extend([ " " * self.output_width])
			self.output = self.output[(-1 * self.height) :]
			self.output_cursor[0] -= 1
		if(obj == self.inpt):
			self.inpt.extend([ " " * self.input_width])
			self.inpt = self.inpt[(-1 * self.height) :]
			self.input_cursor[0] -= 1
	def __str__(self):
		# these threads are really fucked up!
		# If I do not add the \r, it will be shifted
		res = "\r" + ( "#" * self.width)
		res += "\n"
		for i in range(self.height):
			res += "\r{} | {}\n".format(self.output[i],self.inpt[i])
		return res

	def output_puts(self,_str):
		for i in _str:
			self.output_putc(i)
	def input_puts(self,_str):
		for i in _str:
			self.input_putc(i)
	def output_del_char(self):
		row = self.output_cursor[0]
		col = self.output_cursor[1]
		self.output[row] = self.output[row][:col] + " " + self.output[row][col + 1:]
		self.output_cursor[1] -= 1
		if(self.output_cursor[1] < 0):
			self.output_cursor[1] = 0
			self.output_cursor[0] -= 1
		if(self.output_cursor[0] < 0):
			self.output_cursor[0] = 0

	def input_del_char(self):
		row = self.input_cursor[0]
		col = self.input_cursor[1]
		self.inpt[row] = self.inpt[row][:col - 1] + " " + self.inpt[row][col :]
		self.input_cursor[1] -= 1
		if(self.input_cursor[1] < 0):
			self.input_cursor[1] = 0
			self.input_cursor[0] -= 1
		if(self.input_cursor[0] < 0):
			self.input_cursor[0] = 0
	def delscreen(self):
#		for i in range(self.height * self.width):
#			sys.stdout.write("\b")
		print(chr(27) + "[2J")
	

class MiniTTY(object):
	def __init__(self,port, baudrate = 9600, height = 40, width = 100, autorefresh_time = 0.1, RW_timeout = 0.3,read_time = 0.5,*args,encoding = "ascii", PS1 = "$ "):
		# to avoid messy output
		self.refresh_lock = threading.Lock()
		self.screen = Screen(height,width)
		self.autorefresh_time = autorefresh_time
		self.async_serial = AsyncSerial(port = port,baudrate = baudrate, timeout = RW_timeout)
		self.async_serial.async_write_to(self.screen.output_putc,read_time)
		self.autorefresher = threading.Thread(target = self.autorefresh, daemon = True )
		self.autorefresher.start()
		self.buf = ""
		self.encoding = encoding
		self.PS1 = PS1
		self.screen.input_puts(self.PS1)
		self.refresh()
	def refresh(self):
		self.refresh_lock.acquire()
		self.screen.delscreen()
		print( str(self.screen))
		self.refresh_lock.release()
	def autorefresh(self):
		while(1):
			self.refresh()
			time.sleep(self.autorefresh_time)
	def putc(self,_c):
		if(_c == chr(0x03)):
			self.buf = ""
			self.screen.input_putc("\n")
			self.screen.input_puts(self.PS1)
			return
		self.buf += _c
		if(_c == "\r"):
			res = self.async_serial.write(self.buf.encode(self.encoding))
			self.buf = ""
			self.screen.input_puts("\nOK wrote {} bytes\n".format(res))
			self.screen.input_puts(self.PS1)
		else:
			self.screen.input_putc(_c)
		self.refresh()


if __name__ == "__main__":
	getc = getch._Getch()
	port = "/dev/ttyACM0"
	baud = 9600
	if(len(sys.argv) > 1):
		port  = sys.argv[1]
	if(len(sys.argv) > 2):
		baud = int(sys.argv[2])
	tty = MiniTTY(port = port,baudrate = baud, autorefresh_time = 1 )
#	tty.autorefresh()
	while(1):
		try:
			c = getc()
			tty.putc(c)
		except KeyboardInterrupt as e:
			if(e.args[0] == '\x04'):
				break
			tty.putc(chr(0x03))
