#pragma once
#include <QQuickItem3D>
#include <QGLAbstractScene>
#include <QElapsedTimer>
#include <qglshaderprogram.h>
#include <customeffect.h>

class Mesh : public QQuickItem3D
{
    Q_OBJECT
public:
    explicit Mesh(QQuickItem *parent = 0);
    virtual ~Mesh();

    void generateVertexBundle();
    int meshSize() const;
    void setMeshSize(int meshSize);

    const QGLVertexBundle &vertexBundle();
private:
    QGLVertexBundle m_vertexBundle;
    QGLIndexBuffer m_indexBuffer;
    CustomEffect *m_effect;
    bool m_vertexBundleDirty;
    int m_meshSize;
protected:
    virtual void drawItem(QGLPainter *painter);
    virtual void drawEffectSetup(QGLPainter *painter, bool &viewportBlend, bool &effectBlend);
    virtual void drawEffectCleanup(QGLPainter *painter, bool &viewportBlend, bool &effectBlend);
};
