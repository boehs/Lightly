### configuration plugin
add_definitions(-DTRANSLATION_DOMAIN=\"lightly_style_config\")
set(kstyle_lightly_config_PART_SRCS lightlystyleconfig.cpp)

set(kstyle_lightly_config_PART_SRCS ${kstyle_lightly_config_PART_SRCS} lightlystyleconfigmodule.cpp)

kconfig_add_kcfg_files(kstyle_lightly_config_PART_SRCS ../lightlystyleconfigdata.kcfgc)
set(kstyle_lightly_config_PART_FORMS ui/lightlystyleconfig.ui)
ki18n_wrap_ui(kstyle_lightly_config_PART_FORMS_HEADERS ${kstyle_lightly_config_PART_FORMS})

kcoreaddons_add_plugin(lightlystyleconfig SOURCES
    ${kstyle_lightly_config_PART_SRCS}
    ${kstyle_lightly_config_PART_FORMS_HEADERS}
    INSTALL_NAMESPACE "kstyle_config"
)

target_link_libraries(lightlystyleconfig Qt6::Core Qt6::Gui Qt6::Widgets Qt6::DBus)
target_link_libraries(lightlystyleconfig KF6::CoreAddons KF6::ConfigCore KF6::ConfigWidgets KF6::I18n)
if(QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(lightlystyleconfig KF6::KCMUtils)
endif()
kcmutils_generate_desktop_file(lightlystyleconfig)

set(lightly_settings_SOURCES main.cpp)
add_executable(lightly-settings ${lightly_settings_SOURCES} )
target_link_libraries(lightly-settings Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(lightly-settings KF6::I18n KF6::KCMUtils KF6::CoreAddons)

set_target_properties(lightly-settings PROPERTIES OUTPUT_NAME lightly-settings${QT_MAJOR_VERSION})

install(TARGETS lightly-settings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

# icon
ecm_install_icons(ICONS sc-apps-lightly-settings.svgz
    DESTINATION ${KDE_INSTALL_ICONDIR}
    THEME hicolor )


