from typing import *


# Typedef
# ...


# Data Structure
class File_OBJ:

	def __init__(self):
		super().__init__()

		# func
		self.feature_func: Dict[Callable[List[str], None]] = {
			"v":	self._loadVertex_,
			"f":	self._loadFace_,
			"#":	self._loadComment_
		}

		# data
		self.path:	str = ""

		# TODO: obj file do not ONLY have these data
		self.vertex_list:	List[Tuple[float, float, float]]	= []
		self.face_list:		List[Tuple[int, int, int]]			= []

		# operation
		# ...

	def __del__(self):
		pass

	# Operation
	def load(self) -> None:
		if self.path == "":
			return

		# open file
		with open(self.path, "r") as f:

			# for every line
			# first split the line into list of string
			# then as the property of obj file
			# functionality of each line is determined by first element in the string list
			for line in f:
				data: List[str] = line.split()
				if not data:
					continue

				feature: str = data[0]
				try:
					self.feature_func[feature](data[1:])

				# TODO: need exception handling
				except Exception:
					pass

			f.close()

	# Protected
	def _loadVertex_(self, data: List[str]) -> None:
		if len(data) < 3:
			return

		try:
			v_0 = float(data[0])
			v_1 = float(data[1])
			v_2 = float(data[2])
		except ValueError:
			return

		# add to vertex list
		self.vertex_list.append((v_0, v_1, v_2,))

	def _loadFace_(self, data: List[str]) -> None:
		if len(data) < 3:
			return

		# split each string into two index
		f_0: List[str] = data[0].split("//")
		f_1: List[str] = data[1].split("//")
		f_2: List[str] = data[2].split("//")

		try:
			v_0 = int(f_0[0])
			v_1 = int(f_1[0])
			v_2 = int(f_2[0])

		except ValueError:
			return

		# add to face list
		self.face_list.append((v_0, v_1, v_2,))

	def _loadComment_(self, data: List[str]) -> None:
		pass


# Test
if __name__ == '__main__':
	file_obj = File_OBJ()
	file_obj.path = "./OBJ/cube.obj"

	file_obj.load()

	print(file_obj.vertex_list)
	print(file_obj.face_list)
