cmake_minimum_required (VERSION 3.16)
project (glog
  VERSION 0.6.0
  DESCRIPTION "C++ implementation of the Google logging module"
  HOMEPAGE_URL https://github.com/google/glog
  LANGUAGES CXX
)

set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})


# 设置静态库文件目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)

list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include (CheckCXXCompilerFlag)
include (CheckCXXSourceCompiles)
include (CheckCXXSourceRuns)
include (CheckCXXSymbolExists)
include (CheckFunctionExists)
include (CheckIncludeFileCXX)
include (CheckLibraryExists)
include (CheckStructHasMember)
include (CheckTypeSize)
include (CMakeDependentOption)
include (CMakePackageConfigHelpers)
include (CMakePushCheckState)
include (GenerateExportHeader)
include (GNUInstallDirs)

option (WITH_PKGCONFIG "Enable pkg-config support" ON)
option (WITH_SYMBOLIZE "Enable symbolize module" ON)
option (WITH_THREADS "Enable multithreading support" ON)
option (WITH_TLS "Enable Thread Local Storage (TLS) support" ON)


set (CMAKE_C_VISIBILITY_PRESET hidden)
set (CMAKE_CXX_VISIBILITY_PRESET hidden)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#set (CMAKE_DEBUG_POSTFIX d)
set (CMAKE_THREAD_PREFER_PTHREAD 1)

if (WITH_TLS)
  # Cygwin does not support the thread attribute. Don't bother.
  if (HAVE_GCC_TLS)
    set (GLOG_THREAD_LOCAL_STORAGE "__thread")
  elseif (HAVE_MSVC_TLS)
    set (GLOG_THREAD_LOCAL_STORAGE "__declspec(thread)")
  elseif (HAVE_CXX11_TLS)
    set (GLOG_THREAD_LOCAL_STORAGE thread_local)
  endif (HAVE_GCC_TLS)
endif (WITH_TLS)

set (_PC_FIELDS
  "gregs[REG_PC]"
  "gregs[REG_EIP]"
  "gregs[REG_RIP]"
  "sc_ip"
  "uc_regs->gregs[PT_NIP]"
  "gregs[R15]"
  "arm_pc"
  "mc_eip"
  "mc_rip"
  "__gregs[REG_EIP]"
  "__gregs[REG_RIP]"
  "ss.eip"
  "__ss.__eip"
  "ss.rip"
  "__ss.__rip"
  "ss.srr0"
  "__ss.__srr0"
)

set (_PC_HEADERS ucontext.h signal.h)

