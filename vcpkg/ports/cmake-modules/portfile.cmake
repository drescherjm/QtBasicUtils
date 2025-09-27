vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO drescherjm/cmake-modules
    REF 483c991cde7be8ec2402e426857cce57832d73de
    SHA512 7ff461888638bf243164ae3ef2dee1f72ee9c857b420fdc840617d206e3b80b6edc5e143ceb351b75fb2ca64db85a03d1a6611c6c448920deadc5500303b8484
)

# Install the modules and config file
file(INSTALL ${SOURCE_PATH}/Modules DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/Scripts DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesConfig.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
file(INSTALL ${SOURCE_PATH}/cmake/cmake-modulesTargets.cmake DESTINATION ${CURRENT_PACKAGES_DIR}/share/cmake-modules)
