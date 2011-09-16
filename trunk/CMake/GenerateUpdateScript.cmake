set ( UPDATE_CMD0 )
set ( UPDATE_CMD1 )
set ( UPDATE_CMD2 )
set ( UPDATE_CMD3 )
set ( UPDATE_CMD4 )
set ( UPDATE_CMD5 )
set ( UPDATE_CMD6 )
set ( UPDATE_CMD7 )
set ( UPDATE_CMD8 )
set ( UPDATE_CMD9 )
set ( UPDATE_CMD10 )

set ( UPDATE_CMD0 "pushd .")
set ( UPDATE_CMD1 "cd \"${CMAKE_SOURCE_DIR}\"")
set ( UPDATE_CMD2 "svn up")
set ( UPDATE_CMD3 "popd")

configure_file( 	
	"${PROJECT_SOURCE_DIR}/update.bat.in"
	"${PROJECT_BINARY_DIR}/Batch/update.bat"
)