#include <iostream>
#include "influxdb_client.h"


using namespace std;


int main()
{

	influxdb_client db;

	cout<< db.get_client()<< endl;

	return 0;
}
