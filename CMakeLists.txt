# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)


# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SomLauncher" VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Network)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

set(SOURCES SomAlwaysCleaner/SomAlwaysCleaner.cpp
			SomAlwaysCleaner/Time/Time.cpp
			SomAlwaysCleaner/Notifications/Notification.cpp
			SomAlwaysCleaner/Files/Files.cpp
			SomAlwaysCleaner/Deleters/Deleter.cpp)

set(HEADER SomAlwaysCleaner/Time/Time.h 
			SomAlwaysCleaner/Notifications/Notification.h
			SomAlwaysCleaner/Files/Files.h
			SomAlwaysCleaner/Deleters/Deleter.h)


set(SRC_LIST SomAlwaysCleaner/SomAlwaysCleaner.cpp)

#add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER} ${SOURCES})

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER} ${SOURCES})

set(CMAKE_SUPPRESS_REGENERATION false)
set(EXCLUDE_FROM_ALL false)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})