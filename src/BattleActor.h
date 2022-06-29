class BattleActor {
private:
	bool isPlayerControlled;
	bool isAlive;
	float hp;
	float mana;
	int nat;
	struct {
		float pat;
		float mat;
		float pdf;
		float mdf;
		float maxHP;
		float maxMana;
		int dNat;
	} stats;
public:

private:

public:
	//getter
	BattleActor* getAdress();
	void startTurn();
};