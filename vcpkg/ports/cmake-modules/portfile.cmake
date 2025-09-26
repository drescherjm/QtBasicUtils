vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/cmake-modules
    REF e9080014da6c0b009292382fe1f16c481c50cf41
    SHA512 e97de9e96ef193c4f642747e79f041056222ca687d82377763143672587d3808ce997756531b7bf45f57c5d2fbe46dd534c946b07dc35ff9cd33fb49291f56e2
)

# Install the modules and config file
file(INSTALL ${SOURCE_PATH}/Modules DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/Scripts DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesConfig.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesTargets.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
