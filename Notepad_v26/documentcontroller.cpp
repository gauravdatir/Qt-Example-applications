#include "documentcontroller.h"
#include <QQmlFile>
#include <QMimeType>
#include <QMimeDatabase>
#include <QTextCodec>
#include <QFileInfo>

QTextDocument  *DocumentController::m_qtextDocument = nullptr;
DocumentController::DocumentController(QObject *parent)
    : QObject(parent)
{

}


QQuickTextDocument *DocumentController::notepadDoc() const{
    return m_notepadDoc;
}

void DocumentController::setNotepadDoc(QQuickTextDocument *doc) {
    m_notepadDoc = doc;
    emit notepadDocChanged();
}


QTextDocument *DocumentController::getQtextDocument() const{
    if (m_notepadDoc == nullptr)
    {
        m_qtextDocument = nullptr;
    }
    else
    {
        m_qtextDocument = m_notepadDoc->textDocument();
    }
    return m_qtextDocument;
}


bool DocumentController::isUndoAvailable() const{
    m_qtextDocument = getQtextDocument();
    if(m_qtextDocument)
    {
        return m_qtextDocument->isUndoAvailable();
    }
    return false;
}
bool DocumentController::isRedoAvailable() const{
    m_qtextDocument = getQtextDocument();
    if(m_qtextDocument)
    {
        return m_qtextDocument->isRedoAvailable();
    }
    return false;
}

void DocumentController::executeUndoRedo(bool isUndo) {

    m_qtextDocument = getQtextDocument();
    if(m_qtextDocument)
    {
        if(isUndo == true)
        {
            if (m_qtextDocument->isUndoAvailable())
            {
                m_qtextDocument->undo();

            }
        }
        else {
            if (m_qtextDocument->isRedoAvailable())
            {
                m_qtextDocument->redo();

            }
        }
        emit undoChanged();
        emit redoChanged();
    }
}

QColor DocumentController::textColor() const
{
    QTextCursor curCursor = textCursor();

    if (curCursor.isNull())
    {
        return QColor(Qt::black);
    }

    QTextCharFormat textFormat = curCursor.charFormat();
    return textFormat.foreground().color();
}
void DocumentController::setTextColor(const QColor &color){
    QTextCursor curCursor = textCursor();

    QTextCharFormat textFormat;
    if (!curCursor.isNull())
    {
        textFormat = curCursor.charFormat();
    }
    textFormat.setForeground(QBrush(color));

    setFormatting(textFormat);
    emit updateTextColor();
}

int DocumentController::fontSize() const {
    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return 0;
    }

    QTextCharFormat textFormat = curCursor.charFormat();
    return textFormat.font().pointSize();

}
void DocumentController::setFontSize(int size) {

    if (size <= 0)
    {
        return;
    }
    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return;
    }

    if (!curCursor.hasSelection())
    {
        curCursor.select(QTextCursor::WordUnderCursor);
    }

    if(curCursor.charFormat().property(QTextFormat::FontPointSize).toInt() == size)
    {
        return;
    }

    QTextCharFormat textFormat;
    textFormat.setFontPointSize(size);

    setFormatting(textFormat);
    emit updateFontSize();
}

QString DocumentController::fontFamily() const {

    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return QString();
    }
    QTextCharFormat textFormat = curCursor.charFormat();
    return textFormat.font().family();
}
void DocumentController::setFontFamily(const QString &family){

    QTextCharFormat textFormat;
    textFormat.setFontFamily(family);
    setFormatting(textFormat);

    emit updateFontFamily();

}

bool DocumentController::bold() const {
    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return false;
    }
    return curCursor.charFormat().fontWeight() == QFont::Bold;
}
void DocumentController::setBold(bool bold){

    QTextCharFormat textFormat;
    textFormat.setFontWeight(bold ? QFont::Bold : QFont::Normal);

    setFormatting(textFormat);
    emit updateBold();
}


bool DocumentController::italic() const {
    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return false;
    }
    return curCursor.charFormat().fontItalic();
}
void DocumentController::setItalic(bool italic){
    QTextCharFormat textFormat;
    textFormat.setFontItalic(italic);

    setFormatting(textFormat);
    emit updateItalic();
}

bool DocumentController::underline() const {

    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return false;
    }
    return curCursor.charFormat().fontUnderline();
}
void DocumentController::setUnderline(bool underline){
    QTextCharFormat textFormat;
    textFormat.setFontUnderline(underline);
    setFormatting(textFormat);
    emit updateUnderline();
}


Qt::Alignment DocumentController::textAlignment() const {
    QTextCursor curCursor = textCursor();
    if (curCursor.isNull())
    {
        return Qt::AlignLeft;
    }
    return curCursor.blockFormat().alignment();

}

void DocumentController::setTextAlignment(Qt::Alignment textAlignment) {

    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(textAlignment);

    QTextCursor curCursor = textCursor();

    curCursor.mergeBlockFormat(blockFormat);

    emit updateTextAlignment();
}


void DocumentController::setFormatting(const QTextCharFormat &textFormat)
{
    QTextCursor curCursor = textCursor();

    if (!curCursor.isNull())
    {
        if (!curCursor.hasSelection())
        {
            curCursor.select(QTextCursor::WordUnderCursor);
        }
        curCursor.mergeCharFormat(textFormat);
    }
    resetFormating();
}

