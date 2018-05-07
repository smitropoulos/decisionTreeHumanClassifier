# GMM - Decision Tree Classifier

Step 1: Create binary images with the Mixture of Gaussians background subtractor.

Step 2: Choose (manually) which images belong to what class.

Step 3: Process the blobs and prepare a train/test set.

Step 4: Train and evaluate the classifier.

#### This has been compiled and linked using Xcode 9.3 on High Sierra with openCV 3.4.1:
-lopencv_videoio 
-lopencv_video 
-lopencv_photo 
-lopencv_imgproc 
-lopencv_imgcodecs 
-lopencv_highgui 
-lopencv_features2d 
-lopencv_core 
-lopencv_imgcodecs 

#### If you want to use the python script, make sure it is in your executable's dir and is chmod +x


## _An overview of the ML workflow_
![](https://i.imgur.com/cfUv4RR.png)

The complete manuscript can be found in https://www.researchgate.net/publication/322499866_Adaptive_computer_vision_algorithm_for_human_recognition_in_traffic_scenes
