set(QT_MIN_VERSION "5.4.0")
set(KF5_MIN_VERSION "5.9.0")

include(KDEInstallDirs)
include(KDECMakeSettings)

find_package (KF5 REQUIRED COMPONENTS
    Config
    CoreAddons
    WindowSystem
)

set(effect_SRCS
    plugin.cpp
    MatchTitlebar.cpp
)

add_library(kwin_effect_match_titlebar SHARED ${effect_SRCS})

target_link_libraries(kwin_effect_match_titlebar
    PRIVATE
    kwineffects
    # kwinglutils
    KF5::ConfigCore
    KF5::CoreAddons
    KF5::WindowSystem
)

install(
    TARGETS
        kwin_effect_match_titlebar
    DESTINATION
        ${MODULEPATH}/kwin/effects/plugins/
)
