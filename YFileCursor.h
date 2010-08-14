#ifndef YFILECURSOR_H
#define YFILECURSOR_H

#include <QtGlobal>

struct YFileCursor {
    qint64 m_lineAddress;
    int m_charPos;
    int m_length;

    YFileCursor(qint64 linePosition = -1, int lineOffset = -1, int length = -1)
        : m_lineAddress(linePosition)
        , m_charPos(lineOffset)
        , m_length(length)
    {}

    bool isNull() const { return m_lineAddress == -1; }
};

#endif // YFILECURSOR_H