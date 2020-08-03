from typing import *
from Base import *
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
ops_tracer.Sample_buildScene(0)

tracer:			Tracer = Tracer()
tracer.setOps_tracer(ops_tracer)
tracer.start()

# check
ops_tracer.RayTracer_info()


""" object creation """
hitable_sphere_1:	SceneObject_Sphere	= SceneObject_Sphere()
hitable_trimesh_1:	SceneObject_Trimesh	= SceneObject_Trimesh()


""" display """
app = QApplication(sys.argv)
color_background: List[int] = [33, 36, 43]

# create widget
widget = QWidget()
display_tracer:		Display_Tracer = Display_Tracer()

# config widget geo and title
widget.resize(200, 100)
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
display_tracer.setOps_tracer(ops_tracer)
display_tracer.update()

# show
widget.show()

# sys.exit(app.exec_())

