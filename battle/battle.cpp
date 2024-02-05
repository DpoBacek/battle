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

int random(int min, int max);
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
	// Установка информации о враге 
	Enemy() {}
	Enemy(int hp, int damage, int strength_armor, string name) {
		set_info(hp, damage, strength_armor, name);
	}
	void set_info(int hp, bool is_alive) {
		this->hp = hp;
		this->is_alive = is_alive;
	}
	void set_info(int hp, int damage, int strength_armor, string name) {
		this->damage = damage;
		this->hp = hp;
		this->strength_armor = strength_armor;
		this->name = name;
	}
	// Отображение некоторых характеристик врага
	void show() {
		cout << "У " << name << " " << hp << "hp" << " и его урон составляет " << damage << " едениц." << endl;
	}
};


class Player {
private:
	string class_hero;
	int hp;
	int damage_close;
	double sword_damage = 1;
	double counterattack = 1;
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
	// Установка информации о игроке
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
	// Улучшение ближнего боя 
	void training() {
		money -= 75;
		damage_close = damage_close + 5;
		total_score += random(10, 30);
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << ((damage_close - 5) * sword_damage) << " -> " << (damage_close * sword_damage) << endl
			<< "Баланс: " << (money + 75) << " -> " << money << endl << endl;
	}
	// Отображение характеристик
	void show() {
		cout << "Характеристики: " << endl
			<< "Класс: " << class_hero << endl
			<< "Здоровье: " << hp << endl
			<< "Урон: " << (damage_close * sword_damage) << endl
			<< "Баланс: " << money << endl
			<< "Имя: " << name << endl
			<< "Кол-во зелий: " << hp_potion << endl
			<< "Состояние брони: " << strength_armor << "%" << endl << endl;


	}
	// Место, где можно раздобыть золото 
	void guild() {
		int r_event = random(1, 100);
		int r_damage = random(5, 20);
		int r_chance = random(1, 100);
		int r_pay = random(60, 150);

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
			if (strength_armor >= r_damage) strength_armor -= r_damage;
			else if (strength_armor < r_damage) strength_armor = 0;
			else hp -= r_damage;
			total_score += random(20, 40);
		}
		else if (r_chance >= 90) {
			cout << "Вы проваливаете задание получив " << r_damage * 2 << " урона." << endl;
			if (strength_armor >= (r_damage * 2)) strength_armor -= r_damage * 2;
			else if (strength_armor < (r_damage * 2)) strength_armor = 0;
			else hp -= r_damage * 2;
			total_score += random(0, 10);
		}
		if (hp <= 0) is_alive = false;



	}
	// Магазин
	void shop() {
		cout << endl << "Справочный материал для магазина нажав на:" << endl
			<< "y - Вы можете купить зелий за 100 монет " << endl
			<< "n - Вы можите купить броню за 500 монет" << endl
			<< "s - Вы можите купить или улучшить меч за 150 монет" << endl
			<< "На любую другую кнопку чтобы выйти" << endl
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

				if (sword_damage <= 1) {
					money -= 150;
					sword_damage += 0.2;
					cout << "Вы успешно купили меч ваш урон состовляет: " << (damage_close * sword_damage) << endl;
				}
				else {
					money -= 150;
					sword_damage += 0.2;
					cout << "Вы улучили меч ваш урон состовляет: " << (damage_close * sword_damage) << endl;
				}
			}
			else cout << "Недостаточно средств. " << endl;

		}
		cout << "Вы покидаете магазин." << endl << endl;
	}
	// Очистка консали
	void clear() {
		system("cls");
		cout << "Справочный материал нажав на:" << endl
			<< "s - Вы отобразите характеристика " << endl
			<< "t - Вы за 75 монет получите добавку к урону " << endl
			<< "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl
			<< "m - Вы можете сходить в магазин купить зелье" << endl
			<< "a - Вы можете сходить на арена " << endl
			<< "h - Вы можете использовать зелье" << endl
			<< "c - Очистка экрана" << endl << endl;

	}
	// Лечение
	void healing() {
		if (hp_potion >= 1) {
			if (hp >= 100) { cout << name << " здоров." << endl << endl; }
			else if ((hp + 25) >= 100) {
				hp = 100;
				hp_potion -= 1;
				cout << "Вы лечите себя по полной, теперь у вас " << hp << " hp." << endl;
			}
			else {
				hp += 25;
				hp_potion -= 1;
				cout << "Вы лечите себя на 25 hp, теперь у вас " << hp << " hp." << endl;
			}
		}
		else cout << "У вас нет зелий.";
	}
	// Урон по играку
	int damage(Enemy enemy) { // урона по игроку (0 - нанесение урона, 1 - ипользование щита)
		if (random(1, 4) == 4) { return 1; }
		else { return 0; }
	}
	// Арена, где можно сражаться с разными врагами
	void arena() {
		Enemy enemy = r_ememy();
		int r_damage_a = random(5, 25);

		cout << "Вы попадаете на арену и вашим врагом стоноваться " << enemy.name << endl;
		cout << "Ваши действия?" << endl
			<< "a - Нанести урон врагу" << endl
			<< "s - Спрятаться за щитом" << endl
			<< "h - Использовать зелье" << endl
			<< "q - Попытаться сбежать" << endl << endl;
		enemy.show();

		while (enemy.is_alive) {
			if (is_alive == false) return;
			cout << endl << "Что вы предпримите? ";
			int userInput_arena = _getch();
			cout << endl;
			switch (userInput_arena) {
			case 97: fight(0, damage(enemy), enemy); break; // Атака по врагу 
			case 115:fight(1, damage(enemy), enemy); break; // Использование щит
			case 104:if (hp_potion >= 1) fight(2, damage(enemy), enemy); else cout << "У вас нет зелий." << endl; break; // Лечение 
			case 113: cout << "Вы смогли сбежать с арены, но всё прошло не так гладко...\nВы получили " << r_damage_a << " урона."; hp -= r_damage_a; return;
			}
		}

		total_score += random(50, 130);
		int reward = random(0, 75);
		money += reward;
		damage_close = damage_close + 5;
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << ((damage_close - 5) * sword_damage) << " -> " << (damage_close * sword_damage) << endl
			<< "Баланс: " << (money - reward) << " -> " << money << endl << endl;
		cout << "Вы покинули арену." << endl << endl;
	}
	// Проработка действий на арене
	void fight(int player_act, int enemy_act, Enemy& enemy) {
		if (player_act == 0 && enemy_act == 0) {
			// Действия с противником
			if (enemy.hp <= (damage_close * sword_damage * counterattack) && enemy.strength_armor <= 0) {  // Смерть противника 
				enemy.hp = 0;
				cout << "Вы выйграли этот бой. " << endl << endl;
				enemy.is_alive = false;
				enemy.set_info(enemy.hp, enemy.is_alive);
				return;
			}
			else if (enemy.hp > (damage_close * sword_damage * counterattack) && enemy.strength_armor <= 0) { // Удар по противнику 
				enemy.hp -= (damage_close * sword_damage * counterattack);
				cout << "Вы нанесли " << (damage_close * sword_damage * counterattack) << " урона врагу, у врага остольсь " << enemy.hp << " hp." << endl;
			}
			else if (enemy.strength_armor <= (damage_close * sword_damage * counterattack)) { // Разрушение брони противника
				enemy.strength_armor = 0;
				enemy.hp -= ((damage_close * sword_damage * counterattack) / 4);
				cout << "Вы сломали броню противника. У него осталось " << enemy.hp << " hp." << endl << endl;
			}
			else if (enemy.strength_armor > (damage_close * sword_damage * counterattack)) { // Урон по броне противника
				enemy.strength_armor -= (damage_close * sword_damage * counterattack);
				enemy.hp -= ((damage_close * sword_damage * counterattack) / 4);
				cout << "Вы нанесли урон по броне противника её прочность состовляет " << enemy.strength_armor << " hp," << endl
					<< "но вас всё же удалось нанести урон у него осталось " << enemy.hp << " hp." << endl << endl;
			}

			if (random(1, 15) == 1) {
				cout << "Этой атакой вы оглушили противника у вас есть шанс ударить его снова." << endl;
				return;
			}

			// Действия с игроком
			if (hp <= enemy.damage && strength_armor <= 0) { // Смерть игрока
				hp = 0;
				cout << "Вы проиграли этот бой. " << endl;
				is_alive = false;
				set_info(hp, is_alive);
				return;
			}
			else if (hp > enemy.damage && strength_armor <= 0) { // Урон по hp игрока
				hp -= enemy.damage;
				cout << "Вы получили " << enemy.damage << " урона от " << enemy.name << ", у вас осталось " << hp << " hp." << endl;
			}
			else if (strength_armor > enemy.damage) { // Урон про броне игрока
				strength_armor -= enemy.damage;
				hp -= (enemy.damage / 4);
				cout << "Вас защищает ваша броня её прочность состовляет " << strength_armor << " hp," << endl
					<< "но броня не смогла заблокивровать всё урон, урон по hp составил " << hp << endl << endl;

			}
			else if (strength_armor <= enemy.damage) { // Разрушение брони игрока
				strength_armor = 0;
				hp -= (enemy.damage / 4);
				cout << "Вас защищает ваша в последний раз. Урон по hp составил " << hp << endl << endl;
			}
			counterattack = 1;
		}

		if (player_act == 1 && enemy_act == 0) {
			cout << "Вы успешно парируете удар щитом." << endl;
			counterattack = 1.2;
		}

		if (player_act == 0 && enemy_act == 1) {
			cout << "Вы попытались ударить, но ваш противние парировал удар шитом." << endl;
			counterattack = 1;
		}

		if (player_act == 1 && enemy_act == 1) {
			cout << "Вы пробуете защититься щитом ... как и ваш противник." << endl;
			counterattack = 1.2;
		}

		if (player_act == 2) {
			hp -= enemy.damage; cout << "Противник замечает что вы пытаетесь отхалиться, вы получили " << enemy.damage << " урона от " << enemy.name << ", у вас осталось " << hp << " hp." << endl;
			counterattack = 1;
		}

		set_info(hp, is_alive);
		enemy.set_info(enemy.hp, enemy.is_alive);
	}

	void finish_stage() {
		Enemy enemy;
		enemy.set_info(1000, 30, 200, "Червь Абсурда: Аномальный Аннигилятор Астралдименсий");


		cout << "Вы встречаете печального известного " << enemy.name << endl;
		cout << "Ваши действия?" << endl
			<< "a - Нанести урон врагу" << endl
			<< "s - Спрятаться за щитом" << endl
			<< "h - Использовать зелье" << endl << endl;
		enemy.show();

		while (enemy.is_alive) {
			if (is_alive == false) return;
			cout << endl << "Что вы предпримите? ";
			int userInput_arena = _getch();
			cout << endl;
			switch (userInput_arena) {
			case 97: fight(0, damage(enemy), enemy); break; // Атака по боссу 
			case 115:fight(1, damage(enemy), enemy); break; // Использование щит
			case 104:if (hp_potion >= 1) fight(2, damage(enemy), enemy); else cout << "У вас нет зелий." << endl; break; // Лечение 
			}
		}

		total_score += random(100, 400);
		int reward = random(100, 350);
		money += reward;
		damage_close = damage_close + 20;
		cout << "Обновление в ваших характеристиках: " << endl
			<< "Урон: " << ((damage_close - 20) * sword_damage) << " -> " << (damage_close * sword_damage) << endl;
	}

};


