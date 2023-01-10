#pragma once

// KDE
#include <kwineffects.h>

// Qt
#include <QObject>

namespace KWin {

class MatchTitlebar : public Effect {

  Q_OBJECT

public:
  MatchTitlebar();

  static bool supported();

private Q_SLOTS:
  void windowActivated(EffectWindow *w);
};

} // namespace KWin
