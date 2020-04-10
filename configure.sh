#!/bin/sh

# CONFIGURE : cd /home/darko/Radovi/AppDev/opengl-cg && ./configure.sh
# COMPILE   : cd /home/darko/Radovi/AppDev/opengl-cg/build/ && make 01_Cube && ./01_Cube

cd /home/darko/Radovi/AppDev/opengl-cg

mkdir -p build/
cd build/
cmake ../

# cd ../
# exuberant ctags
# gtags --gtagslabel=ctags

# universal ctags
# gtags --gtagslabel=new-ctags
