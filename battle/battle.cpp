#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <locale.h>
#include <random>
#include <string>
#include <time.h>

using namespace std;
static int random(int min, int max);
class Player;
class Enemy;
void fight(int player_act, int enemy_act, Enemy& enemy);
Enemy r_ememy();
Player init();



class Enemy {
private:
	int hp;
	int damage;
	string name;
	int strength_armor;
public:
	bool is_alive = true;
	friend class Player;
	friend void fight(int player_act, int enemy_act, Enemy& enemy);
	Enemy() {}
	Enemy(int hp, int damage, int strength_armor, string name) {
		set_info(hp, damage, strength_armor, name);
	}
	void set_info(int hp, bool is_alive) {
		this->hp = hp;
		this->is_alive = is_alive;
	}
	void show() {
		cout << "У " << name << " " << hp << "hp" << " и его урон составляет " << damage << " едениц." << endl;
	}
	void set_info(int hp, int damage, int strength_armor, string name) {
		this->damage = damage;
		this->hp = hp;
		this->strength_armor = strength_armor;
		this->name = name;
	}
	void e_shield() {}
};

class Player {
private:
	string class_hero;
	int hp;
	int damage_close;
	int sword_damage = 1;
	int counterattack;
	string name;
	int money;
	int hp_potion = 0;
	int strength_armor = 0;
public:
	int total_score = 0;
	int max_total_score = random(1300, 2000);
	bool is_alive = true;
	friend class Enemy;
	friend void fight(int player_act, int enemy_act, Enemy& enemy);

	Player(string class_hero, int hp, int damage, int money, int strength_armor, string hero_name) {
		set_info(class_hero, hp, damage, money, strength_armor, hero_name);
	}

