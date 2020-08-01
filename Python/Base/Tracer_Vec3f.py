from typing import List


class Vec3f:

	def __init__(self):
		self._n:	List[float] = [0, 0, 0]

	def __getitem__(self, key: int) -> float:
		return self._n[key]

	def __setitem__(self, key: int, value: float) -> None:
		self._n[key] = value

	@ property
	def array(self) -> List[float]:
		return self._n
