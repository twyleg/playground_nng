// Copyright (C) 2022 twyleg
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "./items"

Window {
	id: window

	width: 640
	height: 480
	visible: true
	title: qsTr("Stopwatch")

	color: "black"

//	signal startStopButtonClicked
//	signal resetButtonClicked

	Item {
		id: dialItem

		anchors.fill: parent

		Dial {
			id: dial

			anchors.centerIn: parent
			diameter: Math.min(parent.width, parent.height)
		}
	}
}
