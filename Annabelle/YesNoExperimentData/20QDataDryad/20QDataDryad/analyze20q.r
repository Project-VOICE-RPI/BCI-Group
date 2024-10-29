## ---------------------------------------------------------------- ##
## 20Q --- Data analysis script for "Playing 20 Questions with
## the mind" by Stocco et al.
## ---------------------------------------------------------------- ##
## The paper describes the results of Brain-to-brain interface (BBI)
## where a "Respondent" (sender) and an "Inquirer" (receiver)
## play a variant of the 20 Question game.  
## ---------------------------------------------------------------- ##
## This files details the data processing and analysis procedures
## that were used in the published paper. It also includes the code
## to generate Figures 4 and 5 of the published manuscript.
## ---------------------------------------------------------------- ##


## Loads the packages
library(ROCR)        # For ROC analysis
library(infotheo)    # for mutual information
library(compute.es)  # For effect sizes
library(pwr)         # Power calculations
library(car)         # For Levene's test
library(gtools)      # Various graphs
#source('functions.R')   # personalized functions

## Load the data. Data from each experiment's logfile has already
## been preprocessed and transformed into an easy-to-read 
## tabular format. The original logfiles can be find in the
## corresponding directories---they are the filenames with a 
## trailing ".log" extension.

pair1 <- read.table("./Pair1/pair1_results.txt", header=T, sep="\t")
pair2 <- read.table("./Pair2/pair2_results.txt", header=T, sep="\t")
pair3 <- read.table("./Pair3/pair3_results.txt", header=T, sep="\t")
pair4 <- read.table("./Pair4/pair4_results.txt", header=T, sep="\t")
pair5 <- read.table("./Pair5/pair5_results.txt", header=T, sep="\t")

# Creates a special factor to store the pair each dataset is 
# associated with.

pair1$Pair <- "Pair 1"
pair2$Pair <- "Pair 2"
pair3$Pair <- "Pair 3"
pair4$Pair <- "Pair 4"
pair5$Pair <- "Pair 5"

# Merges the data into a single big dataframe.

data <- merge(pair1, pair2, all=T)
data <- merge(data, pair3, all=T)
data <- merge(data, pair4, all=T)
data <- merge(data, pair5, all=T)

# Additional factors need to be created to facilitate ROC analysis
# as supported by the ROCR package. In particular, the ROCR package
# assumes numeric vectors as inputs. In signal detection jargon,
# the vector answers are considered "Signals".  We consider three
# vector signals (1) The "True" signal, i.e. the ideal responses to
# the questions; (2) The "Sender" signal, i.e. the responses given
# by the Respondent (Sender); and eventually (3) The "Receiver" signal,
# that is, the responses as interpreted by the Receiver. 
# The following code generates these three vectors from the list of
# "Yes"/"No" answers in the "data" dataframe.
 
data$TrueSignal <- 0
data$SenderSignal <- 0
data$ReceiverSignal <- 0
data$TrueSignal[data$True_Answer=="Yes"] <- 1
data$SenderSignal[data$Sender_Answer=="Yes"] <- 1
data$ReceiverSignal[data$Receiver_Answer=="Yes"] <- 1

## ---------------------------------------------------------------- ##
## 1. Analysis of Guesses
## ---------------------------------------------------------------- ##
## The most straightforward way to analyze the data --- just counts
## how many mystery objects were correctly guessed by each pair.
## ---------------------------------------------------------------- ##

# First, calculate the number of correct answers for each question.
# (Note that an error could be made by either the Sender or the Receiver)
 
data$CorrectGuess <- 1 * !mapply("xor", data$TrueSignal, data$ReceiverSignal)

# Aggregate by trials. Each trial is a complete 20Q Game.
 
trials <- aggregate(data[c("CorrectGuess")], list(Condition=data$Condition, TrialID=data$Trial_ID, Pair=data$Pair), mean)

