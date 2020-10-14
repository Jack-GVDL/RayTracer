from Base import Camera


class Camera_Default(Camera):

	def __init__(self):
		super().__init__()

		# data
		# ...

		# init
		# ...

	# Operation
	# ...

	# Interface
	def start(self) -> None:
		type_index: int		= self._getType_(self._ops_tracer, "camera_default")
		self._object_index	= self._ops_tracer.Camera_create(type_index)
