
cmake_minimum_required(VERSION 2.8)

project(Plugin)

set(CMAKE_MODULE_PATH ${BRO_DIST}/cmake)

include(BroPlugin)

bro_plugin_begin(BRO test)
bro_plugin_cc(src/TEST.cc src/Plugin.cc ${BRO_DIST}/src/file_analysis/Analyzer.cc)
bro_plugin_bif(src/events.bif)
bro_plugin_dist_files(README CHANGES COPYING VERSION)
bro_plugin_end()
