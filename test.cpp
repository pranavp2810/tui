#include "radiobutton.h"

int main()
{
	//cprintf("La fruta que te gusta es la: ");
	list_checkbox *list1 = new list_checkbox;
	list1->add("manzana");
	list1->add("naranja");
	list1->add("melon");
	list1->add("fresa");

	list1->box(2,1);
   list1->ini->show(4,2);
   //list1->focus();
   //list1->result(3,7);

	getch();

return 0;
}
