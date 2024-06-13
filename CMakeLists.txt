cmake_minimum_required (VERSION 3.7.2)

project(MineSweeper)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(BIN_DIR ${MineSweeper_SOURCE_DIR}/bin)

IF (WIN32)
  set(SDL2_PATH "E:/Project/Library/SDL2-2.30.3")
  set(SDL2_ttf_PATH "E:/Project/Library/SDL2_ttf-2.22.0")
ENDIF()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_ttf_INCLUDE_DIR})

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(MineSweeper 
	${SOURCE_FILES}
)

target_include_directories(MineSweeper PRIVATE include)

target_link_libraries(MineSweeper 
	${SDL2_LIBRARY}
	${SDL2_ttf_LIBRARY}
)

add_custom_command(
	TARGET MineSweeper POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MineSweeper>/assets
)

install(TARGETS MineSweeper DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION bin/assets)


install(TARGETS MineSweeper RUNTIME DESTINATION ${BIN_DIR}/)
set_target_properties(MineSweeper PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/debug/
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/release/ )

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x64/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x64/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )

		add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_ttf_PATH}/lib/x64/SDL2_ttf.dll 
		${BIN_DIR}/debug/SDL2_ttf.dll  )
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_ttf_PATH}/lib/x64/SDL2_ttf.dll
		${BIN_DIR}/debug/SDL2_ttf.dll  )
elseif()
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x86/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x86/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )

		add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_ttf_PATH}/lib/x64/SDL2_ttf.dll 
		${BIN_DIR}/debug/SDL2_ttf.dll  )
	add_custom_command( TARGET MineSweeper POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_ttf_PATH}/lib/x64/SDL2_ttf.dll
		${BIN_DIR}/debug/SDL2_ttf.dll  )
endif()