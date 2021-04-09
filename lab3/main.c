#include "info.h"
#include "space_1.h"
#include "space_2.h"
#include "table.h"
#include "menu.h"

int SPACE1_maxsize = 20, SPACE2_maxsize = 20, SPACE2_maxkeylen = 5;

int main() {
	Table *table = table_new(SPACE1_maxsize, SPACE2_maxsize, SPACE2_maxkeylen);

	start(table);

	table_delete(table);
	return 0;
}
