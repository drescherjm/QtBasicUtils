set(SCRIPT_PATH "${CURRENT_INSTALLED_DIR}/share/qtbase")
include("${SCRIPT_PATH}/qt_install_submodule.cmake")

set(${PORT}_PATCHES)

set(qtstatemachine_HASH "7a2ca552a296ac700cf92a03cb3e1edda678882147b64e858409aa5bbe440b6d7e969c7c68b7364dfa824f167492446c6933dc818decf16692d41359e2782641")

qt_install_submodule(PATCHES    ${${PORT}_PATCHES}
                     CONFIGURE_OPTIONS
                     CONFIGURE_OPTIONS_RELEASE
                     CONFIGURE_OPTIONS_DEBUG
                    )
