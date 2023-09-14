High Level Design of Solution

Document Parser
Has a pointer to IndexHandler because it needs to access the same IndexHandler from all the classes which later 
on my Interface class gives the documentParsers a indexHandler
Reads every document in JSon it them fills all three of my trees (words,organization,and persons) using the 
Index Handler object which gives the documentParser the ability to fill the trees since my three Avltrees are 
declared there Has a function called readstopswrods that fills my unordered set of strings of 
stopwords which is then used for my stop words since it unordedset has very useful functions and the 
lookup of things using a unordered hasmap is 0(1)


Query Processor
Has a pointer to IndexHandler because it needs to access the same IndexHandler from all the classes
Translator for the index handler of what it needs
Parser function is where all the magic happens where it takes the whole query in as a string and 
takes it apart and sees what the user wants to query. I have if else statements within the parser 
function to take into account all possible queries that can be submitted. Like PERSON:.. ORG…
To find insection of documents i first sort the documents based on the relevancy then set intersection 
if the query is more than one word
If it is just one word it finds the documents associated with that word only
the part where i take into part the ‘-’ not include those documents i just simply erase those documents
I have calcweight functions for each setofDocuments which sets the weight for each document
Also have a removespaces functions that returns a vector of unsigned int that are the index of the - when 
wanting to give a persons first and last name or more than one organization name instead of spaces users 
will be prompted to type their query with - acting as a space


Index Handler
Stores all three of my AvlTrees of words,organizations, and persons which then are templeted to contain a string 
and an unordered map that contains a two int the key is the docID and the value is the for keeping track of the 
occurrence. Also has a unordered_map of int as the key and DocumentContents object which holds the 
title,author,and all the necessary information needed.
It has all the necessary function needed for filling up each individual tree like insertPersons and InsertWords etc..
Also function for getting the documents for a certain person/word/orgs of a string that is passed
It also has my read and write to persistence specifically inside the Indexhandler because it needs access 
to all three trees because in AvlTree.h i manipulated some functions within it that allows me to print all 
the contents needed for each AvlNode Also having a int which is the totalnodes in words tree which will 
be helpful for displaying the statistics of unique words in words tree


InterFace
Has a pointer to IndexHandler and creates a new Indexhandler that is passed into Documennt and IndexHandler so that they all are connected to one IndexHandler
This is where the menu is showcased with 7 options to choose from
Option 1 will create a index of the users desire in which they will type the filename they want to create a index by making a DocumenetParser object and passing in the file to parse
Option 2 will read from the persistence but persistence file must be made in order to do this
Option 3 will write to persistence of 4 separate files conating documents,words,persons,and Orgs by calling the IndexHandler object and calling those functions in IndexHandler to write to persistence
Option 4 is for searching for a query which then will take that string that the user types and pass it to parser function within the QueryProcessor and parse the query accordingly giving back the documents associated with the query

AvlTree
Has all the basic of what is need for the tree like the insert,empty,conatins, search,find, functions that was given. I will obviously change the implementation of the tree to work for strings as such but will use the AvlTree that was given
Made it double templeted so that i can have more than just a tree holding a string i needed to be able to store docid and occurrences
Also added function like setcurr hasNext and such and all those function are used for reading and writing to persistence because I was not going to change my structure of the AvlTree so did it that way
AvlNode
It is double templeted so that each node can carry whatever the user makes the tree to be about very useful and very general for usage of any user


Used Data Structures

Document Parser
Main important part is that i used an orderedset of strings to hold my stop words which some people could 
have used a vector if they wanted to use that instead.I used a unorderedset of strings because the use of 
the hash table making the big oh notation O(1) and the unordered set of strings makes it to where i can find 
things within it alot easier. Could say that i used a pointer to a IndexHander Object so that all of 
my classes could be using the same IndexHandler Object whenever the Interface and made a new instance 
of an IndexHandler object and passed it to any of the classes that was using a IndexHandler object 
so that everyone could be on the same page

