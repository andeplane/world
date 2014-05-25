#include "customeffect.h"

#include <QOpenGLShaderProgram>
#include <qfile.h>
#include <fstream>

CustomEffect::CustomEffect() :
    QGLShaderProgramEffect(),
    m_time(0)
{
}

bool CustomEffect::beforeLink() {
    std::ifstream vertexFile("qml/world/shader.vert", std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(vertexFile)),
                     std::istreambuf_iterator<char>());

    QByteArray vertexCode(QByteArray(str.c_str(),str.length()));

    program()->addShaderFromSourceCode
            (QOpenGLShader::Vertex, vertexCode);

    std::ifstream fragmentFile("qml/world/shader.frag", std::ifstream::in);
    str = std::string((std::istreambuf_iterator<char>(fragmentFile)),
              std::istreambuf_iterator<char>());

    QByteArray fragmentCode(QByteArray(str.c_str(),str.length()));

    program()->addShaderFromSourceCode
            (QOpenGLShader::Fragment, fragmentCode);

    vertexFile.close();
    fragmentFile.close();
    return true;
}

void CustomEffect::afterLink() {
    m_timeLocation = program()->uniformLocation("time");
}

void CustomEffect::update(QGLPainter *painter, QGLPainter::Updates updates) {
    QGLShaderProgramEffect::update(painter, updates);
    if(updates & QGLPainter::UpdateColor) {
        program()->setUniformValue(m_timeLocation,(GLfloat)m_time);
    }
}
