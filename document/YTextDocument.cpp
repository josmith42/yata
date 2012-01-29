/*
 * This file is part of yata -- Yet Another Tail Application
 * Copyright 2010 James Smith
 *
 * Licensed under the GNU General Public License.  See license.txt for details.
 */
#include "YTextDocument.h"
#include "YFileCursor.h"
#include "preferences/TextColor.h"
#include "preferences/Preferences.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPalette>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextLayout>

#include <algorithm>

YTextDocument::YTextDocument():
    m_document(new QTextDocument()),
    m_selectedCursor(new QTextCursor()),
    m_numLayoutLines(0),
    m_blockLayoutLines(m_document.data()),
    m_blockGraphicalPositions(m_document.data()),
    m_lineAddresses(m_document.data()),
    m_fileCursor(new YFileCursor()),
    m_width(0),
    m_needs_layout(false)
{
    m_document->setUndoRedoEnabled(false);
    m_document->setUseDesignMetrics(true);
    updateFont();
}

YTextDocument::~YTextDocument()
{
}

void YTextDocument::setText(const QString & text, const std::vector<qint64> & newAddresses)
{
    m_document->setPlainText(text);
    m_lineAddresses.assign(newAddresses);

    select(m_fileCursor->qTextCursor(this));
    m_needs_layout = true;
}

void YTextDocument::layout(int width)
{
    if(!m_needs_layout && m_width == width) {
        return;
    }

    m_width = width;
    m_numLayoutLines = 0;
    qreal dy = 0;
    m_blockLayoutLines.clear();
    m_blockGraphicalPositions.clear();

    for(QTextBlock block = m_document->begin(); block != m_document->end(); block = block.next()) {
        qreal height = layoutBlock(&block);
        m_blockLayoutLines.push_back(m_numLayoutLines);
        m_blockGraphicalPositions.push_back(dy);
        m_numLayoutLines += block.layout()->lineCount();
        dy += height;
    }

    QTextCursor cursor(m_document.data());
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    setColors(&cursor, Preferences::instance()->normalTextColor());

    select(*m_selectedCursor);

    m_needs_layout = false;
}

void YTextDocument::markDirty()
{
    select(*m_selectedCursor);
    updateFont();
    m_needs_layout = true;
}

void YTextDocument::updateFont()
{
    const QFont & font = Preferences::instance()->font();
    if (font != m_document->defaultFont()) {
        m_document->setDefaultFont(font);
        m_needs_layout = true;
    }
}

qreal YTextDocument::layoutBlock(QTextBlock * textBlock)
{
    QTextLayout * layout = textBlock->layout();
    layout->setFont(m_document->defaultFont());
    QFontMetrics fontMetrics(layout->font());

    qreal height = 0;

    layout->beginLayout();
    while(true) {
        QTextLine line = layout->createLine();
        if(!line.isValid()) { break; }
        line.setLineWidth(m_width);
        height += fontMetrics.leading();
        line.setPosition(QPointF(0, height));
        height += line.height();
    }

    layout->endLayout();
    return height;
}

qint64 YTextDocument::blockAddress(QTextBlock block) const
{
    int blockNumber = block.blockNumber();
    if(blockNumber < 0 || static_cast<unsigned int>(blockNumber) >= m_lineAddresses.size()) {
        return -1;
    }
    return m_lineAddresses.at(blockNumber);
}

QTextDocument * YTextDocument::document()
{
    return m_document.data();
}

const QTextDocument * YTextDocument::document() const
{
    return m_document.data();
}

int YTextDocument::numLayoutLines() const
{
    return m_numLayoutLines;
}

void YTextDocument::select(const QTextCursor & cursor)
{
    // Clear current selection first
    setColors(m_selectedCursor.data(), Preferences::instance()->normalTextColor());

    *m_selectedCursor = cursor;
    if(!m_selectedCursor->isNull()) {
        setColors(m_selectedCursor.data(), Preferences::instance()->selectedTextColor());
    }
}

void YTextDocument::setColors(QTextCursor * cursor, const TextColor & textColor)
{
    QTextCharFormat format;
    format.setForeground(textColor.foreground());
    format.setBackground(textColor.background());
    cursor->setCharFormat(format);
}

void YTextDocument::setFileCursor(const YFileCursor & cursor)
{
    *m_fileCursor = cursor;
}
