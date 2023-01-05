#include "MatchTitlebar.hpp"

namespace KWin {

KWIN_EFFECT_FACTORY_SUPPORTED(KWin::MatchTitlebar, "metadata.json",
                              return KWin::MatchTitlebar::supported();)
} // namespace KWin

#include "plugin.moc"
