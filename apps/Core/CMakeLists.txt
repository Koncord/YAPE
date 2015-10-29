set(SOURCE_FILES main.cpp BaseInstruction.cpp ControlUnit.cpp Environment.cpp LexicalInterpreter.cpp RegisterController.cpp
        BaseInstructions.cpp IOSystem.cpp)
set(HEADER_FILES BaseInstruction.hpp ControlUnit.hpp Environment.hpp LexicalInterpreter.hpp RegisterController.hpp
        BaseInstructions.hpp IOSystem.hpp ${Boost_INCLUDE_DIRS})

add_instructions(Instructions OpADD OpJMP OpMOV OpSUB OpJZ OpHLT OpJNZ OpXCHG OpJC OpJNC OpJS OpJNS OpJO OpJNO OpJA
        OpJNA OpINC OpDEC OpCMP OpAND OpTEST OpOR OpNOT OpXOR OpCLC OpCLD OpCLI OpCMC OpNEG OpSHL OpSTC OpSTD OpSTI
        OpMUL OpDIV OpCALL OpPUSH OpPOP OpPUSHA OpPOPA OpRET OpLOOP OpJG OpJGE OpJL OpJLE OpJP OpJNP OpJCXZ OpLOOPNZ
        OpLOOPZ OpADC OpSBB OpIDIV OpCWD OpIMUL1 OpIMUL2 OpIMUL3 OpINT OpINT3 OpIRET)

add_instructions(pluginsystem Plugin Helper Functions)

if(OPTION_GNU_LTO)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
    message(STATUS "LTO enabled.")
endif(OPTION_GNU_LTO)

add_executable(yape ${SOURCE_FILES} ${HEADER_FILES} ${INSTRUCTIONS_FILES})

if (UNIX)
    target_link_libraries(yape dl)
endif(UNIX)

target_link_libraries(yape ${Boost_LIBRARIES} components)
