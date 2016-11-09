set H5S_VER=r1.0.1109.16
set H5S_VER_PHASE=release

mkdir H5S-%H5S_VER%-win32-%H5S_VER_PHASE%
mkdir H5S-%H5S_VER%-win32-%H5S_VER_PHASE%\www
mkdir H5S-%H5S_VER%-win32-%H5S_VER_PHASE%\ssl
REM copy dir from hss
del  h5ss\prj_win32\Release\*.obj /f /s /q
del  h5ss\prj_win32\Release\*.log /f /s /q
del  h5ss\prj_win32\Release\*.pdb /f /s /q
RD /S /Q h5ss\prj_win32\Release\h5ss.tlog
xcopy /y /e h5ss\prj_win32\Release  H5S-%H5S_VER%-win32-%H5S_VER_PHASE%
xcopy /y /e 3rdparty\windows\vs2013\x86  H5S-%H5S_VER%-win32-%H5S_VER_PHASE%


REM copy dir from www ssl bat
xcopy /y /e h5ss\www  H5S-%H5S_VER%-win32-%H5S_VER_PHASE%\www
xcopy /y /e h5ss\ssl  H5S-%H5S_VER%-win32-%H5S_VER_PHASE%\ssl
xcopy /y h5ss\h5ss.bat  H5S-%H5S_VER%-win32-%H5S_VER_PHASE%

