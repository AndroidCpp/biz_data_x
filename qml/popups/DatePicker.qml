import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Qt.labs.calendar 1.0
import QtQuick.Controls.Material 2.0
import "../common"

Popup {
    id: datePickerRoot
    property date selectedDate: new Date()
    property int displayMonth: selectedDate.getMonth()
    property int displayYear: selectedDate.getFullYear()
    property int calendarWidth: isLandscape? parent.width * 0.70 : parent.width * 0.80
    property int calendarHeight: isLandscape? parent.height * 0.90 : parent.height * 0.80
    property bool isOK: false

    x: (parent.width - calendarWidth) / 2
    y: (parent.height - calendarHeight) / 2
    implicitWidth: calendarWidth
    implicitHeight: calendarHeight

    topPadding: 0
    leftPadding: 0
    rightPadding: 0

    GridLayout {
        id: calendarGrid
        // column 0 only visible if Landscape
        columns: 3
        // row 0 only visible if Portrait
        rows: 5
        width: datePickerRoot.calendarWidth
        height: datePickerRoot.calendarHeight

        Pane {
            id: portraitHeader
            visible: !isLandscape
            padding: 0
            Layout.columnSpan: 2
            Layout.column: 1
            Layout.row: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: primaryColor
            }
            ColumnLayout {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 6
                Label {
                    topPadding: 12
                    leftPadding: 24
                    font.pointSize: 18
                    text: datePickerRoot.displayYear
                    color: textOnPrimary
                    opacity: 0.8
                }
                Label {
                    leftPadding: 24
                    bottomPadding: 12
                    font.pointSize: 36
                    text: Qt.formatDate(datePickerRoot.selectedDate, "ddd")+", "+Qt.formatDate(datePickerRoot.selectedDate, "d")+". "+Qt.formatDate(datePickerRoot.selectedDate, "MMM")
                    color: textOnPrimary
                }
            }
        } // portraitHeader

        Pane {
            id: landscapeHeader
            visible: isLandscape
            padding: 0
            Layout.column: 0
            Layout.row: 0
            Layout.rowSpan: 5
            Layout.fillWidth: true
            Layout.fillHeight: true
            background: Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: primaryColor
            }
            ColumnLayout {
                spacing: 6
                Label {
                    topPadding: 12
                    leftPadding: 24
                    rightPadding: 24
                    font.pointSize: 18
                    text: datePickerRoot.displayYear
                    color: textOnPrimary
                    opacity: 0.8
                }
                Label {
                    leftPadding: 24
                    rightPadding: 24
                    font.pointSize: 36
                    text: Qt.formatDate(datePickerRoot.selectedDate, "ddd")
                    color: textOnPrimary
                }
                Label {
                    leftPadding: 24
                    rightPadding: 24
                    font.pointSize: 36
                    text: Qt.formatDate(datePickerRoot.selectedDate, "d")+"."
                    color: textOnPrimary
                }
                Label {
                    leftPadding: 24
                    rightPadding: 24
                    font.pointSize: 36
                    text: Qt.formatDate(datePickerRoot.selectedDate, "MMM")
                    color: textOnPrimary
                }
            }
        } // landscapeHeader

        ColumnLayout {
            id: title
            Layout.columnSpan: 2
            Layout.column: 1
            Layout.row: 1
            Layout.fillWidth: true
            spacing: 6
            RowLayout {
                height: implicitHeight * 2
                spacing: 6
                ButtonFlat {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    text: "<"
                    textColor: Material.foreground
                    onClicked: {
                        if(datePickerRoot.displayMonth > 0) {
                            datePickerRoot.displayMonth --
                        } else {
                            datePickerRoot.displayMonth = 11
                            datePickerRoot.displayYear --
                        }
                    }
                }
                Label {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 3
                    text: monthGrid.title
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                }
                ButtonFlat {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    text: ">"
                    textColor: Material.foreground
                    onClicked: {
                        if(datePickerRoot.displayMonth < 11) {
                            datePickerRoot.displayMonth ++
                        } else {
                            datePickerRoot.displayMonth = 0
                            datePickerRoot.displayYear ++
                        }
                    }
                }
            } // row layout title
        } // title column layout

        DayOfWeekRow {
            Layout.column: 2
            Layout.row: 2
            rightPadding: 24
            Layout.fillWidth: true
            font.bold: false
            opacity: 0.4
        } // day of weeks


        WeekNumberColumn {
            id: weekNumbers
            Layout.column: 1
            Layout.row: 3
            Layout.fillHeight: true
            leftPadding: 24
            month: datePickerRoot.displayMonth
            year: datePickerRoot.displayYear
            font.bold: false
            opacity: 0.4
        } // WeekNumberColumn


        MonthGrid {
            id: monthGrid
            Layout.column: 2
            Layout.row: 3
            Layout.fillHeight: true
            Layout.fillWidth: true
            rightPadding: 24

            month: datePickerRoot.displayMonth
            year: datePickerRoot.displayYear


            onClicked: {
                // Important: check the month to avoid clicking on days outside where opacity 0
                if(date.getMonth() == datePickerRoot.displayMonth) {
                    datePickerRoot.selectedDate = date
                } else {
                    console.log("outside valid month "+date.getMonth())
                }
            }

            delegate: Label {
                id: dayLabel
                readonly property bool selected: model.day === datePickerRoot.selectedDate.getDate()
                                                 && model.month === datePickerRoot.selectedDate.getMonth()
                                                 && model.year === datePickerRoot.selectedDate.getFullYear()
                text: model.day
                font.bold: model.today? true: false
                opacity: model.month === monthGrid.month ? 1 : 0
                color: pressed || selected ? textOnPrimary : model.today ? Material.accent : Material.foreground
                minimumPointSize: 8
                fontSizeMode: Text.Fit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                background: Rectangle {
                    anchors.centerIn: parent
                    width: Math.min(parent.width, parent.height) * 1.2
                    height: width
                    radius: width / 2
                    color: primaryColor
                    visible: pressed || parent.selected
                }
            } // label in month grid
        } // month grid


        ColumnLayout {
            Layout.column: 2
            Layout.row: 4
            id: footer
            Layout.fillWidth: true
            RowLayout {
                ButtonFlat {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    text: qsTr("Today")
                    textColor: accentColor
                    onClicked: {
                        datePickerRoot.selectedDate = new Date()
                        datePickerRoot.displayMonth = datePickerRoot.selectedDate.getMonth()
                        datePickerRoot.displayYear = datePickerRoot.selectedDate.getFullYear()
                    }
                } // cancel button
                ButtonFlat {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    text: qsTr("Cancel")
                    textColor: primaryColor
                    onClicked: {
                        datePickerRoot.close()
                    }
                } // cancel button
                ButtonFlat {
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1
                    text: qsTr("OK")
                    textColor: primaryColor
                    onClicked: {
                        datePickerRoot.isOK = true
                        datePickerRoot.close()
                    }
                } // ok button
            }
        } // footer buttons
    } // grid layout
    onOpened: {
        datePickerRoot.isOK = false
    }
} // popup calendar
