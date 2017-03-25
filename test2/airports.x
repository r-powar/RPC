typedef string stringtype<255>;
typedef struct airportnode* airportlist;


struct airportnode {
	stringtype code;
	stringtype name;
	float latitude;
	float longitude;
	float distance;
	airportlist next;
}; 

struct airportdata {
	float latitude;
	float longitude;
};

union airport_ret switch (int err) {
	case 0:
		airportlist list;
	default:
		void;
};

program AIRPORTPROG {
	version AIRPORT_VERS {
		airport_ret AIRPORTS(airportdata) = 1;
	} = 1;
} = 0x38886665;
