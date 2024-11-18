add_definitions(-DTRANSLATION_DOMAIN="lightly_kwin_deco")

################# configuration #################
configure_file(config-lightly.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-lightly.h )

################# includes #################
include_directories(${CMAKE_SOURCE_DIR}/liblightlycommon)
include_directories(${CMAKE_BINARY_DIR}/liblightlycommon)

################# newt target #################
### plugin classes
set(lightlydecoration_SRCS
    lightlybutton.cpp
    lightlydecoration.cpp
    lightlyexceptionlist.cpp
    lightlysettingsprovider.cpp
    lightlysizegrip.cpp
)
### build library
kconfig_add_kcfg_files(lightlydecoration_SRCS lightlysettings.kcfgc)
add_library(lightlydecoration MODULE
    ${lightlydecoration_SRCS}
    ${lightlydecoration_config_SRCS}
    ${lightlydecoration_config_PART_FORMS_HEADERS})

set_target_properties(lightlydecoration PROPERTIES
    OUTPUT_NAME org.kde.lightly
)

target_link_libraries(lightlydecoration
     PUBLIC
        Qt::Core
        Qt::Gui
        Qt::DBus
        KDecoration2::KDecoration
     PRIVATE
        lightlycommon6
        KF6::CoreAddons
        KF6::ConfigWidgets
        KF6::GuiAddons
        KF6::I18n
        KF6::IconThemes
        KF6::WindowSystem
        KF6::KCMUtils
)

install(TARGETS lightlydecoration DESTINATION ${KDE_INSTALL_PLUGINDIR}/${KDECORATION_PLUGIN_DIR})
install(FILES config/lightlydecorationconfig.desktop DESTINATION  ${KDE_INSTALL_DATADIR}/kservices6)

add_subdirectory(config)
