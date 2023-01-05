set(QT_MIN_VERSION "5.4.0")
set(KF5_MIN_VERSION "5.9.0")

include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS KIO GlobalAccel I18n)

set(effect_SRCS
    plugin.cpp
    MatchTitlebar.cpp
)

add_library(${MATCH_TITlEBAR} SHARED ${effect_SRCS})

target_link_libraries(${MATCH_TITLEBAR}
    PRIVATE
    kwineffects
)

install(
    TARGETS
        ${MATCH_TITLEBAR}
    DESTINATION
        ${MODULEPATH}/kwin/effects/plugins/
)
