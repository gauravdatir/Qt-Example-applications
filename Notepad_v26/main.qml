import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2


import Qt.labs.platform 1.0

import notepad.example.texteditor 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: "Notepad - " + docController.curFileName



    Shortcut {
        sequence: StandardKey.Open
        onActivated: openFileDialog.open()
    }
    Shortcut {
        sequence: StandardKey.SaveAs
        onActivated: saveDialog.open()
    }

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: close()
    }

    MenuBar {
        id: notePadMenu

        Menu {
            id: fileMenu
            title: qsTr("File")
            MenuItem {
                text: qsTr("New")
                onTriggered: newFile.open()
                enabled: true

            }
            MenuItem {
                text: qsTr("Open")
                enabled: true
                onTriggered: openFileDialog.open()

            }
            MenuItem {
                text: qsTr("Save")
                enabled: true
                onTriggered: {
                    if(docController.saveContent() === false)
                        saveDialog.open();
            }

        }
        MenuItem {
            text: qsTr("Save as")
            enabled: true
            onTriggered: saveDialog.open()

        }
        MenuItem {
            text: qsTr("Print")
            enabled: true
        }
        MenuItem {
            text: qsTr("Exit")
            enabled: true
            onTriggered: close()
        }

    }
    Menu {
        id: editMenu
        title: qsTr("Edit")
        // ...

        MenuItem {
            text: qsTr("Undo")
            enabled: true
        }
        MenuItem {
            text: qsTr("cut")
            enabled: true
            onTriggered: textEditArea.cut()
        }
        MenuItem {
            text: qsTr("Copy")
            enabled: true
            onTriggered: textEditArea.copy()
        }
        MenuItem {
            text: qsTr("Paste")
            enabled: true
            onTriggered: textEditArea.paste()
        }
        MenuItem {
            text: qsTr("Select All")
            enabled: true
            onTriggered: textEditArea.selectAll()
        }
    }

    Menu {
        id: formatMenu
        title: qsTr("Format")
        // ...\
        MenuItem {
            text: qsTr("font")
            enabled: true
            onTriggered: {
                fontDialog.currentFont.pointSize = docController.fontSize
                fontDialog.currentFont.family = docController.fontFamily
                fontDialog.open()
            }
        }
        MenuItem {
            text: qsTr("Word Wrap")
            enabled: true
        }
    }
    Menu {
        id: viewMenu
        title: qsTr("View")
        // ...
        MenuItem {
            text: qsTr("Status Bar")
            enabled: true
            checkable: true
        }
    }

    Menu {
        id: helpMenu
        title: qsTr("Help")
        // ...
        MenuItem {
            text: qsTr("help")
            enabled: true
        }
        MenuItem {
            text: qsTr("About Notepad")
            enabled: true
        }
    }
}

