#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/loop.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/motor2D.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/interfaz.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/proyectil.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

