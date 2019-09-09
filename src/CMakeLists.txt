# Very basic CMake project.
cmake_minimum_required(VERSION 2.8.4)

project(mimedecode C CXX)

set(SOURCE_FILES 
    AnyObjectParser.cpp
    Base64Parser.cpp
    Decoder.cpp
    HeaderParser.cpp
    MultipartParser.cpp
    ObjectParser.cpp
    ParserFactory.cpp
    QuotedPrintableParser.cpp
    SimpleParser.cpp
    StringDecoder.cpp
)

set(HEADERS
    AnyObjectParser.h
    Base64Parser.h
    ClientInterface.h
    Decoder.h
    HeaderField.h
    HeaderParser.h
    MultipartParser.h
    Object.h
    ObjectBodyParser.h
    ObjectParser.h
    Parser.h
    ParserFactory.h
    QuotedPrintableParser.h
    SimpleParser.h
    StringDecoder.h
    exceptions.h
)

set(TARGET "mimedecode")

add_library(${TARGET} STATIC ${SOURCE_FILES})

install( TARGETS ${TARGET} DESTINATION lib EXPORT ${TARGET}-config)
install(FILES   ${HEADERS} DESTINATION include)