Query Processor
This also used the pointer to the IndexHanler Object so that everyone is accessing the same 
object which is passed in by the Interface same as the any class that used the pointer to an IndexHandler Object.
Had a vector of DocumentContents Objects called results which was used for storing the results of the 
documents that return when finding the documents of the query

IndexHandler
First off the IndexHandler has three Avltree which are then used to make an AvlTree of a string which 
holds the word and a unordered map of two ints. The first int being the DocId which is used for 
the unordered map I have of documents. They go hand and hand so that i can get the the right documents 
for the right doc id. But the first int is the docId which is the key and second int is for the occurrence. 
The use of the map gave me the ability to linked docid with documentContents object which have literally all 
the information like text,title, and such things but being able to map the docid with not only the documents 
associated with it but also being able to keep up with the occurrences


Interface
Just has a pointer to IndexHandler which is then copied and passed to documnetParser and 
Querry so that everyone is using the same IndexHandler Object


AvlTree/AvlNode
Made it double templated so that the AvlNode itself could hold more then just a string 
because we are needed more info and more storage then just a string so that was very much needed.



User Documentation
Whenever you want to enter a query of a PERSON: and its more than just their first name you need to not 
use a space to separate first and last name but use a - so like for example PERSON:elijah-posiulai
Also when wanting to create an Index you need to first give the path that you want for creating an 
Index like ../sample_data
Sample Query
When making an Index for only the sample_data that had the six json files this is the query results of “sales”:
Article 1: BRIEF-Francesca’s Sees Q4 2017 GAAP Earnings Per Share $0.07 To $0.11
2018-02-28T05:29:00.000+02:00
Reuters Editorial
Article 2: BRIEF-Kewaunee Scientific Q3 Earnings Per Share $0.31
2018-02-28T08:59:00.000+02:00
Reuters Editorial
Article 3: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​
2018-02-28T04:00:00.000+02:00
Reuters Editorial
Select what article you would like the text for 1-3 or if not type 0
Query results for “sales scientific”
Article 1: BRIEF-Kewaunee Scientific Q3 Earnings Per Share $0.31
Publication: 2018-02-28T08:59:00.000+02:00
Author: Reuters Editorial
Query results for “sales PERSON:strax-ab”
Article 1: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​
Publication: 2018-02-28T04:00:00.000+02:00
Author: Reuters Editorial


Three of these query search give back the proper documents which for sales it gave all the documents 
ranked from best to last using relevancy and for “sales scientific” it gave back the intersection of 
those documents and for “sales PERSON:strax-ab” it gave back the intersection of those documents also 
notice how their is no spaces for first and last name it has the ‘-’ to replace the space because thats 
how my query takes things in



Performance

Timing for creating the Index for 300,000+ files took 878 seconds which is 14.63 minitues.

Automatic Test and Memory Test
Test for AVlTree functions
I tested the insert functions to make sure that it would insert the word and the document name 
which was a vector of strings since in Testing i declared my tree to have a string and a vector<string>. 
After the insert functions i tested the contains function to see after insert it if it continued the word 
i just inserted and it did. As well as testing the make empty and


Test for AvlTree memory leaks
-Valgring showed no memory leaks for example when running Valgrind with meme check on clion it 
said nothing to show which means no memory leaks

Test for indexer
-I made function to print out the AvlTree after indexing to make sure that the tree 
was filled with the right things and it was

Test for the complete system
-I timed with my phone and with my chrono to see how long it would take to create an 
index with 300,000+ files and they were the same. I also cout the number of files that it was
indexing and I believe it was around 307,000 files which is very accurate and what should be the 
amount of files Indexed








Timeline

Task
Planned Completion
Actual Completion
Time Spent in Hours
AvlTree/Node
November 8
November 12
10
IndexHandler
November 12
November 28
15
DocumentParser
November 18
November 28
15
QueryProcessor
November 25
December 2
12
InterFace
November 28
December 4
5
Documentation
Dec 2
December 4
2




