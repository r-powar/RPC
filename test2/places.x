typedef string nametype<255>;
typedef string statetype<2>;
typedef struct placenode* placelist;

struct placenode{
	nametype placename;
	statetype state;
	float latitude;
	float longitude;
	placelist next;
};

struct placedata{
	nametype name;
	statetype state;
};

union places_ret switch(int err){
	case 0:
		placelist list;
	default:
		void;
};


program PLACESPROG{
	version PLACES_VERS{
		places_ret PLACES(placedata) = 1;
	}=1;
}=0x38886665;

