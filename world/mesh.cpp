#include "mesh.h"
#include <cmath>
#include <qquickeffect.h>

Mesh::Mesh(QQuickItem *parent) :
    QQuickItem3D(parent),
    m_meshSize(1024),
    m_vertexBundleDirty(true)
{
    m_effect = new CustomEffect();
}

void Mesh::drawItem(QGLPainter *painter) {

    qDebug() << "stuff";

    painter->clearAttributes();
    // Set up normal attributes to use only one element
//    painter->glDisableVertexAttribArray(GLuint(QGL::Normal));
//    painter->glVertexAttrib3f(GLuint(QGL::Normal), normal.x(), normal.y(), normal.z());

    // Set the rest of the vertex bundle (basically only positions)
    painter->setVertexBundle(vertexBundle());
    m_effect->update(painter, QGLPainter::UpdateColor);
    painter->draw(QGL::DrawingMode(QGL::Lines), m_indexBuffer, 0, m_indexBuffer.indexCount());
}

void Mesh::drawEffectSetup(QGLPainter *painter, bool &viewportBlend, bool &effectBlend)
{
    // Setting our custom effect must be done before passing any data
    painter->setUserEffect(m_effect);
}

void Mesh::drawEffectCleanup(QGLPainter *painter, bool &viewportBlend, bool &effectBlend)
{
    painter->setStandardEffect(QGL::FlatColor);
    painter->setColor(Qt::white);
    painter->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (viewportBlend != effectBlend) {
        if (effectBlend)
            glDisable(GL_BLEND);
        else
            glEnable(GL_BLEND);
    }
}

const QGLVertexBundle &Mesh::vertexBundle()
{
    if(m_vertexBundleDirty) {
        generateVertexBundle();
    }
    return m_vertexBundle;
}

void Mesh::generateVertexBundle() {
    m_vertexBundle = QGLVertexBundle();
    m_indexBuffer = QGLIndexBuffer();
    double scale = 100;

    QArray<QVector3D> points;
    QArray<uint> indices;
    for(int j=0; j<m_meshSize; j++) {
        for(int i=0; i<m_meshSize; i++) {
            double x = 2*(i - m_meshSize/2.0) / m_meshSize; // Between -1 and 1
            double z = 2*(j - m_meshSize/2.0) / m_meshSize;
            double y = exp(-(x*x + y*y));
            y = 0;

            points.append(QVector3D(scale*x,scale*y,scale*z));
        }
    }

    for(int i=0; i<m_meshSize-1; i++) {
        for(int j=0; j<m_meshSize-1; j++) {
            int thisVertex = j*m_meshSize + i;
            int rightVertex = j*m_meshSize + i+1;
            int downVertex = (j+1)*m_meshSize + i;
            int downRightVertex = (j+1)*m_meshSize + i+1;

            indices.append(thisVertex, rightVertex, downVertex, thisVertex);
            indices.append(downVertex, rightVertex, downRightVertex, downVertex);
        }
    }

    m_vertexBundle.addAttribute(QGL::Position, points);
    m_indexBuffer.setIndexes(indices);

    points.clear();
    indices.clear();
    m_vertexBundleDirty = false;
}



int Mesh::meshSize() const
{
    return m_meshSize;
}

void Mesh::setMeshSize(int meshSize)
{
    m_meshSize = meshSize;
}

Mesh::~Mesh()
{

}
