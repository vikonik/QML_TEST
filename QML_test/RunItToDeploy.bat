@echo off
echo QML Deploy Script

set RELEASE_DIR=D:\Project\99_QML_Table\QML_TEST\build-QML_Test-Desktop_Qt_5_14_2_MinGW_32_bit-Release\release
set PROJECT_DIR=D:\Project\99_QML_Table\QML_TEST
set QT_PATH=C:\Qt\Qt5.14.2\5.14.2\mingw73_32

echo Step 1: Check if EXE exists
if not exist "%RELEASE_DIR%\QML_Test.exe" (
    echo ERROR: QML_Test.exe not found!
    echo Build the project first in Qt Creator
    pause
    exit
)

echo Step 2: Run windeployqt
cd /d "%RELEASE_DIR%"
"%QT_PATH%\bin\windeployqt.exe" --qmldir "%PROJECT_DIR%" "QML_Test.exe"

echo Step 3: Check result
if exist "qml" (
    echo SUCCESS: qml folder created
) else (
    echo ERROR: qml folder not created
)

echo Step 4: Start application
echo Starting QML_Test.exe...
"QML_Test.exe"

echo.
pause