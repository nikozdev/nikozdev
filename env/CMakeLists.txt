cmake_minimum_required(VERSION 3.3)
# mods
include(cmake/mHelpRegex.cmake)
include(cmake/mHelpOpt.cmake)
# proj
project(NikoZDev
    VERSION 0.0.0
    DESCRIPTION
    "nikodim-zimin-developer root repo"
    ) # project
enable_language(CXX)
set(vProjName ${PROJECT_NAME})
set(vProjNameLib "l${vProjName}") # header-only-library target
set(vProjNameExe "e${vProjName}") # executable target
set(vProjVnum ${PROJECT_VERSION})
set(vProjDesc ${PROJECT_DESCRIPTION})
# lang
set(vLangVnum 23)
set(CMAKE_CXX_STANDARD ${vLangVnum})
set(CMAKE_CXX_STANDARD_REQUIRED ${vLangVnum})
# file
set(vFdirLoc ${PROJECT_SOURCE_DIR}/..)
set(vFdirSrcRoot ${vFdirLoc}/src)
set(vFdirSrcBase ${vFdirSrcRoot}/d${vProjName}.dir)
set(vFdirGen ${vFdirLoc}/gen)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
## lib
add_library(${vProjNameLib} INTERFACE)
set(vProjDefsLib
    "$<$<CXX_COMPILER_ID:MSVC>:>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:>"
    "d${vProjName}ProjName=\"${vProjName}\""
    "d${vProjName}ProjVnum=\"${vProjVnum}\""
    "d${vProjName}ProjDesc=\"${vProjDesc}\""
    ) # vProjDefsLib
### libs
### last
target_compile_definitions(${vProjNameLib} INTERFACE ${vProjDefsLib})
target_include_directories(${vProjNameLib} INTERFACE ${vFdirSrcRoot})
## exe
option(oMakeProjExe "make project executable" 1)
if(oMakeProjExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vProjDefsExe "d${vProjName}MakeProjExe")
    # test
    option(oTestProjExe "test project executable" 1)
    if(oTestProjExe)
        enable_testing()
        add_test(NAME tHello
            COMMAND ${vFdirGen}/${vProjNameExe}
            ) # add_test
        set(vPassRegex "hello test")
        set_tests_properties(tHello PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        list(APPEND vProjDefsExe "d${vProjName}TestProjExe")
    endif(oTestProjExe)
    # libs
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    # last
    target_compile_definitions(${vProjNameExe} PRIVATE ${vProjDefsExe})
endif(oMakeProjExe)
