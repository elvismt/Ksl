#include <QDebug>
#include <QString>

#include <Ksl/Array.h>
#include <Ksl/Graph.h>
using namespace Ksl;

#include <iostream>
using namespace std;

int main()
{
    MemoryPool memPool;
    Graph<QString> graph(&memPool, &memPool, "Lara");

    auto lara = graph.entry();
    graph.addNeighbor(lara, "son", "Bob");
    graph.addNeighbor(lara, "father", "Bruce");

    // Who?
    qDebug() << "Graph entry is" << lara->data();

    // Who is her son?
    auto queryResult = lara->findByEdge("son");
    qDebug() << "her son is" << queryResult->data();

    // Who is her father?
    queryResult = lara->findByEdge("father");
    qDebug() << "her father is" << queryResult->data();

    return 0;
}
