vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/cmake-modules
    REF b9d5a36fc04a2a8c1ec5b60e7ec9d7d4611c6488
    SHA512 943971301dc52972d6eaf9200ec3d4376eec0babf0de11e8da6ec1b51e91e9914e8322604f93a339e9308a07d8ae9d8acef52bcc967084054760c1f96465647c
)

# Install the modules and config file
file(INSTALL ${SOURCE_PATH}/Modules DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/Scripts DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesConfig.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesTargets.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
