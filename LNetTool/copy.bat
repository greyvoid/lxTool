cd bin
copy ..\..\build-LNetTool-Desktop_Qt_5_4_0_MinGW_32bit-Release\release\LNetTool.exe 
::copy ..\..\build-BlessCoin_b-Desktop_Qt_5_4_0_MinGW_32bit-Debug\debug\BlessCoin_b.exe .
::copy ..\lib\NBaseUiKit.dll .
copy D:\mysql\lib\libmysql.dll .
copy ..\..\..\..\work\qt\qt5\LQtTool\bin\LQtTool.dll .
windeployqt LNetTool.exe
::ren BlessCoinServer.exe 公会后台管理.exe
pause