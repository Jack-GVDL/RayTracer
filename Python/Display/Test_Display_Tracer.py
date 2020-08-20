from typing import *
from Base import *
from Lib import *
from Display.Display_Tracer import Display_Tracer
from PyQt5.QtWidgets import *
from PyQt5.Qt import *
from ctypes import CDLL
import ctypes
import sys
import os


""" tracer """
# add dll path
os.add_dll_directory("C:/WINDOWS/system32")
os.add_dll_directory("D:/Anaconda/Library/mingw-w64/bin")  # TODO: it should not use Anaconda

# import dll file
path_tracer:	str = os.path.join(os.getcwd(), "../Base/bin/Tracer.dll")
dll_tracer:		CDLL = ctypes.CDLL(path_tracer)

# create ops
ops_tracer:		Ops_Tracer_DLL = Ops_Tracer_DLL()
ops_tracer.setDLL_tracer(dll_tracer)
ops_tracer.RayTracer_init()

tracer:			Tracer = Tracer()
tracer.setOps_tracer(ops_tracer)
tracer.start()

# check
ops_tracer.RayTracer_info()

# build sample scene
# ops_tracer.Sample_buildScene(0)


""" object creation """
scene:	Scene	= Scene()
# Tracer_Sample.buildScene_0(scene)
# Tracer_Sample.buildScene_1(scene)
Tracer_Sample.buildScene_2(scene)
# Tracer_Sample.buildScene_3(scene)

ops_tracer.Test_checkStatus(0, bytes(), 0)
ops_tracer.Test_checkStatus(1, bytes(), 0)

ops_tracer.Camera_setLookFrom(	1,	Vec3f(0, 1, 2))
ops_tracer.Camera_setLookAt(	1,	Vec3f(0, 1, 0))
ops_tracer.Camera_setAspectRatio(1, 1)


""" display """
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
display_tracer.setDisplaySize(300, 300)
display_tracer.setOps_tracer(ops_tracer)
display_tracer.update()

# show
widget.show()

sys.exit(app.exec_())
