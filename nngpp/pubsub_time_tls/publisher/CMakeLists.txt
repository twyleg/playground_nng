# Copyright (C) 2023 twyleg
set(TARGET_NAME pubsub_time_tls_publisher)


#
# Copy key and cert of the server
#
configure_file(${CMAKE_SOURCE_DIR}/resources/certs/key_pair_file.pem ${CMAKE_CURRENT_BINARY_DIR}/ COPYONLY)


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


target_include_directories(${TARGET_NAME}
        PUBLIC "${CMAKE_SOURCE_DIR}/external/nngpp/include"
)


#
# link against libs
#
target_link_libraries(${TARGET_NAME}
        nngpp
        utils
)
