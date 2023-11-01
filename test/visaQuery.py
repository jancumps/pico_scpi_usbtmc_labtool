#!/usr/bin/env python3

import pyvisa as visa
import time
import sys
import re

from pyvisa import ResourceManager, constants
import traceback


def test_idn():
	isPico = False
	idn = inst.query("*idn?");
	print(idn)

	# check if the IDN string matches the expected pattern. Allow for different serial number
	if(re.search("PICO-PI,LABTOOL,([0-9a-fA-F]+),01.00\n", idn) != None):
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

def handle_event(resource, event, user_handle):
	print(f"Handled event {event.event_type} on {resource}")
	stb = inst.read_stb()
	print("status read finished")
	inst.write("*CLS")
	resource.called = True


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

	print("Basis test")
	print("IDN")
	if(test_idn()):
		print("Instrument found")
		# reset
		inst.write("*RST")
		# test 3 pins
		j = 0
		while j < 3:
			test_pin(j)
			j += 1
	print("SCPI errors after test: "+ inst.query("SYST:ERR:COUNT?"))
	print("Basis test complete")

	print("Service Request test")
	inst.called = False
	event_type = constants.EventType.service_request
	event_mech = constants.EventMechanism.handler
	wrapped = inst.wrap_handler(handle_event)
	user_handle = inst.install_handler(event_type, wrapped, 42)
	inst.enable_event(event_type, event_mech, None)
	
	inst.write("STAT:OPER:DIGI:INP:NTR 4\n")
	inst.write("STAT:OPER:DIGI:INP:ENAB 4\n")
	inst.write("STAT:OPER:ENAB 1\n")

	inst.write("*CLS")
	inst.write("*SRE 128") #leaving Bit6 MSS - off
	
	maxloops = 500
	sleeptime = 0.01
	print("Done setting up. Drive DIGI:INP0 low (push button connected to GP27) within {} s".format(sleeptime * maxloops))
	   
	
	try:
		loops = 0
		while (not inst.called) and (loops < maxloops):
			time.sleep(sleeptime)
			loops += 1				
		if (loops >= maxloops):
			print("Service request not called after {} s".format(sleeptime * loops))
	except: 
		inst.close()
#	   logging.exception("While looping")

	try:
		print("disabling event")
		inst.disable_event(event_type, event_mech)
		print("disabled event")
	except:
		print("err while disabling event")
	try:
		print("uninstalling handler")
		inst.uninstall_handler(event_type, wrapped, user_handle)
		print("uninstalled handler")
	except:
		print("err while uninstalling handler")
	
	print("SCPI errors after test: "+ inst.query("SYST:ERR:COUNT?"))
	print("Service Request test complete")

	inst.close()
	i += 1


print("All Test complete")
