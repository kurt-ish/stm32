const char *strings[] = {
		"������� ����",			// 0 - ������� ����
		"��������� ���������",	// 1
		"��������� �����",		// 2
		"���������",			// 3
		"��������� �������.",	// 4
		"��������� �������",	// 5
		"������ �������",		// 6
		"��� ���������",		// 7 - ��������� ���������
		"������������� ����.",	// 8
		"����������� �� ����",	// 9 - ��������� �����
		"���. ����������",		// 10
		"����. ����������",		// 11
		"����������",			// 12 - ���������
		"���",					// 13
		"�������� ��������",	// 14
		"�����������",			// 15
		"����� ������",			// 16
		"����/�����",			// 17 - ��������� �������
		"����",					// 18
		"�������� � �������",	// 19
/* 20 */"Lorem ipsum dolor sit amet, consectetur\nadipisicing elit, sed do eiusmod tempor\nincididunt ut labore et dolore magna.",
		"Lorem ipsum dolor sit amet,\nconsectetuer adipiscing elit. Maecenas\nporttitor congue massa.",
		"Fusce posuere, magna sed pulvinar\nultricies, purus lectus malesuada\nlibero, sit amet commodo magna eros.",
		"Fusce est. Vivamus a tellus.",
		"Pellentesque habitant morbi tristique\nsenectus et netus et malesuada fames ac\nturpis egestas. Proin pharetra.",
/* 25 */"Mauris et orci. Aenean nec lorem.",
		"In porttitor. Donec laoreet nonummy\naugue.",
		"Suspendisse dui purus, scelerisque at,\nvulputate vitae, pretium mattis, nunc.\nMauris eget neque at sem venenatis.",
		"�����",
		"��������� �����",
		"�������"

};

// ��������, ��������, ��������, �������
const unsigned char mItems[][4] = {
		{1, 1, 1, 20},	// ������� ����
		{2, 1, 2, 21},	//
		{3, 1, 3, 22},	//
		{4, 0, 0, 23},	//
		{5, 1, 4, 24},	//
		{6, 0, 0, 25},	//
		{7, 0, 0, 26},	// ��������� ���������
		{8, 0, 0, 27},	//
		{9, 0, 0, 20},	// ��������� �����
		{10, 0, 0, 21},	//
		{11, 0, 0, 22},	//
		{12, 0, 0, 23}, // ���������
		{13, 0, 0, 24},	//
		{14, 0, 0, 25},	//
		{15, 0, 0, 26},	//
		{16, 0, 0, 27},	//
		{17, 2, 0, 21}, // ��������� �������
		{18, 0, 0, 22},	//
		{19, 0, 0, 23},	//
};

// ��������, �����������, ��������� �����
const unsigned char menu[][3] = {
		{0, 6, 0},	// ������� ����
		{1, 2, 6},	// ��������� ���������
		{2, 3, 8},	// ��������� �����
		{3, 5, 11},	// ���������
		{5, 3, 16},	// ��������� �������
};
