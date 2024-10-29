#!/usr/bin/env python

import time, sys
import numpy as np
import traceback

HLP_MSG = """
PARSE20Q
--------
Parses a log file from the 20Q (20 Questions) experiment.

Usage:

  parse20q.py <log_file> <condtions_file>

where:

  log_file: a log from the 20Q app.

  conditions_file: a text file indicating the condition of
     each numbered trial. A conditions file looks like this:

     +---------------------+
     | 1    Experimental   |
     | 2    Control        |
     | 3    Experimental   |
     | ...  ...            |
     +---------------------+
"""

FIELD_NAMES = ["Trial_ID", "File", "Object",  "Condition",
               "Trial_Start", "Trial_End", "Trial_Duration", "Trial_Accuracy",
               # Questions
               "Question_ID", "Question_Order", "Question", "True_Answer", "Sender_Answer",
               "Sender_Answered_Guessed", "Receiver_Answer",
               "TMS_Intensity", "Question_Start", "Question_End",
               "Question_Duration", "Question_Accuracy"]

STRING_FORMAT = "%Y-%m-%dT%H:%M:%S"

def parse_date( string ):
    date, msecs = string.split(".")
    return time.mktime(time.strptime( date, STRING_FORMAT )) + float("0.%s" % msecs)

def print_time( tme ):
    ms = (tme % 1)
    ms = "%03d" % int(ms * 1000)
    return time.strftime("%Y-%m-%d,%H:%M:%S.",
                         time.localtime(tme)) + ms

# Standardize a string
#
def standardize( string ):
    """Makes all strings standard"""
    string = string.strip()
    string = string.strip("?!")
    string = string.translate(None, ".,:':")
    return string.title()

class Trial(object):
    """A 20Q Trial"""
    def __init__(self, filename):
        self.file = filename
        self.answer = None
        self.true_answers = None
        self._questions = []
        self.id = 0
        self.condition = "Experimental"
        self._accuracy = None
        self._start_time = 0
        self._end_time = 0
        self.duration = None

    @property
    def questions(self):
        return self._questions

    @questions.setter
    def questions(self, lst):
        """Sets the internal questions"""
        if len(lst) > 0:
            self._questions = lst
            self.end_time = lst[-1].end_time
            self.load_true_answers()
            #print self.true_answers
            for q in self._questions:
                q.answer = self.true_answers[standardize(q.question)]

    @property
    def start_time(self):
        """Returns the start time"""
        return self._start_time

    @start_time.setter
    def start_time(self, tme):
        """Sets the start time and, if possible, calculates the duration"""
        self._start_time = tme
        if (self.end_time > 0):
            self.duration = self.end_time - tme

    @property
    def end_time(self):
        """Returns the end time"""
        return self._end_time

    @end_time.setter
    def end_time(self, tme):
        """Sets the end time and, if possible, calculates the duration"""
        self._end_time = tme
        if (self.start_time > 0):
            self.duration = tme - self.start_time

        
    @property
    def accuracy(self):
        if len(self.questions) > 0:
            accs = [x.accuracy for x in self.questions]
            return np.mean(accs)
        else:
            return None

    def load_true_answers(self):
        """Reads the true answers from the corresponding file"""
        if self.file != None and self.answer != None:
            lines = file(".." + self.file, "r").readlines()
            lines = [x.strip().split("\t") for x in lines]
            questions = [standardize(x) for x in lines[0][1:]]
            #print "Questions: ", questions
        
            answers = [x for x in lines[1:]
                       if standardize(x[0]) == standardize(self.answer)]

            if len(answers) != 1:
                print "More than one object found!! %s" % answers
                #print lines
                #print self.answer
                sys.exit(0)
                
            answers = [standardize(x) for x in answers[0][1:]]
            self.true_answers = dict(zip(questions, answers))
            #print self.true_answers

    def as_row(self):
        """returns this trial as three rows of data (one per question)"""
        general = (self.id, self.file, self.answer, self.condition,
                   print_time(self.start_time), print_time(self.end_time),
                   self.duration, self.accuracy)
        general_string = "%d\t%s\t%s\t%s\t%s\t%s\t%0.3f\t%0.3f\t" % general
        rows = [x.as_row() for x in self.questions]
        return [general_string + row for row in rows] 
    
