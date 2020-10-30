from typing import *
from Tracer import *
from Display.Display_Tracer import Display_Tracer
from PyQt5.QtWidgets import *
from PyQt5.Qt import *
import sys
import os
import numpy as np
import cv2
import math


# tracer ops
path_tracer:	str				= os.path.join(os.getcwd(), "../Base/bin/Tracer.dll")
ops_tracer:		Ops_Tracer_DLL	= Ops_Tracer_DLL()
ops_tracer.setDLLPath_tracer(path_tracer)

# tracer
tracer:			Tracer = Tracer()
tracer.setOps_tracer(ops_tracer)
tracer.start()

# Tracer_Sample.buildScene_singleSphere(tracer)
Tracer_Sample.buildScene_0(tracer, 1)
# Tracer_Sample.buildScene_1(tracer)
# Tracer_Sample.buildScene_2(tracer)
# Tracer_Sample.buildScene_3(tracer, 2)

# Tracer_Sample_Cube().load(tracer=tracer)
# Tracer_Sample_Magnolia().load(tracer=tracer)

camera_1: Camera_Default = tracer.Camera_Default()
camera_1.setLookFrom(		Vec3f(1.5, 2, 1.5)	)
camera_1.setLookAt(			Vec3f(0, 0, 0)	)
# camera_1.setAspectRatio(	1920 / 1080		)
# camera_1.setAspectRatio(	1080 / 720		)
camera_1.setAspectRatio(	1				)

# TODO: test
# ops_tracer.Test_checkStatus(0, [], 0)


""" display """
degree: int = 0
while True:
	# change look from
	z = 2 * math.cos(math.radians(degree))
	x = 2 * math.sin(math.radians(degree))
	camera_1.setLookFrom(Vec3f(z, 3, x))

	degree = (degree + 10) % 360

	# OpenCV
	# array: np.ndarray = np.zeros(1920 * 1080 * 3, dtype=np.uint8)
	# camera_1.traceRect(array, 1920, 1080, 5, False, True, 0)
	# image = array.reshape((1080, 1920, 3))

	# array: np.ndarray = np.zeros(1080 * 720 * 3, dtype=np.uint8)
	# camera_1.traceRect(array, 1080, 720, 5, False, True, 0)
	# image = array.reshape((720, 1080, 3))

	array: np.ndarray = np.zeros(200 * 200 * 3, dtype=np.uint8)
	camera_1.traceRect(array, 200, 200, 5, False, True, 0)
	image = array.reshape((200, 200, 3))

	image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

	cv2.imshow("Image", image)
	cv2.waitKey(1)

# # array: np.ndarray = np.zeros(1920 * 1080 * 3, dtype=np.uint8)
# # camera_1.traceRect(array, 1920, 1080, 5, False, True, 0)
# # image = array.reshape((1080, 1920, 3))
#
# # array: np.ndarray = np.zeros(1080 * 720 * 3, dtype=np.uint8)
# # camera_1.traceRect(array, 1080, 720, 5, False, True, 0)
# # image = array.reshape((720, 1080, 3))
#
# array: np.ndarray = np.zeros(200 * 200 * 3, dtype=np.uint8)
# camera_1.traceRect(array, 200, 200, 5, False, True, 0)
# image = array.reshape((200, 200, 3))
#
# image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
#
# cv2.imshow("Image", image)
# cv2.waitKey(0)


"""
# PyQt5
app = QApplication(sys.argv)
color_background: List[int] = [33, 36, 43]

# create widget
widget = QWidget()
display_tracer:		Display_Tracer = Display_Tracer()

# config widget geo and title
widget.resize(600, 600)
widget.move(150, 150)
widget.setWindowTitle("Tracer")

# config widget background color
palette = widget.palette()
color	= QColor(*color_background)
palette.setColor(widget.backgroundRole(), color)
widget.setPalette(palette)

# config layout and add widget
layout = QHBoxLayout()
widget.setLayout(layout)
layout.addWidget(display_tracer)

# update
display_tracer.setDisplaySize(800, 800)
display_tracer.setCamera(camera_1)
display_tracer.update()

# show
widget.show()

sys.exit(app.exec_())
"""
