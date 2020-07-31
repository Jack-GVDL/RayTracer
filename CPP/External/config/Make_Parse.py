import json
import sys


# Operation
def parse(json_path: str, key: str, default_value: str) -> str:
	string: str = ""

	try:
		# open the json file
		with open (json_path, "r") as reader:
			json_file = json.loads(reader.read())
		
		# find the value based on key
		temp = json_file[key]
	
		if type(temp) == list:
			for item in temp:
				string += item
				# string += " "
			temp = string

		string = str(temp)

	except:
		return default_value

	finally:
		return string


# Main Operation
# input
# 0: python file
# 1: json file
# 2: key
# 4: default return value
if __name__ == "__main__":

	# check if the arguments are valid or not
	if len(sys.argv) < 3:
		# raise RuntimeError
		print("")

	# prepare data
	path_:	str = str(sys.argv[1])
	key:    str = str(sys.argv[2])
	value:	str = "" if len(sys.argv) < 4 else (sys.argv[3])

	# operation
	print(parse(path_, key, value))
