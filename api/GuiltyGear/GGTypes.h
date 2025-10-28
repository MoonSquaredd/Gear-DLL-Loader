#ifndef GGTypes
#define GGTypes

typedef enum {
	None = 0,Sol = 1,Ky = 2,May = 3,
	Millia = 4,Axl = 5,Potemkin = 6,Chipp = 7,
	Eddie = 8,Baiken = 9,Faust = 10,Testament = 11,
	Jam = 12,Anji = 13,Johnny = 14,Venom = 15,
	Dizzy = 16,Slayer = 17,INo = 18,Zappa = 19,
	Bridget = 20,RoboKy = 21,ABA = 22,OrderSol = 23,
	Kliff = 24,Justice = 25
} CharacterID;

typedef enum {
	Grey = 0,London = 1,Colony = 2,Russia = 3,
	China = 4,MayShip = 5,Zepp = 6,Nirvana = 7,
	Paris = 8,Hell = 9,Grove = 10,Verdant = 11,
	Castle = 12,Babylon = 13,PhantomCity = 14,Unknown = 15,
	Frasco = 16, Ad2172 = 17, Grave = 18, Heaven = 19,
	Korea = 20
} StageID;

typedef struct {
	int flag;
	int x;
	int y;
	int tx;
	int ty;
	unsigned short actno;
	short Localid;
	unsigned short angle;
	unsigned short padd;
} CREATE_ARG;

#endif