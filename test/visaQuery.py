#!/usr/bin/env python3

import pyvisa as visa
import time
import sys
import re


def test_idn():
	isPico = False
	idn = inst.query("*idn?");
	print(idn)

	# check if the IDN string matches the expected pattern. Allow for different serial number
	if(re.search("PICO-PI,LABTOOL,\d+,01.00\r\n", idn) != None):
		isPico = (inst.is_4882_compliant)


	return isPico


def set_pin(pin, on):
	cmd = "DIGI:OUTP{} {}".format(pin, on)
	inst.write(cmd)

def get_pin(pin):
	cmd = "DIGI:OUTP{}?".format(pin)
	return inst.query(cmd)

def test_pin(pin):
	print("Status of pin {} before setting: {}".format(pin, get_pin(pin)))
	set_pin(pin,1)
	print("Status of pin {} after setting: {}".format(pin, get_pin(pin)))
	time.sleep(1)
	set_pin(pin,0)
	print("Status of pin {} after resetting: {}".format(pin, get_pin(pin)))


rm = visa.ResourceManager()
reslist = rm.list_resources("USB?::?*::INSTR")
print(reslist)

if (len(reslist) == 0):
    sys.exit()

i = 0
inst = None
while i < len(reslist):
	inst = rm.open_resource(reslist[i]);
	inst.timeout = 3000
	inst.clear()

	print("+ IDN")
	if(test_idn()):
		print("Instrument found")
		# reset
		inst.write("*RST")
		# test 3 pins
		j = 0
		while j < 3:
			test_pin(j)
			j += 1

	print("SCPI errors during test: "+ inst.query("SYST:ERR:COUNT?"))
	inst.close()
	i += 1

print("Test complete")
