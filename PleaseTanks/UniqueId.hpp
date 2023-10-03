//
//  UniqueId.h
//  PleaseTanks
//
//  Created by Diniz Sá on 03/10/2023.
//

#pragma once

class UniqueId {
private:
    static int uniqueIdCounter;
protected:
    int uniqueId = 1;
    UniqueId() {
        uniqueId = UniqueId::uniqueIdCounter;
        UniqueId::uniqueIdCounter++;
    }
}
int UniqueId::uniqueIdCounter = 1;
