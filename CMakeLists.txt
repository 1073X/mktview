cmake_minimum_required (VERSION 3.19)
project("${CMAKE_PROJECT_NAME}")
include("$ENV{TOOLCHAIN_PATH}/CMakeLists.txt.in")

add_bin(mktview "source/bin"
    ${LIB_MKT} ${LIB_REF}
    ${LIB_SHM} ${LIB_CFG} ${LIB_LOG}
    ${LIB_COM}
)
add_unittest(
    ${LIB_MKT} ${LIB_REF}
    ${LIB_SHM} ${LIB_CFG} ${LIB_LOG}
    ${LIB_COM}
)


