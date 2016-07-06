// ekke (Ekkehard Gentz) @ekkescorner
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

import "../pages"
import "../common"

Page {
    id: navPage
    property alias depth: navPane.depth
    property string name: "OrderNavPage"
    // index to get access to Loader (Destination)
    property int myIndex: index

    StackView {
        id: navPane
        anchors.fill: parent
        property string name: "OrdersNavPane"
        focus: true

        initialItem: OrdersPage{}

        Loader {
            id: orderListPageLoader
            active: false
            visible: false
            source: "../pages/OrderListPage.qml"
            onLoaded: {
                navPane.push(item)
            }
        }

        function pushOrderListPage() {
            orderListPageLoader.active = true
        }
        function popOnePage() {
            var page = pop()
            if(page.name == "OrderListPage") {
                orderListPageLoader.active = false
                return
            }
        }


    } // navPane

    FloatingActionButton {
        visible: navPane.depth == 1
        property string imageName: dataManager.orderPropertyList.length == 0 ? "/add.png" : "/list.png"
        z: 1
        anchors.margins: 16
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        imageSource: "qrc:/images/"+iconOnPrimaryDarkFolder+imageName
        backgroundColor: primaryDarkColor
        onClicked: {
            if(dataManager.orderPropertyList.length == 0) {
                // navPane.pushNextPage()
            } else {
                navPane.pushOrderListPage()
            }
        }
    } // FAB

    // triggered from BACK KEY
    function goBack() {
        navPane.popOnePage()
    }

    Component.onDestruction: {
        cleanup()
    }

    function init() {
        console.log("INIT OrderNavPane")
    }
    function cleanup() {
        console.log("CLEANUP OrderNavPane")
    }

} // navPage
