# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SomJsonLib")

set(SOURCES	pch.cpp
			Json/Json.cpp
			Json/JsonArray.cpp
			Json/JsonBool.cpp
			Json/JsonNode.cpp
			Json/JsonNodeVirtuals.cpp
			Json/JsonNull.cpp
			Json/JsonNumber.cpp
			Json/JsonObject.cpp
			Json/JsonParcer.cpp
			Json/JsonString.cpp
			Json/JsonTypes.cpp)

set(HEADER framework.h
			SomJson.h
			pch.h
			Json/Json.h
			Json/JsonParcer.h
			Json/JsonTypes.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(SRC_LIST pch.cpp)

#ADD_LIBRARY( ${PROJECT_NAME} STATIC ${HEADER} ${SOURCES} )

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER} ${SOURCES})

set(CMAKE_SUPPRESS_REGENERATION true)
#set(EXCLUDE_FROM_ALL false)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})