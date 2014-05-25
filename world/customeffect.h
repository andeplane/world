#pragma once
#include <QGLShaderProgramEffect>

class CustomEffect : public QGLShaderProgramEffect
{
public:
    CustomEffect();
    void update(QGLPainter *painter, QGLPainter::Updates updates);

protected:
    bool beforeLink();
    void afterLink();
private:
    bool m_firstPaint;
    bool m_regenerate;
    bool m_hasPeriodicCopies;
    bool m_periodicCopiesAllowed;
    QOpenGLShaderProgram* m_program;

    int m_timeLocation;
    double m_time;
};