# Now calculate how many trials were answered correctly (e.g., accuracy of 1 across all
# the thee question-and-answer cycle) 
trials$CorrectFinalAnswer <- trials$CorrectGuess
trials$CorrectFinalAnswer[trials$CorrectFinalAnswer < 1] <- 0

# A few stats: Mean, SD etc.
tapply(trials$CorrectGuess, list(Pair=trials$Pair, Condition=trials$Condition), mean)
tapply(trials$CorrectFinalAnswer, list(Pair=trials$Pair, Condition=trials$Condition), mean)
tapply(trials$CorrectFinalAnswer, list(Pair=trials$Pair, Condition=trials$Condition), sum)

# Aggregate by pair (1-5) and condition (Exp vs. Control)
guesses <- aggregate(trials[c('CorrectFinalAnswer')], list(Pair=trials$Pair, Condition=trials$Condition), sum)
guesses <- as.data.frame(guesses)

# Boxplot
boxplot(CorrectFinalAnswer~Condition, guesses, ylim=c(0,10), main="Correct Guesses", xlab="Conditions", ylab="Num of Correct Guesses", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=1.25, col="black", lwd=2, lty=2)

leveneTest(guesses$CorrectFinalAnswer, guesses$Condition)  # Test for unequal variances
shapiro.test(guesses$CorrectFinalAnswer[guesses$Condition=="Control"])  # Normal distribution
shapiro.test(guesses$CorrectFinalAnswer[guesses$Condition=="Experimental"])  # Normal distribution

# Data is normal and variance are comaprable; runs a T-test to see significant effects.
t.test(CorrectFinalAnswer~Condition, paired=T, data=guesses)

# Calcuates effects sizes, based on t-test value.
tes(13.5, n.1=5, n.2=5)

# Analysis of AUC

## ---------------------------------------------------------------- ##
## 1. ROC Analysis
## ---------------------------------------------------------------- ##
## A more complex analysis of performance. See Fawcett (2006) for a 
## complete introduction to ROC analysis. 
## ---------------------------------------------------------------- ##

## We need to define a few functions to easily access some ROC
## performance measures, which are stored in the "performance" class
## of te ROCR package.

roc.auc<-function(a, b) {
	prediction <- prediction(a, b)
	performance <- performance(prediction, "auc")
	performance@y.values[[1]]
}

acc.auc<-function(a, b) {
	prediction <- prediction(a, b)
	performance <- performance(prediction, "auc")
	performance@acc
}

# An extension of "apply" that works on binary functions.
binary.apply <- function(data, var1, var2, FUN="roc.auc") {
	nc <- length(unique(data$Condition))
	np <- length(unique(data$Pair))
	result = expand.grid(Pair=unique(data$Pair), Condition=unique(data$Condition))
	result$AUC <- 0
	for (c in unique(data$Condition)) {
		for (p in unique(data$Pair)) {
			sub <- subset(data, data$Pair == p & data$Condition == c)
			result$AUC[result$Pair == p & result$Condition == c ] <- do.call(FUN, list(sub[[var1]], sub[[var2]]))
		}
	}
	result
}

# AUC for receivers
rec.auc <- binary.apply(data, "ReceiverSignal", "SenderSignal")
t.test(AUC~Condition, rec.auc, paired=T)   # Significant difference between Exp and Control conditions
t.test(rec.auc$AUC[rec.auc$Condition=="Experimental"], mu=0.5)  # Experimental > chance
t.test(rec.auc$AUC[rec.auc$Condition=="Control"], mu=0.5)  # Control ~~ Chance
#boxplot(AUC~Condition, rec.auc, paired=T, ylim=c(0.5,1))

# AUC for senders
send.auc <- binary.apply(data, "SenderSignal", "TrueSignal")
t.test(AUC~Condition, send.auc, paired=T)   # No difference between Exp and Control conditions
t.test(send.auc$AUC[send.auc$Condition=="Experimental"], mu=0.5)  # Experimental > chance
t.test(send.auc$AUC[send.auc$Condition=="Control"], mu=0.5)  # Control > Chance

