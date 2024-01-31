#include <cmath>
#include <conio.h>
#include <cstring>
#include <iostream>
#include <locale.h>
#include <random>
#include <string>
#include <time.h>

using namespace std;

int random(int min, int max);

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
	int strength_armor = 0;
public:
	int total_score = 0;
	int max_total_score = random(1300, 2000);
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
				cout << " Вы лечите себя на 15 hp, теперь у вас " << hp << "." << endl;
			}
		}
		else cout << "У вас нет зелий.";

	}
	void training() {
		money -= 100;
		damage_close += 10;
		total_score += random(20, 50);
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << (damage_close - 10) << " -> " << damage_close << endl
			<< "Баланс: " << (money + 100) << " -> " << money << endl << endl;
	}
	void show() {
		cout << "Характеристики: " << endl
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
		if (hp < 0) is_alive = false;
		if (strength_armor < 0) strength_armor += abs(strength_armor);



	}
	void shop() {
		cout << endl << "Справочный материал для магазина нажав на:" << endl << "y - Вы можете купить зелий за 100 монет " << endl << "n - Вы можите купить броню за 500 монет" << endl << "На любую другую кнопку чтобы выйти" << endl
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
					strength_armor += (100);
					money -= 500;
					cout << "Вы купиле броню, у которой  " << strength_armor << " прочность и " << money << " монет." << endl;
				}
			}
			else cout << "Недостаточно средств." << endl;
		}
		cout << "Вы покидаете магазин." << endl << endl;
	};
	void finish_stage() {}
};
int random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> random_num(min, max);
	return random_num(gen);
}

int main() {
	int k = 0;
	setlocale(LC_ALL, "RU");
	player user(100, 10, 100, "Ivan"); // ввод данных о персонажа
	enemy pav("Pavel", 100);
	cout << "Справочный материал нажав на:" << endl << "s - Вы отобразите характеристика " << endl << "t - Вы за 100 монет получите добавку к урону " << endl << "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl << "m - Вы можете сходить в магазин купить зелье" << endl << "h - Вы можете использовать зелье" << endl << endl;
	while (user.is_alive) {
		int userInput = _getch();
		switch (userInput) {
		case 104:user.healing(); break;
		case 100:user.damage(pav); break;
		case 115:user.show(); break;
		case 116:user.training(); break;
		case 103:user.guild(); break;
		case 109:user.shop(); break;
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

// АРЕНА должен рандомить защить-атака (шанс на оглушение) (шанс контр атаки после шита x 1.0 - x 1.3)
// СИСТЕМА КЛАССОВ
// total score (1300, 2000) k =1  = действия  должны влиять на него  как только ~> 1000 мы выводим "Знатные люди говорят о вас."  -> любое действие "На вас открыта охота." ->
// -> Открываеться босс 
// Щит всем! 
// рандомизация однотипного текста


