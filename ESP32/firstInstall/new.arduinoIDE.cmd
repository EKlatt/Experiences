ECHO OFF
mkdir %HOMEPATH%\.arduinoIDE"
ECHO  copy "arduino-cli.yaml" "%HOMEPATH%\.arduinoIDE\"
COPY "arduino-cli.yaml" "%HOMEPATH%\.arduinoIDE\"
PAUSE
