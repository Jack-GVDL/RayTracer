import struct
from typing import List


class Vec3f:

	def __init__(self, v0: float = None, v1: float = None, v2: float = None):
		# data
		self._n:	List[float] = [0.0, 0.0, 0.0]

		# init
		if v0 is None:
			# self._n[0]	= 0
			# self._n[1]	= 0
			# self._n[2]	= 0
			pass

		elif v1 is None:
			self._n[0]		= float(v0)
			self._n[1]		= float(v0)
			self._n[2]		= float(v0)

		elif v2 is None:
			raise RuntimeError

		else:
			self._n[0]		= float(v0)
			self._n[1]		= float(v1)
			self._n[2]		= float(v2)

		# check
		# assert type(self._n[0]) is float and type(self._n[1]) is float and type(self._n[2]) is float

	def __getitem__(self, key: int) -> float:
		return self._n[key]

	def __setitem__(self, key: int, value: float) -> None:
		self._n[key] = value

	@ property
	def array(self) -> List[float]:
		return self._n

	def convertToBytes(self) -> bytes:
		data: bytearray = bytearray()

		data.extend(struct.pack("d", self._n[0]))
		data.extend(struct.pack("d", self._n[1]))
		data.extend(struct.pack("d", self._n[2]))

		return data