int random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> random_num(min, max);
	return random_num(gen);
}

// Начало для игрока
Player init() {
	string hero_name;
	int i = 0;
	Player user("0", 0, 0, 0, 0, "0");
	cout << "Придумайте себе имя: "; cin >> hero_name;
	cout << endl << "\tВыберите класс" << endl
		<< "\ta - Assissin " << endl
		<< "\tw - Warrior " << endl
		<< "\tp - Paladin " << endl;

	while (i <= 3) {
		int userInput_class = _getch();
		i++;
		if (userInput_class == 97) {
			user.set_info("Assissin", 50, 20, 100, 0, hero_name);
			system("cls");
			cout << "Вы выбрали класс Assissin" << endl << endl;
			break;
		}
		else if (userInput_class == 119) {
			user.set_info("Warrior", 100, 15, 100, 0, hero_name);
			system("cls");
			cout << "Вы выбрали класс Warrior" << endl << endl;
			break;
		}
		else if (userInput_class == 112) {
			user.set_info("Paladin", 80, 10, 100, 100, hero_name);
			system("cls");
			cout << "Вы выбрали класс Paladin" << endl << endl;
			break;
		}
		else if (userInput_class == 103) {
			user.set_info("God", 10000000, 100, 10000000, 1000, hero_name);
			system("cls");
			cout << "Вы выбрали класс God" << endl << endl;
			break;
		}
		else { cout << "Введено недопустимое действие!" << endl; }

		if (i == 2) user.set_info("Peasant", 50, 5, 10, 0, hero_name);
	}
	return user;
}
// Случайный враг на арену
Enemy r_ememy() {
	Enemy enemy(0, 0, 0, "0");
	int r_ememy = random(1, 20);
	switch (r_ememy) {
	case 1:enemy.set_info(50, 13, 200, "Страж-Каменщик"); break;
	case 2:enemy.set_info(100, 10, 50, "Бандит"); break;
	case 3:enemy.set_info(100, 10, 70, "Бандит"); break;
	case 4:enemy.set_info(100, 8, 10, "Бандит"); break;
	case 5:enemy.set_info(100, 50, 150, "Герой"); break;
	case 6:enemy.set_info(50, 10, 0, "Волк"); break;
	case 7:enemy.set_info(100, 25, 100, "Гладиатор"); break;
	case 8:enemy.set_info(70, 12, 0, "Волк-вожак"); break;
	case 9:enemy.set_info(30, 9, 0, "Ослабевший волк"); break;
	case 10:enemy.set_info(100, 15, 100, "Главарь бандитов"); break;
	case 11:enemy.set_info(70, 30, 1, "Алхимик-Животворец"); break;
	case 12:enemy.set_info(100, 5, 300, "Паладин-Сияющий Защитник"); break;
	case 13:enemy.set_info(90, 20, 70, "Варвар-Колосс Гнева"); break;
	case 14:enemy.set_info(100, 10, 10, "Провидец-Видящий Судьбу"); break;
	case 15:enemy.set_info(100, 20, 80, "Наемник-Клинок Двуручного Разрушения"); break;
	case 16:enemy.set_info(50, 25, 70, " Мастер Алхимии"); break;
	case 17:enemy.set_info(150, 15, 0, " Палач-Исполнитель Кары"); break;
	case 18:enemy.set_info(200, 10, 0, "Древний Друид"); break;
	case 19:enemy.set_info(120, 13, 1, "Палач-Мучитель Тьмы"); break;
	case 20:enemy.set_info(70, 35, 0, "Кровавый Разрушитель"); break;
	}
	return enemy;
}





