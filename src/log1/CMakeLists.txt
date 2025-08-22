cmake_minimum_required(VERSION 3.8)
project(log1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
  message(STATUS "找到yaml-cpp: ${yaml-cpp_INCLUDE_DIRS}")
else()
  message(FATAL_ERROR "未找到yaml-cpp")
endif()


add_custom_command(
  OUTPUT admin.h
  COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/adminpy/adminpy.py
          ${CMAKE_CURRENT_SOURCE_DIR}/admin/admin.yaml admin.h
          DEPENDS admin.yaml adminpy.py
          COMMENT "生成admin.h"
)

add_executable(main src/main.cpp src/log.cpp src/logger.cpp) 
target_include_directories(main PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(main PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  main
  "rclcpp"
)

install(TARGETS main
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
