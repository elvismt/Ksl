#include <QApplication>
#include <QtGui>
#include <QDebug>

#include <Ksl/Array.h>
#include <Ksl/Graph.h>
#include <Ksl/Canvas.h>
using namespace Ksl;


class QuadTree
{
public:

    QPointF data;
    QRectF bound;
    QuadTree *children[4];


    // Constructs a new node
    QuadTree(const QRectF &ibound,
             const QPointF &idata=QPointF(-1.0,-1.0))
        : data(idata)
        , bound(ibound)
    {
        for (auto &child : children)
            child = nullptr;
    }


    // Create child nodes
    void fork() {
        QRectF rec(bound.x(), bound.y(),
            bound.width()/2.0, bound.height()/2.0);
        children[0] = new QuadTree(rec);
        children[1] = new QuadTree(rec.translated(rec.width(), 0.0));
        children[2] = new QuadTree(rec.translated(0.0, rec.height()));
        children[3] = new QuadTree(rec.translated(rec.width(), rec.height()));
    }


    // Insert data in this node or create
    // children to accomodate it
    bool insert(QPointF newData)
    {
        // This data is outside the range of this node
        if (!bound.contains(newData))
            return false;

        // This node has room for this data
        // it is an empty leaf
        if (data.x() == -1.0 && !children[0]) {
            data = newData;
            return true;
        }

        // This node has data and must pass it to children
        if (!children[0]) {
            fork();
            for (auto child : children)
                if (child->insert(data))
                    break;
            data = QPointF(-1.0, -1.0);
        }

        // Add the new data in some child
        for (auto child : children)
            if (child->insert(newData))
                return true;

        // should never be reached
        qDebug() << "Control reached end of QuadTree::insert()!";
        return false;
    }
};



class SquareTreeView: public Canvas
{
public:

    QuadTree *treeRoot;


    SquareTreeView(QuadTree *itreeRoot)
        : Canvas("Ksl QuadTree View")
        , treeRoot(itreeRoot)
    {
        setTimeStep(500);
    }


    static void paintTreeNode(QuadTree *node, QPainter *painter) {
        // Draw the bounding rect
        painter->setPen(Qt::red);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(node->bound);
        // Draw the data point position if there is data
        if (node->data.x() > -1.0) {
            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::blue);
            painter->drawEllipse(node->data, 3, 3);
            painter->setPen(Qt::green);
            painter->drawText(node->data.x()+5, node->data.y()+5,
                QString("(%1,%2)").arg(node->data.x()).arg(node->data.y()));
        }
        // If node has children, paint them
        if (node->children[0]) {
            for (auto child : node->children)
                paintTreeNode(child, painter);
        }
    }


    void paint(QPainter *painter, const QRect &rect) {
        Q_UNUSED(rect)
        if (treeRoot)
            paintTreeNode(treeRoot, painter);
    }


    void insertNode(const QPointF &data) {
        if (!treeRoot)
            treeRoot = new QuadTree(
                QRectF(0.0, 0.0, 500.0, 500.0), data);
        else
            treeRoot->insert(data);
    }


    void leftClick(const QPoint &pos) {
        insertNode(pos);
        updateCanvas();
    }


    void rightClick(const QPoint &pos) {
        Q_UNUSED(pos)
        qDebug() << "TODO: remove node" << pos;
    }


    void animate() {
        int x = 1 + rand() % 499;
        int y = 1 + rand() % 499;
        insertNode(QPointF(x, y));
        updateCanvas();
    }


    void reset() {
        // TODO: delete all elements in the tree
        treeRoot = nullptr;
        updateCanvas();
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SquareTreeView treeView(nullptr);
    treeView.show();
    return app.exec();
}
