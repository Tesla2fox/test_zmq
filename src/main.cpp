#include "Agent.hpp"
#include <iostream>


using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using netAgent::client_data;
using netAgent::Agent;
using netAgent::ReplyInterface;
using std::vector;
using std::string;
using zmq::message_t;
using netAgent::_tool::format;




/*
 * �����������ݵ����ݽṹ��
*/
struct test_data{
	test_data();
	int intVal = 10;
	double doubleVal = 3.12345;
	char strVal[8];
};
test_data::test_data(){
	
	strcpy(strVal, "hello");
}
ostream& operator << (ostream& os, const test_data& dat){
	return os << "intVal = " << dat.intVal << ", doubleVal = " << dat.doubleVal << ", strVal = " << dat.strVal << endl;
}

// �յ�Broadcast�Ĵ�����
void onBroadcast(int ID, int type, void* data, size_t size){
	string msg((char*)data, size);
	cout << format("Get broadcast from %d, type %d, content = %s\n", ID, type, msg.c_str());
}

// �յ�Request�Ĵ�����
void onRequest(int ID, int type, void* data, size_t size, ReplyInterface reply){
	string msg((char*)data, size);
	cout << format("Get request from %d, type %d, content = %s\n", ID, type, msg.c_str());
	if (type == 0){
		test_data data;
		reply.send(&data, sizeof(test_data));
	}
	else
		reply.send(2333);
}

int main(int argc, char* argv[]){
	int myID = 0;
	if (argc > 1)
		myID = atoi(argv[1]);

	int portPubBase = 4455;
	int portRepBase = 5555;
	
	int total_agents = 4;
	if (myID >= total_agents)
		return 0;
	
	vector<client_data> data_list;
	client_data _data("127.0.0.1", 0, portPubBase + 0, portRepBase + 0);
	data_list.push_back(data);
	// data_list.push_back({ "127.0.0.1", 0, portPubBase + 0, portRepBase + 0 });
	for (int i = 1; i < total_agents; ++i)
		data_list.push_back({ "127.0.0.1", i, portPubBase + i, portRepBase + i });
	
	
	client_data& myData = data_list[myID];
	cout << myData << endl;

	Agent agent(myData);
	agent.server_start();					// ʹ������Agent�����ӵ����Agent
	agent.connect_to(data_list, {myID});	// ���ӵ�����Agent
	agent.handle_broadcast = onBroadcast;	// �����յ�Broadcastʱ�Ĵ�����
	agent.handle_request   = onRequest;		// �����յ�Requestʱ�Ĵ�����
	agent.start(netAgent::all_thread);		// ��ʼ�������߳�

	// ����request���� - ��reply_msg
	for (int i = 0; i < total_agents; ++i){
		if (i == myID) continue;
		int res = agent.request(i, 1, "Test reply, type = 1");
		test_data* data = agent.get_more_reply<test_data>();
		if (data != nullptr)
			puts("error data != nullptr");
		else
			cout << format("Get reply from %d : msg = %d\n", i, res);
	}

	// ����request���� - ��reply_msg
	for (int i = 0; i < total_agents; ++i){
		if (i == myID) continue;
		int res = agent.request(i, 0, "Test reply, type = 0");

		test_data* data = agent.get_more_reply<test_data>();
		if (data == nullptr)
			puts("error data == nullptr");
		else
			cout << format("Get reply from %d : msg = %d\n\tdata =", i, res) << *data << endl;
	}

	// ����broadcast����
	for (int i = 0; i < 10; ++i){
		puts("sended");
		agent.broadcast(314, "Test Broadcast, type = 314");
		// sleep(500);
	}
	

	cout << "All Done" << endl;
	system("pause");
	agent.stop();	// ����̷߳���ֹͣ����
	agent.join();	// ����, ֱ�����߳�ֹͣ
	return 0;
}