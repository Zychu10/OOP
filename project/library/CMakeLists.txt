cmake_minimum_required(VERSION 3.4)
project(Library)
set(Boost_USE_MULTITHREADED ON) #uzywa więcej rdzeni

set(SOURCE_FILES
        src/model/Client.cpp include/model/Client.h
        src/model/Room.cpp include/model/Room.h
        src/model/Rent.cpp include/model/Rent.h
        include/model/typedefs.h
        src/model/Repository.cpp include/model/Repository.h
        src/managers/RoomManager.cpp include/managers/RoomManager.h
        src/model/ClientType.cpp include/model/ClientType.h
        src/managers/ClientManager.cpp include/managers/ClientManager.h
        src/managers/RentManager.cpp include/managers/RentManager.h
        include/exceptions/ParameterException.h
        include/exceptions/LogicException.h
        src/menu/TerminalMenu.cpp include/menu/TerminalMenu.h)

#utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing()
find_package(Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)
set(SOURCE_TEST_FILES
        test/master.cpp
        test/ClientTest.cpp
        test/RoomTest.cpp
        test/RentTest.cpp
        test/RepositoryTest.cpp
        test/RoomManagerTest.cpp
        test/ClientManagerTest.cpp
        test/RentManagerTest.cpp
        test/ClientTypeTest.cpp
        )

add_executable(LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries(LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})