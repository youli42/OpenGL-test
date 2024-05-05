#处理glframework
#递归将本文件夹下所有cpp放到FW中
file(GLOB_RECURSE FW  ./ *.cpp)

#将FW中所有cpp编译为fw;这个lib库
add_library(fw ${FW})