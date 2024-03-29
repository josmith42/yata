/*
 * This file is part of yata -- Yet Another Tail Application
 * Copyright 2010 James Smith
 *
 * Licensed under the GNU General Public License.  See license.txt for details.
 */
#ifndef FILEBLOCKREADER_H
#define FILEBLOCKREADER_H

#include <utility>
#include <QtGlobal>
#include <QFile>

#include <vector>

#include "BufferedFile.h"

class QString;

class FileBlockReader {
public:
    FileBlockReader(const QString & filename);

    bool readChunk(QString *data, std::vector<qint64> * filePositions,
        qint64 start_pos, qint64 lines_after_start, qint64 num_lines);
    bool readChunk(QString *data, qint64 start_pos, qint64 length);
    bool readAll(QString * data, std::vector<qint64> * filePositions);
    qint64 getStartPosition(qint64 init_pos, qint64 lines_after_start);

    qint64 size() const;
    const QString & filename() const;

    const QString & errorString() const;

private:
    qint64 beginningOfLine(qint64 start_pos);
    qint64 nextLine(qint64 start_pos);

    bool read(QString * data, std::vector<qint64> * filePositions, qint64 start_pos, qint64 num_lines);

private:
    BufferedFile m_file;
};
#endif