	void set_info(int hp, bool is_alive) {
		this->hp = hp;
		this->is_alive = is_alive;
	}
	void set_info(string class_hero, int hp, int damage, int money, int strength_armor, string hero_name) {
		this->damage_close = damage;
		this->hp = hp;
		this->money = money;
		this->class_hero = class_hero;
		this->strength_armor = strength_armor;
		name = hero_name;
	}
	void training() {
		money -= 75;
		damage_close += 4;
		total_score += random(10, 30);
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << (damage_close - 4) << " -> " << damage_close << endl
			<< "Баланс: " << (money + 75) << " -> " << money << endl << endl;
	}
	void show() {
		cout << "Характеристики: " << endl
			<< "Класс: " << class_hero << endl
			<< "Здоровье: " << hp << endl
			<< "Урон: " << damage_close << endl
			<< "Баланс: " << money << endl
			<< "Имя: " << name << endl
			<< "Состояние брони: " << strength_armor << "%" << endl << endl;


	}
	void guild() {
		int r_event = random(1, 100);
		int r_damage = random(5, 25);
		int r_chance = random(1, 100);
		int r_pay = random(40, 100);

		switch (r_event) {
		case 81: cout << endl << "\tИдя на задание вы нашли потеренный кошелёк, вы искали хозяина этого кошелька полчаса,\nно так и не нашил и решили забрать его себе.\n\t\tВы получаете 100 монет." << endl << endl; money += 100; break;
		case 87: cout << endl << "\tКогда вы шли на задание из травы выпрыгивает змея и кусает вас.\n\t\tВы теряете 10 hp." << endl << endl; hp -= 10; break;
		case 1:  cout << endl << "\tКогда вы шли на задание в вас влетает на сверхзвуковой кабочок.\n\t\tВы теряете " << (hp - 30) << " hp." << endl << endl; hp -= (hp - 30); break;
		default:break;
		}

		cout << "Взяв задание на " << r_pay << " монеты.";
		if (r_chance <= 20) {
			cout << "Вы выполнели его без получения урона. " << endl;
			money += r_pay;
			total_score += random(30, 50);
		}
		else if (r_chance > 20 && r_chance < 90) {
			cout << "Вы выполнели его, но всё прошло не гладко и вы получили " << r_damage << " урона." << endl;
			money += r_pay;
			if (strength_armor > 0) strength_armor -= r_damage;
			else hp -= r_damage;
			total_score += random(20, 40);
		}
		else if (r_chance >= 90) {
			cout << "Вы проваливаете задание получив " << r_damage * 2 << " урона." << endl;
			if (strength_armor > 0) strength_armor -= r_damage * 2;
			else hp -= r_damage * 2;
			total_score += random(0, 10);
		}
		if (hp <= 0) is_alive = false;



	}
	void shop() {
		cout << endl << "Справочный материал для магазина нажав на:" << endl << "y - Вы можете купить зелий за 100 монет " << endl << "n - Вы можите купить броню за 500 монет" << endl << "s - Вы можите купить или улучшить меч за 150 монет" << endl << "На любую другую кнопку чтобы выйти" << endl
			<< "Что хотите купить?" << endl << endl;
		int userInput_shop = _getch();
		int number;
		if (userInput_shop == 121) {
			cout << "Сколько зелий вы хотите купить?" << endl << "Введите число: "; cin >> number;
			if (money >= (100 * number)) {
				money -= (100 * number);
				hp_potion += (1 * number);
				cout << "Вы купиле зелье теперь у вас " << hp_potion << " зелий и " << money << " монет." << endl;
			}
			else cout << "Недостаточно средств." << endl;
		}
		else if (userInput_shop == 110) {
			if (money > 500) {
				if (strength_armor >= 100) cout << "Ваша броня в идеальном состоянии.";
				else {
					strength_armor = (100);
					money -= 500;
					cout << "Вы купиле броню, у которой  " << strength_armor << " прочность и " << money << " монет." << endl;
				}
			}
			else cout << "Недостаточно средств." << endl;
		}
		else if (userInput_shop == 115) {
			if (money > 150) {
				sword_damage += 0.2;
				money -= 150;
				if (sword_damage == 1) cout << "Вы успешно купили меч ваш урон состовляет: " << (damage_close * sword_damage);
				cout << "Вы купиле броню, у которой  " << strength_armor << " прочность и " << money << " монет." << endl;
			}
			else cout << "Недостаточно средств." << endl;

		}
		cout << "Вы покидаете магазин." << endl << endl;
	};
	void clear() {
		system("cls");
		cout << "Справочный материал нажав на:" << endl << "s - Вы отобразите характеристика " << endl << "t - Вы за 100 монет получите добавку к урону " << endl << "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl << "m - Вы можете сходить в магазин купить зелье" << endl << "a - Вы можете сходить на арена " << endl << "h - Вы можете использовать зелье" << endl << "c - Очистка экрана" << endl << endl;

	}
	void healing() {
		if (hp_potion >= 1) {
			if (hp == 100) { cout << name << " здоров." << endl << endl; }
			else {
				hp += 25;
				hp_potion -= 1;
				cout << "Вы лечите себя на 15 hp, теперь у вас " << hp << "." << endl;
			}
		}
		else cout << "У вас нет зелий.";
	}
	int damage(Enemy enemy) { // урона по игроку (0 - нанесение урона, 1 - ипользование щита)
		if (random(1, 4) == 4) { return 1; }
		else { return 0; }
	}
	int e_damage(Enemy enemy) { // урон по врагу (0 - нанесение урона, 1 - ипользование щита)
		return 0;
	}
	int shield() {
		return 1;
	}
	void arena() {
		Enemy enemy = r_ememy();
		int r_damage_a = random(5, 25);
		cout << "Вы попадаете на арену и вашим врагом стоноваться " << enemy.name << endl;
		cout << "Ваши действия?" << endl << "a - Нанести урон врагу" << endl << "s - Спрятаться за щитом" << endl << "h - Использовать зелье" << endl << "q - Попытаться сбежать" << endl << endl;
		enemy.show();

		while (enemy.is_alive) {
			if (is_alive == false) return;
			cout << endl << "Что вы предпримите? ";
			int userInput_arena = _getch();
			cout << endl;
			switch (userInput_arena) {
			case 97: fight(0, damage(enemy), enemy); break; // Атака по врагу 
			case 104:fight(2, damage(enemy), enemy); ; break; // Лечение 
			case 115:fight(1, damage(enemy), enemy); break; // Использование щит
			case 113: cout << "Вы смогли сбежать с арены, но всё прошло не так гладко...\nВы получили " << r_damage_a << " урона."; hp -= r_damage_a; return;
			}
		}
		total_score += random(50, 130);
		cout << "Вы покинули арену." << endl << endl;
	};
	void fight(int player_act, int enemy_act, Enemy& enemy) {
		if (player_act == 0 && enemy_act == 0) {
			if (enemy.hp <= damage_close) { // Удар по противнику 
				enemy.hp = 0;
				cout << "Вы выйграли этот бой. " << endl << endl;
				enemy.is_alive = false;
				enemy.set_info(enemy.hp, enemy.is_alive);
				return;
			}
			else if (enemy.hp > damage_close) {
				enemy.hp -= damage_close;
				cout << "Вы нанесли " << damage_close << " урона врагу, у врага остольсь " << enemy.hp << " hp." << endl;
			}
			if (hp <= enemy.damage) { // Удар по играку
				hp = 0;
				cout << "Вы проиграли этот бой. " << endl;
				is_alive = false;
				set_info(hp, is_alive);
				return;
			}
			else if (hp > enemy.damage) {
				hp -= damage_close;
				cout << "Вы получили " << enemy.damage << " урона от " << enemy.name << ", у вас осталось " << hp << " hp." << endl;
			}
		}
		if (player_act == 1 && enemy_act == 0) { cout << "Вы успешно парируете удар щитом"; }
		if (player_act == 0 && enemy_act == 1) { cout << "Вы попытались ударить, но ваш противние парировал удар шитом. "; }
		if (player_act == 1 && enemy_act == 1) { cout << "Вы пробуете защититься щитом ... как и ваш противник."; }
		if (player_act == 2) { hp -= enemy.damage; cout << "Противник замечает что вы пытаетесь отхалиться, вы получили " << enemy.damage << " урона от " << enemy.name << ", у вас осталось " << hp << " hp." << endl; }
		set_info(hp, is_alive);
		enemy.set_info(enemy.hp, enemy.is_alive);
	}
};






