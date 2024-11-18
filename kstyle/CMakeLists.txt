################# includes #################
include_directories(
  animations
  debug
)

include_directories(${CMAKE_SOURCE_DIR}/liblightlycommon)
include_directories(${CMAKE_BINARY_DIR}/liblightlycommon)

################# configuration #################
configure_file(config-lightly.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-lightly.h )

########### next target ###############
set(lightly_PART_SRCS
    animations/lightlyanimation.cpp
    animations/lightlyanimations.cpp
    animations/lightlyanimationdata.cpp
    animations/lightlybaseengine.cpp
    animations/lightlybusyindicatordata.cpp
    animations/lightlybusyindicatorengine.cpp
    animations/lightlydialdata.cpp
    animations/lightlydialengine.cpp
    animations/lightlyenabledata.cpp
    animations/lightlygenericdata.cpp
    animations/lightlyheaderviewdata.cpp
    animations/lightlyheaderviewengine.cpp
    animations/lightlyscrollbardata.cpp
    animations/lightlyscrollbarengine.cpp
    animations/lightlyspinboxengine.cpp
    animations/lightlyspinboxdata.cpp
    animations/lightlystackedwidgetdata.cpp
    animations/lightlystackedwidgetengine.cpp
    animations/lightlytabbarengine.cpp
    animations/lightlytabbardata.cpp
    animations/lightlytoolboxengine.cpp
    animations/lightlytransitiondata.cpp
    animations/lightlytransitionwidget.cpp
    animations/lightlywidgetstateengine.cpp
    animations/lightlywidgetstatedata.cpp
    debug/lightlywidgetexplorer.cpp
    lightlyaddeventfilter.cpp
    lightlyblurhelper.cpp
    lightlyframeshadow.cpp
    lightlyhelper.cpp
    lightlymdiwindowshadow.cpp
    lightlymnemonics.cpp
    lightlypropertynames.cpp
    lightlyshadowhelper.cpp
    lightlysplitterproxy.cpp
    lightlystyle.cpp
    lightlystyleplugin.cpp
    lightlytileset.cpp
    lightlywindowmanager.cpp
)

kconfig_add_kcfg_files(lightly_PART_SRCS ../kdecoration/lightlysettings.kcfgc)
kconfig_add_kcfg_files(lightly_PART_SRCS lightlystyleconfigdata.kcfgc)

add_library(lightly${QT_MAJOR_VERSION} MODULE ${lightly_PART_SRCS})

target_link_libraries(lightly${QT_MAJOR_VERSION}
    Qt${QT_MAJOR_VERSION}::Core
    Qt${QT_MAJOR_VERSION}::Gui
    Qt${QT_MAJOR_VERSION}::Widgets
    Qt${QT_MAJOR_VERSION}::DBus
)

if( LIGHTLY_HAVE_QTQUICK )
    target_link_libraries(lightly${QT_MAJOR_VERSION}
        Qt${QT_MAJOR_VERSION}::Quick
        KF${QT_MAJOR_VERSION}::CoreAddons
    )
endif()

target_link_libraries(lightly${QT_MAJOR_VERSION}
    KF${QT_MAJOR_VERSION}::CoreAddons
    KF${QT_MAJOR_VERSION}::ConfigCore
    KF${QT_MAJOR_VERSION}::ConfigGui
    KF${QT_MAJOR_VERSION}::GuiAddons
    KF${QT_MAJOR_VERSION}::IconThemes
    KF${QT_MAJOR_VERSION}::WindowSystem
)

if(QT_MAJOR_VERSION STREQUAL "5")
    target_link_libraries(lightly5 KF5::ConfigWidgets)
    if (LIGHTLY_HAVE_QTQUICK)
        target_link_libraries(lightly5 KF5::Kirigami2)
    endif()
else()
    target_link_libraries(lightly6 KF6::ColorScheme)
    if (LIGHTLY_HAVE_QTQUICK)
        target_link_libraries(lightly6 KF6::KirigamiPlatform)
    endif()
endif()


target_link_libraries(lightly${QT_MAJOR_VERSION} lightlycommon${QT_MAJOR_VERSION})

if(KF${QT_MAJOR_VERSION}FrameworkIntegration_FOUND)
    target_link_libraries(lightly${QT_MAJOR_VERSION}  KF${QT_MAJOR_VERSION}::Style)
endif()


if (WIN32)
    # As stated in https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants M_PI only gets defined
    # when if _USE_MATH_DEFINES is defined
    target_compile_definitions(lightly PRIVATE _USE_MATH_DEFINES _BSD_SOURCE)
endif()


########### install files ###############
install(TARGETS lightly${QT_MAJOR_VERSION} DESTINATION ${KDE_INSTALL_QTPLUGINDIR}/styles/)
install(FILES lightly.themerc  DESTINATION  ${KDE_INSTALL_DATADIR}/kstyle/themes)

########### subdirectories ###############

if (QT_MAJOR_VERSION EQUAL "6" AND TARGET "KF6::KCMUtils")
    add_subdirectory(config)
endif()
