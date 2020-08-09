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
		self._x:			int = 200
		self._y:			int = 100
		self._ops_tracer:	Ops_Tracer = None

	# Operation
	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	def setDisplaySize(self, x: int, y: int) -> None:
		self._x = x
		self._y = y

	def paintEvent(self, event: QPaintEvent) -> None:
		# begin painter
		painter:	QPainter = QPainter()
		painter.begin(self)

		# execution time starting point
		start_time = time.time()

		# get pixel and draw on screen
		x_half: float = self._x / 2
		y_half: float = self._y / 2

		for y in range(self._y):
			for x in range(self._x):

				u: float = (x - x_half) / x_half
				v: float = (y - y_half) / y_half

				vec_color: Vec3f = Vec3f()
				self._ops_tracer.Tracer_tracePoint(0, vec_color, u, v, 5)

				color = QColor(
					int(vec_color[0] * 255),
					int(vec_color[1] * 255),
					int(vec_color[2] * 255))

				painter.setPen(color)
				painter.drawPoint(x, self._y - y)  # be careful of coordinate system

		# execution time end point and display time
		end_time = time.time()
		painter.setPen(QColor(255, 255, 255))

		painter.drawText(0, self._y + 20, f"Execution Time: {end_time - start_time}")
		print(f"Execution Time: {end_time - start_time}")

		# end painter
		painter.end()
