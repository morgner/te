add_executable(data
  data.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/data.cpp
#  $<TARGET_OBJECTS:${PROJECT_NAME}>
  )

add_executable(te
  te.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/te.cpp
#  $<TARGET_OBJECTS:${PROJECT_NAME}>
  )

#add_library(${PROJECT_NAME} OBJECT
#   ${CMAKE_CURRENT_SOURCE_DIR}/te.cpp
#   )
