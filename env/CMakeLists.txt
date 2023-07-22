cmake_minimum_required(VERSION 3.3)
# mods
include(dCmake.dir/dHelp.dir/fRegex.cmake)
include(dCmake.dir/dHelp.dir/fOpt.cmake)
# proj
project(NikoZDev
    VERSION 0.1.0
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
set(RUNTIME_OUTPUT_DIRECTORY ${vFdirGen}/dExe.dir)
set(LIBRARY_OUTPUT_DIRECTORY ${vFdirGen}/dLib.dir)
set(ARCHIVE_OUTPUT_DIRECTORY ${vFdirGen}/dLib.dir)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
##type
set(oProjType "Hol")
set(vProjTypeList "Exe;Hol;Dll;Sll")
fOptEnum(oProjType vProjTypeList "project type")
if(oProjType STREQUAL "")
    message("project type is not defined")
elseif(oProjType STREQUAL "Exe")
elseif(oProjType STREQUAL "Hol")
elseif(oProjType STREQUAL "Dll")
elseif(oProjType STREQUAL "Sll")
else()
    message("project type is not handled")
endif(oProjType STREQUAL "")
##conf
set(oProjConf "Work")
set(vProjContList "Work;Play;Dist")
fOptEnum(oProjConf vProjConfList "project configuration")
if(NOT oProjConf IN_LIST vProjConfList)
    message("project configuration is not defined")
elseif(oProjConf STREQUAL "Play")
    set(CMAKE_BUILD_TYPE Release)
elseif(oProjConf STREQUAL "Work")
    set(CMAKE_BUILD_TYPE Debug)
else()
    message("project configuration is not handled")
endif() # oProjConf
## lib
add_library(${vProjNameLib} INTERFACE)
set(vMakeDirsLib ${vFdirSrcRoot})
set(vMakeDefsLib
    "$<$<CXX_COMPILER_ID:MSVC>:>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:>"
    "d${vProjName}ProjName=\"${vProjName}\"" "dProjName=\"${vProjName}\""
    "d${vProjName}ProjVnum=\"${vProjVnum}\"" "dProjVnum=\"${vProjVnum}\""
    "d${vProjName}ProjDesc=\"${vProjDesc}\"" "dProjDesc=\"${vProjDesc}\""
    "d${vProjName}ProjConf${oProjConf}=1" "dProjConf${oProjConf}=1"
    ) # vMakeDefsLib
set(vMakeFeatLib
    cxx_std_20
    cxx_constexpr
    cxx_variadic_templates
    ) # vMakeFeatLib
set(vMakeOptsLib
    -fpermissive
    -Wno-class-conversion
    -Wno-error=narrowing -Wno-narrowing
    ) # vMakeOptsLib
### libs
### last
target_compile_options(${vProjNameLib} INTERFACE ${vMakeOptsLib})
target_compile_features(${vProjNameLib} INTERFACE ${vMakeFeatLib})
target_compile_definitions(${vProjNameLib} INTERFACE ${vMakeDefsLib})
target_include_directories(${vProjNameLib} INTERFACE ${vMakeDirsLib})
target_precompile_headers(${vProjNameLib} INTERFACE ${vFdirSrcBase}/fHead.hxx)
## exe
option(oMakeExe "make executable" 1)
if(oMakeExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vMakeDirsExe "")
    set(vMakeDefsExe "d${vProjName}MakeExe")
    set(vMakeFeatExe "")
    set(vMakeOptsExe "")
    # test
    option(oTestExe "test executable" 1)
    if(oTestExe)
        enable_testing()
        add_test(NAME tHello
            COMMAND ${vFdirGen}/${vProjNameExe}
            ) # add_test
        set(vPassRegex "hello test")
        set_tests_properties(tHello PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        list(APPEND vMakeDefsExe "d${vProjName}TestExe")
    endif(oTestExe)
    # libs
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    # last
    target_compile_options(${vProjNameExe} PRIVATE ${vMakeOptsExe})
    target_compile_features(${vProjNameExe} PRIVATE ${vMakeFeatExe})
    target_compile_definitions(${vProjNameExe} PRIVATE ${vMakeDefsExe})
    target_include_directories(${vProjNameExe} PRIVATE ${vMakeDirsExe})
    target_precompile_headers(${vProjNameExe} PRIVATE ${vFdirSrcBase}/fHead.hxx)
endif(oMakeExe)
