add_executable(data
  data.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/data.cpp
#  $<TARGET_OBJECTS:${PROJECT_NAME}>
  )

add_executable(index
  index.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
#  $<TARGET_OBJECTS:${PROJECT_NAME}>
  )

#add_library(${PROJECT_NAME} OBJECT
#   ${CMAKE_CURRENT_SOURCE_DIR}/index.cpp
#   )
