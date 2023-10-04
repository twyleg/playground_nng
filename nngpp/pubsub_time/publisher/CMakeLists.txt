# Copyright (C) 2023 twyleg
set(TARGET_NAME pubsub_time_publisher)


#
# add source files to target
#
add_executable(${TARGET_NAME}
	publisher.cc
)


#
# set target properties
#
set_target_properties(${TARGET_NAME}
	PROPERTIES
	CXX_STANDARD 17
	INCLUDE_CURRENT_DIR ON
)


#
# link against libs
#
target_link_libraries(${TARGET_NAME}
	nngpp
)
