#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/statemanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/initcredits_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mainmenu_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pausemenu_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gameover_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shop_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/options_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/map_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/control_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/inventario_state.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/credits_state.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)