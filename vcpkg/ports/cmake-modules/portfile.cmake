vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/cmake-modules
    REF bdd48bba0691d542fbf5e74e74b21af7b2ba8e09
    SHA512 d124afe43b992074207738236c00ddef387d654802343e74b2c7e9a9752b26d8c71e49e9ef3994058ead1e9caf267090a88dca72dbde5b49604ba965cc528d11
)

# Install the modules and config file
file(INSTALL ${SOURCE_PATH}/Modules DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/Scripts DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesConfig.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesTargets.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