# AUC for pairs
pair.auc <- binary.apply(data, "ReceiverSignal", "TrueSignal")

# Test for parametric test assumptions
leveneTest(pair.auc$AUC, pair.auc$Condition)  # Test for unequal variances, F = 0.05, p > 0.82
shapiro.test(pair.auc$AUC[pair.auc$Condition=="Control"])  # Normal distribution, W = 0.84, p = 0.16
shapiro.test(pair.auc$AUC[pair.auc$Condition=="Experimental"])  # Normal distribution, W = 0.89, p = 0.34

# Proceed with T test
t.test(AUC~Condition, pair.auc, paired=T)   # Sign difference between Exp and Control conditions
t.test(pair.auc$AUC[pair.auc$Condition=="Experimental"], mu=0.5)  # Experimental > chance
t.test(pair.auc$AUC[pair.auc$Condition=="Control"], mu=0.5)  # Control > Chance

# Calcuates effects sizes, based on t-test value.
tes(11.93, n.1=5, n.2=5)  # Effect size


## ---------------------------------------------------------------- ##
## 3. Mutual Information
## ---------------------------------------------------------------- ##
## A conservative way to calculate the amount of information (in bits)
## That has been transferred along the BBI between respondents and 
## inquireres. 
## ---------------------------------------------------------------- ##

# MI for pairs
pair.mi <- binary.apply(data, "ReceiverSignal", "TrueSignal", FUN="mutinformation")
names(pair.mi)[3] <- "MI"
pair.mi$MI <- natstobits(pair.mi$MI) * 30

# Test for parametric test assumptions
leveneTest(pair.mi$MI, pair.mi$Condition)  # Test for unequal variances, F = 2.73, p > 0.13
shapiro.test(pair.mi$MI[pair.mi$Condition=="Control"])  # Normal distribution, W = 0.78, p = 0.06
shapiro.test(pair.mi$MI[pair.mi$Condition=="Experimental"])  # Normal distribution, W = 0.99, p = 0.98

# Not great, let's sq.root:
leveneTest(sqrt(pair.mi$MI), pair.mi$Condition)  # Test for unequal variances, F = 0.14, p > 0.71
shapiro.test(sqrt(pair.mi$MI)[pair.mi$Condition=="Control"])  # Normal distribution, W = 0.82, p = 0.12
shapiro.test(sqrt(pair.mi$MI)[pair.mi$Condition=="Experimental"])  # Normal distribution, W = 0.99, p = 0.98

# Proceed with t-test on sqrt data
t.test(sqrt(MI)~Condition, pair.mi, paired=T)   # No difference between Exp and Control conditions
t.test(sqrt(pair.mi$MI)[pair.mi$Condition=="Experimental"], mu=0)  # Experimental > chance
t.test(sqrt(pair.mi$MI)[pair.mi$Condition=="Control"], mu=0)  # Control > Chance

# Effect size 
tes(8.30, n.1=5, n.2=5)

# Follow-up analysis: Mutual Information for senders and receivers
# separately.   

# MI for receivers
rec.mi <- binary.apply(data, "ReceiverSignal", "SenderSignal", FUN="mutinformation")
names(rec.mi)[3] <- "MI"
rec.mi$MI <- natstobits(rec.mi$MI) * 30
t.test(MI~Condition, rec.mi, paired=T)   # Significant difference between Exp and Control conditions
t.test(rec.mi$MI[rec.mi$Condition=="Experimental"], mu=0)  # Experimental > chance
t.test(rec.mi$MI[rec.mi$Condition=="Control"], mu=0)  # Control ~ Chance

# MI for senders
send.mi <- binary.apply(data, "SenderSignal", "TrueSignal", FUN="mutinformation")
names(send.mi)[3] <- "MI"
send.mi$MI <- natstobits(send.mi$MI) * 30
t.test(MI~Condition, send.mi, paired=T)   # No difference between Exp and Control conditions
t.test(send.mi$MI[send.mi$Condition=="Experimental"], mu=0)  # Experimental > chance
t.test(send.mi$MI[send.mi$Condition=="Control"], mu=0)  # Control > Chance

