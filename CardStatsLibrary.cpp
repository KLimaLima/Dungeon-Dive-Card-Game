#include "CardStatsLibrary.h"

CardStatsLibrary::CardStatsLibrary()
{
}

CardStatsLibrary::~CardStatsLibrary()
{
}

int CardStatsLibrary::getAttack(int id)
{
	switch (id) {
	case -1:
		return 0;
		break;
	case 0:
		return 7;
		break;
	case 1:
		return 4;
		break;
	case 2:
		return 6;
		break;
	case 3:
		return 5;
		break;
	case 4:
		return 8;
		break;
	case 5:
		return 5;
		break;
	case 6:
		return 10;
		break;
	case 7:
		return 5;
		break;
	case 8:
		return 5;
		break;
	case 9:
		return 7;
		break;
	case 10:
		return 6;
		break;
	case 11:
		return 10;
		break;
	case 12:
		return 8;
		break;
	case 13:
		return 8;
		break;
	case 14:
		return 8;
		break;
	case 15:
		return 2;
		break;
	case 16:
		return 5;
		break;
	case 17:
		return 9;
		break;
	case 18:
		return 7;
		break;
	case 19:
		return 6;
		break;
	case 20:
		return 3;
		break;
	case 21:
		return 2;
		break;
	case 22:
		return 6;
		break;
	case 23:
		return 9;
		break;
	case 24:
		return 10;
		break;
	}
}

int CardStatsLibrary::getHP(int id)
{
	switch (id) {
	case -1:
		return 0;
	case 0:
		return 10;
		break;
	case 1:
		return 6;
		break;
	case 2:
		return 7;
		break;
	case 3:
		return 7;
		break;
	case 4:
		return 9;
		break;
	case 5:
		return 10;
		break;
	case 6:
		return 2;
		break;
	case 7:
		return 10;
		break;
	case 8:
		return 7;
		break;
	case 9:
		return 5;
		break;
	case 10:
		return 9;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return 5;
		break;
	case 13:
		return 5;
		break;
	case 14:
		return 8;
		break;
	case 15:
		return 5;
		break;
	case 16:
		return 7;
		break;
	case 17:
		return 10;
		break;
	case 18:
		return 9;
		break;
	case 19:
		return 9;
		break;
	case 20:
		return 6;
		break;
	case 21:
		return 4;
		break;
	case 22:
		return 8;
		break;
	case 23:
		return 10;
		break;
	case 24:
		return 10;
		break;
	}
}

string CardStatsLibrary::getpath(int id)
{
	switch (id) {
	case -1:
		return "Texture/NO CARDS OFFICIAL.png";//UBAH UTK TRANSPARENT CARD DONE
	case 0:
		return "Texture/Kimi.png";
		break;
	case 1:
		return "Texture/Arian.png";
		break;
	case 2:
		return "Texture/Knight.png";
		break;
	case 3:
		return "Texture/Khaice.png";
		break;
	case 4:
		return "Texture/Ligar.png";
		break;
	case 5:
		return "Texture/Deku.png";
		break;
	case 6:
		return "Texture/Gojou.png";
		break;
	case 7:
		return "Texture/Goku.png";
		break;
	case 8:
		return "Texture/Kaneki.png";
		break;
	case 9:
		return "Texture/Killua.png";
		break;
	case 10:
		return "Texture/Levi.png";
		break;
	case 11:
		return "Texture/Megumin.png";
		break;
	case 12:
		return "Texture/Nezuko.png";
		break;
	case 13:
		return "Texture/Tomioka.png";
		break;
	case 14:
		return "Texture/Yuno (1).png";
		break;
	case 15:
		return "Texture/Katak Boy.png";
		break;
	case 16:
		return "Texture/Red Dragon.png";
		break;
	case 17:
		return "Texture/Pokko.png";
		break;
	case 18:
		return "Texture/Kong.png";
		break;
	case 19:
		return "Texture/Wood Kong.png";
		break;
	case 20:
		return "Texture/Monster House.png";
		break;
	case 21:
		return "Texture/Ponti.png";
		break;
	case 22:
		return "Texture/Oktupus.png";
		break;
	case 23:
		return "Texture/Darkgon.png";
		break;
	case 24:
		return "Texture/Cruel.png";
		break;
	}
}
