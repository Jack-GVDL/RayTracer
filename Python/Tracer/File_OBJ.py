from typing import *


# Typedef
# ...


# Data Structure
class File_OBJ:

	def __init__(self):
		super().__init__()

		# func
		self.feature_func: Dict[Callable[List[str], None]] = {
			"v":	self._loadGeometricVertex_,
			"vt":	self._loadTextureCoordinate_,
			"vn":	self._loadVertexNormal_,
			"vp":	self._loadParameterSpaceVertex_,
			"f":	self._loadFace_,
			"l":	self._loadLine_,
			"#":	self._loadComment_
		}

		# data
		self.path:	str = ""

		self.geometric_vertex_list:		List[Tuple[float, float, float]]	= []
		self.face_list:					List[Tuple[int, int, int]]			= []
		self.vertex_normal_list:		List[Tuple[float, float, float]]	= []
		self.texture_coordinate_list:	List[Tuple[float]]					= []
		self.line_list:					List[List[int]]						= []

		# TODO: type not define
		# self.parameter_space_vertex_list

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
	# TODO: optional [w]
	def _loadGeometricVertex_(self, data: List[str]) -> None:
		if len(data) < 3:
			return

		try:
			v_0 = float(data[0])
			v_1 = float(data[1])
			v_2 = float(data[2])

		except ValueError:
			return

		# add to vertex list
		self.geometric_vertex_list.append((v_0, v_1, v_2,))

	# TODO: optional [v, w]
	def _loadTextureCoordinate_(self, data: List[str]) -> None:
		if len(data) < 1:
			return

		try:
			v_0 = float(data[0])

		except ValueError:
			return

		# add to texture coordinate list
		self.texture_coordinate_list.append((v_0,))

	def _loadVertexNormal_(self, data: List[str]) -> None:
		if len(data) < 3:
			return

		try:
			v_0 = float(data[0])
			v_1 = float(data[1])
			v_2 = float(data[2])

		except ValueError:
			return

		# add to vertex normal list
		self.vertex_normal_list.append((v_0, v_1, v_2,))

	# TODO: not yet completed
	def _loadParameterSpaceVertex_(self, data: List[str]) -> None:
		pass

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

	def _loadLine_(self, data: List[str]) -> None:
		if len(data) < 1:
			return

		line = []
		try:
			for item in data:
				line.append(int(item))

		except ValueError:
			return

		# add to line list
		self.line_list.append(line)

	def _loadComment_(self, data: List[str]) -> None:
		pass


if __name__ == '__main__':
	# load file
	file_obj = File_OBJ()
	file_obj.path = "./OBJ/cube.obj"
	file_obj.load()

	# print loaded data
	print(file_obj.geometric_vertex_list)
	print(file_obj.face_list)
