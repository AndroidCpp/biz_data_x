// ekke (Ekkehard Gentz) @ekkescorner
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0
import org.ekkescorner.data 1.0
import "../common"

Page {
    id: orderListPage
    property string name: "OrderListPage"
    bottomPadding: 24
    topPadding: 16

    // HEADER
    Component {
        id: headerComponent
        // placed the header controls inside a ToolBar
        // otherwise the header whill shine through to list content
        // while scrolling with ListView.OverlayHeader
        ToolBar {
            width: parent.width
            // default stackorder of 1 doesn't work
            z:2
            // here we set the background to list background
            background: Rectangle{color: Material.background}
            // now header controls work as expected
            ColumnLayout {
                width: parent.width
                RowLayout {
                    spacing: 20
                    Layout.fillWidth: true
                    LabelSubheading {
                        leftPadding: 24
                        rightPadding: 12
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Order Info")
                        opacity: secondaryTextOpacity
                        wrapMode: Label.WordWrap
                        font.italic: true
                        font.bold: true
                    } // label order
                    LabelSubheading {
                        Layout.fillWidth: false
                        leftPadding: 12
                        rightPadding: 24
                        text: qsTr("Express Delivery")
                        opacity: secondaryTextOpacity
                        wrapMode: Label.WordWrap
                        font.italic: true
                        font.bold: true
                    } // label express
                } // end Row Layout
                HorizontalListDivider{}
            } // end Col Layout
        } // toolbar
    } // header component
    // SECTION HEADER
    Component {
        id: sectionHeading
        ToolBar {
            width: parent.width
            // using z 1 because section header must under list header
            z:1
            background: Rectangle{color: Material.background}
            ColumnLayout {
                width: parent.width
                LabelSubheading {
                    topPadding: 6
                    bottomPadding: 6
                    leftPadding: 24
                    text: Qt.formatDate(section, Qt.DefaultLocaleLongDate)
                    anchors.verticalCenter: parent.verticalCenter
                    color: primaryColor
                }
                HorizontalListDivider{}
            } // col layout
        } // toolbar
    }

    // LIST ROW
    Component {
        id: orderRowSwipeComponent
        SwipeDelegate {
            id: rowDelegate
            width: parent.width
            height: dataColumn.implicitHeight
            padding: 0
            text: " "
            down: pressed || swipe.complete

            onClicked: {
                if(swipe.complete) {
                    console.log("NOW REMOVE")
                    // listModel.remove(index)
                    return
                }
                if(swipe.position == 0) {
                    listView.currentIndex = index
                    navPane.pushOrderDetail(index)
                    return
                }
            }

            // hint: if using without SwipeDelegate move onClicked code
            // inside a MouseArea at leftColumn
            // TODO set dataColumn directly as contentItem (not yet because of a bug mentioned by J-P)
            ColumnLayout {
                id: dataColumn
                parent: rowDelegate.contentItem
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                RowLayout {
                    spacing: 20
                    Layout.fillWidth: true
                    Item {
                        id: leftColumn
                        Layout.preferredWidth: 1
                        Layout.fillWidth: true
                        // important to get height resized automatically if remakrs is changed from elsewhere
                        implicitHeight: threeLabels.implicitHeight
                        ColumnLayout {
                            id: threeLabels
                            width: parent.width
                            spacing: 6
                            LabelBody {
                                topPadding: 6
                                leftPadding: 24
                                rightPadding: 12
                                text: model.modelData.customerAsDataObject.name + ", " + model.modelData.customerAsDataObject.city
                                wrapMode: Label.WordWrap
                                font.bold: true
                            } // label
                            LabelBody {
                                visible: model.modelData.remarks.length > 0
                                leftPadding: 24
                                rightPadding: 12
                                text: model.modelData.remarks
                                wrapMode: Label.WordWrap
                            } // label
                            LabelBodySecondary {
                                leftPadding: 24
                                rightPadding: 12
                                text: "Nr: " + model.modelData.nr + qsTr(", Positions: ") + model.modelData.positionsPropertyList.length
                                wrapMode: Label.WordWrap
                            } // label
                        } // 3 label rows in left column
                    } // leftColumn
                    // right column: because left column fills all available space
                    // the switch is at the right side
                    SwitchWithLeftLabel {
                        leftPadding: 12
                        rightPadding: 12
                        text: qsTr("Express")
                        checked: model.modelData.expressDelivery
                        onCheckedChanged: {
                            model.modelData.expressDelivery = checked
                        }
                    } // switch express
                } // end Row Layout
                HorizontalListDivider{}
            } // end Col Layout


            swipe.behind:
                Label {
                Layout.fillWidth: true
                text: "Remove"
                color: "white"
                width: parent.width
                height: parent.height
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                background: Rectangle {
                    color: Material.color(Material.Red, rowDelegate.pressed ? Material.Shade800 : Material.Shade500)
                }
            }

            ListView.onRemove: SequentialAnimation {
                PropertyAction { target: rowDelegate; property: "ListView.delayRemove"; value: true }
                NumberAnimation { target: rowDelegate; property: "height"; to: 0; easing.type: Easing.InOutQuad }
                PropertyAction { target: rowDelegate; property: "ListView.delayRemove"; value: false }
            }
        }


    } // orderRowSwipeComponent

    // LIST VIEW
    ListView {
        id: listView
        focus: true
        clip: true
        // highlight: Rectangle {color: Material.listHighlightColor }
        currentIndex: -1
        anchors.fill: parent
        // setting the margin to be able to scroll the list above the FAB to use the Switch on last row
        bottomMargin: 40
        // QList<Order*>
        model: dataManager.orderPropertyList

        delegate: orderRowSwipeComponent // orderRowComponent
        header: headerComponent
        // in Landscape header scrolls away
        // in protrait header always visible
        headerPositioning: isLandscape? ListView.PullBackHeader : ListView.OverlayHeader

        section.property: "orderDate"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

        ScrollIndicator.vertical: ScrollIndicator { }
    } // end listView

    Component.onDestruction: {
        cleanup()
    }

    // called immediately after Loader.loaded
    function init() {
        console.log(qsTr("Init done from OrderListPage"))
    }
    // called from Component.destruction
    function cleanup() {
        console.log(qsTr("Cleanup done from OrderListPage"))
    }
} // end primaryPage
