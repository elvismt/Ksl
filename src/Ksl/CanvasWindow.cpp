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

KSL_BEGIN_NAMESPACE

CanvasWindow::CanvasWindow(const QString &title,
                           int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , Ksl::Object(new CanvasWindowPrivate(this))
{
    KSL_PUBLIC(CanvasWindow);

    // Set up central widget
    setWindowTitle(title);
    m->centralWidget = new QWidget();
    m->mainVLayout = new QVBoxLayout();
    m->centralWidget->setLayout(m->mainVLayout);
    setCentralWidget(m->centralWidget);

    // Set up drawing area
    m->drawingArea = new CanvasWindowDrawingArea(this);
    m->drawingArea->canvasWindow = this;
    m->mainVLayout->addWidget(m->drawingArea);
    m->drawingArea->setMinimumSize(width, height);
    m->drawingArea->timer = new QTimer(this);
    m->drawingArea->timeStep = 40;
    connect(m->drawingArea->timer, &QTimer::timeout,
            this, &CanvasWindow::animate);

    // Set up tool bar
    m->toolBar = addToolBar("mainToolBar");
    m->toolBar->setMovable(false);
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
        tr("Animate"), m->drawingArea, SLOT(startAnimation()));
    m->toolBar->addAction(
        QIcon(":/icons/icons/media-playback-stop.png"),
        tr("Stop"), m->drawingArea, SLOT(stopAnimation()));

    // Set up status bar
    statusBar()->showMessage(tr("Ready!"), 5000);
}


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

void CanvasWindow::mouseRelease(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void CanvasWindow::mouseMove(const QPoint &pos) {
    Q_UNUSED(pos)
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

void CanvasWindow::reset() {
    // pass
}

void CanvasWindow::repaintCanvas() {
    KSL_PUBLIC(CanvasWindow);
    m->drawingArea->repaint();
}

void CanvasWindow::setTimeStep(int milisecs) {
    KSL_PUBLIC(CanvasWindow);
    m->drawingArea->timeStep = milisecs;
}

void CanvasWindow::save() {
    KSL_PUBLIC(CanvasWindow);
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("Chose a file name"), QDir::homePath(), tr("PNG files (*.png)"));
    if (filePath.isEmpty())
        return;
    if (!filePath.endsWith(".png", Qt::CaseInsensitive))
        filePath.append(".png");
    QPixmap pixmap = m->drawingArea->grab();
    pixmap.save(filePath, "png");
}


/******************/


CanvasWindowDrawingArea::CanvasWindowDrawingArea(QWidget *parent)
    : QWidget(parent)
    , fillBack(true)
    , backBrush(Qt::white)
{
    setAutoFillBackground(false);
    setMouseTracking(true);
}

void CanvasWindowDrawingArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QRect rect = this->rect();
    painter.begin(this);
    if (fillBack)
        painter.fillRect(rect, backBrush);
    canvasWindow->paint(rect, &painter);
    painter.end();
}

void CanvasWindowDrawingArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        canvasWindow->leftClick(event->pos());
    else if (event->button() == Qt::RightButton)
        canvasWindow->rightClick(event->pos());
}

void CanvasWindowDrawingArea::mouseReleaseEvent(QMouseEvent *event) {
    canvasWindow->mouseRelease(event->pos());
}

void CanvasWindowDrawingArea::mouseMoveEvent(QMouseEvent *event) {
    canvasWindow->mouseMove(event->pos());
}

void CanvasWindowDrawingArea::startAnimation() {
    timer->start(timeStep);
}

void CanvasWindowDrawingArea::stopAnimation() {
    timer->stop();
}

KSL_END_NAMESPACE
