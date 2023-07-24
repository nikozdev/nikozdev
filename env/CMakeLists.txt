cmake_minimum_required(VERSION 3.3...3.8)
include_guard(GLOBAL)
# mods
include(dCmake.dir/dHelp.dir/fRegex.cmake)
include(dCmake.dir/dHelp.dir/fOpt.cmake)
# proj
project(NikoZDev
    VERSION 0.2.0
    DESCRIPTION "nikodim-zimin-developer template repo"
    ) # project
enable_language(CXX)
set(vProjName ${PROJECT_NAME})
set(vProjNameLib "l${vProjName}")
set(vProjNameExe "e${vProjName}")
set(vProjNameDir "d${vProjName}.dir")
set(vProjNameDst "p${vProjName}")
set(vProjVnum ${PROJECT_VERSION})
set(vProjVnumMajor ${PROJECT_VERSION_MAJOR})
set(vProjVnumMinor ${PROJECT_VERSION_MINOR})
set(vProjVnumMicro ${PROJECT_VERSION_PATCH})
set(vProjNameVer
    "${vProjName}-${vProjVnumMajor}-${vProjVnumMinor}-${vProjVnumMicro}"
    ) # vProjNameVer
set(vProjDesc ${PROJECT_DESCRIPTION})
# lang
set(vLangVnum 23)
set(CMAKE_CXX_STANDARD ${vLangVnum})
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# file
set(vFdirLocRoot "${PROJECT_SOURCE_DIR}/..")
set(vFdirSrcRoot "${vFdirLocRoot}/src")
set(vFdirSrcBase "${vFdirSrcRoot}/${vProjNameDir}")
set(vFdirGenRoot "${vFdirLocRoot}/gen")
set(vFdirEnvRoot "${vFdirLocRoot}/env")
set(vFdirDocRoot "${vFdirLocRoot}/doc")
set(vFdirDstRoot "$ENV{HOME}$ENV{USERPROFILE}/.local")
set(vFdirDstBins "${vFdirDstRoot}/bin")
set(vFdirDstLibs "${vFdirDstRoot}/lib")
set(vFdirDstHead "${vFdirDstRoot}/include")
set(vFdirDstProj "${vFdirDstLibs}/cmake/p${vProjNameVer}.dir")
set(CMAKE_INSTALL_PREFIX "${vFdirDstRoot}" CACHE PATH "install prefix" FORCE)
#conf
set(oProjConfPick "Work")
set(vProjConfList "Work;Play;Dist;")
set(vProjConfDesc "controlled by oProjConfPick")
fOptEnum(oProjConfPick vProjConfList "project configuration")
if(oProjConfPick STREQUAL "")
    message("project configuration is not defined")
elseif(oProjConfPick STREQUAL "Work")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING ${vProjConfDesc} FORCE)
elseif(oProjConfPick STREQUAL "Play")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING ${vProjConfDesc} FORCE)
elseif(oProjConfPick STREQUAL "Dist")
    set(CMAKE_BUILD_TYPE Release CACHE STRING ${vProjConfDesc} FORCE)
else()
    message("project configuration is not handled")
endif(oProjConfPick STREQUAL "")
fOptEnum(CMAKE_BUILD_TYPE CMAKE_CONFIGURATION_TYPES ${vProjConfDesc})
mark_as_advanced(FORCE CMAKE_BUILD_TYPE)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
## lib
add_library(${vProjNameLib} INTERFACE)
set(vMakeDirsLib
$<BUILD_INTERFACE:${vFdirSrcRoot}>;
$<INSTALL_INTERFACE:${vFdirDstHead}>;
) # vMakeDirsLib
set(vMakeDefsLib
    $<$<CXX_COMPILER_ID:MSVC>:>
    $<$<CXX_COMPILER_ID:GNU,Clang>:>
    "d${vProjName}ProjName=\"${vProjName}\"" "dProjName=\"${vProjName}\""
    "d${vProjName}ProjVnum=\"${vProjVnum}\"" "dProjVnum=\"${vProjVnum}\""
    "d${vProjName}ProjDesc=\"${vProjDesc}\"" "dProjDesc=\"${vProjDesc}\""
    "d${vProjName}ProjConf${oProjConfPick}" "dProjConf${oProjConfPick}"
    ) # vMakeDefsLib
set(vMakeFeatLib
    cxx_std_23
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
set(vLibsList "")
find_package(pLibAsist "1.0.1" REQUIRED)
target_link_libraries(${vProjNameLib} INTERFACE pLibAsist::lLibAsist)
list(APPEND vLibsList "pLibAsist")
### last
target_compile_options(${vProjNameLib} INTERFACE ${vMakeOptsLib})
target_compile_features(${vProjNameLib} INTERFACE ${vMakeFeatLib})
target_compile_definitions(${vProjNameLib} INTERFACE ${vMakeDefsLib})
target_include_directories(${vProjNameLib} INTERFACE ${vMakeDirsLib})
target_sources(${vProjNameLib}
    INTERFACE FILE_SET HEADERS
    BASE_DIRS "${vFdirSrcBase}"
    FILES
    "${vFdirSrcBase}/fHead.hxx"
    ) # target_sources
target_precompile_headers(${vProjNameLib} INTERFACE ${vFdirSrcBase}/fHead.hxx)
## exe
option(oMakeExe "make project executable" 1)
if(oMakeExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vMakeDirsExe "")
    set(vMakeDefsExe "d${vProjName}MakeExe")
    set(vMakeFeatExe "")
    set(vMakeOptsExe "")
    # test
    option(oTestExe "test project executable" 1)
    if(oTestExe)
        include(CTest)
        enable_testing()
        list(APPEND vMakeDefsExe "d${vProjName}TestExe")
        #
        set(vTestName "tHello")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe}
            ) # add_test
        set(vPassRegex "hello test")
        set_tests_properties(tHello PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
        mark_as_advanced(FORCE CMAKE_BUILD_TYPE)
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
# pack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${vFdirDocRoot}/fLicense.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${vProjVnumMajor}")
set(CPACK_PACKAGE_VERSION_MINOR "${vProjVnumMinor}")
set(CPACK_PACKAGE_VERSION_PATCH "${vProjVnumMicro}")
include(CPack)
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${vFdirEnvRoot}/dCMake.dir/dPack.dir/fConfig.cmake.in"
    "${vFdirGenRoot}/${vProjNameDst}Config.cmake"
    INSTALL_DESTINATION "${vFdirDstProj}"
    ) # package Config
write_basic_package_version_file(
    "${vFdirGenRoot}/${vProjNameDst}ConfigVersion.cmake"
    VERSION ${vProjVnum}
    COMPATIBILITY SameMajorVersion
    ) # package ConfigVersion
install(
    TARGETS ${vProjNameLib} EXPORT ${vProjNameDst}
    FILE_SET HEADERS DESTINATION ${vFdirDstHead}/${vProjNameDir}
    ) # install target with header
install(EXPORT "${vProjNameDst}"
    FILE "${vProjNameDst}.cmake"
    DESTINATION "${vFdirDstProj}"
    NAMESPACE "${vProjNameDst}::"
    ) # install Target
install(FILES
    "${vFdirGenRoot}/${vProjNameDst}Config.cmake"
    "${vFdirGenRoot}/${vProjNameDst}ConfigVersion.cmake"
    DESTINATION "${vFdirDstProj}"
    ) # install ConfigVersion
export(EXPORT "${vProjNameDst}"
    FILE "${vFdirGenRoot}/${vProjNameDst}.cmake"
    NAMESPACE "${vProjNameDst}::"
    ) # export Target
