//
//  AudioInjectorManager.h
//  libraries/audio/src
//
//  Created by Stephen Birarda on 2015-11-16.
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#pragma once

#ifndef hifi_AudioInjectorManager_h
#define hifi_AudioInjectorManager_h

#include <queue>
#include <mutex>

#include <QtCore/QPointer>
#include <QtCore/QThread>

#include <DependencyManager.h>

class AudioInjector;
using InjectorQPointer = QPointer<AudioInjector>;
using TimeInjectorPointerPair = std::pair<uint64_t, InjectorQPointer>;
using InjectorQueue = std::queue<TimeInjectorPointerPair>;

class AudioInjectorManager : public QObject, public Dependency {
    Q_OBJECT
    SINGLETON_DEPENDENCY
public:
    ~AudioInjectorManager();
private slots:
    void run();
private:
    bool threadInjector(AudioInjector* injector);
    void restartFinishedInjector();
    void addInjectorToQueue(AudioInjector* injector);
    
    AudioInjectorManager() {};
    AudioInjectorManager(const AudioInjectorManager&) = delete;
    AudioInjectorManager& operator=(const AudioInjectorManager&) = delete;
    
    void createThread();
    
    QThread* _thread { nullptr };
    bool _shouldStop { false };
    InjectorQueue _injectors;
    std::mutex _injectorsMutex;
    std::condition_variable _injectorReady;
    
    friend class AudioInjector;
};

#endif // hifi_AudioInjectorManager_h
