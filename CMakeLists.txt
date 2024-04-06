cmake_minimum_required (VERSION 3.0)
cmake_policy(VERSION 3.0)


get_filename_component(APP_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${APP_NAME})

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)



#自动查找头文件路径函数
macro(FIND_INCLUDE_DIR result curdir)  #定义函数,2个参数:存放结果result；指定路径curdir；
    file(GLOB_RECURSE children "${curdir}/*.hpp" "${curdir}/*.h" )	#遍历获取{curdir}中*.hpp和*.h文件列表
    set(dirlist "")														#定义dirlist中间变量，并初始化
    foreach(child ${children})											#for循环
        string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})			#字符串替换,用/前的字符替换/*h
        if(IS_DIRECTORY ${LIB_NAME})									#判断是否为路径
            if(dirlist MATCHES ${LIB_NAME})#判断dirlist是否含有${LIB_NAME}
            else()
              LIST(APPEND dirlist ${LIB_NAME})							#将合法的路径加入dirlist变量中
            endif()
        endif()															#结束判断
    endforeach()														#结束for循环
    set(${result} ${dirlist})											#dirlist结果放入result变量中
endmacro()

macro(GENERATE_C_FILE_LIST HEADER_FILE)
    # 获取目标目录下的所有.c文件
    file(GLOB_RECURSE C_FILES LIST_DIRECTORIES false "${CMAKE_CURRENT_SOURCE_DIR}/src/refs/*.c")

    # 将.c文件名写入头文件
    file(WRITE ${HEADER_FILE} "// Auto-generated file, do not edit\n")
    file(APPEND ${HEADER_FILE} "#define REFS    \\\n")

    foreach(C_FILE ${C_FILES})
        get_filename_component(FILE_NAME ${C_FILE} NAME_WE)
        file(APPEND ${HEADER_FILE} "  REF(${FILE_NAME})\\ \n")
    endforeach()
    file(APPEND ${HEADER_FILE} "\n")
    foreach(C_FILE ${C_FILES})
        get_filename_component(FILE_NAME ${C_FILE} NAME_WE)
        file(APPEND ${HEADER_FILE} "#include \"${FILE_NAME}.h\"\n")
    endforeach()

    file(APPEND ${HEADER_FILE} "
#define REF(x)  \\
    extern Gcomponent *x;   \\
    typedef struct x##_Graphic_Parm_s x##_Graphic_Parm; \\
    void init_##x();\\
    void set_##x##_parm(x##_Graphic_Parm parm,Gcomponent* reference);\\
                      \n
    REFS
#undef REF
")





    foreach(C_FILE ${C_FILES})
        get_filename_component(FILE_NAME ${C_FILE} NAME_WE)
        get_filename_component(FILE_PATH ${C_FILE} DIRECTORY)

        set(headfile_path ${CMAKE_SOURCE_DIR}/build/${FILE_NAME}_arch.h)
        if(NOT EXISTS ${FILE_PATH}/${FILE_NAME}.arch)
            message(FATAL_ERROR "Reference ${FILE_NAME} does not exist arch file ${FILE_NAME}.arch in path ${FILE_PATH}!")
        endif()
        file(READ ${FILE_PATH}/${FILE_NAME}.arch arch)
        string(REPLACE "\n" "\\\n" arch_text ${arch} )

        file(WRITE ${headfile_path} "// Auto-generated file, do not edit\n")
        file(APPEND ${headfile_path} "
#include\"RTree/GraphicsDataStructures.h\"
#define GARCH   \\
    ${arch_text}

#define Component(x) static Gcomponent *x;
#define Component_Group(x, num) static Gcomponent *x;
#define DefGraphicPart(x)
#define EndGraphicPart(x)

    GARCH
#undef DefGraphicPart
#undef Component
#undef Component_Group
#undef EndGraphicPart
        ")
    endforeach()

endmacro()

macro(GENERATE_ARCH ref_floder)
    string(REGEX REPLACE ".*/(.*)" "\\1" ref ${ref_floder})
    set(headfile_path ${ref_floder}ref_arch.h)
    file(READ ${ref_floder}ref.arch arch)
    file(WRITE ${} "// Auto-generated file, do not edit\n")
    file(APPEND ${HEADER_FILE} "
    #define

    #define GARCH   \\
        ${arch}

    ")
endmacro()



file(GLOB_RECURSE SOURCE
    "src/*.h"
    "src/*.c"
)
FIND_INCLUDE_DIR(project_IncludeDir src/)
GENERATE_C_FILE_LIST(${CMAKE_SOURCE_DIR}/build/ref_list.h)

add_executable(${APP_NAME} ${SOURCE} ${CMAKE_SOURCE_DIR}/build/ref_list.h)
target_link_libraries(${APP_NAME} ${LIBS})
target_include_directories(${APP_NAME} PRIVATE ${project_IncludeDir} ${CMAKE_SOURCE_DIR}/build/)
if(MSVC)
target_compile_options(${APP_NAME} PRIVATE /std:c++17 /MP)
target_link_options(${APP_NAME} PUBLIC /ignore:4099)
endif(MSVC)
if(WIN32)
set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${APP_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")
elseif(UNIX)
set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/")
endif(WIN32)

include_directories(${CMAKE_SOURCE_DIR}/include)
