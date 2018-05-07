#!/Users/stefanosmitropoulos/anaconda3/bin/python
from sys import argv
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sn

if argv[1] == 'help' or argv[1] == 'h':
    print("Usage: First paramter is either a string or a number. "
          "In case of a string, provide a .txt file with the "
          "following format: [attributes]\\t[classnumber]. "
          "A classifier will be built from the file.\n"
          "In case of a number, a pretrained classifier will be loaded. "
          "Use ")

if argv[1] == 'live':
    from sklearn.externals import joblib
    classifier = joblib.load('CART_Classifier.pkl')
    file_handle = open('/Users/stefanosmitropoulos/Developer/C++ Programming/decisionTreeHumanClassifier /build/Debug/demo_real_time/ouput.txt', 'r')
    lines_list = file_handle.readlines()
    # Extract dimensions from first line. Cast values to integers from strings.
    X_test=[]

    for row in lines_list:

        x=[]
        for j in row:
            x.append(j)

        x=x[:-1]
        X_test.append(x)

    # Feature Scaling
    from sklearn.preprocessing import StandardScaler
    sc = StandardScaler()
    #X_test = sc.fit_transform(X_test)
    #X_test = sc.transform(X_test)
    y_pred = classifier.predict(X_test)
    print("Specimen of class ",y_pred[0])



if argv[1].isalpha():

    print ("Processing...")
    # This opens a handle to your file, in 'r' read mode
    #file_handle = open(sys.argv[1], 'r')
    file_handle = open('set.txt', 'r')
    # Read in all the lines of your file into a list of lines
    lines_list = file_handle.readlines()
    # Extract dimensions from first line. Cast values to integers from strings.
    data=[]
    classnumber=[]

    for row in lines_list:

        x=[]
        for j in row:
            x.append(j)

        y=x[-2]
        x=x[:-3]
        data.append(x)
        classnumber.append(y)

    #data=np.append(data,x,axis=0)

    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(data,
            classnumber, test_size = 0.25, random_state = 0)


    # Feature Scaling
    from sklearn.preprocessing import StandardScaler
    sc = StandardScaler()
    X_train = sc.fit_transform(X_train)
    X_test = sc.transform(X_test)

    # Fitting Decision Tree Classification to the Training set
    from sklearn.tree import DecisionTreeClassifier
    classifier = DecisionTreeClassifier(criterion = 'entropy', random_state = 0)
    classifier.fit(X_train, y_train)

    ##Save the classifier
    #from sklearn.externals import joblib
    #joblib.dump(classifier, 'filename.pkl')

    # Predicting the Test set results
    y_pred = classifier.predict(X_test)

    # Making the Confusion Matrix
    from sklearn.metrics import confusion_matrix
    cm = confusion_matrix(y_test, y_pred)

    print(cm)

    accuracy = float(cm[0,0]+cm[1,1]) / len(y_test)

    print("Accuracy is ",round(accuracy*100,2),"%")

    df_cm = pd.DataFrame(cm, index = [i for i in ("1","0")],
                      columns = [i for i in ("1","0")])
    plt.figure(figsize = (5,3))
    sn.heatmap(df_cm, annot=True)

else:

    from sklearn.externals import joblib
    classifier = joblib.load('CART_Classifier.pkl')
    #CREATE X_test
    y_pred = classifier.predict(X_test)
    print("Specimen of class ",y_pred[0])




