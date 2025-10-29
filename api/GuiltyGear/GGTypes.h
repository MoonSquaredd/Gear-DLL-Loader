#ifndef GGTypes
#define GGTypes

typedef enum {
	None = 0, Sol = 1, Ky = 2, May = 3,
	Millia = 4, Axl = 5, Potemkin = 6, Chipp = 7,
	Eddie = 8, Baiken = 9, Faust = 10, Testament = 11,
	Jam = 12, Anji = 13, Johnny = 14, Venom = 15,
	Dizzy = 16, Slayer = 17, INo = 18, Zappa = 19,
	Bridget = 20, RoboKy = 21, ABA = 22, OrderSol = 23,
	Kliff = 24, Justice = 25
} CharacterID;

typedef enum {
	Grey = 0, London = 1, Colony = 2, Russia = 3,
	China = 4, MayShip = 5, Zepp = 6, Nirvana = 7,
	Paris = 8, Hell = 9, Grove = 10, Verdant = 11,
	Castle = 12, Babylon = 13, PhantomCity = 14, Unknown = 15,
	Frasco = 16, Ad2172 = 17, Grave = 18, Heaven = 19,
	Korea = 20
} StageID; //Add 20 for reload variants and 40 for slash variants

typedef enum {
	GM_Load = 0, GM_Save = 1, GM_VGA = 2, GM_CharMenu = 4,
	GM_Init = 5, GM_Main = 6, GM_Title = 9, GM_Debug = 12,
	GM_CharSelect = 15, GM_StageSelect = 16, GM_VS = 17, GM_End = 19,
	GM_Win = 20, GM_Options = 25, GM_Mission = 36, GM_Story = 42,
	GM_Credit = 44, GM_Movie = 45, GM_MissionWin = 47, GM_SurvivalCheck = 48,
	GM_Gallery = 49, GM_SurvivalMain = 50, GM_TeamVS = 51, FRAMERATE_TEST = 52,
	GM_Replay = 53, GM_SoundMenu = 56
} GameModeID;

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
