/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <Ksl/FigureWidget_p.h>

namespace Ksl {

FigureWidget::FigureWidget(Ksl::ObjectPrivate *priv, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(FigureWidget);
    m->figure = new Figure("Ksl", this);
    setMinimumSize(200, 200);
    setAutoFillBackground(false);
    setMouseTracking(true);
}

FigureWidget::FigureWidget(QWidget *parent)
    : FigureWidget(new FigureWidgetPrivate(this), parent)
{ }

Figure* FigureWidget::figure() const {
    KSL_PUBLIC(const FigureWidget);
    return m->figure;
}

QSize FigureWidget::sizeHint() const {
    KSL_PUBLIC(const FigureWidget);
    return m->sizeHint;
}

void FigureWidget::setSizeHint(const QSize &sizeHint) {
    KSL_PUBLIC(FigureWidget);
    m->sizeHint = sizeHint;
}

void FigureWidget::paintEvent(QPaintEvent *event) {
    KSL_PUBLIC(FigureWidget);
    Q_UNUSED(event)

    m->painter.begin(this);
    m->figure->paint(rect(), &m->painter);
    m->painter.end();
}

void FigureWidget::save() {
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("Chose a file name"), QDir::homePath(), tr("PNG files (*.png)"));
    if (filePath.isEmpty())
        return;
    if (!filePath.endsWith(".png", Qt::CaseInsensitive))
        filePath.append(".png");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QPixmap pixmap = m->canvasArea->grab();
#else
    QPixmap pixmap = QPixmap::grabWidget(this);
#endif
    pixmap.save(filePath);
}

} // namespace Ksl
