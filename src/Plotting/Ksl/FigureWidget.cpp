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
#include <Ksl/FigureScale.h>
#include <Ksl/Math.h>

namespace Ksl {

FigureWidget::FigureWidget(Ksl::ObjectPrivate *priv, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(FigureWidget);
    m->mouseRectPen.setStyle(Qt::DashLine);
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

    if (m->mousePressed) {
        m->painter.setPen(m->mouseRectPen);
        m->painter.setBrush(Qt::NoBrush);
        m->painter.setRenderHint(QPainter::Antialiasing, false);
        m->painter.drawRect(
            m->mouseMoveP1.x(), m->mouseMoveP1.y(),
            m->mouseMoveP2.x() - m->mouseMoveP1.x(),
            m->mouseMoveP2.y() - m->mouseMoveP1.y());
    }
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


void FigureWidget::mousePressEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureWidget);
    if (!m->figure->scaleList().isEmpty()) {
        if (event->button() == Qt::LeftButton) {
            m->mouseMoveP1 = event->pos();
            m->mouseMoveP2 = event->pos();
            m->mousePressed = true;
        }
    }
}


void FigureWidget::mouseMoveEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureWidget);
    if (m->mousePressed) {
        m->mouseMoveP2 = event->pos();
        update();
    }
}


void FigureWidget::mouseReleaseEvent(QMouseEvent *event) {
    KSL_PUBLIC(FigureWidget);

    if (m->mousePressed) {
        m->mousePressed = false;
        m->mouseMoveP2 = event->pos();
        for (auto scale : m->figure->scaleList()) {
            // Only change viewport if the drag was at least
            // 4 points wide
            QPoint move = m->mouseMoveP2 - m->mouseMoveP1;
            if ((Math::pow2(move.x()) + Math::pow2(move.y())) < 16)
                continue;

            // Get drag ends in data space
            QPointF p1 = scale->unmap(m->mouseMoveP1);
            QPointF p2 = scale->unmap(m->mouseMoveP2);

            if (p1.x() > p2.x()) {
                double tmp = p1.x();
                p1.setX(p2.x());
                p2.setX(tmp);
            }
            if (p1.y() > p2.y()) {
                double tmp = p1.y();
                p1.setY(p2.y());
                p2.setY(tmp);
            }
            scale->trackRect(
                QRectF(p1.x(), p1.y(),
                       p2.x() - p1.x(),
                       p2.y() - p1.y()));
        }
        update();
    }
}


void FigureWidget::mouseDoubleClickEvent(QMouseEvent * event) {
    KSL_PUBLIC(FigureWidget);
    Q_UNUSED(event)
    for (auto scale : m->figure->scaleList())
        scale->rescale();
    update();
}

} // namespace Ksl
