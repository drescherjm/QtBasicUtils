vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/libqxt-cmake
    REF 2cbaf998cf6fb6bc2dce0582d38ae41b9655578d # or use a specific tag/commit
    SHA512 03814279a38246456c1dd10dfb9721b77ecf8098b0f394117debe893a5966a2bb61dab0780b28f56d37b2000bfefb4bd18b39d4fa3f054b9f1c2c7308c2d38bf # Replace with the actual sha512 03814279a38246456c1dd10dfb9721b77ecf8098b0f394117debe893a5966a2bb61dab0780b28f56d37b2000bfefb4bd18b39d4fa3f054b9f1c2c7308c2d38bf by vcpkg hash
)

set(CONFIGURE_OPTIONS)

if("qt5" IN_LIST FEATURES AND "qt6" IN_LIST FEATURES)
    message(FATAL_ERROR "Features 'qt5' and 'qt6' cannot be used together.")
elseif("qt5" IN_LIST FEATURES)
    list(APPEND CONFIGURE_OPTIONS -DSELECT_QT_VERSION="Qt5")
elseif("qt6" IN_LIST FEATURES)
    list(APPEND CONFIGURE_OPTIONS -DSELECT_QT_VERSION="Qt6")
else()
    message(FATAL_ERROR "Either 'qt5' or 'qt6' must be enabled.")
endif()

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    OPTIONS ${CONFIGURE_OPTIONS}
)

vcpkg_cmake_build()
vcpkg_cmake_install()

# Fixup cmake config locations and paths. This is essential for vcpkg to setup the SimpleLibraryExampleConfig.cmake file 
# and setup each configuration for multiconfig generators like Visual Studio 2022. 
# Remember that vcpkg builds the Debug and Release config then maps the other configs: MinSizeRel, RelWithDebInfo to
# use the binaries created for the Release config. 
vcpkg_cmake_config_fixup(PACKAGE_NAME libQxt CONFIG_PATH lib/cmake/libQxt)

