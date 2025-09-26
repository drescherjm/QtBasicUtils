vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/cmake-modules
    REF bdd48bba0691d542fbf5e74e74b21af7b2ba8e09
    SHA512 de5794314eea45dbfa96eebf513753f37887297d042b965b2ee09d1b3f593159cc3457529c129b93e5ce9f4b743571a550af2c5fd15a01e8d8f87466bc078264
)

# Install the modules and config file
file(INSTALL ${SOURCE_PATH}/Modules DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules/Modules)
file(INSTALL ${SOURCE_PATH}/Scripts DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules/Scripts)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesConfig.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