static int random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> random_num(min, max);
	return random_num(gen);
}

Player init() {
	string hero_name;
	int i = 0;
	Player user("0", 0, 0, 0, 0, "0");
	cout << "Придумайте себе имя: "; cin >> hero_name;
	cout << endl << "\tВыберите класс" << endl << "\ta - Assissin " << endl << "\tw - Warrior " << endl << "\tp - Paladin " << endl;
	while (i <= 3) {
		int userInput_class = _getch();
		i++;
		if (userInput_class == 97) { user.set_info("Assissin", 50, 20, 100, 0, hero_name); system("cls"); cout << "Вы выбрали класс Assissin" << endl << endl; break; }
		else if (userInput_class == 119) { user.set_info("Warrior", 100, 12, 100, 0, hero_name); system("cls"); cout << "Вы выбрали класс Warrior" << endl << endl; break; }
		else if (userInput_class == 112) { user.set_info("Paladin", 80, 10, 100, 100, hero_name); system("cls"); cout << "Вы выбрали класс Paladin" << endl << endl; break; }
		else if (userInput_class == 103) { user.set_info("God", 10000000, 100, 10000000, 100, hero_name); system("cls"); cout << "Вы выбрали класс God" << endl << endl; break; }
		else { cout << "Введено недопустимое действие!" << endl; }
		if (i == 2) user.set_info("Peasant", 50, 5, 10, 0, hero_name);
	}
	return user;
}
Enemy r_ememy() {
	Enemy enemy(0, 0, 0, "0");
	int r_ememy = random(1, 10);
	switch (r_ememy) {
	case 1:enemy.set_info(200, 20, 0, "Тигр"); break;
	case 2:enemy.set_info(100, 10, 50, "Бандит"); break;
	case 3:enemy.set_info(100, 10, 70, "Бандит"); break;
	case 4:enemy.set_info(100, 8, 10, "Бандит"); break;
	case 5:enemy.set_info(100, 50, 150, "Герой"); break;
	case 6:enemy.set_info(50, 10, 0, "Волк"); break;
	case 7:enemy.set_info(100, 25, 100, "Гладиатор"); break;
	case 8:enemy.set_info(70, 12, 0, "Волк-вожак"); break;
	case 9:enemy.set_info(30, 9, 0, "Ослабевший волк"); break;
	case 10:enemy.set_info(100, 15, 100, "Главарь бандитов"); break;
	}
	return enemy;
}





int main() {
	int k = 0;
	setlocale(LC_ALL, "RU");
	Player user = init();
	Enemy enemy = r_ememy();

	cout << "Справочный материал нажав на:" << endl << "s - Вы отобразите характеристика " << endl << "t - Вы за 100 монет получите добавку к урону " << endl << "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl << "m - Вы можете сходить в магазин купить зелье" << endl << "a - Вы можете сходить на арена " << endl << "h - Вы можете использовать зелье" << endl << "c - Очистка экрана" << endl << endl;
	while (user.is_alive) {
		int userInput = _getch();
		switch (userInput) {
		case 104:user.healing(); break;
		case 115:user.show(); break;
		case 116:user.training(); break;
		case 103:user.guild(); break;
		case 109:user.shop(); break;
		case 99:user.clear(); break;
		case 97:user.arena(); break;
		default:cout << "Введено недопустимое действие!" << endl; break;
		}
		if (user.total_score >= user.max_total_score && k == 0) k++;
		switch (k) {
		case 1:cout << endl << endl << "------------------------------------------" << endl << "Знатные люди говорят о вас." << endl << "------------------------------------------" << endl << endl << endl; k++; break;
		case 2:cout << endl << endl << "------------------------------------------" << endl << "На вас открыта охота." << endl << "------------------------------------------" << endl << endl << endl; k++;   break;
			//case 3: finish_stage; break;
		}

	}
	cout << endl << "Вы мертвы...";


}


// АРЕНА должен рандомить защить-атака				 !!!!!!!!!!(шанс на оглушение) (шанс контр атаки после шита x 1.0 - x 1.3) !!!!!!!!!!
// 
// total score (1300, 2000) k =1  = действия  должны влиять на него  как только ~> 1000 мы выводим "Знатные люди говорят о вас."  -> любое действие "На вас открыта охота." ->
// -> Открываеться босс 

// рандомизация однотипного текста
// не наноситься урон
