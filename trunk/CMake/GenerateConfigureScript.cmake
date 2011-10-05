set ( CONFIGURE_CMD0 )
set ( CONFIGURE_CMD1 )
set ( CONFIGURE_CMD2 )
set ( CONFIGURE_CMD3 )
set ( CONFIGURE_CMD4 )
set ( CONFIGURE_CMD5 )
set ( CONFIGURE_CMD6 )
set ( CONFIGURE_CMD7 )
set ( CONFIGURE_CMD8 )
set ( CONFIGURE_CMD9 )
set ( CONFIGURE_CMD10 )

set ( CONFIGURE_CMD0 "@pushd .")
set ( CONFIGURE_CMD1 "@cd \"${CMAKE_BINARY_DIR}\"")
set ( CONFIGURE_CMD2 "@cmake \"${CMAKE_SOURCE_DIR}\"")
set ( CONFIGURE_CMD3 "@popd")

configure_file( 	
	"${PROJECT_SOURCE_DIR}/configure.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/configure.bat"
)