if (HAVE_UCONTEXT_H AND NOT PC_FROM_UCONTEXT)
  foreach (_PC_FIELD ${_PC_FIELDS})
    foreach (_PC_HEADER ${_PC_HEADERS})
      set (_TMP
      ${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/uctfield.cpp)
      file (WRITE ${_TMP} "
#define _GNU_SOURCE 1
#include <${_PC_HEADER}>
int main(void)
{
  ucontext_t u;
  return u.${_PC_FIELD} == 0;
}
")
      try_compile (HAVE_PC_FROM_UCONTEXT ${CMAKE_CURRENT_BINARY_DIR} ${_TMP}
        COMPILE_DEFINITIONS _GNU_SOURCE=1)

      if (HAVE_PC_FROM_UCONTEXT)
        set (PC_FROM_UCONTEXT ${_PC_FIELD} CACHE)
      endif (HAVE_PC_FROM_UCONTEXT)
    endforeach (_PC_HEADER)
  endforeach (_PC_FIELD)
endif  (HAVE_UCONTEXT_H AND NOT PC_FROM_UCONTEXT)

if (STL_STD_NAMESPACE)
  set (STL_NAMESPACE std)
else (STL_STD_NAMESPACE)
  set (STL_NAMESPACE "")
endif (STL_STD_NAMESPACE)

set (GOOGLE_NAMESPACE google)
set (_START_GOOGLE_NAMESPACE_ "namespace ${GOOGLE_NAMESPACE} {")
set (_END_GOOGLE_NAMESPACE_ "}")
set (ac_cv_have_glog_export 1)

if (HAVE___UINT16)
  set (ac_cv_have___uint16 1)
else (HAVE___UINT16)
  set (ac_cv_have___uint16 0)
endif (HAVE___UINT16)

if (HAVE_INTTYPES_H)
  set (ac_cv_have_inttypes_h 1)
else (HAVE_INTTYPES_H)
  set (ac_cv_have_inttypes_h 0)
endif (HAVE_INTTYPES_H)

if (HAVE_LIB_GFLAGS)
  set (ac_cv_have_libgflags 1)
else (HAVE_LIB_GFLAGS)
  set (ac_cv_have_libgflags 0)
endif (HAVE_LIB_GFLAGS)

if (HAVE_STDINT_H)
  set (ac_cv_have_stdint_h 1)
else (HAVE_STDINT_H)
  set (ac_cv_have_stdint_h 0)
endif (HAVE_STDINT_H)

if (HAVE_SYS_TYPES_H)
  set (ac_cv_have_systypes_h 1)
else (HAVE_SYS_TYPES_H)
  set (ac_cv_have_systypes_h 0)
endif (HAVE_SYS_TYPES_H)

if (HAVE_U_INT16_T)
  set (ac_cv_have_u_int16_t 1)
else (HAVE_U_INT16_T)
  set (ac_cv_have_u_int16_t 0)
endif (HAVE_U_INT16_T)

if (HAVE_UINT16_T)
  set (ac_cv_have_uint16_t 1)
else (HAVE_UINT16_T)
  set (ac_cv_have_uint16_t 0)
endif (HAVE_UINT16_T)

if (HAVE_UNISTD_H)
  set (ac_cv_have_unistd_h 1)
else (HAVE_UNISTD_H)
  set (ac_cv_have_unistd_h 0)
endif (HAVE_UNISTD_H)

set (ac_google_namespace ${GOOGLE_NAMESPACE})
set (ac_google_end_namespace ${_END_GOOGLE_NAMESPACE_})
set (ac_google_start_namespace ${_START_GOOGLE_NAMESPACE_})

if (HAVE___ATTRIBUTE__)
  set (ac_cv___attribute___noreturn "__attribute__((noreturn))")
  set (ac_cv___attribute___noinline "__attribute__((noinline))")
  set (ac_cv___attribute___printf_4_5 "__attribute__((__format__(__printf__, 4, 5)))")
elseif (HAVE___DECLSPEC)
  set (ac_cv___attribute___noreturn "__declspec(noreturn)")
  #set (ac_cv___attribute___noinline "__declspec(noinline)")
endif (HAVE___ATTRIBUTE__)

if (HAVE___BUILTIN_EXPECT)
  set (ac_cv_have___builtin_expect 1)
else (HAVE___BUILTIN_EXPECT)
  set (ac_cv_have___builtin_expect 0)
endif (HAVE___BUILTIN_EXPECT)

if (HAVE_USING_OPERATOR)
  set (ac_cv_cxx_using_operator 1)
else (HAVE_USING_OPERATOR)
  set (ac_cv_cxx_using_operator 0)
endif (HAVE_USING_OPERATOR)

if (HAVE_CXX11_CONSTEXPR)
  set (ac_cv_cxx11_constexpr 1)
else (HAVE_CXX11_CONSTEXPR)
  set (ac_cv_cxx11_constexpr 0)
endif (HAVE_CXX11_CONSTEXPR)

if (HAVE_CXX11_CHRONO)
  set (ac_cv_cxx11_chrono 1)
else (HAVE_CXX11_CHRONO)
  set (ac_cv_cxx11_chrono 0)
endif (HAVE_CXX11_CHRONO)

if (HAVE_CXX11_NULLPTR_T)
  set (ac_cv_cxx11_nullptr_t 1)
else (HAVE_CXX11_NULLPTR_T)
  set (ac_cv_cxx11_nullptr_t 0)
endif (HAVE_CXX11_NULLPTR_T)

if (HAVE_EXECINFO_H)
  set (HAVE_STACKTRACE 1)
endif (HAVE_EXECINFO_H)

if (HAVE_CXX11_ATOMIC)
  set (ac_cv_cxx11_atomic 1)
else (HAVE_CXX11_ATOMIC)
  set (ac_cv_cxx11_atomic 0)
endif (HAVE_CXX11_ATOMIC)

if (WITH_SYMBOLIZE)
  if (WIN32 OR CYGWIN)
    cmake_push_check_state (RESET)
    set (CMAKE_REQUIRED_LIBRARIES DbgHelp)

    check_cxx_source_runs ([=[
    #include <windows.h>
    #include <dbghelp.h>
    #include <cstdlib>

    void foobar() { }

    int main()
    {
        HANDLE process = GetCurrentProcess();

        if (!SymInitialize(process, NULL, TRUE))
            return EXIT_FAILURE;

        char buf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
        SYMBOL_INFO *symbol = reinterpret_cast<SYMBOL_INFO *>(buf);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        void* const pc = reinterpret_cast<void*>(&foobar);
        BOOL ret = SymFromAddr(process, reinterpret_cast<DWORD64>(pc), 0, symbol);

        return ret ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    ]=] HAVE_SYMBOLIZE)

    cmake_pop_check_state ()

    if (HAVE_SYMBOLIZE)
      set (HAVE_STACKTRACE 1)
    endif (HAVE_SYMBOLIZE)
  elseif (UNIX OR (APPLE AND HAVE_DLADDR))
    set (HAVE_SYMBOLIZE 1)
  endif (WIN32 OR CYGWIN)
endif (WITH_SYMBOLIZE)

# CMake manages symbolize availability. The definition is necessary only when
# building the library. Switch to add_compile_definitions once we drop support
# for CMake below version 3.12.
add_definitions (-DGLOG_NO_SYMBOLIZE_DETECTION)

check_cxx_source_compiles ("
#include <cstdlib>
#include <ctime>
int main()
{
    time_t timep;
    struct tm result;
    localtime_r(&timep, &result);
    return EXIT_SUCCESS;
}
" HAVE_LOCALTIME_R)

set (SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})

if (WITH_THREADS AND Threads_FOUND)
  if (CMAKE_USE_PTHREADS_INIT)
    set (HAVE_PTHREAD 1)
  endif (CMAKE_USE_PTHREADS_INIT)
else (WITH_THREADS AND Threads_FOUND)
  set (NO_THREADS 1)
endif (WITH_THREADS AND Threads_FOUND)

# fopen/open on Cygwin can not handle unix-type paths like /home/....
# therefore we translate TEST_SRC_DIR to windows-path.
if (CYGWIN)
  execute_process (COMMAND cygpath.exe -m ${CMAKE_CURRENT_SOURCE_DIR}
                   OUTPUT_STRIP_TRAILING_WHITESPACE
                   OUTPUT_VARIABLE TEST_SRC_DIR)
  set (TEST_SRC_DIR \"${TEST_SRC_DIR}\")
else (CYGWIN)
  set (TEST_SRC_DIR \"${CMAKE_CURRENT_SOURCE_DIR}\")
endif (CYGWIN)

configure_file (src/config.h.cmake.in config.h)
configure_file (src/glog/logging.h.in glog/logging.h @ONLY)
configure_file (src/glog/raw_logging.h.in glog/raw_logging.h @ONLY)
configure_file (src/glog/stl_logging.h.in glog/stl_logging.h @ONLY)
configure_file (src/glog/vlog_is_on.h.in glog/vlog_is_on.h @ONLY)

add_compile_options ($<$<AND:$<BOOL:${HAVE_NO_UNNAMED_TYPE_TEMPLATE_ARGS}>,$<NOT:$<CXX_COMPILER_ID:GNU>>>:-Wno-unnamed-type-template-args>)

set (_glog_CMake_BINDIR ${CMAKE_INSTALL_BINDIR})
set (_glog_CMake_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR})
set (_glog_CMake_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set (_glog_CMake_INSTALLDIR ${_glog_CMake_LIBDIR}/cmake/glog)

set (_glog_CMake_DIR glog/cmake)
set (_glog_CMake_DATADIR ${CMAKE_INSTALL_DATAROOTDIR}/${_glog_CMake_DIR})
set (_glog_BINARY_CMake_DATADIR
  ${CMAKE_CURRENT_BINARY_DIR}/${_glog_CMake_DATADIR})

# Add additional CMake find modules here.
set (_glog_CMake_MODULES)

# Generate file name for each module in the binary directory
foreach (_file ${_glog_CMake_MODULES})
  get_filename_component (_module "${_file}" NAME)

  list (APPEND _glog_BINARY_CMake_MODULES
    ${_glog_BINARY_CMake_DATADIR}/${_module})
endforeach (_file)

if (_glog_CMake_MODULES)
  # Copy modules to binary directory during the build
  add_custom_command (OUTPUT ${_glog_BINARY_CMake_MODULES}
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${_glog_BINARY_CMake_DATADIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${_glog_CMake_MODULES}
    ${_glog_BINARY_CMake_DATADIR}
    DEPENDS ${_glog_CMake_MODULES}
    COMMENT "Copying find modules..."
  )
endif (_glog_CMake_MODULES)

set (GLOG_PUBLIC_H
  ${CMAKE_CURRENT_BINARY_DIR}/glog/export.h
  ${CMAKE_CURRENT_BINARY_DIR}/glog/logging.h
  ${CMAKE_CURRENT_BINARY_DIR}/glog/raw_logging.h
  ${CMAKE_CURRENT_BINARY_DIR}/glog/stl_logging.h
  ${CMAKE_CURRENT_BINARY_DIR}/glog/vlog_is_on.h
  src/glog/log_severity.h
  src/glog/platform.h
)

set (GLOG_SRCS
  ${GLOG_PUBLIC_H}
  src/base/commandlineflags.h
  src/base/googleinit.h
  src/base/mutex.h
  src/demangle.cc
  src/demangle.h
  src/logging.cc
  src/raw_logging.cc
  src/symbolize.cc
  src/symbolize.h
  src/utilities.cc
  src/utilities.h
  src/vlog_is_on.cc
)

if (HAVE_PTHREAD OR WIN32 OR CYGWIN)
  list (APPEND GLOG_SRCS src/signalhandler.cc)
endif (HAVE_PTHREAD OR WIN32 OR CYGWIN)

if (CYGWIN OR WIN32)
  list (APPEND GLOG_SRCS
    src/windows/port.cc
    src/windows/port.h
  )
endif (CYGWIN OR WIN32)

add_library (glogbase OBJECT
  ${_glog_BINARY_CMake_MODULES}
  ${GLOG_SRCS}
)

#add_library (glog
#  $<TARGET_OBJECTS:glogbase>
#)

add_library (glog STATIC
  $<TARGET_OBJECTS:glogbase>
)


add_library (glog::glog ALIAS glog)

set (glog_libraries_options_for_static_linking)


if (HAVE_DBGHELP)
  target_link_libraries (glog PRIVATE dbghelp)
  set (glog_libraries_options_for_static_linking "${glog_libraries_options_for_static_linking} -ldbghelp")
endif (HAVE_DBGHELP)

if (HAVE_PTHREAD)
  target_link_libraries (glog PRIVATE ${CMAKE_THREAD_LIBS_INIT})

  if (CMAKE_THREAD_LIBS_INIT)
    set (glog_libraries_options_for_static_linking "${glog_libraries_options_for_static_linking} ${CMAKE_THREAD_LIBS_INIT}")
  endif (CMAKE_THREAD_LIBS_INIT)
endif (HAVE_PTHREAD)

if (gflags_FOUND)
  # Prefer the gflags target that uses double colon convention
  if (TARGET gflags::gflags)
    target_link_libraries (glog PUBLIC gflags::gflags)
  else (TARGET gflags::gflags)
    target_link_libraries (glog PUBLIC gflags)
  endif (TARGET gflags::gflags)

  set (glog_libraries_options_for_static_linking "${glog_libraries_options_for_static_linking} -lgflags")

  target_compile_definitions (glog PRIVATE
    GFLAGS_DLL_DECLARE_FLAG=GOOGLE_GLOG_DLL_DECL
    GFLAGS_DLL_DEFINE_FLAG=GOOGLE_GLOG_DLL_DECL
  )
endif (gflags_FOUND)

if (ANDROID)
  target_link_libraries (glog PRIVATE log)
  set (glog_libraries_options_for_static_linking "${glog_libraries_options_for_static_linking} -llog")
endif (ANDROID)

set_target_properties (glog PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties (glog PROPERTIES SOVERSION 1)

if (CYGWIN OR WIN32)
  target_compile_definitions (glog PUBLIC GLOG_NO_ABBREVIATED_SEVERITIES)
endif (CYGWIN OR WIN32)

if (WITH_CUSTOM_PREFIX)
  target_compile_definitions (glog PUBLIC GLOG_CUSTOM_PREFIX_SUPPORT)
endif (WITH_CUSTOM_PREFIX)

set_target_properties (glog PROPERTIES PUBLIC_HEADER "${GLOG_PUBLIC_H}")

target_include_directories (glog BEFORE PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
  "$<INSTALL_INTERFACE:${_glog_CMake_INCLUDE_DIR}>"
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (CYGWIN OR WIN32)
  target_include_directories (glogbase PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/windows>"
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/windows)

  target_include_directories (glog PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/windows>"
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/windows)
endif (CYGWIN OR WIN32)

set_target_properties (glog PROPERTIES DEFINE_SYMBOL GOOGLE_GLOG_IS_A_DLL)

target_include_directories (glogbase PUBLIC
  $<TARGET_PROPERTY:glog,INCLUDE_DIRECTORIES>)
target_compile_definitions (glogbase PUBLIC
  $<TARGET_PROPERTY:glog,COMPILE_DEFINITIONS>
  PRIVATE GOOGLE_GLOG_IS_A_DLL)

generate_export_header (glog
  EXPORT_MACRO_NAME GOOGLE_GLOG_DLL_DECL
  EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/glog/export.h)

string (STRIP "${glog_libraries_options_for_static_linking}" glog_libraries_options_for_static_linking)

if (WITH_PKGCONFIG)
  set (VERSION ${PROJECT_VERSION})
  set (prefix ${CMAKE_INSTALL_PREFIX})
  set (exec_prefix ${CMAKE_INSTALL_FULL_BINDIR})
  set (libdir ${CMAKE_INSTALL_FULL_LIBDIR})
  set (includedir ${CMAKE_INSTALL_FULL_INCLUDEDIR})

  configure_file (
    "${PROJECT_SOURCE_DIR}/libglog.pc.in"
    "${PROJECT_BINARY_DIR}/libglog.pc"
    @ONLY
  )

  unset (VERSION)
  unset (prefix)
  unset (exec_prefix)
  unset (libdir)
  unset (includedir)
endif (WITH_PKGCONFIG)


set (glog_CMake_VERSION 3.0)

configure_package_config_file (glog-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/glog-config.cmake
  INSTALL_DESTINATION ${_glog_CMake_INSTALLDIR}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file (
  ${CMAKE_CURRENT_BINARY_DIR}/glog-config-version.cmake
  COMPATIBILITY SameMajorVersion)

export (PACKAGE glog)

get_filename_component (_PREFIX "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)

# Directory containing the find modules relative to the config install
# directory.
file (RELATIVE_PATH glog_REL_CMake_MODULES
  ${_PREFIX}/${_glog_CMake_INSTALLDIR}
  ${_PREFIX}/${_glog_CMake_DATADIR}/glog-modules.cmake)

get_filename_component (glog_REL_CMake_DATADIR ${glog_REL_CMake_MODULES}
  DIRECTORY)

set (glog_FULL_CMake_DATADIR
  ${CMAKE_CURRENT_BINARY_DIR}/${_glog_CMake_DATADIR})

configure_file (glog-modules.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/glog-modules.cmake @ONLY)

install (CODE
"
set (glog_FULL_CMake_DATADIR \"\\\${CMAKE_CURRENT_LIST_DIR}/${glog_REL_CMake_DATADIR}\")
set (glog_DATADIR_DESTINATION ${_glog_CMake_INSTALLDIR})

if (NOT IS_ABSOLUTE ${_glog_CMake_INSTALLDIR})
  set (glog_DATADIR_DESTINATION \"\${CMAKE_INSTALL_PREFIX}/\${glog_DATADIR_DESTINATION}\")
endif (NOT IS_ABSOLUTE ${_glog_CMake_INSTALLDIR})

configure_file (\"${CMAKE_CURRENT_SOURCE_DIR}/glog-modules.cmake.in\"
  \"${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/glog-modules.cmake\" @ONLY)
file (INSTALL
  \"${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/glog-modules.cmake\"
  DESTINATION
  \"\${glog_DATADIR_DESTINATION}\")
"
  COMPONENT Development
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/glog-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/glog-config-version.cmake
  DESTINATION ${_glog_CMake_INSTALLDIR})

# Find modules in share/glog/cmake
install (DIRECTORY ${_glog_BINARY_CMake_DATADIR}
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/glog
  COMPONENT Development
  FILES_MATCHING PATTERN "*.cmake"
)

