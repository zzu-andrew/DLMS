cmake_minimum_required (VERSION 3.16)
project (DLMS
        VERSION 0.1.0
        DESCRIPTION "Distributed Linux monitoring system"
        HOMEPAGE_URL https://github.com/zzu-andrew/DLMS
        LANGUAGES CXX
        )


# Linux 分布式监控系统
set (CPACK_PACKAGE_NAME DLMS)
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Distributed Linux monitoring system")
set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})



message(STATUS　${CPACK_PACKAGE_VERSION})






add_subdirectory(3rd/glog)




