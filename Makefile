all: iq

# 実行ファイルの生成
iq: iq.obj Camera.obj GL_Utility.obj Stage.obj Player.obj
	bcc32 iq.obj Camera.obj GL_Utility.obj Stage.obj Player.obj

main: main.obj Stage.obj GL_Utility.obj
	bcc32 main.obj Stage.obj GL_Utility.obj


# オブジェクトファイルの生成
iq.obj: iq.cpp iq.h common.h
	bcc32 -c iq.cpp

main.obj: main.cpp main.h common.h
	bcc32 -c main.cpp

Stage.obj: Stage.cpp Stage.h common.h
	bcc32 -c Stage.cpp

Player.obj: Player.cpp Player.h common.h
	bcc32 -c Player.cpp

GL_Utility.obj: GL_Utility.cpp GL_Utility.h common.h
	bcc32 -c GL_Utility.cpp

Camera.obj: Camera.cpp Camera.h common.h
	bcc32 -c Camera.cpp

.PHONY: clean
clean:
	del *.obj *.tds *.exe *~
