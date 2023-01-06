#include "MatchTitlebar.hpp"

namespace KWin {

KWIN_EFFECT_FACTORY_SUPPORTED(MatchTitlebar, "metadata.json",
                              return MatchTitlebar::supported();)
} // namespace KWin

#include "plugin.moc"
