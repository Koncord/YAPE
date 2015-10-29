macro (add_instructions dir)
    set (files)

    foreach (u ${ARGN})
        file (GLOB ALL "${dir}/${u}.[ch]pp")

        foreach (f ${ALL})
            list (APPEND files "${f}")
            list (APPEND INSTRUCTIONS_FILES "${f}")
        endforeach (f)

    endforeach (u)

    source_group ("${dir}" FILES ${files})
endmacro (add_instructions)

macro (add_components dir)
    set (files)

    foreach (u ${ARGN})
        file (GLOB ALL "${dir}/${u}.[ch]pp")

        foreach (f ${ALL})
            list (APPEND files "${f}")
            list (APPEND COMPONENTS_FILES "${f}")
        endforeach (f)

    endforeach (u)

    source_group ("$components\\{dir}" FILES ${files})
endmacro (add_components)

