import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import CompPhys.World 1.0

Viewport  {
    id: rootViewport

    width: 1280
    height: 720

    fillColor: "black"
    blending: true
    fovzoom: false

    light: Light {
        ambientColor: Qt.rgba(1,1,1,1)
        position.x: 0
        position.y: 1
        position.z: 0
        linearAttenuation: 0.08
    }

    camera: Camera {
        id: myCamera
        eye: Qt.vector3d(0,1,0)
        center: Qt.vector3d(1,1,0)
        nearPlane: 1
        farPlane: 5000
    }

    World {
        id: world
    }

    Keys.onPressed: {
        if(event.key === Qt.Key_P) {
            multiSphere.hasPeriodicCopies = !multiSphere.hasPeriodicCopies
        }
    }
}
