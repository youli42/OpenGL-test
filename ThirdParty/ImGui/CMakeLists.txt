#处理Gui

#递归将本文件夹下所有cpp放到GUI中
file(GLOB_RECURSE GUI  ./ *.cpp)

#将WRAPPER中所有cpp编译为wrapper;这个lib库
add_library(gui ${GUI})