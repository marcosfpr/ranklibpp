#include <iostream>

#include "RankLib.h"

#include <memory>

using std::shared_ptr;

int main() {
    try{
        shared_ptr<DataPoint> dp(new DataPoint("0 qid:9 1:0.12669249302743557 2:0.04972683037778472 3:0.030740317368190363 4:0.04913259249099099 5:0.030939496114630673 6:0.012714688705947316 7:0.0 8:0.0 9:0.0157837238620372 10:0.0 11:0.0 12:0.0 13:0.0 # m/10002008-charly 11"));
        
        std::cout << "Hello, DataPoint:\n" << dp->toString() << std::endl;

        sample_t samples;
        samples.push_back(dp);

        RankList rl(samples);

        std::cout << "Hello, RankList: " << rl.toString();
    }
    catch(RankLibError* e){
        std::cout << e->what();
    }
    
    
    return 0;
}
