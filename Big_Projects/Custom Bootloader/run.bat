@ECHO OFF

make clean
timeout /t 1 /nobreak
make
timeout /t 1 /nobreak
make flash_bootloader