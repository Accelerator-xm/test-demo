#include<iostream>
#include"Graph.h"
#include"Tourism.h"

using namespace std;

int main() {

	int bRunning = 1;

	while (bRunning) {
		//�������
		cout << "=======��������ϵͳ========" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "������������(0-5):";
		cin >> bRunning;

		switch (bRunning)
		{
		case 1: CreateGraph(); break;
		case 2: GetSpotInfo(); break;
		case 3: TravelPath(); break;
		case 4: FindShortPath(); break;
		case 5: DesignPath(); break;
		default:
			cout << "======���˳�======" << endl;
			break;
		}
	}



	return 0;
}