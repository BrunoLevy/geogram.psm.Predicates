cmake_minimum_required(VERSION 3.16)

project(geogram_predicates LANGUAGES CXX)

find_package(Threads REQUIRED)

# Public inline arithmetic uses globals that are not exported by Windows DLLs.
add_library(geogram_predicates STATIC Predicates_psm.cpp Predicates_psm.h)
add_library(geogram::predicates ALIAS geogram_predicates)

target_include_directories(geogram_predicates PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(geogram_predicates PUBLIC Threads::Threads)
target_compile_features(geogram_predicates PUBLIC cxx_std_17)
target_compile_definitions(geogram_predicates PUBLIC GEO_STATIC_LIBS)

# Exact predicates, including inline code in the public header, must not
# contract multiply-add operations into FMAs.
if(MSVC)
    target_compile_options(geogram_predicates PUBLIC /fp:strict)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
    target_compile_options(geogram_predicates PUBLIC -ffp-contract=off)
endif()
