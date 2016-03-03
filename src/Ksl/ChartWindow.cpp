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
    m->figureArea = new FigureWidget(this);
    m->figureArea->setSizeHint(QSize(width, height));
    m->layout->addWidget(m->figureArea, 1);

    // Set up status bar
    m->statusBar = new QStatusBar(this);
    m->layout->addWidget(m->statusBar);
    m->statusBar->showMessage("Ready!", 4000);
}


ChartWindow::ChartWindow(const QString &title,
                         int width, int height, QWidget *parent)
    : ChartWindow(new ChartWindowPrivate(this), title, width, height, parent)
{ }


Figure* ChartWindow::addFigure(const QString &name,
                               int initRow, int endRow,
                               int initCol, int endCol)
{
    KSL_PUBLIC(ChartWindow);

    Figure *figure = new Figure(name,this);
    m->figures.append(figure);

    // Automatically position up to
    // 6 figures
    if (initRow == -1) {
        if (m->figures.size() == 1)
            m->figureArea->add(
                figure, 0, 0, 0, 0);
        if (m->figures.size() == 2)
            m->figureArea->add(
                figure, 1, 1, 0, 0);
        if (m->figures.size() == 3)
            m->figureArea->add(
                figure, 0, 0, 1, 1);
        if (m->figures.size() == 4)
            m->figureArea->add(
                figure, 1, 1, 1, 1);
        if (m->figures.size() == 5)
            m->figureArea->add(
                figure, 2, 2, 0, 0);
        if (m->figures.size() == 6)
            m->figureArea->add(
                figure, 2, 2, 1, 1);
    }
    else {
        m->figureArea->add(
            figure, initRow, endRow,
            initCol, endCol);
    }
    return figure;
}


Figure* ChartWindow::figure(const QString &name) {
    KSL_PUBLIC(const ChartWindow);
    for (auto fig : m->figures)
        if (fig->name() == name)
            return fig;
    return addFigure(name);
}


Figure* ChartWindow::figure(int index) const {
    KSL_PUBLIC(const ChartWindow);
    return m->figures[index];
}


QList<Figure*> ChartWindow::figureList() const {
    KSL_PUBLIC(const ChartWindow);
    return m->figures;
}


void ChartWindow::save() {
    KSL_PUBLIC(ChartWindow);
    m->figureArea->save();
}


void ChartWindow::showStatusMessage(const QString &message, int milisecs) {
    KSL_PUBLIC(ChartWindow);
    m->statusBar->showMessage(message, milisecs);
}

} // namespace Ksl