class Question(object):
    """A 20Q question"""
    def __init__(self, question):
        self.question = question
        self.answer = None            # The "true" answer
        self.sender_answer = None     # The sender's response
        self.sender_answer_guessed = False   
        self.receiver_answer = None   # The receiver's understanding 
        self.tms_intensity = 0        # True intensity of the TMS pulse
        self.id = 0
        self.number = 0
        self._accuracy = None
        self._start_time = 0
        self._end_time = 0
        self.duration = 0

    @property
    def accuracy(self):
        if self.sender_answer is not None and self.receiver_answer is not None:
            self.compute_accuracy()
            return self._accuracy
        else:
            return None
        
    def compute_accuracy(self):
        if self.sender_answer == self.receiver_answer:
            self._accuracy = 1
        else:
            self._accuracy = 0

            
    @property
    def start_time(self):
        """Returns the start time"""
        return self._start_time

    
    @start_time.setter
    def start_time(self, tme):
        """Sets the start time and, if possible, calculates the duration"""
        self._start_time = tme
        if (self.end_time > 0):
            self.duration = self.end_time - tme

            
    @property
    def end_time(self):
        """Returns the end time"""
        return self._end_time

    
    @end_time.setter
    def end_time(self, tme):
        """Sets the end time and, if possible, calculates the duration"""
        self._end_time = tme
        if (self.start_time > 0):
            self.duration = tme - self.start_time

            
    def as_row(self):
        """Returns the data as a text row"""
        data = (self.id, self.order, self.question, self.answer, self.sender_answer,
                self.sender_answer_guessed, self.receiver_answer,
                self.tms_intensity, print_time(self.start_time),
                print_time(self.end_time),
                self.duration, self.accuracy)

        str = "%d\t%d\t%s\t%s\t%s\t%s\t%s\t%d\t%s\t%s\t%0.3f\t%0.3f"
        return str % data

            
def timestamped_log_entry(txt):
    """Checks whether a line is a 'normal', timestamped log entry"""
    try:
        parse_date(txt[0:23])
        return True
    except Exception as e:
        return False

    
