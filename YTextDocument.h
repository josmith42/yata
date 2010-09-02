#ifndef YTEXTDOCUMENT_H
#define YTEXTDOCUMENT_H

#include <QScopedPointer>
#include <QString>
#include <vector>

class QTextBlock;
class QTextDocument;
class QTextCursor;

class YTextDocument {
public:
    explicit YTextDocument(const QString & text = QString());
    void setText(const QString & text);
    void layout(int width);

    QTextBlock findBlockAtLayoutPosition(int layoutPosition, int * closestLayoutPos = 0);
    int blockLayoutPosition(QTextBlock block);

    QTextDocument * document();
    int numLayoutLines() const;

    void select(const QTextCursor & cursor);

private:
    int layoutBlock(QTextBlock * textBlock);

private:
    QScopedPointer<QTextDocument> m_document;
    QScopedPointer<QTextCursor> m_selectedCursor;

    int m_numLayoutLines;
    std::vector<int> m_blockLayoutPositions;
    int m_width;
    bool m_needs_layout;
};

#endif // YTEXTDOCUMENT_H
