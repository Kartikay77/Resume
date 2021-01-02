df<-read.csv("C:/Users/Dell/Desktop/HeartHealthPrediction-master/heart.csv")
df$Thal<-factor(df$Thal,levels =c("fixed","normal","reversable"),labels =  c(0,1,2))
df$ChestPain<-factor(df$ChestPain,levels =c("typical","asymptomatic","nonanginal","nontypical"),labels =  c(0,1,2,3))
library(ggplot2)
library(caret)#FOR SVM
library(dplyr)
library(ISLR)#FOR DESICION TREE

#data visulization

x_matrix<- data.matrix(df)
x_heatmap<- heatmap(x_matrix, Rowv=NA, Colv=NA, scale="column", margins=c(5,10))
x_heatmap<- heatmap(x_matrix, Rowv=NA, Colv=NA, col = cm.colors(256),scale="column", margins=c(5,10))
df
summary(df)
sum(is.na(df))
df[is.na(df)] = 0
is.na(df)
pairs(df,lower.panel=NULL)
plot(x = df$Age,y = df$MaxHR,
     xlab = "Age",
     ylab = "MaxHeartRate",
     xlim = c(20,100),
     ylim = c(50,200),		 
     main = "Age vs MaxHeartRate",
     pch=0:1
     
     
)
points(df$Age[df$Target=='0'],df$MaxHR[df$Target=='0'],col="blue")
points(df$Age[df$Target=='1'],df$MaxHR[df$Target=='1'],col="red")
legend("topright",legend = c("Disease","No Disease"), col = c("red","blue"),pch = 0:1)


library(corrgram)
corrgram(df)

boxplot(df)



str(df)
df[df$Sex == 0,]$Sex <- "F"
df[df$Sex == 1,]$Sex <- "M"
df$Sex<- as.factor(df$Sex)
df$ChestPain<- as.factor(df$ChestPain)
df$Fbs<- as.factor(df$Fbs)
df$RestECG<- as.factor(df$RestECG)
df$ExAng<- as.factor(df$ExAng)
df$Slope<-as.factor(df$Slope)
df$Thal<-as.factor(df$Thal)
df$Target<-ifelse(test=df$Target == 0, yes="Healthy" , no="Unhealthy")
df$Target<- as.factor(df$Target)
str(df)
xtabs(~ Target + Sex , data = df)
xtabs(~ Target + ChestPain , data = df)
xtabs(~ Target + Fbs , data = df)
xtabs(~ Target + RestECG , data = df)

anyNA(df)



#splitting in taining and testing
set.seed(3033)
intrain<-createDataPartition(y=df$Target, p=0.75, list = FALSE)
training<-df[intrain, ]
testing<-df[-intrain, ]

dim(training)
dim(testing)

tC<-trainControl(method = "repeatedcv", number = 10, repeats = 3)

#Logistic Regression 
lr<-glm(Target ~., data=training , family = binomial(link="logit"))

lrp<-predict(lr,newdata=testing)
lrp
table(lrp,testing$Target)



#SupportVectorMachine
svm_linear<-train(Target~.,data = training, method="svmLinear", trControl=tC, preProcess =c("center","scale"),tuneLength=10)
svm_linear

        #prediction
tp<-predict(svm_linear, newdata = testing)
tp
confusionMatrix(table(tp, testing$Target ))


#DecisionTreeClassifier
library(rpart)
dtc_fit <- rpart(Target~., data = training)
dtc_fit
        #prediction
predict_dtc <-predict(dtc_fit, newdata=testing, type = 'class')
predict_dtc
confusionMatrix(predict_dtc, testing$Target )





#RandomForestClassifier
library(randomForest)
rf<-randomForest(Target~.,data = training)
rf
rf_predict<-predict(rf, newdata = testing, type = 'class')
rf_predict
confusionMatrix(rf_predict, testing$Target )



#neural network 
str(training)
training$Sex<-as.numeric(training$Sex)
training$ChestPain<-as.numeric(training$ChestPain)

training$RestECG<-as.numeric(training$RestECG)

training$Slope<-as.numeric(training$Slope)
training$Thal<-as.numeric(training$Thal)
training$Target<-as.numeric(training$Target)
library(neuralnet)
training$Target<-factor(training$Target,levels = c(1,2) , labels = c(0,1))
training$ExAng<-factor(training$ExAng,levels = c(1,2) , labels = c(0,1))
training$Fbs<-factor(training$Fbs,levels = c(1,2) , labels = c(0,1))

training$ExAng<-as.numeric(training$ExAng)
training$Fbs<-as.numeric(training$Fbs)
training[is.na(training)] = 0
NN=neuralnet(Target~., data=training , hidden = c(4,2),threshold=0.01)
NN


str(testing)
testing$Sex<-as.numeric(testing$Sex)
testing$ChestPain<-as.numeric(testing$ChestPain)

testing$RestECG<-as.numeric(testing$RestECG)

testing$Slope<-as.numeric(testing$Slope)
testing$Thal<-as.numeric(testing$Thal)
testing$Target<-as.numeric(testing$Target)
testing$Target<-factor(testing$Target,levels = c(1,2) , labels = c(0,1))
testing$ExAng<-factor(testing$ExAng,levels = c(1,2) , labels = c(0,1))
testing$Fbs<-factor(testing$Fbs,levels = c(1,2) , labels = c(0,1))

testing$ExAng<-as.numeric(testing$ExAng)
testing$Fbs<-as.numeric(testing$Fbs)
testing$Target<-as.numeric(testing$Target)
testing[is.na(testing)] = 0
NN_predict<-predict(NN, newdata = testing, type = 'class')
NN_predict
confusionMatrix(NN_predict, testing$Target )
plot(NN)

