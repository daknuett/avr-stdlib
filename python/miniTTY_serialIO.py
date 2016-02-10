#!/usr/bin/python3.5

import asyncio,aiohttp,threading
import serial

class AsyncSerial(serial.Serial):
	def __init__(self,timeout = 0.3,port = "/dev/ttyACM0", baudrate = 9600, *args, **kwargs):
		serial.Serial.__init__(self,port = port,baudrate = baudrate, *args, **kwargs)
		self.timeout = timeout

	def read(self,count = 1):
		res = b''
		for i in range(count):
			try:
				res += self._read()
			except TimeoutError:
				return res
		return res
	def _read(self):
		return serial.Serial.read(self,1)

	def write(self,_bytes):
		return serial.Serial.write(self,_bytes)


	"""
	look every ``seconds'' seconds for characters and write
	them to an object  using the method ``_method''
	"""
	def async_write_to(self, _method, seconds = 1):
		self.async_process = threading.Thread(target = self._async_write_to, args = (_method,seconds),daemon = True)
		self.async_process.start()


	def _async_write_to(self, _method, seconds):
		while(1):
			while(1):
				try:
					c = self.read(1)
					if(len(c) == 0):
						continue
					_method(c.decode())
				except  asyncio.TimeoutError:
					break
				except ValueError:
					pass
			time.sleep(seconds)
	def stop_write_to(self):
		self.async_process.join()



if __name__ == "__main__":
	from miniTTY import *
	import sys
	import getch
	screen = Screen(height = 50, width = 100)
	ser = AsyncSerial(baudrate = 1200)
	ser.async_write_to(screen.output_putc)
	getc = getch._Getch()
	while(1):
		c = "\n"
		try:
			c = getc()
		except KeyboardInterrupt as e:
			c = "\n"
			if(e.args[0] == '\x04'):
				sys.exit()
		print("\f")
		screen.input_putc(c)
		print(str(screen))

