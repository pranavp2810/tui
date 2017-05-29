#ifndef __CHECKBOX_H
#define __CHECKBOX_H

	#ifndef __STRING_H
		#include <string>
	#endif

	#ifndef __CONIO_H
		#include "conio.h"
	#endif

	#ifndef __STDIO_H
		#include <stdio.h>
	#endif

#define VER 0	//will be used to display checkbox vertically
#define HOR 1	//will be used to display checkbox horizontally
#define SHOWLEN 7	//"   [ ] " ->  given length between multiple checkboxes 
#define UP 72	//will be used to detect up arrow key
#define DOWN 80	//will be used to detect down arrow key
#define LEFT 75	//will be used to detect left arrow key
#define RIGHT 77	//will be used  to detect right arrow key
#define ESC 27	//detects the escape key
#define ENT 13	//enter key
#define BCK 8	//backspace key

 class checkbox
{
	public:
		checkbox(std::string checkboxname);	//constructor for checkbox, takes a name
		virtual ~checkbox();
		virtual void show(int,int);	//print on screen
		void focus();	//focus cursor inside checkbox
		void checked(bool mark);	//will mark as checked or not
      		bool checked();	//returns checked_; 1 = checked, 0 = !checked
   		std::string name();	//returns name_; the checkbox name
		void next (checkbox *next_);	//gives next a value
		void back (checkbox *back_);	//gives back a value
		virtual checkbox *next();	//returns next checkbox in list
		virtual checkbox *back();	//returns previous checkbox in list
	private:
		checkbox *next__;	//stores next checkbox
		checkbox *back__;	//stores previous checkbox
	 
	protected:
		int x;	//x-coordinate for show and focus
		int y;	//y-coordinate for show and focus
      		int width;	// "[ ]" checkbox width
	      	bool checked_;	//variable for checked()	
      		std::string name_;	//used to store checkbox name
};

class list_checkbox
{
	public:
		list_checkbox();	//constructor takes no parameters
		~list_checkbox();
		virtual void add(std::string name);	//this will add a new checkbox to the list_checkbox
		int count();	//will count how many checkboxes in the list_checkbox
		virtual checkbox *last();	//will return the last checkbox object in the list_checkbox
		virtual void show(int x, int y, bool dir);	//used to display the checkbox options
		virtual	void focus();	//will move to desired checkbox
		virtual void result(int x, int y); //will print checked items
		virtual void box(int x, int y);	//prints border around items
    private:
		checkbox *ini; //initial node in the list
	protected:
		int count_;	//used to store the number of checkboxes in the list_checkbox

};

//checkbox object constructor

checkbox::checkbox(std::string checkboxname)
{
	x = 1;
   	y = 1;
  	width = 1;
   	checked_ = 0;
   	name_ = checkboxname;
	next__ = NULL;
	back__ = NULL;
}

//checkbox object destructor

checkbox::~checkbox()
{
}

//method returns next item in the list
checkbox *checkbox::next()
{
	return next__;
}

//method returns previous item in the list
checkbox *checkbox::back()
{
	return back__;
}

//gives  next the value inserted
void checkbox::next(checkbox * next_)
{
	next__=next_;	
}

//gives back the value inserted
void checkbox::back(checkbox *back_)
{
	back__=back_;
}

//method used to print the checkbox in the console

void checkbox::show(int x1, int y1)
{
	 int xmax = 80 - SHOWLEN -this->name().size();	//there are usually only 80 characters available to print on the screen, needs to take into account the name length and closing bracket "]"
    	 if(x1>=1 && x1 <=xmax)	//if x coordinate is within boundaries, assign it to x
    	 {
       	    x=x1;
    	 }
    	 else	//else assign its max
    	 {
		if(x1<1) x=1;
		if(x1 > xmax) x=xmax;
   	 }

   	 if(y1 >=1 && y1 <=25)	//there are usually only 25 characters in the y direction
    	 {
      	     y=y1;	///if input y is within the boundary then assign it to the y coordinate
    	 }
    	 else	//else assign its max coordinate or its min
   	 {
      	   if(y1 <1) y=1;
      	   if(y1>25) y=25;
   	 }

	 gotoxy(x,y);	//used to move cursor to desired lovation
	 cprintf("[");	//intiial bracket
	 for(int i=0; i<width; i++)
	 {
		 cprintf(" ");
	 }
	 cprintf("]");	//closing bracket
   	 gotoxy(x+5,y);
   	 printf(name().c_str());	//print checkbox name
	 gotoxy(x+1,y);	//move cursor to selection "[ ]"
}