QTextCursor DocumentController::textCursor() const {
    m_qtextDocument = getQtextDocument();

    if (!m_qtextDocument)
    {
        return QTextCursor();
    }

    QTextCursor curCursor = QTextCursor(m_qtextDocument);
    if (m_selectionStart != m_selectionEnd)
    {
        curCursor.setPosition(m_selectionStart);
        curCursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    }
    else {
        curCursor.setPosition(m_cursorPosition);
    }
    return curCursor;
}


void DocumentController::resetFormating()
{
    emit undoChanged();
    emit redoChanged();
}

int DocumentController::cursorPosition() const {
    return m_cursorPosition;
}

int DocumentController::selectionStart() const {
    return m_selectionStart;
}

int DocumentController::selectionEnd() const{
    return m_selectionEnd;
}

void DocumentController::setSelectionStart(int value) {
    if (m_selectionStart != value)
    {
        m_selectionStart = value;
        resetFormating();
        emit selectionStartChanged();
    }
}

void DocumentController::setSelectionEnd(int value) {
    if (m_selectionEnd != value)
    {
        m_selectionEnd = value;
        resetFormating();
        emit selectionEndChanged();
    }
}

void DocumentController::setCursorPosition(int value) {
    if (m_cursorPosition != value)
    {
        m_cursorPosition = value;
        resetFormating();
        emit cursorPositionChanged();
    }
}



QString DocumentController::curFileName()const {
    const QString curFilePath = QQmlFile::urlToLocalFileOrQrc(m_currentFileUrl);
    QString curFileName = QFileInfo(curFilePath).fileName();
    if(curFileName.isEmpty())
    {
        curFileName ="untitled.txt";
    }
    return curFileName;
}


void DocumentController::createFile(const QUrl &fileUrl)
{
    if (fileUrl.isEmpty())
        return;
    const QString filename = QQmlFile::urlToLocalFileOrQrc(QUrl(fileUrl));

    QFile fileObj(filename);

    fileObj.open(QFile::WriteOnly);
    fileObj.write("");
    fileObj.close();

    QMimeType mimeType = QMimeDatabase().mimeTypeForFile(filename);

    if(fileObj.open(QFile::ReadOnly))
    {
        QByteArray content = fileObj.readAll();
        m_qtextDocument = m_notepadDoc->textDocument();

        if(m_qtextDocument)
        {
            if (mimeType.inherits("text/markdown"))
            {
                emit fileContentLoaded(QString::fromUtf8(content), Qt::MarkdownText);
            }
            else {
                emit fileContentLoaded(QString::fromUtf8(content), Qt::MarkdownText);
            }
            m_qtextDocument->setModified(false);
        }
    }
    m_currentFileUrl = fileUrl;
    emit curFileChanged();
}


void DocumentController::openFile(const QUrl &fileUrl){
    if (fileUrl.isEmpty())
        return;
    const QString filename = QQmlFile::urlToLocalFileOrQrc(QUrl(fileUrl));


    if (QFile::exists(filename))
    {
        QMimeType mimeType = QMimeDatabase().mimeTypeForFile(filename);

        QFile fileObj(filename);

        if(fileObj.open(QFile::ReadOnly))
        {
            QByteArray content = fileObj.readAll();
            m_qtextDocument = m_notepadDoc->textDocument();

            if(m_qtextDocument)
            {
                if (mimeType.inherits("text/markdown"))
                {
                    emit fileContentLoaded(QString::fromUtf8(content), Qt::MarkdownText);
                }
                else {
                    QTextCodec *code = QTextCodec::codecForHtml(content);
                    emit fileContentLoaded(code->toUnicode(content), Qt::AutoText);
                }
                m_qtextDocument->setModified(false);
            }
        }
    }
    m_currentFileUrl = fileUrl;
    emit curFileChanged();
}

bool  DocumentController::saveContent(){
    if (m_currentFileUrl.isEmpty() || m_notepadDoc == nullptr)
    {
        return false;
    }

    m_qtextDocument = m_notepadDoc->textDocument();


    const QString curfilePath = m_currentFileUrl.toLocalFile();
    const bool isHtml = QFileInfo(curfilePath).suffix().contains(QLatin1String("htm"));

    QFile fileObj(curfilePath);

    if (fileObj.open(QFile::WriteOnly))
    {
        if (isHtml)
        {
            fileObj.write(m_qtextDocument->toHtml().toUtf8());
        }
        else {
            fileObj.write(m_qtextDocument->toPlainText().toUtf8());
        }
        fileObj.close();
    }
    return true;
}

bool DocumentController::saveAs(const QUrl &fileUrl){
    if (fileUrl.isEmpty() || m_notepadDoc == nullptr)
    {
        return false;
    }

    m_qtextDocument = m_notepadDoc->textDocument();


    const QString curfilePath = fileUrl.toLocalFile();
    const bool isHtml = QFileInfo(curfilePath).suffix().contains(QLatin1String("htm"));

    QFile fileObj(curfilePath);

    if (fileObj.open(QFile::WriteOnly))
    {
        if (isHtml)
        {
            fileObj.write(m_qtextDocument->toHtml().toUtf8());
        }
        else {
            fileObj.write(m_qtextDocument->toPlainText().toUtf8());
        }
        fileObj.close();
        m_currentFileUrl = fileUrl;
        emit curFileChanged();
    }
    return true;
}

void DocumentController::printFile() {

    QPrinter printer;

    QPrintDialog printDialog(&printer);

    if (printDialog.exec() == QDialog::Accepted)
    {
        m_qtextDocument->print(&printer);
    }

}
