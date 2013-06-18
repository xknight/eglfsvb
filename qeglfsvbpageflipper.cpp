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

#include "qeglfsvbpageflipper.h"

#include <QImage>

#include <sys/mman.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>

QT_BEGIN_NAMESPACE

QEglFSVBPageFlipper::QEglFSVBPageFlipper() : m_buffer(0)
{
    fd = open("/dev/fb0", O_RDWR | O_CLOEXEC);
    if (fd < 0)
        qFatal("QEglFsPageFlipper: could not open /dev/fb0.");
}

QEglFSVBPageFlipper::~QEglFSVBPageFlipper()
{
    if (fd >= 0)
        close(fd);

    if (m_buffer)
        m_buffer->release();
}

bool QEglFSVBPageFlipper::displayBuffer(QPlatformScreenBuffer *buffer)
{
    QImage *frame = static_cast<QImage *>(buffer->handle());

    QImage tmpFrame;
    if (frame->width() * 4 != frame->bytesPerLine()) {
        tmpFrame = frame->copy();
        frame = &tmpFrame;
    }


    int area = frame->bytesPerLine() * frame->height();
    void *mapped = mmap(NULL, area, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped == MAP_FAILED) {
        qWarning("Unable to map fbdev.\n");
        return false;
    }

    buffer->aboutToBeDisplayed();

    memcpy(mapped, frame->constBits(), area);
    munmap(mapped, area);

    buffer->displayed();

    if (m_buffer)
        m_buffer->release();
    m_buffer = buffer;

    return true;
}

void QEglFSVBPageFlipper::setDirectRenderingActive(bool active)
{
    if (!active && m_buffer) {
        m_buffer->release();
        m_buffer = 0;
    }
}

QT_END_NAMESPACE
