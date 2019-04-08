add_executable(vector3d_test vector3d_test.cpp)
target_link_libraries(vector3d_test enhance)# boost_unit_test_framework)
add_test(NAME Vector3d COMMAND vector3d_test)
target_include_directories(vector3d_test PUBLIC ../.)
target_include_directories(vector3d_test PUBLIC ../lib/boost/include/)



add_executable(box3d_test box3d_test.cpp)
target_link_libraries(box3d_test enhance)# boost_unit_test_framework)
add_test(NAME Box3d COMMAND box3d_test)
target_include_directories(box3d_test PUBLIC ../.)
target_include_directories(box3d_test PUBLIC ../lib/boost/include/)
