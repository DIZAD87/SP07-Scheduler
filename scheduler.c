//Libraries
  #include <string.h> //Used for strlen
  #include <stdio.h> //Used for standard io
  #include <stdlib.h> //Used for atoi and exit(0)
  #include <malloc.h> //Used for malloc
  #include <stdbool.h> //Used for bool
  #include <unistd.h> //Used for sleeping

//Function prototypes
  struct node* createList();
  struct node* scanList(struct node* endPointerEntry);
  struct node* removeCurrent(struct node* currentPointerEntry);
  void add(int pidEntry, int timerEntry, struct node* endPointerEntry);
  void printList(struct node* endPointerEntry);
  bool isEmpty();

//Global variables
  //Master node
    struct node
      {//Start of startNode
        int pid;
        int timer;
        struct node *next;
      };//End of startNode

  //Other Variables
    int i, j, k;
    int processCount = 0;

//Functions
  //Main function(s)
    int main()
      {//Start of main
         //Notify START
           printf("\n*************************START************************\n");
	   printf("***********************SCHEDULER**********************\n");
         //IMPORTANT! Create and scan the list
	   scanList(createList());
         //Notify END 
	   printf("**************************END*************************\n");
           return 0;
      }//End of main

  //Auxiliary function(s)
    struct node* createList()
      {//Start of createList
       //Variables
         FILE *fp;
         int split = 0;
         int charMax = 1000;
         char pidString[charMax];
         char timerString[charMax];
         char line[charMax];
         char* filename = "test1.txt";
	 struct node *currentPointer;
	 struct node *startNode;
         struct node *endPointer;
       //Notify START
         printf("******************PART I: CREATE LIST*****************\n");
       //Open the file
         fp = fopen(filename, "r"); //Read-only
       //If file did not open successfully...
         if(fp == NULL)
           {//start of if
             printf("ERROR! File could not be opened!");
           }//end of if
       //If file opened successfully...
         else
           {//Start of master else
	    //Extract the file information
              while(fgets(line, charMax, fp) != NULL)
                {//Start of while fgets
	         //Reset split
		   split = 0;
	         //Separate the pidString and timerString
	           for(i = 0; i < strlen(line); i++)
 	             {//Start of for 
	              //Split at the space
	                if(line[i] == 32) //ASCII#32 is a space
	                  {//Start of if
		            split = 1;
		            pidString[i] = '\0';
		          }//End of if
		      //If splitting 1st string, then its a pidString
	                if(split == 0)
		          {//Start of if
		            pidString[i] = line[i];
		          }//End of if
                      //If splitting 2nd string, then its a timerString
	                else if(split == 1)
		          {//Start of else if
	                    timerString[i - strlen(pidString)] = line[i + 1]; //+1 to account for space
	                  }//End of else if
	             }//End of for
	         //Close the timerString string
		   timerString[i] = '\0';
	         //Add the node(after the extraction is complete)
	           //Increase the processCount
                     processCount++;
	           //If it's the 1st node...
	             if (processCount == 1)
	               {//start of if
	                //Set the space for this new startNode
	                  startNode = malloc(sizeof(struct node));
                        //Assign the values to this new startNode
	                  (*startNode).next = startNode; //Set first one to itself
	                  (*startNode).pid = atoi(pidString);
	                  (*startNode).timer = atoi(timerString);
 	                  endPointer = startNode; //Connect the endPointer to the startNode
	                }//End of if
	           //If it's a remaining node...
	             else
	               {//Start of else
	                  //Traverse until you see the end of the list
	                  //Go to the endPointer
	                    currentPointer = endPointer; //Go to the endPointer
	                  //Add a node
                            (*currentPointer).next = malloc(sizeof(struct node));
	                    currentPointer = (*currentPointer).next; //index 1 node
	                  //Add the values to this new node
		            add(atoi(pidString), atoi(timerString), currentPointer);	
                            endPointer = currentPointer; //The endPointer now becomes this new node added
	                    (*endPointer).next = startNode; //connect the endpointer to the startnode in a loop
	               }//End of else
	          //Notify that node is added	
                    printf("Adding node#%d to list...", processCount);
                  //Print the list
	            printList(endPointer);
                  //Reset the pidString and timerString for the new node
	            memset(pidString, 0, sizeof pidString);
	            memset(timerString, 0, sizeof timerString);
                }//End of while fgets
           //Close the file and exit
             fclose(fp);
           }//End of master else
            //Return the endPointer
	      return endPointer;
      }//End of createList

  //Add the startNode
    void add(int pidEntry, int timerEntry, struct node* endPointerEntry)
      {//Start of add
         (*endPointerEntry).pid = pidEntry;
         (*endPointerEntry).timer = timerEntry;
      }//End of add

  //Print the listvalue
    void printList(struct node* PointerEntry)
      {//Start of printList
        //Variables
          struct node *currentPointer;
	//print text
	  printf("\nContent:\n");
	//Only print if the list is not empty
	  if(isEmpty() == false)
            {//Start of if
             //Update the currentPointer
	       currentPointer = PointerEntry;
	       currentPointer = (*currentPointer).next; //Go to start
             //Print the pointer content
	       for (i = 0; i < processCount; i++)
		  {//Start of for
                    printf(">NODE(pid:%d / timer:%d)\n", (*currentPointer).pid, (*currentPointer).timer);
                    currentPointer = (*currentPointer).next; //Index to next pointer
		  }//End of for
            }//End of if
	printf("\n");
      }//End of printList

  //Check that list is empty
    bool isEmpty()
      {//Start of isEmtpy
	if (processCount > 0)
	  {return false;}
        else
          {return true;}
      }//End of isEmpty

  //Scan function
    struct node* scanList(struct node* endPointerEntry)
      {//Start of scanList
       //Variables
	int scanCount = 1;
	int deduct = 0;
	 struct node *currentPointer;
         struct node *previousPointer;
	 struct node *nextPointer;
	 currentPointer = endPointerEntry;
       //Notify start
         printf("******************PART II: SCAN LIST******************\n");
       //Print the original list
         printf("Original list content...");
         printList(endPointerEntry);
       //Print remaining nodes
	 printf("Now scanning through list...\n");
       //Perform scans
	 while (isEmpty() == false)
           {//Start of while
	      sleep(1);
	      printf("running scan#%d...", scanCount);
	      scanCount++;
	    //Scan the list
              for(i = 0; i < processCount; i++)
	        {//Start of for
		   //Update the pointers
		     previousPointer = currentPointer; //The prevPointer will lag 1 node behind
		     currentPointer = (*currentPointer).next; //index
	             (*currentPointer).timer--; //Decrement timer
                   //If the timer is < 1, remove the process
		     if ((*currentPointer).timer < 1)
		       {//Start of if 
			//remove the process
			  nextPointer = removeCurrent(currentPointer);
			//Stitch
	       		  (*previousPointer).next = nextPointer; //connect the endpointer to the startnode to complete the loop
			  currentPointer = previousPointer; //Update the currentPointer to the nextPointer
			  deduct++; //Update the deduction
		       }//End of if
		}//End of for
		//Update the processCount
		  processCount -= deduct;
                //Reset the deductions
                  deduct = 0;
	     //Print the list
	       printList(currentPointer);
	   }//End of while
	return endPointerEntry;
      }//End of scanList

  //Remove process function
    struct node* removeCurrent(struct node* currentPointerEntry)
      {//Start of removeCurrent
       //Variables
         struct node *currentPointer;
         struct node *nextPointer;
       //Remove the node if the structure is not empty and has more than 1 item
         if(isEmpty() == false && processCount > 1)
           {//Start of if
	    //update the pointers
	      nextPointer = currentPointerEntry;
	      nextPointer = (*nextPointer).next; //index
	    //Make the node NULL to remove it
              currentPointerEntry = NULL;
	      free(currentPointerEntry);
	    //Return a reference to next node so it can stitch
	      return nextPointer;
	   }//End of if
       //Remove the node and refer current to NULL if structure is not empty and has 1 node left
         else if(isEmpty() == false && processCount == 1)
           {//Start of if
	    //Make the node NULL to remove it
              currentPointerEntry = NULL;
	      free(currentPointerEntry);
	    //Return a reference to next node so it can stitch
	      return currentPointerEntry;
	   }//End of if
       //If the structure is empty, return NULL
	 else
	   {return NULL;}
    }//End of removeCurrent
