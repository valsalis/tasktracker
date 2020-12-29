/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "analogclock.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

#include <QDebug>
#include <QPainterPath>

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    setMinimumSize(400,400);
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    QColor hourColor(127, 0, 127);
    QPen hourPen(hourColor, 2);
    QColor minuteColor(0, 127, 127, 191);

    QPainterPath hourHandPath;
    hourHandPath.moveTo(10.0, 0.0);
    hourHandPath.arcTo(-10.0, 10.0, 20.0, -20.0, 0.0, 180.0);
    hourHandPath.lineTo(0.0, -40.0);
    hourHandPath.lineTo(10.0, 0.0);
    hourHandPath.closeSubpath();

    QPainterPath minuteHandPath;
    minuteHandPath.moveTo(10.0, 0.0);
    minuteHandPath.arcTo(-10.0, 10.0, 20.0, -20.0, 0.0, 180.0);
    minuteHandPath.lineTo(0.0, -70.0);
    minuteHandPath.lineTo(10.0, 0.0);
    minuteHandPath.closeSubpath();

    int side = qMin(width(), height());
    QTime time(QTime::currentTime());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);  // Translates the coordinate system by the vector (dx, dy). Moves the origin to the center
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(Qt::NoPen); // painter.setPen(Qt::SolidLine);
    painter.setBrush(hourColor);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0))); // rotates the coordinate system in degrees
    painter.drawPath(hourHandPath);
    painter.restore();

    painter.setPen(hourPen);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(68, 0, 76, 0);
        painter.rotate(30.0);
    }

    painter.save();
    QFont font = painter.font();
    font.setPixelSize(13);
    painter.setFont(font);
    painter.drawText(QRect(-10, -98 , 20, 20), Qt::AlignCenter,"XII");
    painter.drawText(QRect(78, -10 , 20, 20), Qt::AlignCenter,"III");
    painter.drawText(QRect(-10, 78 , 20, 20), Qt::AlignCenter,"VI");
    painter.drawText(QRect(-98, -10 ,20, 20), Qt::AlignCenter,"IX");
    painter.restore();

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    // painter.drawConvexPolygon(minuteHand, 3);
    painter.drawPath(minuteHandPath);
    painter.restore();

    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(72, 0, 76, 0);
        painter.rotate(6.0);
    }
}
