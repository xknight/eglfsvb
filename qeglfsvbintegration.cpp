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

#include "qeglfsvbintegration.h"
#include "qeglfsvbscreen.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <QGuiApplication>

#include <QDebug>

QT_BEGIN_NAMESPACE

#define VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE              (1U << 0)
#define VMMDEV_MOUSE_GUEST_NEEDS_HOST_CURSOR         (1U << 2)
#define VMMDEV_MOUSE_NEW_PROTOCOL                    (1U << 4)
#define VMMDEV_MOUSE_HOST_RECHECKS_NEEDS_HOST_CURSOR (1U << 5)
#define VBOXGUEST_IOCTL_SET_MOUSE_STATUS _IOC(_IOC_READ|_IOC_WRITE, 'V', 10, sizeof(quint32))

QEglFSVBIntegration::QEglFSVBIntegration()
    : mScreen(new QEglFSVBScreen(display()))
{
    // Override inherited screen
    delete QEglFSIntegration::screen();
    screenAdded(mScreen);

#ifdef QT_NO_CURSOR
    // Tell host to keep host cursor
    int fd = open("/dev/vboxguest", O_RDWR);
    if (fd >= 0) {
        qDebug() << "open mouse success";
        quint32 features = VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE|VMMDEV_MOUSE_GUEST_NEEDS_HOST_CURSOR
                           |VMMDEV_MOUSE_NEW_PROTOCOL|VMMDEV_MOUSE_HOST_RECHECKS_NEEDS_HOST_CURSOR;
        qDebug() << "ioctl" << ioctl(fd, VBOXGUEST_IOCTL_SET_MOUSE_STATUS, &features);
    }
#endif

}

QT_END_NAMESPACE
