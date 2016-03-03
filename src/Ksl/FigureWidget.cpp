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
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    setMinimumSize(200, 200);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

FigureWidget::FigureWidget(QWidget *parent)
    : FigureWidget(new FigureWidgetPrivate(this), parent)
{ }

Figure* FigureWidget::figure(const QString &name) {
    KSL_PUBLIC(FigureWidget);
    for (auto &entry : m->figureList)
        if (entry.figure->name() == name)
            return entry.figure;
    return nullptr;
}

void FigureWidget::add(Figure *figure,
                       int initRow, int endRow,
                       int initCol, int endCol)
{
    KSL_PUBLIC(FigureWidget);

    FigureWidgetPrivate::FigureTableEntry newFigureEntry;
    newFigureEntry.figure = figure;
    newFigureEntry.initRow = initRow;
    newFigureEntry.endRow = endRow;
    newFigureEntry.initCol = initCol;
    newFigureEntry.endCol = endCol;
    m->figureList.append(newFigureEntry);

    if (endRow > m->lastRow) m->lastRow = endRow;
    if (endCol > m->lastCol) m->lastCol = endCol;
}

QList<Figure*> FigureWidget::figureList() const {
    KSL_PUBLIC(const FigureWidget);
    QList<Figure*> list;
    for (auto &entry : m->figureList)
        list.append(entry.figure);
    return list;
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

    const QRect widgetRect = this->rect();
    const int colWidth = widgetRect.width() / (m->lastCol + 1);
    const int rowHeight = widgetRect.height() / (m->lastRow + 1);

    m->painter.begin(this);
    for (auto &entry : m->figureList)
    {
        const int x = entry.initCol * colWidth;
        const int y = entry.initRow * rowHeight;
        const int width = (entry.endCol - entry.initCol + 1) * colWidth;
        const int height = (entry.endRow - entry.initRow + 1) * rowHeight;

        QRect entryRect(x, y, width, height);
        entry.figure->paint(entryRect, &m->painter);
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

} // namespace Ksl
