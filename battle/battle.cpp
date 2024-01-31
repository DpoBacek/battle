#include <cmath>
#include <conio.h>
#include <cstring>
#include <iostream>
#include <locale.h>
#include <string>
#include <time.h>

using namespace std;


class enemy {
private:
	string name;
	int damage = 10;
public:
	int health;
	friend class player;
	enemy(string name, int health) {
		this->name = name;
		this->health = health;
	}
};

class player {
private:
	int hp;
	int damage_close;
	string name;
	int money;
	int hp_potion = 0;
	int	armor;
	int strength_armor;
public:
	bool is_alive = true;
	player(int hp, int damade, int money, string name) {
		this->damage_close = damade;
		this->hp = hp;
		this->money = money;
		this->name = name;
	}
	void damage(enemy& enemy) {
		if (enemy.health < 11) {
			cout << enemy.name << " умирает от рук " << name << endl; enemy.health -= damage_close;
		}
		else {
			enemy.health -= damage_close;
			cout << name << " наносит 10 урона " << enemy.name << endl;
			cout << "У " << enemy.name << " " << enemy.health << " hp." << endl << endl;
		}
	}
	void healing() {
		if (hp_potion >= 1) {

			if (hp == 100) { cout << name << " здоров." << endl << endl; }
			else {
				hp += 15;
				hp_potion -= 1;
				cout << " Вы лечите себя на 10 hp, теперь у вас " << hp << "." << endl;
			}
		}
		else cout << "У вас нет зелий.";

	}
	void training() {
		money -= 100;
		damage_close += 10;
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << (damage_close - 10) << " -> " << damage_close << endl
			<< "Баланс: " << (money + 100) << " -> " << money << endl << endl;
	}
	void show() {
		cout << "Характеристики: " << endl
			<< "Здоровье: " << hp << endl
			<< "Урон: " << damage_close << endl
			<< "Баланс: " << money << endl
			<< "Имя: " << name << endl << endl;

	}
	void guild() {
		//srand(time(NULL));
		int r_damage = 5 + rand() % 25;
		int r_pay = 40 + rand() % 100;
		int r_chanse = 1 + rand() % 100;
		int r_event = 1 + rand() % 1;

		switch (r_event) {
		case 81: cout << "Идя на задание вы нашли потеренный кошелёк, вы искали хозяина этого кошелька полчаса, но так и не нашил и решили забрать его себе.\nВы получаете 100 монет." << endl; money += 100; break;
		case 87: cout << "Когда вы шли на задание из травы выпрыгивает змея и кусает вас.\nВы теряете 10 hp." << endl; hp -= 10; break;
		case 1:  cout << "Когда вы шли на задание в вас влетает на сверхзвуковой кабочок.\nВы теряете " << (hp - 1) << " hp." << endl; hp = hp - (hp - 1); break;
		default:break;
		}


		cout << "Взяв задание на " << r_pay << ".";
		if (r_chanse <= 20) {
			cout << " Вы выполнели его без получения урона. " << endl;
			money += r_pay;
		}
		else if (r_chanse > 20 && r_chanse < 90) {
			cout << "Вы выполнели его, но всё прошло не гладко и вы получили " << r_damage << " урона." << endl;
			money += r_pay;
			hp -= r_damage;
		}
		else if (r_chanse >= 90) {
			cout << "Вы проваливаете задание получив " << r_damage * 2 << " урона." << endl;
			hp -= r_damage * 2;
		}
		if (hp < 0) is_alive = false;


	}
	void shop() {
		cout << "Вы можете купить зелье возтановления за 100 монет или купить броню." << endl
			<< "Хотите купить? Нажмите 'y' если хотите купить зелье и 'n' если броню " << endl;
		int userInput_shop = _getch();
		int number;
		if (userInput_shop == 121) {
			cout << "Сколько зелий вы хотите купить?" << endl << "Введите число: "; cin >> number;
			if (money > (100 * number)) {
				money -= (100 * number);
				hp_potion += (1 * number);
				cout << "Вы купиле зелье теперь у вас " << hp_potion << " зелий и " << money << " монет." << endl;
			}
			else cout << "Недостаточно средств.";
		}
		else if (userInput_shop == 110) {
			if (money > 500) {
				money -= 500;
				hp_potion += (1);
				cout << "Вы купиле зелье теперь у вас " << hp_potion << " зелий и " << money << " монет." << endl;
			}
			else cout << "Недостаточно средств.";
		}

		else cout << "adaasd";
	};
};



int main() {
	setlocale(LC_ALL, "RU");

	player ivan(100, 10, 100, "Ivan");
	enemy pav("Pavel", 100);
	cout << "Справочный материал нажав на:" << endl << "s - Вы отобразите характеристика " << endl << "t - Вы за 100 монет получите добавку к урону " << endl << "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl << "f - Вы можете сходить в магазин купить зелье" << endl;
	while (ivan.is_alive) {
		int userInput = _getch();
		switch (userInput) {
		case 104:ivan.healing(); break;
		case 100:ivan.damage(pav); break;
		case 115:ivan.show(); break;
		case 116:ivan.training(); break;
		case 103:ivan.guild(); break;
		case 102:ivan.shop(); break;
		default:cout << "Введено недопустимое действие!" << endl;
		}
	}

	cout << endl << "Вы мертвы...";

}