//method used to move cursor to selection "[ ]"

void checkbox::focus()
{
   	gotoxy(x+1,y);
}

//return if the checkbox has been checked or not

bool checkbox::checked()
{
	return checked_;
}

//method used to check or not the checkbox

void checkbox::checked(bool mark)
{
	checked_=mark;
}

//return the checkbox name

std::string checkbox::name()
{
	return name_;
}

//list_checkbox constructor

list_checkbox::list_checkbox()
{
	count_ = 0;
	ini = NULL;
}

//list_checkbox destructor

list_checkbox::~list_checkbox()
{
	checkbox *current = this ->ini;

	while(current)
	{
		checkbox *next = current->next();
		delete current;
		current = next;
	}
}

//return the number of items in the list_checkbox

int list_checkbox::count()
{
	return count_;
}

//return the last checkbox in the list_checkbox

checkbox *list_checkbox::last()
{
	checkbox *end = this->ini;

	while(end->next() !=NULL)
	{
		end = end->next();
	}
	
	return end;
}

//add new checkbox to the list_checkbox

void list_checkbox::add(std::string name)
{
	checkbox *newcheckbox = new checkbox(name);
	
	if(count_ == 0)
	{
		this->ini=newcheckbox;
		count_++;
	}
	else
	{
		newcheckbox->back(this->last());
		this->last()->next(newcheckbox);
		count_++;
	}

}

//print the checkboxes into the screen

void list_checkbox::show(int x, int y, bool dir)
{
   	checkbox *temp = this->ini;
	if(dir == VER)
	{
		for(int i=0;temp;i++)
		{
			temp->show(x,y+i);
			temp=temp->next();
		}
	}
	else
	{
		for(int i=0; temp ; i++)
		{
			if(i==0)
			{
				temp->show(x,y);
				x += temp->name().size() + SHOWLEN;
			}
			else
			{
				temp->show(x, y);
				x+=temp->name().size() + SHOWLEN;
			}
			temp=temp->next();
		}

	}
}

//move cursor to each checkbox

void list_checkbox::focus()
{
	int key;
	checkbox* temp = this->ini;
	temp->focus();
	do
	{
		key=getch();
		if(key == UP)
		{
			if(temp->back()) temp=temp->back();		
			temp->focus();
		}

		if(key == DOWN)
		{
			if(temp->next()) temp=temp->next();
			temp->focus();
		}


		if(key == ENT )
		{
         		if(temp->checked()==0)
			{
				temp->checked(1);
				cprintf("X");
				temp->focus();
			}
		}

		if(key == BCK)
		{
			if(temp->checked()==1) 
			{
				temp->checked(0);
				cprintf(" ");
				temp->focus();
			}
		}


	
	}while(key!=ESC);

}

//prints the checked items

void list_checkbox::result(int x, int y)
{
	checkbox *temp = this->ini;

	int xmax = 80 - temp->name().size();	//there are usually only 80 characters available to print on the screen, needs to take into account the name length

	if(x<1) x=1;
	if(x > xmax) x=xmax;

	if(y<1 || y>25) 	//if outside boundaries, assign its max coordinate or its min
	{
		if(y <1) y=1;
		if(y >25) y=25;
	}

		
	while(temp && y<25 && x<xmax)	//print the selected items
	{
		gotoxy(x,y);

		if(temp->checked())
		{
			cprintf(temp->name().c_str());
		}
			
		temp=temp->next();
		y++;
	}
}

//prints border around items

void list_checkbox::box(int x, int y)
{
	checkbox *temp = this->ini;
	int maxlen=0;
	gotoxy(x+1,y);

	for(;temp;temp=temp->next())
	{
		if(temp->name().size()>maxlen) maxlen = temp->name().size();
	}

	for(int i=0; i<maxlen +SHOWLEN +1; i++)
	{
		cprintf ("-");
	}

	for(int i=0;i<this->count();i++)
	{
		gotoxy(x,y+1+i);
		cprintf("|");
		for(int i=0;i<maxlen+SHOWLEN+1;i++)
		{
			cprintf(" ");
		}
		cprintf("|");
	}

	gotoxy(x+1,y+this->count()+1);

	for(int i=0;i<maxlen+SHOWLEN+1;i++)
	{
		cprintf("-");
	}
	this->show(x+2,y+1,0);
}

#endif
