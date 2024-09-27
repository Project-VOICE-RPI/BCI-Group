#!/bin/sh
cd . && echo \
@goto cmd \
>/dev/null

# posix shell code
toolpath=$(cd /home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils && pwd)
PATH=$PATH:$toolpath
export PATH
echo Added BCI2000 build tools to PATH variable.
exec /bin/sh

# windows cmd code
:cmd
@echo off
cls
set PATH=%PATH%;/home/dante/School/Senior/Fall/RCOS/BCI-Group/BCI-2000/build/buildutils
cmd /k echo Added BCI2000 build tools to PATH variable.

