#!/Users/stefanosmitropoulos/anaconda3/bin/python
import sys
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sn

print ("Processing...")
# This opens a handle to your file, in 'r' read mode
file_handle = open(sys.argv[1], 'r')
#file_handle = open('set.txt', 'r')
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

