#pragma once

#include <kwineffects.h>

namespace KWin {

class MatchTitlebar : public Effect {

  Q_OBJECT

public:
  MatchTitlebar();

  static bool supported();

private:
  void windowActivated(EffectWindow *w);
};

} // namespace KWin
