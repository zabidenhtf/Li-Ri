# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-src"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-build"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/tmp"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/src/simpleini-populate-stamp"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/src"
  "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/src/simpleini-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/src/simpleini-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/zabiden/Documents/Li-Ri/build/_deps/simpleini-subbuild/simpleini-populate-prefix/src/simpleini-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
