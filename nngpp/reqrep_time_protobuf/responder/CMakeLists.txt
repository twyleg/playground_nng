# Copyright (C) 2023 twyleg
set(TARGET_NAME regrep_time_protobuf_responder)


#
# add source files to target
#
add_executable(${TARGET_NAME}
        responder.cc
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
        time_idl
)
