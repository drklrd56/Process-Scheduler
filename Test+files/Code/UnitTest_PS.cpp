#include "ProcessScheduler.h"

#include <fstream>
#include <string>
#include "gtest/gtest.h"


TEST(testProcessScheduling, Jobfileopen)
{
	ifstream is("..\\ProcessScheduler\\job.txt",std::ifstream::in); //ProcessScheduling
	
	if(!is.is_open())
		{
			
			ASSERT_TRUE(false);
		}
	else
	{
		ASSERT_TRUE(true);
	}
	is.close();

		
}

TEST(testProcessScheduling, ProcessTextFile)
{
	runProcessScheduling("..\\ProcessScheduler\\job.txt", 3);
	ifstream is("..\\ProcessScheduler\\Process.txt",std::ifstream::in);
	
	if(!is.is_open())
		{
			
			ASSERT_TRUE(false);
		}
	else
	{
	string data;
	is >> data;
	EXPECT_EQ(0,data.compare("Time"));
	is >> data;
	
	EXPECT_EQ(0,data.compare("0"));
	
	is >> data;
	EXPECT_EQ(0,data.compare("P0"));
	is >> data;
	EXPECT_EQ(0,data.compare("Running"));
	is >> data;
	EXPECT_EQ(0,data.compare("CPU"));
	is >> data;
	EXPECT_EQ(0,data.compare("Time"));
	is >> data;
	EXPECT_EQ(0,data.compare("1"));
	is >> data;
	EXPECT_EQ(0,data.compare("P0"));
	is >> data;
	EXPECT_EQ(0,data.compare("Running"));
	is >> data;
	EXPECT_EQ(0,data.compare("CPU"));
	is >> data;
	EXPECT_EQ(0,data.compare("P1"));
	is >> data;
	EXPECT_EQ(0,data.compare("Ready"));
	is >> data;
	EXPECT_EQ(0,data.compare("FCFS-1"));
	is >> data;
	EXPECT_EQ(0,data.compare("Time"));
	is >> data;
	EXPECT_EQ(0,data.compare("2"));
	is >> data;
	EXPECT_EQ(0,data.compare("P0"));
	is >> data;
	EXPECT_EQ(0,data.compare("Running"));
	is >> data;
	EXPECT_EQ(0,data.compare("CPU"));
	is >> data;
	EXPECT_EQ(0,data.compare("P1"));
	is >> data;
	EXPECT_EQ(0,data.compare("Ready"));
	is >> data;
	EXPECT_EQ(0,data.compare("FCFS-1"));
	is >> data;
	EXPECT_EQ(0,data.compare("P2"));
	is >> data;
	EXPECT_EQ(0,data.compare("Ready"));
	is >> data;
	EXPECT_EQ(0,data.compare("FCFS-1"));
	is >> data;
	EXPECT_EQ(0,data.compare("Time"));
	is >> data;
	EXPECT_EQ(0,data.compare("3"));
	is >> data;
	EXPECT_EQ(0,data.compare("P0"));
	is >> data;
	EXPECT_EQ(0,data.compare("Ready"));
	is >> data;
	EXPECT_EQ(0,data.compare("FCFS-2"));
	is >> data;
	EXPECT_EQ(0,data.compare("P1"));
	is >> data;
	EXPECT_EQ(0,data.compare("Running"));
	is >> data;
	EXPECT_EQ(0,data.compare("CPU"));
	is >> data;
	EXPECT_EQ(0,data.compare("P2"));
	is >> data;
	EXPECT_EQ(0,data.compare("Ready"));
	is >> data;
	EXPECT_EQ(0,data.compare("FCFS-1"));
	}
	is.close();

}

TEST(testProcessScheduling, CPUTextFile)
{
	runProcessScheduling("..\\ProcessScheduler\\job.txt", 3);
	ifstream is("..\\ProcessScheduler\\CPU.txt",std::ifstream::in);
	
	if(!is.is_open())
		{
			
			ASSERT_TRUE(false);
		}
	else
	{
		string data;
		string temp;
		data="";
		while(!is.eof())
		{
			is >> temp;

			data = data + temp + " ";

		}
		EXPECT_EQ(0,data.compare("Time 0 P0 COMPUTE Time 1 P0 COMPUTE Time 2 P0 COMPUTE Time 3 P1 COMPUTE "));
	}
	is.close();

}

TEST(testProcessScheduling, QueueTextFile)
{
	runProcessScheduling("..\\ProcessScheduler\\job.txt", 3);
	ifstream is("..\\ProcessScheduler\\Queue.txt",std::ifstream::in);
	
	if(!is.is_open())
		{
			
			ASSERT_TRUE(false);
		}
	else
	{
		string data;
		string temp;
		data="";
		while(!is.eof())
		{
			is >> temp;

			data = data + temp + " ";

		}
		EXPECT_EQ(0,data.compare("Time 0 FCFS-1: FCFS-2: SJF: HardDisk: Network: Device: Time 1 FCFS-1: P1 FCFS-2: SJF: HardDisk: Network: Device: Time 2 FCFS-1: P2 P3 FCFS-2: SJF: HardDisk: Network: Device: Time 3 FCFS-1: P2 FCFS-2: P0 SJF: HardDisk: Network: Device: "));
	}
	is.close();

}
