find_package(KF5 REQUIRED COMPONENTS
    Config
    CoreAddons
    WindowSystem
)

find_package (KDecoration2 REQUIRED)

set(effect_SRCS
    plugin.cpp
    MatchTitlebar.cpp
)

add_library(kwin_effect_match_titlebar SHARED ${effect_SRCS})

target_link_libraries(kwin_effect_match_titlebar
    PRIVATE

    kwineffects
    kwinglutils

    KF5::ConfigCore
    KF5::CoreAddons
    KF5::WindowSystem

    KDecoration2::KDecoration

    epoxy
)

install(
    TARGETS kwin_effect_match_titlebar
    DESTINATION ${PLUGIN_INSTALL_DIR}/kwin/effects/plugins/
)
