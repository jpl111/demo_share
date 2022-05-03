cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()


set(IUP_HOME E:/MyFiles/MFC/IUP/iup-3.25_Win32_dll12_lib)

#add include dir
include_directories(.
                    ${IUP_HOME}/include
                    )

#add lib dir
link_directories(${IUP_HOME})


add_executable(Test main.c)


if(MSVC)
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			#LINK_FLAGS "/ENTRY:mainCRTStartup"
		)

        set(CMAKE_C_FLAGS "${EXTRA_CFLAGS} -DUSG_WINMAIN")

elseif(CMAKE_COMPILER_IS_GNUCXX)
        #set_target_properties(${PROJECT_NAME} PROPERTIES
        #WIN32_EXECUTABLE YES
        #LINK_FLAGS "/ENTRY:mainCRTStartup"
        #)
else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
endif(MSVC)

#link lib
target_link_libraries(${PROJECT_NAME} IUP)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

