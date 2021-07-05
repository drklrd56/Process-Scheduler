/*
	Ali Hamza
	i17-0254
	CS-E
	Process Scheduler.h
*/

#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class ProcessScheduler
{
  private:
	template <typename T>
	class Queue
	{
		struct Node
		{
			T data;
			Node *next;
		};
		Node *front;
		Node *rear;
		int numItems;

	  public:
		int getLength()
		{
			return numItems;
		}
		Queue()
		{
			front = NULL;
			rear = NULL;
			numItems = 0;
		}
		T getElementAtFRONT()
		{
			if (!isEmpty())
				return front->data;
		}

		bool isEmpty()
		{
			if (numItems == 0)
				return true;
			return false;
		}
		T Find(int Index)
		{
			if (Index > 0)
			{
				int currentIndex = 1;
				Node *currentNode = front;
				if (Index != currentIndex)
				{
					currentNode = currentNode->next;
					currentIndex++;
				}
				return currentNode->data;
			}
		}
		void enqueue(T &newDataItem)
		{
			Node *newNode = new Node;
			newNode->data = newDataItem;
			newNode->next = NULL;
			if (isEmpty())
			{
				front = newNode;
				rear = newNode;
			}
			else
			{
				rear->next = newNode;
				rear = newNode;
			}
			numItems++;
			//cout << numItems << endl;
		}
		T dequeue()
		{
			if (isEmpty())
				cout << "Queue is Empty." << endl;
			else
			{
				Node *temp;
				T value = front->data;
				temp = front->next;
				delete front;
				front = temp;
				if (front == NULL)
					rear = NULL;
				numItems--;
				return value;
			}
		}
		void makeNull()
		{
			while (!isEmpty())
				dequeue();
			front = NULL;
		}
		void Display()
		{
			if (!isEmpty())
			{
				Node *start = front;
				while (start != NULL)
				{
					cout << start->data << " ";
					start = start->next;
				}
				cout << endl;
			}
			else
			{
				cout << "Empty" << endl;
			}
		}
		~Queue()
		{
			makeNull();
		}
	};
	class Process
	{
		string substr(string Actual_String)
		{
			string subString = "";
			for (int Index = 0; Index < Actual_String.length(); Index++)
			{
				if (Index + 1 < Actual_String.length())
					if (Actual_String[Index + 1] >= 48 && Actual_String[Index + 1] <= 57)
						break;
				subString += Actual_String[Index];
			}
			return subString;
		}
		int StringToInt(const string Actual_String)
		{
			int Number = 0;
			for (int Index = 0, spaceCount = 0; Index < Actual_String.length(); Index++)
			{
				if (spaceCount >= 2)
				{
					if (int(Actual_String[Index]) >= 48 && int(Actual_String[Index]) <= 57)
					{
						Number *= 10;
						Number += 48 - int(Actual_String[Index]);
					}
				}
				if (Actual_String[Index] == ' ')
					spaceCount++;
			}
			return abs(Number);
		}
		class Instruction
		{
		  public:
			string Command;
			int excecutionTime;
			string commandType;
			int internalCLOCK;
			Instruction()
			{
				Command = "";
				internalCLOCK = -1;
				excecutionTime = -1;
				commandType = "";
			}
			int getClock()
			{
				//cout << internalCLOCK << endl;
				return internalCLOCK;
			}
			void setClock(int externalUpdate)
			{
				internalCLOCK = externalUpdate;
			}
			void resetInternalClock()
			{
				internalCLOCK = 0;
			}
			bool checkInteralClock()
			{
				return internalCLOCK >= excecutionTime;
			}
		};
		string Name;
		string currentQueue;
		int Index;
		string State;
		Queue<Instruction> fileInstructions;
		void insertTopQueue(Instruction obj)
		{
			int length = fileInstructions.getLength();
			Queue<Instruction> temp;
			Instruction toADD;
			for (int Index = 0; Index < length; Index++)
			{
				toADD = fileInstructions.dequeue();
				temp.enqueue(toADD);
			}
			fileInstructions.enqueue(obj);
			for (int Index = 0; Index < length; Index++)
			{
				toADD = temp.dequeue();
				fileInstructions.enqueue(toADD);
			}
		}
		int arrivalTime;

	  public:
		void Clear()
		{
			fileInstructions.makeNull();
		}
		int getLength()
		{
			return fileInstructions.getLength();
		}
		void readProcess(string path)
		{
			ifstream inputFile;
			inputFile.open(path);
			if (inputFile.is_open())
			{
				string command, type, line;
				int exTime;
				inputFile.seekg(0);
				Clear();
				Instruction addObject;
				getline(inputFile, line, '\n');
				while (1)
				{
					getline(inputFile, line, '\n');
					if (line == "End")
						break;
					command = substr(line);
					exTime = StringToInt(line);
					addObject.Command = command;
					addObject.excecutionTime = exTime;
					type = "";
					if (command != "COMPUTE")
					{
						for (int Index = 0, spaceCount = 0; Index < command.length(); Index++)
						{
							if (spaceCount >= 1)
							{
								type += command[Index];
							}
							if (command[Index] == ' ')
								spaceCount++;
						}
					}
					else
						type = command;
					addObject.commandType = type;
					fileInstructions.enqueue(addObject);
				}
				inputFile.close();
			}
			else
				cout << "Error Occured, File Can't be Opened." << endl;
		}
		string getName()
		{
			return Name;
		}
		void setName(string name)
		{
			Name = name;
		}
		string getState()
		{
			return State;
		}
		void setState(string state)
		{
			State = state;
		}
		int getIndex()
		{
			return Index;
		}
		void setIndex(int index)
		{
			Index = index;
		}
		void setTime(int time)
		{
			arrivalTime = time;
		}
		int getTime()
		{
			return arrivalTime;
		}
		void setQueue(string Queue)
		{
			currentQueue = Queue;
		}
		string getQueue()
		{
			return currentQueue;
		}
		Instruction getInstructions()
		{
			return fileInstructions.getElementAtFRONT();
		}
		int moveInternalClock()
		{
			Instruction save = fileInstructions.dequeue();
			int time = save.getClock();
			time++;
			save.setClock(time);
			insertTopQueue(save);
			return time;
		}
		void resetClock()
		{
			fileInstructions.getElementAtFRONT().resetInternalClock();
		}
		bool checkClock()
		{
			return fileInstructions.getElementAtFRONT().checkInteralClock();
		}
		void operator=(Process &P2)
		{
			if (this->Name != P2.Name)
			{
				this->Index = P2.Index;
				this->Name = P2.Name;
				this->arrivalTime = P2.arrivalTime;
				//this->fileInstructions.makeNull();
				int length = P2.fileInstructions.getLength();
				Instruction toADD;
				for (int Index = 0; Index < length; Index++)
				{
					toADD = P2.fileInstructions.dequeue();
					this->fileInstructions.enqueue(toADD);
				}
				this->State = P2.State;
				this->currentQueue = P2.currentQueue;
			}
		}
		void Display()
		{
			cout << Index << " ";
			cout << Name << " ";
			cout << arrivalTime << " ";
			cout << State << " ";
			cout << currentQueue << " ";
			cout << fileInstructions.getLength() << endl;
			;
			int length = fileInstructions.getLength();
			Instruction toAdd;
			cout << "command "
				 << "Type "
				 << "ExecutionTime " << endl;
			for (int Index = 0; Index < length; Index++)
			{
				toAdd = fileInstructions.dequeue();
				cout << toAdd.Command << " " << toAdd.commandType << " " << toAdd.excecutionTime << endl;
				fileInstructions.enqueue(toAdd);
			}
			cout << endl;
		}
		string removeASingleInstruction()
		{
			return fileInstructions.dequeue().Command;
		}
		void getASingleInstruction(string &Command, string &Type, int &exTime)
		{
			if (!fileInstructions.isEmpty())
			{
				Instruction I1 = fileInstructions.getElementAtFRONT();
				Command = I1.Command;
				Type = I1.commandType;
				exTime = I1.excecutionTime;
			}
		}
	};
	template <typename T>
	class List
	{
		struct Node
		{
			T value;
			Node *next;
			Node *previous;
		};
		Node *head;
		Node *tail;
		int numItems;

	  public:
		List()
		{
			head = NULL;
			numItems = 0;
			tail = NULL;
		}
		~List()
		{
			makeNull();
		}
		void makeNull()
		{
			Node *currNode = head;
			Node *nextNode = NULL;
			while (currNode != NULL)
			{
				nextNode = currNode->next;
				delete currNode; // destroy the current node
				currNode = nextNode;
			}
			tail = NULL;
			head = NULL;
			numItems = 0;
		}
		bool isEmpty()
		{
			return head == NULL;
		}
		bool insert(T &newDataItem, int index)
		{
			if (index <= 0)
				return false;
			int currentIndex = 2;
			Node *currentNode = head;
			while (currentNode != NULL && currentIndex < index)
			{
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (index > 1 && currentNode == NULL)
				return false;
			Node *newNode = new Node();
			newNode->value = newDataItem;
			if (index == 1)
			{
				if (head != NULL)
					head->previous = newNode;
				newNode->next = head;
				newNode->previous = NULL;
				head = newNode;
				numItems++;
				if (tail == NULL)
					tail = newNode;
			}
			else
			{
				if (tail == currentNode)
					tail = newNode;
				newNode->next = currentNode->next;
				newNode->previous = currentNode;
				if (currentNode->next != NULL)
					currentNode->next->previous = newNode;
				currentNode->next = newNode;
				currentNode = newNode;
				numItems++;
			}
		}
		int Find(T DataItem)
		{
			int currentIndex = 1;
			Node *currentNode = head;
			while (currentNode != NULL && currentNode->value != DataItem)
			{
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (currentNode != NULL)
				return currentIndex;
			return 0;
		}
		T &FindData(const int Index)
		{
			int currentIndex = 1;
			Node *currentNode = head;
			while (currentNode != NULL && currentIndex != Index)
			{
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (currentNode != NULL)
			{
				return currentNode->value;
			}
		}
		int getLength()
		{
			return numItems;
		}
		bool DeleteIndex(int Index)
		{
			int currentIndex = 1;
			Node *currentNode = head;
			while (currentNode != NULL && currentIndex != Index)
			{
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (currentNode)
			{
				if (currentNode->previous)
				{
					//T retValue=currentNode->value;
					Node *oldNode;
					oldNode = currentNode;
					oldNode->previous->next = oldNode->next;
					if (oldNode->next != NULL)
						oldNode->next->previous = currentNode->previous;
					if (oldNode == tail)
						tail = oldNode->previous;
					currentNode = oldNode->previous;
					delete oldNode;
					numItems--;
					return currentIndex;
				}
				else
				{
					//T retValue=currentNode->value;
					if (currentNode->next != NULL)
						currentNode->next->previous = NULL;
					head = currentNode->next;
					if (currentNode == tail)
						tail = NULL;
					delete currentNode;
					numItems--;
					return currentIndex;
				}
			}
			return 0;
		}
		void swap(int IndexHigher, int IndexLower)
		{
			if (this->numItems > 1)
			{
				Node *firstElement = head;
				int currentIndex = 1;
				while (currentIndex != IndexHigher)
				{
					firstElement = firstElement->next;
					currentIndex++;
				}
				Node *secondElement = head;
				currentIndex = 1;
				while (currentIndex != IndexLower)
				{
					secondElement = secondElement->next;
					currentIndex++;
				}
				T temp = firstElement->value;
				firstElement->value = secondElement->value;
				secondElement->value = temp;
			}
		}
		int Delete(T DataItem)
		{
			int currentIndex = 1;
			Node *currentNode = head;
			while (currentNode != NULL && currentNode->value != DataItem)
			{
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (currentNode)
			{
				if (currentNode->previous)
				{
					Node *oldNode;
					oldNode = currentNode;
					oldNode->previous->next = oldNode->next;
					if (oldNode->next != NULL)
						oldNode->next->previous = currentNode->previous;
					if (oldNode == tail)
						tail = oldNode->previous;
					currentNode = oldNode->previous;
					delete oldNode;
					numItems--;
					return currentIndex;
				}
				else
				{
					if (currentNode->next != NULL)
						currentNode->next->previous = NULL;
					head = currentNode->next;
					if (currentNode == tail)
						tail = NULL;
					delete currentNode;
					numItems--;
					return currentIndex;
				}
			}
			return 0;
		}
		void DisplayList()
		{
			int num = 0;
			Node *currNode = head;
			while (currNode != NULL)
			{
				currNode->value.Display(); // << " ";
				currNode = currNode->next;
				num++;
			}
			if (isEmpty())
				cout << "EMpty" << endl;
		}
	};
	class Processor
	{
	  public:
		bool isProcessorFree;
		int IndexInProcessor;
		string previousQueue;
		int systemTick;
		int tickLength;
		Processor()
		{
			isProcessorFree = true;
			IndexInProcessor = -1;
			previousQueue;
			systemTick = 0;
			tickLength = 3;
		}
	};
	void sortQueue(Queue<int> &SJF)
	{
		int length=SJF.getLength();
		int *array=new int[length];
		for(int Index=0;Index<length;Index++)
		{
			array[Index]=SJF.dequeue();
		}
		int temp=0;
		for(int Index=0;Index<length;Index++)
		{
			for(int Index_Second=0;Index_Second<length-1;Index_Second++)
			{
				if(Processess.FindData(array[Index_Second]).getLength()>Processess.FindData(array[Index_Second+1]).getLength())
				{
					temp=array[Index_Second];
					array[Index_Second]=array[Index_Second+1];
					array[Index_Second+1]=temp;
				}
			}
		}
		for(int Index=0;Index<length;Index++)
		{
			SJF.enqueue(array[Index]);
		}
	}
	int StringToInt(const string Actual_String)
	{
		int Number = 0;
		for (int Index = 0, spaceCount = 0; Index < Actual_String.length(); Index++)
		{
			if (spaceCount >= 1)
			{
				if (int(Actual_String[Index]) >= 48 && int(Actual_String[Index]) <= 57)
				{
					Number *= 10;
					Number += 48 - int(Actual_String[Index]);
				}
			}
			if (Actual_String[Index] == ' ')
				spaceCount++;
		}
		return abs(Number);
	}
	string substr(string Actual_String)
	{
		string subString = "";
		for (int Index = 0; Index < Actual_String.length(); Index++)
		{
			if (Actual_String[Index] == ' ')
				break;
			subString += Actual_String[Index];
		}
		return subString;
	}
	List<Process> Processess;
	bool checkStates()
	{
		int count = 0;
		int length = Processess.getLength();
		for (int Index = 1; Index <= length; Index++)
		{
			if (Processess.FindData(Index).getState() == "TERMINATED")
				count++;
		}
		if (count == length)
			return false;
		else
			return true;
	}
	void WriteProcess(ofstream &ProcessFile, int writeTime)
	{
		ProcessFile << "Time " << writeTime << endl;
		for (int Index = 1; Index <= Processess.getLength(); Index++)
		{
			if (Processess.FindData(Index).getState() != "New" && Processess.FindData(Index).getState() != "TERMINATED")
			{
				ProcessFile << Processess.FindData(Index).getName() << " "
							<< Processess.FindData(Index).getState() << " "
							<< Processess.FindData(Index).getQueue()<<endl;
			}
		}
	}
	void WriteQueue(ofstream &QueueFile, Queue<int> &FCFS1, Queue<int> &FCFS2, Queue<int> &SJF, Queue<int> &HardDisk, Queue<int> &Device, Queue<int> &Network, int writeTime)
	{
		QueueFile << "Time " << writeTime << endl;
		QueueFile << "FCFS-1:";
		for (int Index = 1; Index <= FCFS1.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(FCFS1.Find(Index)).getName();
		}
		QueueFile << endl
				  << "FCFS-2:";
		for (int Index = 1; Index <= FCFS2.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(FCFS2.Find(Index)).getName();
		}
		QueueFile << endl
				  << "SJF:";
		for (int Index = 1; Index <= SJF.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(SJF.Find(Index)).getName();
		}
		QueueFile << endl
				  << "HardDisk:";
		for (int Index = 1; Index <= HardDisk.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(HardDisk.Find(Index)).getName();
		}
		QueueFile << endl
				  << "Network:";
		for (int Index = 1; Index <= Network.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(Network.Find(Index)).getName();
		}
		QueueFile << endl
				  << "Device:";
		for (int Index = 1; Index <= Device.getLength(); Index++)
		{
			QueueFile << " " << Processess.FindData(Device.Find(Index)).getName();
		}
	}
	void sortProcess()
	{
		int time;
		int length = Processess.getLength();
		;
		for (int Index = 1; Index < length; Index++)
		{
			for (int Index_Second = 1; Index_Second < length; Index_Second++)
			{
				if (Processess.FindData(Index_Second).getTime() > Processess.FindData(Index_Second + 1).getTime())
				{
					Processess.insert(Processess.FindData(Index_Second + 1), Index_Second);
					Processess.FindData(Index_Second).setIndex(Index_Second);
					Processess.DeleteIndex(Index_Second + 2);
				}
			}
		}
	}
	void getJob(string fileName)
	{
		ifstream InputFile;
		InputFile.open(fileName);
		if (InputFile.is_open())
		{
			string Line, Command = "";
			int Index = 1, time;
			Process toAdd;
			getline(InputFile, Line, '\n');
			// Add a Fully Read Process with Instructions into Process List
			while (Line != "")
			{
				Command = substr(Line);
				time = StringToInt(Line);
				//cout<<Line<<"    "<<time<<endl;
				toAdd.setTime(time);
				toAdd.setIndex(Index);
				toAdd.setName(Command);
				toAdd.setState("New");
				toAdd.setQueue("NONE");
				// Extra Work
				Command += ".txt";
				toAdd.Clear();
				toAdd.readProcess(Command);
				Processess.insert(toAdd, Index);
				Index++;
				if (InputFile.eof())
					break;
				getline(InputFile, Line, '\n');
			}
			InputFile.close();
		}
		else
		{
			cout << "Error" << endl;
		}
	}
	
  public:
	void DisplayProcesses()
	{
		Processess.DisplayList();
	}
	void ProcessScheduling(string fileName, int endTime)
	{
		getJob(fileName);
		if (Processess.getLength() > 1)
			sortProcess();
		//Processess.DisplayList();
		//Queues
		Queue<int> FCFS1;
		Queue<int> FCFS2;
		Queue<int> SJF;
		Queue<int> Network;
		Queue<int> HardDisk;
		Queue<int> Device;
		// Variables

		//Files For Write the Data of Processess Queues and CPU
		ofstream ProcessFile, QueueFile, CPUFile;
		CPUFile.open("CPU.txt");
		ProcessFile.open("Process.txt");
		QueueFile.open("Queue.txt");
		// Processor that Execute iNstructioms
		Processor singleCore;
		// Variable USed For Something Down there IDK
		string command, type;
		int countTick = 0, time, Index_Process = 1, exTime, writeTime = 0, Index = 1,startLoop=0;
		bool InSJF = false, isFound = false;
		const int FSCS1_TICKLENGTH = 3, FSCS2_TICKLENGTH = 6;
		// Check if States of the Processess for Not terminated then Execute the Processess
		//Processess.DisplayList();
		while (startLoop!= endTime+1)
		{
			writeTime=singleCore.systemTick;
			if (checkStates() == false)
			{

				if (writeTime != 0)
					{
						//ProcessFile<<endl;
						QueueFile << endl;
						CPUFile << endl;
					}
				CPUFile << "Time " << writeTime;
				WriteProcess(ProcessFile, writeTime);
				WriteQueue(QueueFile, FCFS1, FCFS2, SJF, HardDisk, Device, Network, writeTime);
				singleCore.systemTick++;
			}
			else
			{
				if (Processess.getLength() <= 0)
					break;
				// check processes after each system Tick if the arrivalTIme==systemTick
				//move Process to FCSS1 after changing State and Queue
				if (Index <= Processess.getLength())
				{
					time = Processess.FindData(Index).getTime();
					if (singleCore.systemTick == time && Processess.FindData(Index).getState() != "TERMINATED")
					{
						Processess.FindData(Index).setState("Ready");
						Processess.FindData(Index).setQueue("FCFS-1");
						Index_Process = Processess.FindData(Index).getIndex();
						FCFS1.enqueue(Index);
						isFound = true;
						Index++;
					}
				}
				// if Processor is Free then Move a Process from Ready Queues to Processor
				if (singleCore.isProcessorFree == true)
				{
					// First check FSCS1 if Process Present then get THe Top Process else move to FCFS2 or SJF
					// Get the Process from the Priority Queues and Move it to the Processor
					if (!FCFS1.isEmpty())
					{
						// move the process from FCFS1 to Processor Completely Detch
						singleCore.IndexInProcessor = FCFS1.dequeue();
						Processess.FindData(singleCore.IndexInProcessor).setState("Running");
						singleCore.previousQueue = Processess.FindData(singleCore.IndexInProcessor).getQueue();
						Processess.FindData(singleCore.IndexInProcessor).setQueue("CPU");
					}
					else if (!FCFS2.isEmpty())
					{
						singleCore.IndexInProcessor = FCFS2.dequeue();
						if (singleCore.IndexInProcessor > 0)
						{
							Processess.FindData(singleCore.IndexInProcessor).setState("Running");
							singleCore.previousQueue = Processess.FindData(singleCore.IndexInProcessor).getQueue();
							Processess.FindData(singleCore.IndexInProcessor).setQueue("CPU");
						}
					}
					else if (!SJF.isEmpty())
					{
						singleCore.IndexInProcessor = SJF.dequeue();
						if (singleCore.IndexInProcessor > 0)
						{
							Processess.FindData(singleCore.IndexInProcessor).setState("Running");
							singleCore.previousQueue = Processess.FindData(singleCore.IndexInProcessor).getQueue();
							Processess.FindData(singleCore.IndexInProcessor).setQueue("CPU");
						}
						InSJF = true;
					}
					if (singleCore.IndexInProcessor > 0)
						singleCore.isProcessorFree = false;
				}
				//Write Process+Queue+CPU
				if (isFound == true && Processess.FindData(singleCore.IndexInProcessor).getLength() > 0)
				{
					if (writeTime != 0)
					{
						//ProcessFile<<endl;
						QueueFile << endl;
						CPUFile << endl;
					}
					CPUFile << "Time " << writeTime << endl;
					Processess.FindData(singleCore.IndexInProcessor).getASingleInstruction(command, type, exTime);
					CPUFile << Processess.FindData(singleCore.IndexInProcessor).getName() << " " << command;
					WriteProcess(ProcessFile, writeTime);
					WriteQueue(QueueFile, FCFS1, FCFS2, SJF, HardDisk, Device, Network, writeTime);
					countTick++;
				}
				else
				{
					if (writeTime != 0)
					{
						//ProcessFile<<endl;
						QueueFile << endl;
						CPUFile << endl;
					}
					CPUFile << "Time " << writeTime;
					WriteProcess(ProcessFile, writeTime);
					WriteQueue(QueueFile, FCFS1, FCFS2, SJF, HardDisk, Device, Network, writeTime);
				}
				// Execute Instructions
				if (singleCore.IndexInProcessor > 0)
				{
					if (Processess.FindData(singleCore.IndexInProcessor).getLength() > 0)
					{
						// check Processor if Free the move a process from schduler to Processor;
						// Read the Instructions from the Process that is In processor
						Processess.FindData(singleCore.IndexInProcessor).getASingleInstruction(command, type, exTime);
						//Write CPU
						if (type == "COMPUTE")
						{
							// if simple process then remove it from
							Processess.FindData(singleCore.IndexInProcessor).removeASingleInstruction();
						}
						else
						{
							countTick = 0;
							// remove Process from PRocessor and move it to Waiting Queue(Respective)
							// if the type is not COMPUTE
							if (Processess.FindData(singleCore.IndexInProcessor).getState() != "Waiting")
							{
								if (type == "NETWORK")
								{
									singleCore.isProcessorFree = true;
									Network.enqueue(singleCore.IndexInProcessor);
									Processess.FindData(singleCore.IndexInProcessor).setState("Waiting");
									Processess.FindData(singleCore.IndexInProcessor).setQueue("Network");
								}
								else if (type == "DISK")
								{
									singleCore.isProcessorFree = true;
									HardDisk.enqueue(singleCore.IndexInProcessor);
									Processess.FindData(singleCore.IndexInProcessor).setState("Waiting");
									Processess.FindData(singleCore.IndexInProcessor).setQueue("HardDisk");
								}
								else
								{
									singleCore.isProcessorFree = true;
									Processess.FindData(singleCore.IndexInProcessor).setState("Waiting");
									Processess.FindData(singleCore.IndexInProcessor).setQueue("Device");
									Device.enqueue(singleCore.IndexInProcessor);
								}
							}
						}
					}
				}
				// move Clocks of all the Indices in the Waiting Queue
				// check the Clocks
				// if the Clock== Waiting Time(ExexcutionTime)
				// Remove the Process index from the respective Waiting Queue and move the
				// Process to  FCSCS-1 after removing the Waiting Instruction and Set State to Ready
				if (HardDisk.getLength() > 0)
				{
					Processess.FindData(HardDisk.getElementAtFRONT()).moveInternalClock();
					if (Processess.FindData(HardDisk.getElementAtFRONT()).checkClock())
					{
						Index_Process = HardDisk.dequeue();
						Processess.FindData(Index_Process).removeASingleInstruction();
						if (Index_Process > 0)
						{
							if (Processess.FindData(Index_Process).getLength()>=1)
							{
								FCFS1.enqueue(Index_Process);
								Processess.FindData(Index_Process).setQueue("FCFS-1");
								Processess.FindData(Index_Process).setState("Ready");
							}
							else
							{
								Processess.FindData(Index_Process).Clear();
								Processess.FindData(Index_Process).setState("TERMINATED");
								Processess.FindData(Index_Process).setQueue("NONE");
							}
						}
					}
				}
				if (Network.getLength() > 0)
				{
					Processess.FindData(Network.getElementAtFRONT()).moveInternalClock();
					if (Processess.FindData(Network.getElementAtFRONT()).checkClock())
					{
						Index_Process = Network.dequeue();
						Processess.FindData(Index_Process).removeASingleInstruction();
						if (Processess.FindData(Index_Process).getLength()>0)
						{
							FCFS1.enqueue(Index_Process);
							Processess.FindData(Index_Process).setQueue("FCFS-1");
							Processess.FindData(Index_Process).setState("Ready");
						}
						else
						{
							Processess.FindData(Index_Process).Clear();
							Processess.FindData(Index_Process).setState("TERMINATED");
							Processess.FindData(Index_Process).setQueue("NONE");
						}
					}
				}
				if (Device.getLength() > 0)
				{
					Processess.FindData(Device.getElementAtFRONT()).moveInternalClock();
					if (Processess.FindData(Device.getElementAtFRONT()).checkClock())
					{
						Index_Process = Device.dequeue();
						Processess.FindData(Index_Process).removeASingleInstruction();
						if (Processess.FindData(Index_Process).getLength()>0)
						{
							FCFS1.enqueue(Index_Process);
							Processess.FindData(Index_Process).setQueue("FCFS-1");
							Processess.FindData(Index_Process).setState("Ready");
						}
						else
						{
							Processess.FindData(Index_Process).Clear();
							Processess.FindData(Index_Process).setState("TERMINATED");
							Processess.FindData(Index_Process).setQueue("NONE");
						}
					}
				}
				//if Instructions Are Equal to Zer0 Then Set State to Terminated
				if (singleCore.IndexInProcessor > 0)
				{
					if (Processess.FindData(singleCore.IndexInProcessor).getLength() <= 0)
					{
						// THe TERMINATED Process will never come in the Processesor Again
						Processess.FindData(singleCore.IndexInProcessor).Clear();
						Processess.FindData(singleCore.IndexInProcessor).setState("TERMINATED");
						Processess.FindData(singleCore.IndexInProcessor).setQueue("NONE");
						singleCore.isProcessorFree = true;
					}
				}
				// Setting the End accordong to the Queue
				if (singleCore.previousQueue == "FCFS-1")
					singleCore.tickLength = FSCS1_TICKLENGTH;
				else if (singleCore.previousQueue == "FCFS-2")
					singleCore.tickLength = FSCS2_TICKLENGTH;
				singleCore.systemTick++;
				// Implement the Slices and move the Process in Processor to another Queue and
				// Free the Processor
				if (InSJF == false)
				{
					if (countTick == singleCore.tickLength)
					{
						countTick = 0;
						singleCore.isProcessorFree = true;
						// The Processes Hasn't stop workin jump to the Next Queue
						if (Processess.FindData(singleCore.IndexInProcessor).getState() != "TERMINATED")
						{
							// Get the Process to ready State
							Processess.FindData(singleCore.IndexInProcessor).setState("Ready");
							if (singleCore.previousQueue == "FCFS-1")
							{
								Processess.FindData(singleCore.IndexInProcessor).setQueue("FCFS-2");
								FCFS2.enqueue(singleCore.IndexInProcessor);
							}
							else if (singleCore.previousQueue == "FCFS-2")
							{
								Processess.FindData(singleCore.IndexInProcessor).setQueue("SJF");
								SJF.enqueue(singleCore.IndexInProcessor);
								if (SJF.getLength() > 1)
									sortQueue(SJF);
							}
						}
					}
				}
				if (InSJF == true)
				{
					if (SJF.getLength() == 0)
					{
						countTick = 0;
						InSJF = false;
					}
				}
			}
			startLoop++;
		}
		// Closing the Files and Making The Processess List Empty;
		ProcessFile.seekp(-1,ios::end);
		ProcessFile.put('\0');
		ProcessFile.close();
		CPUFile.close();
		QueueFile.close();
		Processess.makeNull();
	}
	~ProcessScheduler()
	{
		Processess.makeNull();
	}
};
void runProcessScheduling(string fileName, int endTime)
{
	ProcessScheduler S1;
	S1.ProcessScheduling(fileName, endTime);
}