cmake_minimum_required(VERSION 3.3)
include_guard(GLOBAL)
# mods
include(dCmake.dir/dHelp.dir/fRegex.cmake)
include(dCmake.dir/dHelp.dir/fOpt.cmake)
# proj
project(NikoZDev
    VERSION 0.2.0
    DESCRIPTION
    "nikodim-zimin-developer root repo"
    ) # project
enable_language(CXX)
set(vProjName ${PROJECT_NAME})
set(vProjNameLib "l${vProjName}")
set(vProjNameExe "e${vProjName}")
set(vProjVnum ${PROJECT_VERSION})
set(vProjVnumMajor ${PROJECT_VERSION_MAJOR})
set(vProjVnumMinor ${PROJECT_VERSION_MINOR})
set(vProjVnumMicro ${PROJECT_VERSION_PATCH})
set(vProjDesc ${PROJECT_DESCRIPTION})
# lang
set(vLangVnum 23)
set(CMAKE_CXX_STANDARD ${vLangVnum})
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# file
set(vFdirLocRoot "${PROJECT_SOURCE_DIR}/..")
set(vFdirSrcRoot "${vFdirLocRoot}/src")
set(vFdirSrcBase "${vFdirSrcRoot}/d${vProjName}.dir")
set(vFdirGenRoot "${vFdirLocRoot}/gen")
set(vFdirEnvRoot "${vFdirLocRoot}/env")
set(vFdirDocRoot "${vFdirLocRoot}/doc")
set(vFdirDstRoot "${CMAKE_INSTALL_PREFIX}")
set(vFdirDstBins "${vFdirDstRoot}/bin")
set(vFdirDstLibs "${vFdirDstRoot}/lib")
set(vFdirDstHead "${vFdirDstRoot}/include")
set(CMAKE_INSTALL_PREFIX "${vFdirDstRoot}")
set(vFdirLibRoot "${vFdirLocRoot}/lib")
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
set(vProjConfList "Work;Play;Dist;")
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
set(vMakeDirsLib ${vFdirSrcRoot} ${vFdirDstHead})
set(vMakeDefsLib
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
    -Wno-narrowing
    -Wno-macro-redefined
    ) # vMakeOptsLib
### libs
find_package(pLibAsist CONFIG REQUIRED)
target_link_libraries(${vProjNameLib} INTERFACE pLibAsist::lLibAsist)
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
            COMMAND ${vFdirGenRoot}/${vProjNameExe}
            ) # add_test
        set(vPassRegex "hello test")
        set_tests_properties(tHello PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        list(APPEND vMakeDefsExe "d${vProjName}TestExe")
    endif(oTestExe)
    # libs
    target_link_libraries(${vProjNameExe} PUBLIC ${vProjNameLib})
    # last
    target_compile_options(${vProjNameExe} PRIVATE ${vMakeOptsExe})
    target_compile_features(${vProjNameExe} PRIVATE ${vMakeFeatExe})
    target_compile_definitions(${vProjNameExe} PRIVATE ${vMakeDefsExe})
    target_include_directories(${vProjNameExe} PRIVATE ${vMakeDirsExe})
    target_precompile_headers(${vProjNameExe} PRIVATE ${vFdirSrcBase}/fHead.hxx)
endif(oMakeExe)
