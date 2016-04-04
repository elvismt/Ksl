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
    setWindowIcon(QIcon(
        ":/icons/icons/preferences-kcalc-constants.png"));
    m->layout = new QVBoxLayout();
    setLayout(m->layout);

    // Set up tool bar
    m->toolBar = new QToolBar("toolBar", this);
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
    for (auto scale : figureArea->figure()->scaleList()) {
        delete scale;
    }
}


Figure* Chart::figure() const {
    KSL_PUBLIC(const Chart);
    return m->figureArea->figure();
}


XYScale* Chart::scale(const QString &name) {
    KSL_PUBLIC(Chart);

    auto scale = m->figureArea->figure()->scale(name);
    if (!scale) {
        scale = new XYScale(name);
        m->figureArea->figure()->add(scale);
    }
    return static_cast<XYScale*>(scale);
}


Plot* Chart::plot(const Array<1> &x, const Array<1> &y,
                  const char *style,
                  const QString &name,
                  const QString &scaleName)
{
    auto newPlot = new Plot(x, y, style, name, this);
    scale(scaleName)->add(newPlot);
    return newPlot;
}


Plot* Chart::plot(const Array<1> &y,
                  const char *style,
                  const QString &name,
                  const QString &scaleName)
{
    auto x = linspace(0.0, double(y.size()));
    auto newPlot = new Plot(x, y, style, name, this);
    scale(scaleName)->add(newPlot);
    return newPlot;
}


TextPlot* Chart::text(const QString &text, const QPointF &pos,
                      const QColor &stroke, float rotation,
                      const QString &scaleName)
{
    auto newText = new TextPlot(text, pos, QPen(stroke), rotation, this);
    scale(scaleName)->add(newText);
    return newText;
}


LinePlot* Chart::line(double a, double b,
                      const QString &style,
                      const QString &name,
                      const QString &scaleName)
{
    auto newLine = new LinePlot(a, b, style, name, this);
    scale(scaleName)->add(newLine);
    return newLine;
}


PolyPlot* Chart::poly(const Array<1> &a, double xMin, double xMax,
                      const char *style, const QString &name,
                      const QString &scaleName)
{
    auto newPoly = new PolyPlot(a, xMin, xMax, style, name, this);
    scale(scaleName)->add(newPoly);
    return newPoly;
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
