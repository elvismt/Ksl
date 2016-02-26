#include <Ksl/Canvas_p.h>
#include <QtGui>

KSL_BEGIN_NAMESPACE


CanvasDrawingArea::CanvasDrawingArea(int width, int height,
                                     Canvas *canvas, CanvasPrivate *canvPriv)
    : QWidget(canvas)
{
    this->canvas = canvas;
    this->canvPriv = canvPriv;
    this->defaultSize = QSize(width, height);
    this->painter = new QPainter();
    setMinimumSize(200, 200);
    resize(width, height);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);
}


QSize CanvasDrawingArea::sizeHint() const {
    return defaultSize;
}


void CanvasDrawingArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    painter->begin(this);
    painter->setPen(Qt::blue);
    QRect rect = this->rect();
    canvas->paint(painter, rect);
    painter->end();
}


void CanvasDrawingArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        canvas->leftClick(event->pos());
    else if (event->button() == Qt::RightButton)
        canvas->rightClick(event->pos());
}


Canvas::Canvas(const QString &title, int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , Ksl::Object(new CanvasPrivate(this, width, height))
{
    KSL_PUBLIC(Canvas);
    m->centralWidget = new QWidget();
    m->mainLayout = new QVBoxLayout(m->centralWidget);
    m->centralWidget->setLayout(m->mainLayout);
    m->mainLayout->addWidget(m->drawingArea);

    setWindowTitle(title);
    setCentralWidget(m->centralWidget);
}


Canvas::~Canvas() {
    KSL_PUBLIC(Canvas);
    delete m->centralWidget;
}


void Canvas::paint(QPainter *painter, const QRect &rect) {
    Q_UNUSED(painter)
    Q_UNUSED(rect)
}


void Canvas::leftClick(const QPoint &pos) {
    Q_UNUSED(pos)
}


void Canvas::rightClick(const QPoint &pos) {
    Q_UNUSED(pos)
}

KSL_END_NAMESPACE
