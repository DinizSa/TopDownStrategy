//
//  AudioPlayer.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class AudioPlayer {
protected:
    int audioPlayerId;
public:
    AudioPlayer(){
        static int nextAudioPlayerId = 0;
        audioPlayerId = nextAudioPlayerId;
        nextAudioPlayerId++;
    }
};
