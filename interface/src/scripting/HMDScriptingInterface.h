//
//  HMDScriptingInterface.h
//  interface/src/scripting
//
//  Created by Thijs Wenker on 1/12/15.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_HMDScriptingInterface_h
#define hifi_HMDScriptingInterface_h

#include <QtScript/QScriptValue>

#include <GLMHelpers.h>

class QScriptContext;
class QScriptEngine;


class HMDScriptingInterface : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool magnifier READ getMagnifier)
    Q_PROPERTY(bool active READ isHMDMode)
    Q_PROPERTY(float ipd READ getIPD)

public:
    static HMDScriptingInterface& getInstance();
    
    static QScriptValue getHUDLookAtPosition2D(QScriptContext* context, QScriptEngine* engine);
    static QScriptValue getHUDLookAtPosition3D(QScriptContext* context, QScriptEngine* engine);

public slots:
    void toggleMagnifier();

private:
    HMDScriptingInterface() = default;
    bool getMagnifier() const;
    bool isHMDMode() const;
    float getIPD() const;

    bool getHUDLookAtPosition3D(glm::vec3& result) const;
};

#endif // hifi_HMDScriptingInterface_h
