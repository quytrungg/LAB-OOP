#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <conio.h>

#define SWHP 1000
#define SWATK 12
#define KNHP 1500
#define KNATK 18
#define SPHP 800
#define SPATK 8

class Soldier;
class Visitor;
class Swordman;
class Knight;
class Spikeman;
class Player;
class GameRule;
class SwordmanRule;
class KnightRule;
class SpikemanRule;
class Game;

class RandomIntegerGenerator {
public:
	RandomIntegerGenerator() { srand(time(NULL)); }
	int next() { return rand(); }
	int next(int ceiling) { return rand() % ceiling; }
	int next(int left, int right) { return left + rand() % (right + 1 - left); }
};

class Soldier {
protected:
	int HP;
	int ATK;
public:
	Soldier();
	Soldier(int hp, int atk) { HP = hp; ATK = atk; }
	int gethp() { return HP; }
	void sethp(int hp) { HP = hp; }
	int getatk() { return ATK; }
	void setatk(int atk) { ATK = atk; }
	bool isAlive() { return HP > 0; }
	virtual void attackSoldier(Soldier* s) = 0;
	virtual std::string displaySoldier() = 0;
};

class Visitor {
public:
	virtual void attack(Swordman& s) = 0;
	virtual void attack(Knight& k) = 0;
	virtual void attack(Spikeman& s) = 0;
	virtual void hitBy(Swordman& s) = 0;
	virtual void hitBy(Knight& k) = 0;
	virtual void hitBy(Spikeman& s) = 0;
	void selectAttack(Soldier* s);
};

class Swordman : public Soldier, public Visitor {
public:
	Swordman(int hp, int atk);
	void attack(Swordman& s);
	void attack(Knight& k);
	void attack(Spikeman& s);
	void hitBy(Swordman& s);
	void hitBy(Knight& k);
	void hitBy(Spikeman& s);
	void attackSoldier(Soldier* s);
	std::string displaySoldier();
};

class Knight : public Soldier, public Visitor {
public:
	Knight(int hp, int atk);
	void attack(Swordman& s);
	void attack(Knight& k);
	void attack(Spikeman& s);
	void hitBy(Swordman& s);
	void hitBy(Knight& k);
	void hitBy(Spikeman& s);
	void attackSoldier(Soldier* s);
	std::string displaySoldier();
};

class Spikeman : public Soldier, public Visitor {
public:
	Spikeman(int hp, int atk);
	void attack(Swordman& s);
	void attack(Knight& k);
	void attack(Spikeman& s);
	void hitBy(Swordman& s);
	void hitBy(Knight& k);
	void hitBy(Spikeman& s);
	void attackSoldier(Soldier* s);
	std::string displaySoldier();
};

class Player {
private:
	std::vector<Soldier*> _pieces;
public:
	std::vector<Soldier*>& pieces() { return _pieces; }
	void displayPieces();
};

class GameRule {
public:
	virtual bool satisfaction(Player p) = 0;
	virtual void applyPieces(Player p) = 0;
};

class SwordmanRule : public GameRule {
public:
	bool satisfaction(Player p);
	void applyPieces(Player p);
};

class KnightRule : public GameRule {
public:
	bool satisfaction(Player p);
	void applyPieces(Player p);
};

class SpikemanRule : public GameRule {
public:
	bool satisfaction(Player p);
	void applyPieces(Player p);
};

class Game {
private:
	Player red, blue;
	std::vector<GameRule*> rules;
	short turns;
public:
	Game();
	int getrules() {
		return rules.size();
	}
	void startGame();
	void playGame();
	void displayGame();
	void applyRules(Player p);
	int checkWin();
};

#endif // !HEADER_H
