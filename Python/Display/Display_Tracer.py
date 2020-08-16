from typing import List
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.Qt import *
from Base import *
import time


class Display_Tracer(QWidget):

	def __init__(self):
		super().__init__()

		# data
		self._x:			int			= 200
		self._y:			int			= 100

		self._image:		List[Vec3f]	= []
		self._image_array:	List[float]	= []
		self._time:			time		= None

		self._ops_tracer:	Ops_Tracer = None
		self._is_rendered:	bool	= False

	# Operation
	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	def setDisplaySize(self, x: int, y: int) -> None:
		self._x = x
		self._y = y

	def reset(self) -> None:
		self._is_rendered = False

	def paintEvent(self, event: QPaintEvent) -> None:
		self._render_()
		self._paint_()

	# Helper
	def _render_(self) -> None:
		if self._is_rendered:
			return

		# execution time starting point
		start_time = time.time()

		# get pixel and draw on screen
		self._image.clear()
		self._image_array.clear()

		# backup
		# pixel by pixel
		# x_half: float = self._x / 2
		# y_half: float = self._y / 2
		#
		# for y in range(self._y):
		# 	for x in range(self._x):
		#
		# 		u: float = (x - x_half) / x_half
		# 		v: float = (y - y_half) / y_half
		#
		# 		# get color
		# 		vec_color: Vec3f = Vec3f()
		# 		self._ops_tracer.Tracer_tracePoint(0, vec_color, u, v, 5)
		#
		# 		# adjust color value
		# 		# (0, 1) -> (0, 255)
		# 		vec_color[0] *= 255
		# 		vec_color[1] *= 255
		# 		vec_color[2] *= 255
		#
		# 		self._image.append(vec_color)

		# pixel array
		self._ops_tracer.Tracer_traceRect(0, self._image_array, self._x, self._y, 5, False, True)

		for index in range(0, len(self._image_array), 3):

			self._image.append(
				Vec3f(
					self._image_array[index + 0] * 255,
					self._image_array[index + 1] * 255,
					self._image_array[index + 2] * 255))

		# execution time end point and display time
		end_time = time.time()
		self._time = end_time - start_time
		print(f"Execution Time: {self._time}")

		# mark is rendered
		self._is_rendered = True

	def _paint_(self) -> None:
		# begin painter
		painter:	QPainter = QPainter()
		painter.begin(self)

		# paint
		for y in range(self._y):
			for x in range(self._x):

				color = QColor(
					int(self._image[x + y * self._x][0]),
					int(self._image[x + y * self._x][1]),
					int(self._image[x + y * self._x][2]))

				painter.setPen(color)
				painter.drawPoint(x, y)

		# display time
		painter.setPen(QColor(255, 255, 255))
		painter.drawText(0, self._y + 20, f"Execution Time: {self._time}")
		# print(f"Execution Time: {self._time}")

		# end painter
		painter.end()
