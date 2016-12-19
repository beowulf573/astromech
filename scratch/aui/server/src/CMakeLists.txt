link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

add_executable(aui_server # name of the executable on Windows will be example.exe 
    main.cc 
    myarea.cc 
    myarea.h )

target_link_libraries(aui_server
    ${GTKMM_LIBRARIES}  )