def parse_log_file(filename, control_trials=[]):
    """Parses the log file line by line"""
    fin = file(filename, 'r')

    trial = None      # Current trial
    question = None   # Current question
    trials = []       # List of trials
    questions = []    # (Partial) list of questions

    # Counters
    trial_counter = 1
    question_counter = 1

    line_counter = 0
    
    for line in fin.xreadlines():

        line_counter += 1
        line = line.strip()
        #print("Parsing line %d" % line_counter)
        try:
            if timestamped_log_entry(line):
                #print("Timestamped!")
                # If the event has a timestamp, it's one of the
                # "regular" events
            
                time = parse_date(line[0:23])  # Server date
                message = line[60:]            # Logged message
            
                # The script logic: examines each log entry
                # and decides whatb to do (brutal, but efficient)

                
                # * THE FILE BEING USED: <FILEPATH> *
                #
                # This is the entry that marks the beginning of a new
                # trial; it corresponds to the moment the Receiver selects
                # a list.
                
                if message.startswith("The file being used"):
                    #print("New trial")
                    filename = message.split(":")[1]   # The list file name
                    filename = filename.strip()        # ...stripped

                    # If an existing trial is open, we need to save it first
                    
                    if trial != None:
                        questions.append(question)    # Add any open question
                        trial.questions = questions   # Add the questions
                        trials.append(trial)          # Add the trials to the list

                    # Resets the questions 
                    questions = []
                    question = None
                
                    # Creates a new trial
                    trial = Trial(filename)
                    trial.id = trial_counter

                    if trial_counter in control_trials:
                        trial.condition = "Control"

                    # Updates the counter
                    trial_counter += 1 

                # * ANSWER IS: <OBJECT>
                #
                # This is the message logged when the software selects a random
                # object from the list. This marks the beginning of the trial.
                #
                elif message.startswith("Answer is"):
                    if trial is not None:
                        answ = message[10:].strip()
                        trial.answer = answ
                        trial.start_time = time
                        
                    else:
                        raise Exception("Answer without new trial: '%s'" % message)

                # * ASKING QUESTION: <QUESTION>? *
                #
                # This is the log entry for the moment the Receiver selects the
                # question. This is the begnning of a question cycle.
                #
                elif message.startswith("Asking question"):
                    qstn = message.split(":")[1].strip()

                    #print("New question created @ %d: %s" % (line_counter, qstn))
                    if question is not None:
                        questions.append(question)
                    
                    question = Question(qstn)
                    question.id = question_counter
                    question_counter += 1
                    question.order = len(questions) + 1
                    question.start_time = time

                # * [NEGATIVE | POSITIVE] SIGNAL DETECTED, TRIGGERING TMS *
                #
                # These are the entries for the moment in which the sender has
                # made an identifiable "Yes/No" answer.
                #  
                elif message.startswith("Negative signal detected"):
                    question.sender_answer = "No"

                elif message.startswith("Positive signal detected"):
                    question.sender_answer = "Yes"

                # * [NEGATIVE | POSITIVE] ANSWER RECEIVED *
                #
                # These are the entries for the moment in which the
                # receiver responds Yes or No to the question
                # "Have you seen a flash of light?". This entry marks the
                # end of the Question cycle.
                # 
                elif message.startswith("Negative answer received"):
                    question.receiver_answer = "No"
                    question.end_time = time

                elif message.startswith("Positive answer received"):
                    question.receiver_answer = "Yes"
                    question.end_time = time

                # * TMS INTENSITY = <INTENSITY> *
                #
                # This is the server entry taking note of the final value
                # of the stimulation intensity.
                # 
                elif message.startswith("TMS intensity"):
                    intns = int(message.split("=")[1])
                    question.tms_intensity = intns
    
            # If the entry has no timestamp, then it must be one of the
            # two possible "notational" marks: Either "Run #X Started" or
            # "Chose closest target". Only the second one is of interest. 
            else:
                if line == "Chose closest target" and question is not None:
                    question.sender_answer_guessed = True
    

        except Exception as e:
            print """Error: %s @ line %d ("%s")""" % (e, line_counter, line)
            traceback.print_exc(e)
            sys.exit(0)

    # End of the log file; save the remaining questions
    questions.append(question)
    trial.questions = questions
    trials.append(trial)
    return trials
    



def parse_trial_description(filename):
    """Parses a trial description"""
    conditions = []
    with open(filename, "r") as f:
        for line in f.xreadlines():
            if len(line.strip()) > 0:
                trial_num, condition = line.strip().split()
                conditions.append((int(trial_num), condition))

    return conditions

def save_table(trials, filename="trials.txt"):
    """Saves the trials as a table file"""
    pass



## If this code is used as a script

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(HLP_MSG)
    else:
        log_file = sys.argv[1]
        trial_description = sys.argv[2]

        trials = parse_log_file(log_file)
        conditions = parse_trial_description(trial_description)

        for num, cond in conditions[0 : len(trials) - 1]:
            t = [x for x in trials if x.id == num]
            t[0].condition = cond

        header = ""
        for f in FIELD_NAMES[:-1]:
            header += "%s\t" % f
        header += "%s" % FIELD_NAMES[-1]
        print(header)

        for trial in trials:
            for row in trial.as_row():
                print(row)
                
