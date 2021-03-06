/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QEGLFSVBPAGEFLIPPER_H
#define QEGLFSVBPAGEFLIPPER_H

#include <qpa/qplatformscreenpageflipper.h>
#include <QTransform>

QT_BEGIN_NAMESPACE

class QPlatformScreen;
class QWindow;

class QEglFSVBPageFlipper : public QPlatformScreenPageFlipper
{
  Q_OBJECT

public:
    QEglFSVBPageFlipper(QPlatformScreen *screen);
    ~QEglFSVBPageFlipper();

    bool displayBuffer(QPlatformScreenBuffer *buffer);

    bool isActive() const { return m_active; }

private slots:
#ifdef QT_EGLFSVB_ENABLE_ROTATION
    void setWindow(QWindow *window);
    void setOrientation(Qt::ScreenOrientation orientation);
#endif

private:
    Q_INVOKABLE void setDirectRenderingActive(bool active);

    QPlatformScreen *m_screen;
    QWindow *m_window;
    QPlatformScreenBuffer *m_buffer;
    bool m_active;
    QTransform m_transform;

    int fd;
};

QT_END_NAMESPACE
#endif // QEGLFSVBPAGEFLIPPER_H