## ---------------------------------------------------------------- ##
## 4. Data visualization and figures.
## ---------------------------------------------------------------- ##
## A conservative way to calculate the amount of information (in bits)
## That has been transferred along the BBI between respondents and 
## inquireres. 
## ---------------------------------------------------------------- ##

plot.roc <- function(pairnum=1, type="", data=NULL) {	
	par(mar=c(3,3,2,2))
	if (is.null(data)) {
		pair <- paste("Pair", pairnum, sep="")
		file <-  paste("./", pair, "/pair", pairnum, "_results.txt", sep="")
		data <- read.table(file, header=T, sep="\t")
	} else  {
		data <- subset(data, data$Pair == paste("Pair", pairnum))
	}
	data$TrueSignal <- 0
	data$SenderSignal <- 0
	data$ReceiverSignal <- 0
	data$TrueSignal[data$True_Answer=="Yes"] <- 1
	data$SenderSignal[data$Sender_Answer=="Yes"] <- 1
	data$ReceiverSignal[data$Receiver_Answer=="Yes"] <- 1

	experiment <- subset(data, data$Condition=="Experimental")
	control <- subset(data, data$Condition=="Control")

	if (type %in% c("Receiver","Inquirer")) {
		exp_prediction <- prediction(experiment$ReceiverSignal, experiment$SenderSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$ReceiverSignal, control$SenderSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")
		
	} else if (type %in% c("Sender", "Respondent")) {
		exp_prediction <- prediction(experiment$SenderSignal, experiment$TrueSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$SenderSignal, control$TrueSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")
	} else {
		exp_prediction <- prediction(experiment$ReceiverSignal, experiment$TrueSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$ReceiverSignal, control$TrueSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")

	}

	plot(x=c(0, exp_performance@x.values[[1]][2], 1), y=c(0, exp_performance@y.values[[1]][2], 1), type="l", col="red", lwd=2, main=paste(type, paste("Pair", pairnum)))
	grid()
	polygon(x=c(0, exp_performance@x.values[[1]][2], 1, 1), y=c(0, exp_performance@y.values[[1]][2], 1, 0), col="#EE111144")
		
	polygon(x=c(0, con_performance@x.values[[1]][2], 1, 1), y=c(0, con_performance@y.values[[1]][2], 1, 0), col="#99999988")
		
	lines(x=exp_performance@x.values[[1]], y=exp_performance@y.values[[1]], col="red", lwd=3)
		
	lines(x=con_performance@x.values[[1]], y=con_performance@y.values[[1]], col="grey50", lwd=3)
		
	mtext(side=1, text="False Positive Rate", line=2, cex=par("cex"))	
	mtext(side=2, text="True Positive Rate", line=2, cex=par("cex"))
	legend(legend=c("Experimental", "Control"), x="bottomright", bty="n", col=c("red", "grey50"), lwd=3)

}


plot.all.rocs <- function() {
	for (i in c(1,2,3,4,5)) {
		#for (j in c("Sender", "Receiver", "")) {
		for (j in c("Respondent", "Inquirer", "")) {
			pdf(paste("Pair", i, "/", j, "Pair", i, ".pdf", sep=""), width=3, height=3)
			plot.roc(i, j)
			dev.off()
		}
	}
}


figure4 <- function() {
	layout(matrix(1:3, ncol=3, byrow=T), widths= c(1, 1, 1), heights=c(1, 1, 1))
	par(mar=c(3,4,3,2))
	
	plot.new()
	plot.window(xlim=c(0, 1), ylim=c(-0.5, 10), fg="grey55", col.axis="grey55", col.lab="grey55")
	axis(2)
	axis(1, at=c(0.2, 0.8), labels=c("Control", "Experimental"))
	for (pair in unique(guesses$Pair)) {
		lines(x=c(0.2, 0.8), y=guesses$CorrectFinalAnswer[guesses$Pair==pair], col="#55555544", lwd=1, lty=1)
		points(x=c(0.2, 0.8), y=guesses$CorrectFinalAnswer[guesses$Pair==pair], pch=18, col="#55555544", bg="#22222288", lwd=1, lty=1)	
	}
	ms <- tapply(guesses$CorrectFinalAnswer, guesses$Condition, mean)
	ses <- tapply(guesses$CorrectFinalAnswer, guesses$Condition, se)
	
	#lines(x=c(0.2, 0.8), y=ms, col="#FF000088", lwd=2, lty=1)
	points(x=c(0.2, 0.8), y=ms, pch=21, col=c("#00000088", "#FF000088"), bg=c("#00000088", "#FF000088"), lwd=2, lty=3, cex=1.5)
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms + ses), col=c("#00000088", "#FF000088"), lwd=1.5, lty=1, angle=90, length=0.05)	
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms - ses), col=c("#00000088", "#FF000088"), lwd=1.5, lty=1, angle=90, length=0.05)
	
	abline(h=1.25, col="black", lwd=2, lty=3)
	box(bty="O", col="grey75")
	title(main="(A)\nCorrect Guesses", ylab="Number of Correct Guesses")
		
	pair.auc <- pair.auc[order(pair.auc$Condition),]

	plot.new()
	plot.window(xlim=c(0, 1), ylim=c(0.475, 1), fg="grey55", col.axis="grey55", col.lab="grey55")
	axis(2)
	axis(1, at=c(0.2, 0.8), labels=c("Control", "Experimental"))
	for (pair in unique(pair.auc$Pair)) {
		lines(x=c(0.2, 0.8), y=pair.auc$AUC[pair.auc$Pair==pair], col="55555544", lwd=1, lty=1)
		points(x=c(0.2, 0.8), y=pair.auc$AUC[pair.auc$Pair==pair], pch=18, col="55555544", bg="55555544", lwd=1, lty=1)	
	}
	ms <- tapply(pair.auc$AUC, pair.auc$Condition, mean)
	ses <- tapply(pair.auc$AUC, pair.auc$Condition, se)
	
	#lines(x=c(0.2, 0.8), y=ms, col="#FF000088", lwd=2, lty=1)
	points(x=c(0.2, 0.8), y=ms, pch=21, col=c("#00000088", "#FF000088"), bg=c("#00000088", "#FF000088"), lwd=2, lty=3, cex=1.5)
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms + ses), col=c("#00000088", "#FF000088"), lwd=2, lty=1, angle=90, length=0.05)	
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms - ses), col=c("#00000088", "#FF000088"), lwd=2, lty=1, angle=90, length=0.05)
	
	#abline(h=0, col="black", lwd=1)
	abline(h=0.5, col="black", lwd=2, lty=3)
	box(bty="O", col="grey55")
	title(main="(B)\n Area Under the Curve", ylab="Area Under the ROC Curve")
	
	pair.mi <- pair.mi[order(pair.mi$Condition),]

	plot.new()
	plot.window(xlim=c(0, 1), ylim=c(-1.5, 30), fg="grey55", col.axis="grey55", col.lab="grey55")
	axis(2)
	axis(1, at=c(0.2, 0.8), labels=c("Control", "Experimental"))
	for (pair in unique(pair.auc$Pair)) {
		lines(x=c(0.2, 0.8), y=pair.mi$MI[pair.mi$Pair==pair], col="55555544", lwd=1, lty=1)
		points(x=c(0.2, 0.8), y=pair.mi$MI[pair.mi$Pair==pair], pch=18, col="55555544", bg="22222288", lwd=1, lty=1)	
	}
	ms <- tapply(pair.mi$MI, pair.mi$Condition, mean)
	ses <- tapply(pair.mi$MI, pair.mi$Condition, se)
	
	points(x=c(0.2, 0.8), y=ms, pch=21, col=c("#000000", "#FF0000"), bg=c("#00000088", "#FF000088"), lwd=2, lty=3, cex=1.5)
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms + ses), col=c("#00000088", "#FF000088"), lwd=2, lty=1, angle=90, length=0.05)	
	arrows(x0=c(0.2, 0.8), y0=ms, x1=c(0.2, 0.8), y1=(ms - ses), col=c("#00000088", "#FF000088"), lwd=2, lty=1, angle=90, length=0.05)
	
	abline(h=0, col="black", lwd=2, lty=3)
	box(bty="O", col="grey55")
	title(main="(C)\nMutual Information", ylab="Total Number of Bits")
}

