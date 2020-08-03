from typing import List
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.Qt import *
from Base import *


class Display_Tracer(QWidget):

	def __init__(self):
		super().__init__()

		# data
		self._x:			int = 200
		self._y:			int = 100
		self._ops_tracer:	Tracer_Ops = None

	# Operation
	def setOps_tracer(self, ops: Tracer_Ops) -> None:
		self._ops_tracer = ops

	def setDisplaySize(self, x: int, y: int) -> None:
		self._x = x
		self._y = y

	def paintEvent(self, event: QPaintEvent) -> None:
		painter:	QPainter = QPainter()
		painter.begin(self)

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

		painter.end()
