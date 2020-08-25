from typing import List
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.Qt import *
from Base import *
import time
import numpy as np


class Display_Tracer(QWidget):

	def __init__(self):
		super().__init__()

		# data
		self._w:			int			= 200
		self._h:			int			= 100

		self._image:		QPixmap		= None
		self._time:			time		= None

		self._ops_tracer:	Ops_Tracer	= None
		self._is_rendered:	bool		= False

	# Operation
	def setOps_tracer(self, ops: Ops_Tracer) -> None:
		self._ops_tracer = ops

	def setDisplaySize(self, w: int, h: int) -> None:
		self._w = w
		self._h = h

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

		# get picture
		array = np.zeros(self._w * self._h * 3, dtype=np.uint8)
		self._ops_tracer.Tracer_traceRect(1, array, self._w, self._h, 5, False, True)
		self._image = QPixmap.fromImage(QImage(array, self._w, self._h, QImage.Format_RGB888))

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

		# paint pixel map
		painter.drawPixmap(0, 0, self._image)

		# display time
		painter.setPen(QColor(255, 255, 255))
		painter.drawText(0, self._h + 20, f"Execution Time: {self._time}")
		# print(f"Execution Time: {self._time}")

		# end painter
		painter.end()
