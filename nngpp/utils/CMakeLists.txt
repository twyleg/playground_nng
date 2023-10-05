# Copyright (C) 2023 twyleg
set(TARGET_NAME utils)


#
# add source files to target
#
add_library(${TARGET_NAME}
        time.cc
        time.h
)


#
# set target properties
#
set_target_properties(${TARGET_NAME}
	PROPERTIES
	CXX_STANDARD 17
	INCLUDE_CURRENT_DIR ON
)

target_include_directories(${TARGET_NAME}
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../"
        PUBLIC "${CMAKE_SOURCE_DIR}/external/rapidjson/include"
)

#
# link against libs
#
target_link_libraries(${TARGET_NAME}
)
