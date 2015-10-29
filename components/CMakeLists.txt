project (Components)

add_components(Memory Memory)
add_components(Opcode Opcode)
add_components(Utils Utils)
add_components(BaseDevice BaseDevice)
add_components(BitFont BitFont)

add_components(Serialize SerializablePOD Serializable)

add_library(components STATIC ${COMPONENTS_FILES} ${HEADER_FILES} ${SOURCE_FILES})

set(COMPONENTS_FILES ${COMPONENTS_FILES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