int main() {
	int k = 0;
	setlocale(LC_ALL, "RU");
	system("chcp 1251 > null");
	Player user = init();
	Enemy enemy = r_ememy();

	cout << "Справочный материал нажав на:" << endl
		<< "s - Вы отобразите характеристика " << endl
		<< "t - Вы за 75 монет получите добавку к урону " << endl
		<< "g - Вы сходите в гильдию и попытаетесь выполнить их задание " << endl
		<< "m - Вы можете сходить в магазин купить зелье" << endl
		<< "a - Вы можете сходить на арена " << endl
		<< "h - Вы можете использовать зелье" << endl
		<< "c - Очистка экрана" << endl << endl;

	// Главное меню и отслеживание действий игрока
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

		// Приближение босса
		if (user.total_score >= user.max_total_score && k == 0) k++;
		switch (k) {
		case 1:cout << endl << endl << "------------------------------------------" << endl << "Знатные люди говорят о вас." << endl << "------------------------------------------" << endl << endl << endl; k++; break;
		case 2:cout << endl << endl << "------------------------------------------" << endl << "На вас открыта охота." << endl << "------------------------------------------" << endl << endl << endl; k++;   break;
		case 3:user.finish_stage(); break;
		}
	}
	cout << endl << "Вы мертвы...";


}


// рандомизация однотипного текста