header: ToolBar {
    id: topToolbar
    Row {
        anchors.fill: parent

        ToolButton {
            id: newButton
            contentItem: Rectangle {
                color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/Newfile.svg"
                }
            }
            onClicked: newFile.open()
        }

        ToolButton {
            id: openButton
            contentItem: Rectangle {
                color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/folder-open.svg"
                }
            }
            onClicked: openFileDialog.open();
        }
        ToolButton {
            id: saveButton
            contentItem: Rectangle {
                color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/save.svg"
                }
            }
            onClicked: {
                if(docController.saveContent() === false)
                saveDialog.open();
            }
        }
        ToolButton {
            id: saveAsButton
            contentItem: Rectangle {
                color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/saveas.svg"
                }
            }
            onClicked: saveDialog.open()
        }
        ToolButton {
            id: printButton
            contentItem: Rectangle {
                color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/print.svg"
                }
            }
            onClicked: docController.printFile()
        }

        ToolButton {
            id: undoButton
            enabled: docController.isUndoAvailable
            contentItem: Rectangle {
                color: docController.isUndoAvailable ? "black" : "grey"
                Image {
                    anchors.fill: parent
                    source: "images/undo.svg"
                }
            }
             onClicked: docController.executeUndoRedo(true)
        }
        ToolButton {
            id: redoButton
            enabled: docController.isRedoAvailable
            contentItem: Rectangle {
                color: docController.isRedoAvailable ? "black" : "grey"
                Image {
                    anchors.fill: parent
                    source: "images/dustin-w-Redo-icon.svg"
                }
            }
             onClicked: docController.executeUndoRedo(false)
        }
        ToolButton {
            id: cutButton
            contentItem: Rectangle {
                //  color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/cut.svg"
                }
            }
            onClicked: textEditArea.cut();
        }
        ToolButton {
            id: copyButton
            contentItem: Rectangle {
                // color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/primary-copy.svg"
                }
            }
            onClicked: textEditArea.copy()
        }
        ToolButton {
            id: pasteButton
            contentItem: Rectangle {
                //  color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/Paste.svg"
                }
            }
            onClicked: textEditArea.paste()
        }
        ToolButton {
            id: boldButton
            checkable: true
            checked:docController.bold
            contentItem: Rectangle {
                //  color: "black"
                Image {
                    anchors.fill: parent
                    source: "images/fttext-bold.svg"
                }
            }
             onClicked: docController.bold = !docController.bold
        }
        ToolButton {
            id: italicButton
            checkable: true
            checked:docController.italic
            contentItem: Rectangle {

                Image {
                    anchors.fill: parent
                    source: "images/primary-text-italic.svg"
                }
            }
             onClicked:docController.italic = !docController.italic
        }
        ToolButton {
            id: underlineButton
            checkable: true
            checked:docController.underline
            contentItem: Rectangle {
                Image {
                    anchors.fill: parent
                    source: "images/mono-text-under.svg"
                }
            }
             onClicked: docController.underline = !docController.underline
        }
        ToolButton {
            id: texColor
            contentItem: Rectangle {
                Text {
                    id: colText
                    text: "A"
                    color: colorDialog.color
                    anchors.top: parent.top
                    font.pointSize: 10
                    height: parent.height * 0.8
                }
                Rectangle {
                    id: colorStrip
                    anchors.top: colText.bottom
                    width: parent.width
                    height: parent.height * 0.2
                    color: colorDialog.color
                }
            }
            onClicked: colorDialog.open()
        }

        ToolButton {
            id: textAlignLeft
            checkable: true
            checked: docController.textAlignment === Qt.AlignLeft
            contentItem: Rectangle {
                color: "grey";
                Image {
                    anchors.fill: parent
                    source: "images/mono-align-left.svg"
                }
            }
            onClicked: docController.textAlignment = Qt.AlignLeft
        }
        ToolButton {
            id: textAlignCenter
            checkable: true
            checked: docController.textAlignment === Qt.AlignCenter
            contentItem: Rectangle {
                Image {
                    anchors.fill: parent
                    source: "images/mono-text-center.svg"
                }
            }
            onClicked: docController.textAlignment = Qt.AlignCenter
        }
        ToolButton {
            id: textAlignRight
            checkable: true
            checked:docController.textAlignment === Qt.AlignRight
            contentItem: Rectangle {
                Image {
                    anchors.fill: parent
                    source: "images/mono-text-right.svg"
                }
            }
             onClicked: docController.textAlignment = Qt.AlignRight
        }
    }
}


FontDialog {
    id: fontDialog
    onAccepted: {
        docController.fontSize = font.pointSize
        docController.fontFamily = font.family
    }
}

ColorDialog {
    id: colorDialog
    currentColor: "black"

}

FileDialog {
    id: openFileDialog
    nameFilters: ["Text and  HTML (*.txt *.html *.htm)","Text files (*.txt)","HTML files (*.html *.htm)"]
    fileMode: FileDialog.OpenFile
    onAccepted: {
        docController.openFile(file);
    }
    onRejected: {
        // skip open
    }
}

FileDialog {
    id: saveDialog
    nameFilters: ["Text and  HTML (*.txt *.html *.htm)","Text files (*.txt)", "HTML files (*.html *.htm)"]
    fileMode: FileDialog.SaveFile
    onAccepted: {
        docController.saveAs(file);
    }
    onRejected: {
        // skip saving
    }
}

FileDialog {
    id: newFile
    fileMode: FileDialog.SaveFile
    title: "Create new file"

    onAccepted:  {
        docController.createFile(file);
    }
}


DocumentController {
    id: docController
    notepadDoc: textEditArea.textDocument
    cursorPosition: textEditArea.cursorPosition
    selectionStart: textEditArea.selectionStart
    selectionEnd: textEditArea.selectionEnd
    textColor:colorDialog.color

    onFileContentLoaded: {
        textEditArea.textFormat = format;
        textEditArea.text = content
    }
}

TextArea {
    id: textEditArea
    width: parent.width
    anchors.top: topToolbar.bottom
    anchors.bottom: parent.bottom
    selectByMouse: true
    persistentSelection: true
    //text:
    textFormat: Qt.RichText
    Component.onCompleted: forceActiveFocus()
}

footer: ToolBar {
    id: bottomToolbar
}
}
