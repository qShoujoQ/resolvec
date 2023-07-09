cmake_minimum_required (VERSION 3.10)
project (resolvec)

set (CMAKE_C_STANDARD 23)

# create library out of source/misc folder
add_library (
    misc
    src/misc/debug.h
    src/misc/debug.c
    src/misc/misc.h
    src/misc/bytes.c
    src/misc/bytes.h
)

# create library out of source/net folder
add_library (
    net
    src/net/net.h
    src/net/format.h
    src/net/format.c
    src/net/transfer.h
    src/net/transfer.c
)

# net depends on misc
target_link_libraries (net misc)

add_library(
    dns
    src/dns/dns.h
    src/dns/dns.c
    src/dns/packet.h
    src/dns/packet.c
)

# dns depends on everything
target_link_libraries (dns net)
target_link_libraries (dns misc)

add_executable (
    ${PROJECT_NAME}
    src/tests_examples.c
    src/resolvec.h
)

# resolvec depends on everything
target_link_libraries (${PROJECT_NAME} misc)
target_link_libraries (${PROJECT_NAME} net)
target_link_libraries (${PROJECT_NAME} dns)

target_link_libraries (${PROJECT_NAME} ws2_32)
