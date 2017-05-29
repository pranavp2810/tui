#ifndef __RADIOBUTTON_H
#define __RADIOBUTTON_H

	#ifndef __CHECKBOX_H
		#include "checkbox.h"
	#endif

 class radiobutton : public checkbox
{
	public:
		radiobutton(std::string radiobuttonname);	//constructor for radiobutton, takes a name
		~radiobutton();
		void show(int,int);
		void next (radiobutton *next_);
		void back (radiobutton *back_);
		radiobutton *next();
		radiobutton *back();
	private: 
		radiobutton *next__;
		radiobutton *back__;
};

class list_radiobutton : public list_checkbox
{
	public:
		list_radiobutton() : list_checkbox() {};	//constructor takes no parameters
		~list_radiobutton();
		void add(std::string name);
		radiobutton *last();
		void show(int x, int y, bool dir);
		void focus();	//will move to desired radiobutton
		void result (int x, int y);
	private:
		void check(radiobutton *current);
		radiobutton *ini;

};

//radiobutton object constructor
radiobutton::radiobutton(std::string radiobuttonname)
:checkbox(radiobuttonname)
{
}

//radiobutton object destructor
radiobutton::~radiobutton()
{
}

radiobutton *radiobutton::next()
{
	return next__;
}

radiobutton *radiobutton::back()
{
	return back__;
}

void radiobutton::next(radiobutton *next_)
{
	next__=next_;
}

void radiobutton::back(radiobutton *back_)
{
	back__=back_;
}

 

void radiobutton::show(int x1, int y1)
{
         int xmax = 80 - SHOWLEN -this->name().size();  //there are usually only 80 characte  rs available to print on the screen, needs to take into account the name length and closing   bracket "]"
         if(x1>=1 && x1 <=xmax) //if x coordinate is within boundaries, assign it to x
         {  
            x=x1;
         }
         else   //else assign its max
         {
                if(x1<1) x=1; 
                if(x1 > xmax) x=xmax;
         }

         if(y1 >=1 && y1 <=25)  //there are usually only 25 characters in the y direction
         {
             y=y1;      ///if input y is within the boundary then assign it to the y coordin  ate
         }
         else   //else assign its max coordinate or its min
         {
           if(y1 <1) y=1;
           if(y1>25) y=25;
         }
  
         gotoxy(x,y);   //used to move cursor to desired lovation
         cprintf("(");  //intiial bracket
         for(int i=0; i<width; i++)
         {
               cprintf(" ");
         }
         cprintf(")");  //closing bracket
         gotoxy(x+5,y);
         printf(name().c_str());        //print checkbox name
         gotoxy(x+1,y); //move cursor to selection "[ ]"
}

list_radiobutton::~list_radiobutton()
{
	radiobutton *current = this ->ini;

	while(current)
	{
		radiobutton *next(current->next());
		delete current;
		current = next;
	}
}

radiobutton *list_radiobutton::last()
{
	radiobutton *end = this->ini;

	while(end->next() !=NULL)
	{
		end = end->next();
	}
	
	return end;
}

void list_radiobutton::add(std::string name)
{
	radiobutton *newradiobutton = new radiobutton (name);

	if(count_==0)
	{
		this->ini = newradiobutton;
		count_++;
	}
	else
	{
		newradiobutton->back(this->last());
		this->last()->next(newradiobutton);
		count_++;
	}
}

//print the radiobuttones into the screen

void list_radiobutton::show(int x, int y, bool dir)
{
	radiobutton *temp = this->ini;
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
		for(int i =0; temp ; i++)
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

//focus in each radiobutton

void list_radiobutton::focus()
{
	int key;
	radiobutton* temp = this->ini;
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
			this->check(temp);
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

void list_radiobutton::check(radiobutton *current)
{
	radiobutton *temp = current;
	radiobutton *back(current->back());		 
	radiobutton *next(current->next());

	if(!temp->checked())
	{
		for(;back;back=back->back())
		{
				back->focus();
				cprintf(" ");
				back->checked(0);
		}
	
		for(;next;next=next->next())
		{
				next->focus();
				cprintf(" ");
				next->checked(0);
		}
       		
		temp->focus();
		temp->checked(1);
		cprintf("*");
		temp->focus();
	}
}


void list_radiobutton::result(int x, int y)
{
	radiobutton *temp = this->ini;

	int xmax = 80 - temp->name().size();

	if(x<1) x=1;
	if(x > xmax) x=xmax;

	if(y<1 || y> 25)
	{
		if(y<1) y=1;
		if(y>25) y=25;
	}

	while(temp && y<25 && x<xmax)
	{
		gotoxy(x,y);

		if(temp->checked())
		{
			cprintf(temp->name().c_str());
		}

		temp = temp->next();
		y++;
	}
}


#endif
