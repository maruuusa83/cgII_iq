all: main.obj Stage.obj GL_Utility.obj
	bcc32 main.obj Stage.obj GL_Utility.obj

main.obj: main.cpp main.h common.h
	bcc32 -c main.cpp

Stage.obj: Stage.cpp Stage.h common.h
	bcc32 -c Stage.cpp

GL_Utility.obj: GL_Utility.cpp GL_Utility.h common.h
	bcc32 -c GL_Utility.cpp


clean:
	del *.obj *.tds *.exe