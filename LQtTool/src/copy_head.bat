@echo off
echo lsx ����ͷ�ļ������Ե�......
::pause

set resulePath=F:\work\qt\qt5\LQtTool\include
if not exist %resulePath% md %resulePath%;
::cd src

::for /f "delims=" %%i in ('dir /s/b *.h') do (
::xcopy %%i ..\include\
::echo %%i
::)

::�ȿ��������ļ�����ɾ��cpp�ļ�

:: �Ҳ� ����Ҳ̫ǿ���˰�
::/s���Ʒǿյ�Ŀ¼����Ŀ¼�����ʡ�ԡ�/s������xcopy�����ڵ���Ŀ¼�й���
::/e����������Ŀ¼��������Ŀ¼������/e���롰/s���͡�/t��������ѡ��һ��ʹ�á�
::/y ����
xcopy *.h ..\include /s /y

echo ������ɣ�
::echo. & pause