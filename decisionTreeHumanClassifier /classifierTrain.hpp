//
//  classifierTrain.hpp
//  decisionTreeHumanClassifier 
//
//  Created by Stefanos Mitropoulos on 05/05/2018.
//  Copyright © 2018 Stefanos Mitropoulos. All rights reserved.
//

#ifndef classifierTrain_hpp
#define classifierTrain_hpp

#include <stdio.h>
#include "wizard.hpp"
#include "opencv2/opencv.hpp"


void classifierTrain(params& par);
void classifierLive(cv::Mat tempImage);

#endif /* classifierTrain_hpp */