figure5 <- function() {
	par(fg="grey50")
	layout(matrix(1:3, nrow=1, byrow=T), widths= c(1, 1, 1), heights=c(1))
		
	# Subplot 1: Pairs 
	plot.new()
	plot.window(xlim=c(0,1), y=c(0,1))
	axis(1, col="grey50", fg="grey50", at=seq(0, 1, 1/2))
	axis(2, col="grey50", fg="grey50")
	box(bty="o", col="grey50")
	#grid()
	for (pair in sort(unique(data$Pair))) {
		#text(x=1/2, y=1/2, adj=c(1,1)/2, labels=c(pair), font=2, cex=1.*par("cex.main"))
		
		# Experimental condition, runs 
		experiment <- subset(data, data$Condition == "Experimental" & data$Pair == pair)

		#Control condition
		control <- subset(data, data$Condition == "Control" & data$Pair == pair)

		# 1. Data, given the Target as truth and the Sender's shots as prediction
		
		exp_prediction <- prediction(experiment$ReceiverSignal, experiment$TrueSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$ReceiverSignal, control$TrueSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")

		lines(x=exp_performance@x.values[[1]], y=exp_performance@y.values[[1]], col="#FF000044", lwd=0.75, lty=1)
		lines(x=con_performance@x.values[[1]], y=con_performance@y.values[[1]], col="#33333344", lwd=0.75, lty=1)
		points(x=c(exp_performance@x.values[[1]][2]), y=c(exp_performance@y.values[[1]][2]), pch=21, col="red", bg="#FF000044", cex=1.5)
		points(x=c(con_performance@x.values[[1]][2]), y=c(con_performance@y.values[[1]][2]), pch=21, col="#333333", bg="#22222233", cex=1.5)

	}
	title(main="(A)\nROC Pairs", xlab="False Positive Rate", ylab="True Positive Rate")	
	legend(legend=c("Experimental", "Control"), x="bottomright", bty="n", pch=21, col=c("red", "#333333"), bg=c("#FF000044", "#22222233"), lwd=1)
	
	# Subplot 2: The Respondents 
	
	plot.new()
	plot.window(xlim=c(0,1), y=c(0,1))
	axis(1, col="grey50", fg="grey50", at=seq(0, 1, 1/2))
	axis(2, col="grey50", fg="grey50")
	box(bty="o", col="grey50")
	for (pair in sort(unique(data$Pair))) {
		# Experimental condition, runs 
		experiment <- subset(data, data$Condition == "Experimental" & data$Pair == pair)

		#Control condition
		control <- subset(data, data$Condition == "Control" & data$Pair == pair)

		# 2. Data, given the Target as truth and the BCI input as prediction

		exp_prediction <- prediction(experiment$SenderSignal, experiment$TrueSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$SenderSignal, control$TrueSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")
		
		lines(x=exp_performance@x.values[[1]], y=exp_performance@y.values[[1]], col="#FF000044", lwd=0.75, lty=1)
		lines(x=con_performance@x.values[[1]], y=con_performance@y.values[[1]], col="#33333344", lwd=0.75, lty=1)
		points(x=c(exp_performance@x.values[[1]][2]), y=c(exp_performance@y.values[[1]][2]), pch=21, col="red", bg="#FF000044", cex=1.5)
		points(x=c(con_performance@x.values[[1]][2]), y=c(con_performance@y.values[[1]][2]), pch=21, col="#333333", bg="#22222233", cex=1.5)

		
	}
	
	title(main="(B)\nROC Respondents", xlab="False Positive Rate", ylab="True Positive Rate")

	# Subplot 3: The inquirers

	plot.new()
	plot.window(xlim=c(0,1), y=c(0,1))
	axis(1, col="grey50", fg="grey50", at=seq(0, 1, 1/2))
	axis(2, col="grey50", fg="grey50")
	box(bty="o", col="grey50")
	for (pair in sort(unique(data$Pair))) {
		# Experimental condition, runs 
		experiment <- subset(data, data$Condition == "Experimental" & data$Pair == pair)

		#Control condition
		control <- subset(data, data$Condition == "Control" & data$Pair == pair)

		# 3. Data, given the BCI pulse as truth and the fire response as prediction

		exp_prediction <- prediction(experiment$ReceiverSignal, experiment$SenderSignal)
		exp_performance <- performance(exp_prediction, "tpr", "fpr")

		con_prediction <- prediction(control$ReceiverSignal, control$SenderSignal)
		con_performance <- performance(con_prediction, "tpr", "fpr")

		lines(x=exp_performance@x.values[[1]], y=exp_performance@y.values[[1]], col="#FF000044", lwd=0.75, lty=1)
		lines(x=con_performance@x.values[[1]], y=con_performance@y.values[[1]], col="#33333344", lwd=0.75, lty=1)
		points(x=c(exp_performance@x.values[[1]][2]), y=c(exp_performance@y.values[[1]][2]), pch=21, col="red", bg="#FF000044", cex=1.5)
		points(x=c(con_performance@x.values[[1]][2]), y=c(con_performance@y.values[[1]][2]), pch=21, col="#333333", bg="#22222233", cex=1.5)

	} 
	
	title(main="(C)\nROC Inquirers",  xlab="False Positive Rate", ylab="True Positive Rate")	
}


# Generates various boxplots
plot.boxplots <- function() {
	pdf("Guesses.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(CorrectFinalAnswer~Condition, guesses, ylim=c(0,10), main="Correct Guesses", xlab="Conditions", ylab="Num of Correct Guesses", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=1.25, col="black", lwd=2, lty=2)	
	dev.off()

	pdf("AUC_pairs.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(AUC~Condition, pair.auc, ylim=c(0, 1), main="Area Under ROC Curve\n(Pairs)", xlab="Conditions", ylab="Area Under Curve", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()

	pdf("AUC_respondents.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(AUC~Condition, send.auc, ylim=c(0, 1), main="Area Under ROC Curve\n(Respondents)", xlab="Conditions", ylab="Area Under Curve", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()

	pdf("AUC_inquirers.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(AUC~Condition, rec.auc, ylim=c(0, 1), main="Area Under ROC Curve\n(Inquirers)", xlab="Conditions", ylab="Area Under Curve", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()

	
	pdf("MI_pairs.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(MI~Condition, pair.mi, ylim=c(0, 30), main="Mutual Information\n(Pairs)", xlab="Conditions", ylab="Number of Bits", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()
	
	pdf("MI_respndents.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(MI~Condition, send.mi, ylim=c(0, 30), main="Mutual Information\n(Respondents)", xlab="Conditions", ylab="Number of Bits", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()
	
	pdf("MI_inquirers.pdf", width=3, height=3)
	par(mar=c(3,4,2,1))
	boxplot(MI~Condition, pair.mi, ylim=c(0, 30), main="Mutual Information\n(Inquirers)", xlab="Conditions", ylab="Number of Bits", col=c("grey", "red"), border=c("grey25", "darkred"))
abline(h=0, col="black", lwd=2, lty=2)	
	dev.off()
}



