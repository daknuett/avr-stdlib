#!/usr/bin/python3

import serial
import sys

BS = 1


def print_from_port(port):
	_str = "h"
	while (_str != ""):
		try:
			_bytes = port.read(BS)
		except KeyboardInterrupt:
			print("<<<=== END {} : {} ===>>>".format(port.port,port.baudrate))
			return
		except TypeError as e:
			# this is an indexed serial exception ;-)
			print("<<<===!!! END + ERR (CONN broken) {} !!!===>>>".format( e))
			return
		try:
			_str = _bytes.decode("ascii")
		except Exception as _e:
			if(isinstance(_e,KeyboardInterrupt)):
				break
			try:
				_str = _bytes.decode("utf-8")
			except Exception as e:
				print("<<<!!! ERR {} !!!>>>".format(e))
				if(isinstance(e,KeyboardInterrupt)):
					break
		print(_str, end = "")


port = "/dev/ttyACM0"
baud = 1200

if(len(sys.argv) > 1):
	port = sys.argv[1]
if(len(sys.argv) > 2):
	baud = int(sys.argv[2])

ser = serial.Serial(port = port, baudrate = baud)
print("<<<###  START {} : {}  ###>>>".format(port,baud))
print_from_port(ser)
