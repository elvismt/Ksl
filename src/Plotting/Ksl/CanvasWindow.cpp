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

#include <Ksl/CanvasWindow_p.h>
#include <QIcon>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>

namespace Ksl {

CanvasWindow::CanvasWindow(Ksl::ObjectPrivate *priv, const QString &title,
                           int width, int height, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(CanvasWindow);

    // Set out layout
    setWindowTitle(title);
    setWindowIcon(QIcon(":/icons/icons/preferences-kcalc-constants.png"));
    m->layout = new QVBoxLayout();
    setLayout(m->layout);

    // Set up tool bar
    m->toolBar = new QToolBar("toolBar", this);
    m->toolBar->setMovable(false);
    m->layout->addWidget(m->toolBar);

    // Set up canvas area
    m->canvasArea = new _CanvasArea(QSize(width, height), this);
    m->layout->addWidget(m->canvasArea);

    // Populate tool bar
    m->toolBar->addAction(
        QIcon(":/icons/icons/dialog-close.png"),
        tr("Close"), this, SLOT(close()));
    m->toolBar->addSeparator();
    m->toolBar->addAction(
        QIcon(":/icons/icons/document-save.png"),
        tr("Export Image"), this, SLOT(save()));
    m->toolBar->addSeparator();
    m->toolBar->addAction(
        QIcon(":/icons/icons/edit-undo.png"),
        tr("Reset"), this, SLOT(reset()));
    m->toolBar->addAction(
        QIcon(":/icons/icons/media-seek-forward.png"),
        tr("Start"), this, SLOT(start()));
    m->toolBar->addAction(
        QIcon(":/icons/icons/media-playback-start.png"),
        tr("Start"), m->canvasArea, SLOT(startAnimation()));
    m->toolBar->addAction(
        QIcon(":/icons/icons/media-playback-stop.png"),
        tr("Stop"), m->canvasArea, SLOT(stopAnimation()));
}

CanvasWindow::CanvasWindow(const QString &title,
                         int width, int height, QWidget *parent)
    : CanvasWindow(new CanvasWindowPrivate(this), title, width, height, parent)
{ }

void CanvasWindow::paint(const QRect &rect, QPainter *painter) {
    Q_UNUSED(rect)
    Q_UNUSED(painter)
    // pass
}

void CanvasWindow::leftClick(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void CanvasWindow::rightClick(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void CanvasWindow::clickRelease(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void CanvasWindow::pointerMove(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void CanvasWindow::showToolBar(bool showBar) {
    KSL_PUBLIC(CanvasWindow);
    m->toolBar->setVisible(showBar);
    update();
}

void CanvasWindow::reset() {
    // pass
}

void CanvasWindow::start() {
    // pass
}

void CanvasWindow::animate() {
    // pass
}

void CanvasWindow::stop() {
    // pass
}

void CanvasWindow::save() {
    KSL_PUBLIC(CanvasWindow);
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("Chose a file name"), QDir::homePath(), tr("PNG files (*.png)"));
    if (filePath.isEmpty())
        return;
    if (!filePath.endsWith(".png", Qt::CaseInsensitive))
        filePath.append(".png");
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QPixmap pixmap = m->canvasArea->grab();
#else
    QPixmap pixmap = QPixmap::grabWidget(m->canvasArea);
#endif
    pixmap.save(filePath);
}

void CanvasWindow::repaintCanvas() {
    KSL_PUBLIC(CanvasWindow);
    m->canvasArea->repaint();
}

QRect CanvasWindow::canvasRect() {
    KSL_PUBLIC(CanvasWindow);
    return m->canvasArea->rect();
}

void CanvasWindow::setTimeStep(int milisecs) {
    KSL_PUBLIC(CanvasWindow);
    m->canvasArea->timeStep = milisecs;
}

_CanvasArea::_CanvasArea(const QSize defaultSize, QWidget *parent)
    : QWidget(parent)
{
    // Init menbers and size
    this->defaultSize = defaultSize;
    this->canvasWindow = static_cast<CanvasWindow*>(parent);
    this->timeStep = 50;
    this->timer = new QTimer(parent);
    connect(timer, SIGNAL(timeout()), canvasWindow, SLOT(animate()));
    resize(defaultSize);
    setMinimumSize(200, 200);

    // White background
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);
}

QSize _CanvasArea::sizeHint() const {
    return defaultSize;
}

void _CanvasArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    painter.begin(this);
    canvasWindow->paint(rect(), &painter);
    painter.end();
}

void _CanvasArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        canvasWindow->leftClick(event->pos());
    else if (event->button() == Qt::RightButton)
        canvasWindow->rightClick(event->pos());
}

void _CanvasArea::mouseMoveEvent(QMouseEvent *event) {
    canvasWindow->pointerMove(event->pos());
}

void _CanvasArea::mouseReleaseEvent(QMouseEvent *event) {
    canvasWindow->clickRelease(event->pos());
}

void _CanvasArea::startAnimation() {
    timer->start(timeStep);
}

void _CanvasArea::stopAnimation() {
    timer->stop();
}

} // namespace Ksl
