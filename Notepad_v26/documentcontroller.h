#ifndef DOCUMENTCONTROLLER_H
#define DOCUMENTCONTROLLER_H

#include <QObject>
#include <QQuickTextDocument>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrintDialog>
#include <QPrinter>

class DocumentController  : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQuickTextDocument *notepadDoc READ notepadDoc  WRITE setNotepadDoc  NOTIFY notepadDocChanged)

    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE  setCursorPosition NOTIFY cursorPositionChanged)

    Q_PROPERTY(int selectionStart READ selectionStart WRITE setSelectionStart NOTIFY selectionStartChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd WRITE setSelectionEnd NOTIFY selectionEndChanged)

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY updateTextColor)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY updateFontSize)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY updateFontFamily)

    Q_PROPERTY(bool bold READ bold WRITE setBold NOTIFY updateBold)
    Q_PROPERTY(bool italic READ italic WRITE setItalic NOTIFY updateItalic)
    Q_PROPERTY(bool underline READ underline WRITE setUnderline NOTIFY updateUnderline)

    Q_PROPERTY(Qt::Alignment textAlignment READ  textAlignment WRITE setTextAlignment NOTIFY updateTextAlignment)

    Q_PROPERTY(bool isUndoAvailable READ isUndoAvailable  NOTIFY undoChanged)
    Q_PROPERTY(bool isRedoAvailable READ isRedoAvailable  NOTIFY redoChanged)

    Q_PROPERTY(QString curFileName READ curFileName NOTIFY curFileChanged)


public:
    explicit DocumentController(QObject *parent = nullptr);

    QQuickTextDocument *notepadDoc() const;

    void setNotepadDoc(QQuickTextDocument *doc);


    int cursorPosition() const;
    void setCursorPosition(int value);

    int selectionStart() const;
    void setSelectionStart(int value);

    int selectionEnd() const;
    void setSelectionEnd(int value);

    QColor textColor() const;
    void setTextColor(const QColor &color);


    int fontSize() const;
    void setFontSize(int size);

    QString fontFamily() const;
    void setFontFamily(const QString &family);

    bool bold() const;
    void setBold(bool bold);

    bool italic() const;
    void setItalic(bool italic);

    bool underline() const;
    void setUnderline(bool underline);

    Qt::Alignment textAlignment() const;

    void setTextAlignment(Qt::Alignment textAlignment);

    QString curFileName()const;

    Q_INVOKABLE void executeUndoRedo(bool isUndo);


    bool isUndoAvailable() const;
    bool isRedoAvailable() const;

signals:
    void notepadDocChanged();

    void fileContentLoaded(const QString &content, int format);

    void cursorPositionChanged();
    void selectionStartChanged();
    void selectionEndChanged();

    void updateTextColor();
    void updateFontSize();
    void updateFontFamily();

    void updateBold();
    void updateItalic();
    void updateUnderline();
    void updateTextAlignment();

    void undoChanged();
    void redoChanged();

    void curFileChanged();

public slots:
    void openFile(const QUrl &fileUrl);

    bool saveContent();

    bool saveAs(const QUrl &fileUrl);

    void createFile(const QUrl &fileUrl);

    void printFile();
private:

    QTextDocument  *getQtextDocument() const;

    QTextCursor  textCursor() const;

    void setFormatting(const QTextCharFormat &textFormat);

    void resetFormating();

    int m_cursorPosition;
    int m_selectionStart;
    int m_selectionEnd;
    QUrl m_currentFileUrl;
    static QTextDocument  *m_qtextDocument;
    QQuickTextDocument *m_notepadDoc;
};

#endif // DOCUMENTCONTROLLER_H
