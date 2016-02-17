file(GLOB SRCS *.cpp ../src/*.cpp)

add_executable(${APP_NAME}
    ${SRCS}
)

# Specify here the libraries this program depends on
link_directories(/usr/local/lib)

target_link_libraries(${APP_NAME}
	proxygenhttpserver 
	folly
	glog 
	gflags
	pthread
)

install(TARGETS ${APP_NAME} EXPORT ${APP_NAME} DESTINATION bin)