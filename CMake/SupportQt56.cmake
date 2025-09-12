# Find Qt via vcpkg if not found fail hard!
find_package(QT NAMES ${SELECT_QT_VERSION} REQUIRED)

# The ability to support Qt5 or Qt6 is based on the following stackoverflow answer:
# https://stackoverflow.com/a/71131723/487892

#Create a variable containing Qt5 or Qt6
set(QT Qt${QT_VERSION_MAJOR})


set(${PROJECT_NAME}_QT_VERSION ${QT_VERSION_MAJOR})