const char *strings[] = {
		"Главное меню",			// 0 - Главное меню
		"Параметры двигателя",	// 1
		"Настройки защит",		// 2
		"Измерения",			// 3
		"Параметры регулир.",	// 4
		"Настройки системы",	// 5
		"Журнал событий",		// 6
		"Ток двигателя",		// 7 - Параметры двигателя
		"Сопротивление стат.",	// 8
		"Ограничение по току",	// 9 - Настройка защит
		"Мин. напряжение",		// 10
		"Макс. напряжение",		// 11
		"Напряжение",			// 12 - Измерения
		"Ток",					// 13
		"Скорость вращения",	// 14
		"Температура",			// 15
		"Время работы",			// 16
		"Дата/время",			// 17 - Настройки системы
		"Звук",					// 18
		"Сведения о системе",	// 19
/* 20 */"Lorem ipsum dolor sit amet, consectetur\nadipisicing elit, sed do eiusmod tempor\nincididunt ut labore et dolore magna.",
		"Lorem ipsum dolor sit amet,\nconsectetuer adipiscing elit. Maecenas\nporttitor congue massa.",
		"Fusce posuere, magna sed pulvinar\nultricies, purus lectus malesuada\nlibero, sit amet commodo magna eros.",
		"Fusce est. Vivamus a tellus.",
		"Pellentesque habitant morbi tristique\nsenectus et netus et malesuada fames ac\nturpis egestas. Proin pharetra.",
/* 25 */"Mauris et orci. Aenean nec lorem.",
		"In porttitor. Donec laoreet nonummy\naugue.",
		"Suspendisse dui purus, scelerisque at,\nvulputate vitae, pretium mattis, nunc.\nMauris eget neque at sem venenatis.",
		"Время",
		"Начальный экран",
		"Справка"

};

// Название, действие, значение, справка
const unsigned char mItems[][4] = {
		{1, 1, 1, 20},	// Главное меню
		{2, 1, 2, 21},	//
		{3, 1, 3, 22},	//
		{4, 0, 0, 23},	//
		{5, 1, 4, 24},	//
		{6, 0, 0, 25},	//
		{7, 0, 0, 26},	// Параметры двигателя
		{8, 0, 0, 27},	//
		{9, 0, 0, 20},	// Настройка защит
		{10, 0, 0, 21},	//
		{11, 0, 0, 22},	//
		{12, 0, 0, 23}, // Измерения
		{13, 0, 0, 24},	//
		{14, 0, 0, 25},	//
		{15, 0, 0, 26},	//
		{16, 0, 0, 27},	//
		{17, 2, 0, 21}, // Настройка системы
		{18, 0, 0, 22},	//
		{19, 0, 0, 23},	//
};

// Название, колличество, начальный пункт
const unsigned char menu[][3] = {
		{0, 6, 0},	// Главное меню
		{1, 2, 6},	// Параметры двигателя
		{2, 3, 8},	// Настройка защит
		{3, 5, 11},	// Измерения
		{5, 3, 16},	// Настройка системы
};
