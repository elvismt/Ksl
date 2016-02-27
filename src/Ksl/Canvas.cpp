#include <Ksl/Canvas_p.h>
#include <QtGui>

KSL_BEGIN_NAMESPACE


CanvasDrawingArea::CanvasDrawingArea(int width, int height,
                                     Canvas *canvas, CanvasPrivate *canvPriv)
{
    this->canvas = canvas;
    this->canvPriv = canvPriv;
    this->defaultSize = QSize(width, height);
    this->painter = new QPainter();
    // Ensure all of the canvas is visible
    setMinimumSize(width+1, height+1);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);
    setMouseTracking(true);
}


QSize CanvasDrawingArea::sizeHint() const {
    return defaultSize;
}

QSize CanvasDrawingArea::minimumSizeHint() const {
    return defaultSize;
}


void CanvasDrawingArea::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    painter->begin(this);
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


void CanvasDrawingArea::mouseMoveEvent(QMouseEvent *event) {
    canvas->mouseMove(event->pos());
}


void CanvasDrawingArea::mouseReleaseEvent(QMouseEvent *event) {
    canvas->mouseRelease(event->pos());
}


void CanvasDrawingArea::_animate() {
    canvPriv->timer->start(canvPriv->timeStep);
}


void CanvasDrawingArea::_stopAnimation() {
    canvPriv->timer->stop();
}


Canvas::Canvas(const QString &title,
               int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , Ksl::Object(new CanvasPrivate(this, width, height))
{
    KSL_PUBLIC(Canvas);
    m->init(title);
}


Canvas::Canvas(ObjectPrivate *priv, const QString &title,
               int width, int height, QWidget *parent)
    : QMainWindow(parent)
    , Ksl::Object(priv)
{
    KSL_PUBLIC(Canvas);
    Q_UNUSED(width)
    Q_UNUSED(height)
    m->init(title);
}


void CanvasPrivate::init(const QString &title) {
    KSL_PRIVATE(Canvas);
    // The drawing area is the main widget
    drawingArea->setParent(m);
    centralWidget = new QWidget();
    mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(drawingArea);
    m->setCentralWidget(centralWidget);
    m->setWindowTitle(title);
    m->setWindowIcon(
        QIcon(":/icons/icons/preferences-kcalc-constants.png"));

    timeStep = 40;
    timer = new QTimer(m);
    QObject::connect(timer, &QTimer::timeout,
        m, &Canvas::animate);

    // Create tool bar
    toolBar = m->addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->addAction(
        QIcon(":/icons/icons/dialog-close.png"),
        QObject::tr("Quit"), m, SLOT(close()));
    toolBar->addSeparator();
    toolBar->addAction(
        QIcon(":/icons/icons/document-save.png"),
        QObject::tr("Save PNG"), m, SLOT(savePng()));
    toolBar->addSeparator();
    toolBar->addAction(
        QIcon(":/icons/icons/edit-undo.png"),
        QObject::tr("Reset"), m, SLOT(reset()));
    toolBar->addAction(
        QIcon(":/icons/icons/media-seek-forward.png"),
        QObject::tr("Start"), m, SLOT(start()));
    toolBar->addAction(
        QIcon(":/icons/icons/media-playback-start.png"),
        QObject::tr("Animate"), drawingArea, SLOT(_animate()));
    toolBar->addAction(
        QIcon(":/icons/icons/media-playback-stop.png"),
        QObject::tr("Stop"), drawingArea, SLOT(_stopAnimation()));

    // Create status bar
    m->statusBar()->showMessage("Ready!", 3000);
}


Canvas::~Canvas() {
    KSL_PUBLIC(Canvas);
    delete m->drawingArea->painter;
}


void Canvas::updateCanvas() {
    KSL_PUBLIC(Canvas);
    m->drawingArea->repaint();
}


void Canvas::setTimeStep(int milisecs) {
    KSL_PUBLIC(Canvas);
    m->timeStep = milisecs;
}


void Canvas::savePng() {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Chose a file name"), QDir::homePath(),
        tr("PNG Files (*.png)"));

    if (fileName.size() < 1)
        return;

    if (!fileName.endsWith(".png", Qt::CaseInsensitive))
        fileName.append(".png");

    QImage image(600, 500, QImage::Format_ARGB32);
    QPainter painter(&image);
    paint(&painter, QRect(0, 0, 600, 500));
    image.save(fileName, "png");
}


void Canvas::paint(QPainter *painter, const QRect &rect) {
    Q_UNUSED(painter)
    Q_UNUSED(rect)
    // pass
}


void Canvas::leftClick(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}


void Canvas::rightClick(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void Canvas::mouseMove(const QPoint &pos) {
    statusBar()->showMessage(
        QString("( %1, %2 )").arg(pos.x()).arg(pos.y()), 3000);
}

void Canvas::mouseRelease(const QPoint &pos) {
    Q_UNUSED(pos)
    // pass
}

void Canvas::reset() {
    // pass
}

void Canvas::start() {
    // pass
}

void Canvas::animate() {
    // pass
}

void Canvas::stop() {
    // pass
}

KSL_END_NAMESPACE
