#include "radiobutton.h"

int main()
{
	cprintf("La fruta que te gusta es la: ");
	list_radiobutton *list1 = new list_radiobutton;
	list1->add("manzana");
	list1->add("naranja");
	list1->add("melon");
	list1->add("fresa");
	list1->show(3,3,0);
   list1->focus();
   list1->result(3,7);

	getch();

return 0;
}
