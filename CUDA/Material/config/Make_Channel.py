import json
import sys
from enum import IntEnum
from typing import List
# from config.Make_Parse import parse  # use this when using ide
from Make_Parse import parse


# Enum
class ChannelDirection(IntEnum):
	CHANNEL_UP		= 0,
	CHANNEL_DOWN	= 1


# Data
# ...


# Operation
# if the channel is path channel
# then the configured path should be a relative path starting from work directory
# and currently the path_cur will be in $(work_directory)/config
def channel(direction: ChannelDirection, name: str, path_cur: str, is_path: bool) -> str:
	# TODO: currently only spoort channel up
	if direction != ChannelDirection.CHANNEL_UP:
		return ""

	string : str = ""
	
	# parse json file to get child list
	# reminder
	# the last one of the string list will be an empty string
	# it should be ignore or otherwise the function will go deep infinitely
	work_directory	: str		= parse(path_cur + "/" + "makeconfig.json", "WORK_DIR", "")		
	child_str		: str		= parse(path_cur + "/" + "makeconfig.json", "CHILD", "")
	child_list		: List[str]	= child_str.split(" ")

	# recursively to get into the child to get output
	for child in child_list[:-1]:
		temp: str = channel(direction, name, path_cur + "/" + work_directory + "/" + child + "/config", is_path)

		# if is_path == True, then need to adjust the output path
		if is_path is False:
			string += " " + temp
			continue

		# split function will remove all the space between the string
		# so it need to add it back later
		path_list:	List[str] = temp.split(" ")	
		for path_ in path_list[:-1]:
			string += child + "/" + path_
			string += " "
	
	# get output of this level
	self_str : str = parse(path_cur + "/" + "makeconfig_Export.json", name, "")
	string += self_str

	# return output
	return string


# Main Operation
# input
# 0: python file
# 1: channel direction
# 2: channel name
# 3: is path (if is path, then need to config the path at the final)
if __name__ == "__main__":

	# check if the arguments are valid or not
	if len(sys.argv) < 3:
		# raise RuntimeError
		print("")

	# prepare data
	direction:	ChannelDirection	= ChannelDirection(int(sys.argv[1]))
	name:		str					= str(sys.argv[2])
	is_path:	bool				= True if sys.argv[3] == "true" else False

	# operation
	print(channel(direction, name, ".", is_path))
