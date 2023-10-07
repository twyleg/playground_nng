# Copyright (C) 2023 twyleg
cmake_minimum_required(VERSION 3.26.4)

project(playground_nngpp)

# Externals
add_subdirectory(external/nngpp/)

# IDL
add_subdirectory(resources/idl/)

# Common
add_subdirectory(utils/)

# Examples
add_subdirectory(pubsub_time/)
add_subdirectory(pubsub_time_tls/)
add_subdirectory(pubsub_multiple_topics/)
add_subdirectory(reqrep_time/)
add_subdirectory(reqrep_time_protobuf/)
