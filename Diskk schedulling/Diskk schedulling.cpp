#include <cmath>
#include <iostream>
#include <algorithm>
#include <list> 
#include <iterator> 
#include <string>
using namespace std;

//********************************** FCFS *****************************************
void FCFS(int requests[], int head_position, int req_count, int distance, int seek_count)
{
	cout << "FCFS: " << endl;
	distance = abs(head_position - requests[0]);
	for (int i = 0; i < req_count - 1; i++) {
		distance += abs(requests[i] - requests[i + 1]);
	}
	cout << "Order: " << head_position << " -> ";
	for (int i = 0; i < req_count; i++) {
		string _ = " -> ";
		if (i == req_count - 1) {
			_ = "";
		}
		cout << requests[i] << _;
	}
	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}


//********************************** CLOOK ****************************************
void CLOOK(int requests[], int head_position, int req_count, int seek_count, int disk_size, bool direction_right) {
	int* requests_x = new int[req_count];
	for (int i = 0; i < req_count; i++) {
		requests_x[i] = requests[i];
	}
	cout << "C-Look: " << endl;
	sort(requests_x, requests_x + req_count);

	list<int>leftt;
	list<int>rightt;
	for (int i = 0; i < req_count; i++)
	{
		if (requests_x[i] > head_position)
			rightt.push_back(requests_x[i]);
		else
			leftt.push_back(requests_x[i]);
	}
	list<int> CLOOK_requests;
	CLOOK_requests.push_back(head_position);
	if (direction_right) {
		leftt.reverse();
	}
	else {
		rightt.reverse();
	}
	for (int i = 0; i < 2; i++)
	{

		if (direction_right)
		{
			for (list <int> ::iterator i = rightt.begin(); i != (rightt.end()); i++)
			{
				CLOOK_requests.push_back(*i);
			}
		}
		else

		{
			for (auto i = leftt.rbegin(); i != (leftt.rend()); i++)
			{

				CLOOK_requests.push_back(*i);

			}

		}
		if (i == 0)
			//as not to walk till the end of the disk
		/*{
			LOOK_requests.push_back((end - 1)*upper);
		}*/
			direction_right = !direction_right;
	}
	int total_distance = 0;
	cout << "Order: ";

	for (list <int> ::iterator i = CLOOK_requests.begin(); i != prev(CLOOK_requests.end()); i++) {
		cout << *i << " -> ";
		//cout << *i << " - " << *next(i) << " = " << abs(*i - *next(i)) << endl;
		total_distance += abs(*i - *next(i));

	}
	cout << *prev(CLOOK_requests.end());
	cout << "\n" << "Seek: " << total_distance << " cylinders, " << total_distance * seek_count << "ms";
	cout << endl << endl;
}

//********************************** CSCAN ****************************************
void CSCAN(int requests[], int head_position, int req_count, int distance, int seek_count, int disk_size)
{
	cout << "CSCAN: " << endl;
	string _ = " -> ";
	cout << "Order: " << head_position << " -> ";

	sort(requests, requests + req_count);
	distance = 0;
	int bound_z = disk_size - 1;
	bool bbound = false;
	int next_index = 0;
	for (int i = 0; i < req_count; i++) {

		if (requests[i] >= head_position && distance == 0)
		{
			distance = abs(head_position - requests[i]);
		}
	}

	for (int i = 0; i < req_count; i++) {

		if (requests[i] > head_position)
		{

			cout << requests[i] << _;
			if (requests[i] == bound_z)
			{
				bbound = true;
			}
		}

	}
	for (int i = 0; i < req_count - 1; i++) {
		if (requests[i] > head_position)
		{
			next_index = requests[i + 1];
			distance += abs(requests[i] - next_index);
		}

	}
	int bound_x = 0;

	if (!bbound)
	{

		cout << bound_z << _;
		distance += abs(bound_z - next_index);
		distance += abs(bound_x - bound_z);
		next_index = bound_x;


	}
	cout << bound_x << _;

	for (int i = 0; i < req_count; i++)
	{

		if (requests[i] < head_position)
		{

			if (requests[i + 1] > head_position)
			{
				_ = "";
			}
			if (requests[i] != bound_x)
			{
				cout << requests[i] << _;

			}



		}
	}

	for (int i = 0; i < req_count; i++)
	{
		if (requests[i] < head_position)
		{
			distance += abs(requests[i] - next_index);

		}
		next_index = requests[i];

	}





	cout << "\n" << "Seek: " << distance << " cylinders, " << distance * seek_count << "ms";
	cout << endl << endl;
}



//********************************** Driver Code **********************************
int main()
{
	//INPUTS
	int n;
	/*cout << "How many requests? : ";
	cin >> n;
	cout << "enter the list of requests"<<endl;
	int*requests = new int[n];
	for (int i = 0; i < n; i++) {
		cout << i+1 << " - ";
		cin >> requests[i];
	}
	int req_count = n;*/
	/**/ int requests[8] = { 98, 183, 40, 122, 10, 124, 65, 175 };
	int req_count = sizeof(requests) / sizeof(requests[0]); /**/
	int head_position = 50;
	int disk_size = 200;
	int seek_count = 6;
	bool direction_right = false;
	int distance = 0;

	
	CSCAN(requests, head_position, req_count, distance, seek_count, disk_size);
	CLOOK(requests, head_position, req_count, seek_count, disk_size, direction_right);
	FCFS(requests, head_position, req_count, distance, seek_count);
	
}



