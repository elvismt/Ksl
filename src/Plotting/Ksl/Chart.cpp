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

#include <Ksl/Chart_p.h>
#include <QIcon>
#include <QAction>
#include <QFileDialog>
#include <QMouseEvent>

namespace Ksl {

Chart::Chart(Ksl::ObjectPrivate *priv, const QString &title,
                         int width, int height, QWidget *parent)
    : QWidget(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(Chart);

    // Set out layout
    setWindowTitle(title);
    setMouseTracking(true);
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
    m->translationAction = m->toolBar->addAction(
        QIcon(":/icons/icons/move-translate.png"),
        tr("Move viewport"));
    m->translationAction->setCheckable(true);
    connect(m->translationAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleTranslation(bool)));
    m->zoomingAction = m->toolBar->addAction(
            QIcon(":/icons/icons/zoom-select.png"),
            tr("Move viewport"));
    m->zoomingAction->setCheckable(true);
    connect(m->zoomingAction, SIGNAL(toggled(bool)),
            this, SLOT(toggleZooming(bool)));

    // chartArea
    m->figureArea = new FigureWidget(this);
    m->figureArea->setSizeHint(QSize(width, height));
    m->figureArea->setMouseOperation(FigureWidget::NoMouseOperation);
    m->layout->addWidget(m->figureArea, 1);
}


Chart::Chart(const QString &title,
                         int width, int height, QWidget *parent)
    : Chart(new ChartPrivate(this), title, width, height, parent)
{ }


ChartPrivate::~ChartPrivate() {
    // Clean up
    for (auto scale : xyScales)
        delete scale;
    for (auto plot : xyPlots)
        delete plot;
}


Figure* Chart::figure() const {
    KSL_PUBLIC(const Chart);
    return m->figureArea->figure();
}


XYScale* Chart::scale(const QString &name) {
    KSL_PUBLIC(Chart);
    if (m->xyScales.contains(name))
        return m->xyScales[name];

    auto newScale = new XYScale(name);
    m->xyScales[name] = newScale;
    m->figureArea->figure()->add(newScale);
    return newScale;
}


XYPlot* Chart::plot(const QString &name,
                    const Array<1> &x, const Array<1> &y,
                    const QString &style,
                    const QString &scaleName)
{
    KSL_PUBLIC(Chart);
    if (m->xyPlots.contains(name))
        return nullptr;

    auto newPlot = new XYPlot(x, y, style, name, this);
    m->xyPlots[name] = newPlot;
    scale(scaleName)->add(newPlot);
    return newPlot;
}


XYPlot* Chart::plot(const QString &name) const {
    KSL_PUBLIC(const Chart);
    if (m->xyPlots.contains(name))
        return m->xyPlots[name];
    return nullptr;
}


TextPlot* Chart::text(const QString &text, const QPointF &pos,
                                      const QColor &stroke, float rotation,
                                      const QString &scaleName)
{
    auto item = scale(scaleName)->item(text);
    if (!item) {
        item = new TextPlot(text, pos, stroke, rotation, this);
        scale(scaleName)->add(item);
        return static_cast<TextPlot*>(item);
    }
    return nullptr;
}


LinePlot* Chart::line(const QString &name, double a, double b,
                            const QColor &stroke, const QString &scaleName)
{
    auto item = scale(scaleName)->item(name);
    if (!item) {
        item = new LinePlot(a, b, stroke, name, this);
        scale(scaleName)->add(item);
        return static_cast<LinePlot*>(item);
    }
    return nullptr;
}


PolyPlot* Chart::poly(const QString &name,
                            const Array<1> &a, double xMin, double xMax,
                            const QColor &stroke, const QString &scaleName)
{
    auto item = scale(scaleName)->item(name);
    if (!item) {
        item = new PolyPlot(a, stroke, xMin, xMax, name, this);
        scale(scaleName)->add(item);
        return static_cast<PolyPlot*>(item);
    }
    return nullptr;
}


void Chart::save() {
    KSL_PUBLIC(Chart);
    m->figureArea->save();
}


void Chart::toggleTranslation(bool activate) {
    KSL_PUBLIC(Chart);
    Q_UNUSED(activate)
    if (activate) {
        m->figureArea->setMouseOperation(
            FigureWidget::Translation);
        if (m->zoomingAction->isChecked())
            m->zoomingAction->setChecked(false);
    } else {
        if (!m->zoomingAction->isChecked())
            m->figureArea->setMouseOperation(
                FigureWidget::NoMouseOperation);
    }
}


void Chart::toggleZooming(bool activate) {
    KSL_PUBLIC(Chart);
    Q_UNUSED(activate)
    if (activate) {
        m->figureArea->setMouseOperation(
            FigureWidget::Zooming);
        if (m->translationAction->isChecked())
            m->translationAction->setChecked(false);
    } else {
        if (!m->translationAction->isChecked())
            m->figureArea->setMouseOperation(
                FigureWidget::NoMouseOperation);
    }
}

} // namespace Ksl
