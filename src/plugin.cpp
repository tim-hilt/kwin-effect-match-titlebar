#include "MatchTitlebar.hpp"

KWIN_EFFECT_FACTORY_SUPPORTED_ENABLED(KWin::MatchTitlebar, "metadata.json",
                                      return KWin::MatchTitlebar::supported();
                                      , return true;)

#include "plugin.moc"
