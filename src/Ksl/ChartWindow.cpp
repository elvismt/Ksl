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

#include <Ksl/ChartWindow_p.h>
#include <QIcon>
#include <QFileDialog>
#include <QMouseEvent>

namespace Ksl {

ChartWindow::ChartWindow(Ksl::ObjectPrivate *priv, const QString &title,
                         int width, int height, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(ChartWindow);

    // Set out layout
    setWindowTitle(title);
    setWindowIcon(QIcon(":/icons/icons/preferences-kcalc-constants.png"));
    m->layout = new QVBoxLayout();
    setLayout(m->layout);

    // Set up tool bar
    m->toolBar = new QToolBar("toolBar", this);
    m->toolBar->setMovable(false);
    m->layout->addWidget(m->toolBar);

    // Populate tool bar
    m->toolBar->addAction(
        QIcon(":/icons/icons/dialog-close.png"),
        tr("Close"), this, SLOT(close()));
    m->toolBar->addSeparator();
    m->toolBar->addAction(
        QIcon(":/icons/icons/document-save.png"),
        tr("Export Image"), this, SLOT(save()));
    m->toolBar->addSeparator();

    // chartArea
    m->chartArea = new _ChartArea(QSize(width, height), this);
    m->layout->addWidget(m->chartArea, 1);

    // Set up figure
    m->chartArea->figure = new Figure(title, this);

    // Set up status bar
    m->statusBar = new QStatusBar(this);
    m->layout->addWidget(m->statusBar);
    m->statusBar->showMessage("Ready!", 4000);
}

ChartWindow::ChartWindow(const QString &title,
                         int width, int height, QWidget *parent)
    : ChartWindow(new ChartWindowPrivate(this), title, width, height, parent)
{ }

ChartWindowPrivate::~ChartWindowPrivate() {
    // Clean all up
    for (auto scale : xyScales)
        delete scale;
    for (auto plot : xyPlots)
        delete plot;
}

Figure* ChartWindow::figure() const {
    KSL_PUBLIC(ChartWindow);
    return m->chartArea->figure;
}

void ChartWindow::save() {
    KSL_PUBLIC(ChartWindow);
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("Chose a file name"), QDir::homePath(), tr("PNG files (*.png)"));
    if (filePath.isEmpty())
        return;
    if (!filePath.endsWith(".png", Qt::CaseInsensitive))
        filePath.append(".png");
    m->chartArea->figure->save(
        filePath, m->chartArea->size());
}

XYScale* ChartWindow::xyScale(const QString &name) {
    KSL_PUBLIC(ChartWindow);

    if (m->xyScales.contains(name))
        return m->xyScales[name];

    auto newScale = new XYScale(name);
    m->xyScales[name] = newScale;
    m->chartArea->figure->add(newScale);
    return newScale;
}

Ksl::XYPlot* ChartWindow::xyPlot(const QString &name,
                                 const Array<1> &x, const Array<1> &y,
                                 XYPlot::Symbol symbol,
                                 const QColor &stroke,
                                 const QColor &fill,
                                 const QString &scaleName)
{
    KSL_PUBLIC(ChartWindow);
    if (!m->xyPlots.contains(name)) {
        auto plot = new XYPlot(x, y, symbol, name, stroke, fill);
        m->xyPlots[name] = plot;
        xyScale(scaleName)->add(plot);
        return plot;
    }
    return nullptr;
}

XYPlot* ChartWindow::xyPlot(const QString &name) const {
    KSL_PUBLIC(ChartWindow);
    if (m->xyPlots.contains(name))
        return m->xyPlots[name];
    return nullptr;
}

void ChartWindow::showStatusMessage(const QString &message, int milisecs) {
    KSL_PUBLIC(ChartWindow);
    m->statusBar->showMessage(message, milisecs);
}

QHash<QString,XYScale*> ChartWindow::xyScalesHash() const {
    KSL_PUBLIC(ChartWindow);
    return m->xyScales;
}

QHash<QString,XYPlot*> ChartWindow::xyPlotsHash() const {
    KSL_PUBLIC(ChartWindow);
    return m->xyPlots;
}

_ChartArea::_ChartArea(const QSize defaultSize, QWidget *parent)
    : QWidget(parent)
{
    this->defaultSize = defaultSize;
    this->window = static_cast<ChartWindow*>(parent);
    resize(defaultSize);
    setMinimumSize(200, 200);
    setAutoFillBackground(false);
    setMouseTracking(true);
}

QSize _ChartArea::sizeHint() const {
    return defaultSize;
}

void _ChartArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    painter.begin(this);
    figure->paint(rect(), &painter);
    painter.end();
}

void _ChartArea::mouseMoveEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    auto scale = window->xyScale();

    // Show position only if there is only one scale
    // to avoid ambiguity
    if (scale && window->xyScalesHash().size() == 1) {
        QPointF p = scale->unmap(event->pos());
        window->showStatusMessage(QString("X = %1, Y = %2")
            .arg(p.x(), 0, 'f', 2).arg(p.y(), 0, 'f', 2), 3000);
    }
}

} // namespace Ksl
