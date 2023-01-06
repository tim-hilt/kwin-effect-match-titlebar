#include "MatchTitlebar.hpp"

#include <kwinglutils.h>
#include <syslog.h>

namespace KWin {

static void convertFromGLImage(QImage &img, int w, int h) {
  // from QtOpenGL/qgl.cpp
  // SPDX-FileCopyrightText: 2010 Nokia Corporation and /or its subsidiary(-ies)
  // see https://github.com/qt/qtbase/blob/dev/src/opengl/qgl.cpp
  if (QSysInfo::ByteOrder == QSysInfo::BigEndian) {
    // OpenGL gives RGBA; Qt wants ARGB
    uint *p = reinterpret_cast<uint *>(img.bits());
    uint *end = p + w * h;
    while (p < end) {
      uint a = *p << 24;
      *p = (*p >> 8) | a;
      p++;
    }
  } else {
    // OpenGL gives ABGR (i.e. RGBA backwards); Qt wants ARGB
    for (int y = 0; y < h; y++) {
      uint *q = reinterpret_cast<uint *>(img.scanLine(y));
      for (int x = 0; x < w; ++x) {
        const uint pixel = *q;
        *q = ((pixel << 16) & 0xff0000) | ((pixel >> 16) & 0xff) |
             (pixel & 0xff00ff00);

        q++;
      }
    }
  }
  img = img.mirrored();
}

MatchTitlebar::MatchTitlebar() {
  connect(effects, &EffectsHandler::windowActivated, this,
          &MatchTitlebar::windowActivated);
}

bool MatchTitlebar::supported() {
  return effects->isOpenGLCompositing() && GLFramebuffer::supported();
}

void MatchTitlebar::windowActivated(EffectWindow *w) {
  if (!w) {
    return;
  }

  /*
   * TODO:
   * 8. Set Palette::ActiveTitlebar from effect
   * 9. Slim down Color-query-function
   * 10. Split up into multiple atomic functions
   * 11. Ask in Matrix if improvements can be made
   */

  WindowPaintData d;
  QRectF geometry = w->clientGeometry();
  qreal devicePixelRatio = 1;
  std::unique_ptr<GLTexture> offscreenTexture;
  std::unique_ptr<GLFramebuffer> target;
  offscreenTexture.reset(new GLTexture(
      GL_RGBA8, QSizeF(geometry.size() * devicePixelRatio).toSize()));
  offscreenTexture->setFilter(GL_LINEAR);
  offscreenTexture->setWrapMode(GL_CLAMP_TO_EDGE);
  target.reset(new GLFramebuffer(offscreenTexture.get()));

  if (!target->valid()) {
    return;
  }

  d.setXTranslation(-geometry.x());
  d.setYTranslation(-geometry.y());

  // render window into offscreen texture
  int mask = PAINT_WINDOW_TRANSFORMED | PAINT_WINDOW_TRANSLUCENT;
  QImage img;
  GLFramebuffer::pushFramebuffer(target.get());
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);

  QMatrix4x4 projection;
  projection.ortho(QRect(0, 0, geometry.width() * devicePixelRatio,
                         geometry.height() * devicePixelRatio));
  d.setProjectionMatrix(projection);

  effects->drawWindow(w, mask, infiniteRegion(), d);

  // copy content from framebuffer into image
  img = QImage(offscreenTexture->size(), QImage::Format_ARGB32);
  img.setDevicePixelRatio(devicePixelRatio);
  glReadnPixels(0, 0, img.width(), img.height(), GL_RGBA, GL_UNSIGNED_BYTE,
                img.sizeInBytes(), static_cast<GLvoid *>(img.bits()));
  GLFramebuffer::popFramebuffer();
  convertFromGLImage(img, img.width(), img.height());

  const QRgb *line = reinterpret_cast<const QRgb *>(img.constBits());
  std::unordered_map<QRgb, unsigned int> cols{};

  for (int x = 0; x < img.width(); ++x) {
    const QRgb &rgb = line[x];
    cols[rgb]++;
  }

  std::pair<QRgb, unsigned int> max{};

  for (auto pix : cols) {
    if (pix.second >= max.second) {
      max = pix;
    }
  }

  syslog(LOG_NOTICE, "[Match Titlebar] Prominent color: %x", max.first);
}

} // namespace KWin
