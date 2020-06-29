import json
import sys


if __name__ != "__main__":
    # raise RuntimeError
    print("")


# This program is to return the string value with the given key
# The key is provided from the command line argument
# Then it will open json file and search the value
# The program will finally return print the value as the return


# check if the the argument is valid or not
if len(sys.argv) < 2:
    # raise RuntimeError
    print("")


# Data
json_path = "./makeconfig.json"
key = str(sys.argv[1])
value = "" if len(sys.argv) < 3 else str(sys.argv[2])


# Operation
# open the json file
with open(json_path, "r") as reader:
    json_file = json.loads(reader.read())


# find the value based on key
try:
    temp = json_file[key]
    
    if type(temp) == list:
        string = ""
        for item in temp:
            string += item
        temp = string

    value = str(temp)

except:
    print(value)

finally:
    print(value)
