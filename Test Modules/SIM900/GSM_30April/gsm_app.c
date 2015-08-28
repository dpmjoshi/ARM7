#include "includes.h"

DIAL diallist[20];
DIAL *diallist_head;
DIAL *diallist_tail;




void GSM_APP_call()
{
	U8 Uc_dial_stat = 0;
	U8 phone_no[15];

	Uc_dial_stat = APP_phone_dial(phone_no);
	if(Uc_dial_stat == 1)
	{                                                                                           
		clrscr();
   		ms_delay(10000);
		lcd_line3_disp("Calling...",0);
		lcd_line4_disp("End Call",12);
		lcd_line2_disp(phone_no,0);
		gsm_voice_call(phone_no);
		rtc_get_time(time);
		rtc_get_date(&date[0]);
		GSM_APP_diallist_update(phone_no, time);
		lcd_line_disp(time,12,1);
	}
	else if(Uc_dial_stat == 0)
	{
	 	clrscr();
   		ms_delay(5000);
		lcd_line2_disp("Call Cancelled !",0);
		ms_delay(20000);
		APP_default_page();
	}
	else if(Uc_dial_stat == 2)
	{
		clrscr();
		ms_delay(20000);
		APP_default_page();
	}	
}

/**********************************************************************************/
/* Function Name: GSM_APP_diallist_init											  */
/* Arguments	: U8 diallist_size - Configurable size of diallist, limited to 20 */
/* Return Types	: 																  */
/* Description	: 															      */
/**********************************************************************************/

void GSM_APP_diallist_init(U8 diallist_size)
{
	DIAL *caller1;
	DIAL *caller2;
 
	caller1 = &diallist[0];
	caller2 = &diallist[1];

 	while(diallist_size)				  // Preparing a doubly link list 
 	{									  
	 	caller2->prev = caller1;		  
		caller1->next = caller2;	
		caller1->cnt  = FREE;
		caller1++;
		caller2++;
		diallist_size--; 
 	}

	diallist_head  = &diallist[0];		   // Assigning Head of the list
	diallist_tail  = diallist_head;		   // At initialization Head & Tail are same.
	caller1->next  = &diallist[0];		   // making list circular. Caller1 is incremented in while and hence it will be the last no.
	diallist_head->prev = caller1;		   // providing a back link to the Head of list
}

/**********************************************************************************/
/* Function Name: GSM_APP_diallist_show											  */
/* Arguments	: *phone_no 										  			  */
/* Return Types	: 																  */
/* Description	: 															      */
/**********************************************************************************/

U8 GSM_APP_diallist_show()
{
	U8 uc_cnt = 0;
	U8 key_temp = 0;
	U8 opt = 0;
	U8 *diallist_arr[10] = {"Call", "Delete", "Clear List", "Exit", " "};
	
	DIAL *diallist_temp;
	DIAL *diallist_first;
	DIAL *temp;
  
	clrscr();

	lcd_line_disp("Delete", 0, 4);
	lcd_line_disp("Exit", 16, 4);
	diallist_temp = diallist_head->prev;  // diallist_head 's prev node is allocated to diallist_temp	 
	diallist_first = diallist_head->prev; // diallist_head 's prev node is allocated to diallist_first	 
	while(1)
	{ 		
		for(uc_cnt = 1; uc_cnt < 4; uc_cnt++)	//	 
  		{
			if(diallist_temp->cnt == NOT_FREE)
			{
				lcd_line_disp(diallist_temp->no, 0, uc_cnt);
				lcd_line_disp(diallist_temp->time, 12, uc_cnt);
				diallist_temp = diallist_temp->prev;	
			}
  		}
		lcd_line_disp("Options", 0, 4);
		lcd_line_disp("Exit", 16, 4);
		key_temp = get_key(1);
		ms_delay(100);

		if(key_temp == 'D')
		{
			APP_default_page();
		 	return 0;
		}

		else if(key_temp == 'E')
		{
			opt =  GSM_APP_options(diallist_arr, 4);
			
			if(opt == 1)
			{
			 	
			}
			else if(opt == 2)
			{
				diallist_temp = diallist_first->prev;
				GSM_APP_diallist_delete(diallist_first);
		   		diallist_first = diallist_temp;
				clrscr();		

				uart0_tx_string("\r\n\ndiallist First: ");
				uart0_tx_string(diallist_first->no);
			
				temp  = diallist_head->prev;
				uart0_tx_string("\r\ndiallist Head: ");
				uart0_tx_string(temp->no);

				uart0_tx_string("\r\ndiallist Tail: ");
				uart0_tx_string(diallist_tail->no);
   			}

		}
		else if(key_temp == 'C')   // Scroll DOWN											     
		{
			diallist_temp  = diallist_first->prev;
			if(diallist_temp->cnt == NOT_FREE)
			{
				clrscr();
				diallist_first = diallist_first->prev;

				uart0_tx_string("\r\n\ndiallist First: ");
				uart0_tx_string(diallist_first->no);

				temp  = diallist_head->prev;
				uart0_tx_string("\r\ndiallist Head: ");
				uart0_tx_string(temp->no);
			}
			else
			{
				diallist_temp  = diallist_first;	
			}

		}
		else if(key_temp == 'B')	// Scroll UP
		{
			diallist_temp  = diallist_first->next;	
			if(diallist_temp->cnt == NOT_FREE)
			{
				clrscr();
	 			diallist_first = diallist_first->next;
				
				uart0_tx_string("\r\n\ndiallist First: ");
				uart0_tx_string(diallist_first->no);

				temp  = diallist_head->prev;
				uart0_tx_string("\r\ndiallist Head: ");
				uart0_tx_string(temp->no);
			}
			else
			{
			 	diallist_temp  = diallist_first;	
			}
		}

		diallist_temp  = diallist_first;
	}
}

/**********************************************************************************/
/* Function Name: GSM_APP_diallist_update										  */
/* Arguments	: *phone_no, *time 										  		  */
/* Return Types	: 																  */
/* Description	: 															      */
/**********************************************************************************/

void GSM_APP_diallist_update(U8 *phone_no, U8 *time)
{
	uart0_tx_string("\r\n\ ");
	LIB_str_copy(phone_no, &diallist_head->no[0], 10);	 // Common part for both cases 
	LIB_str_copy(time, &diallist_head->time[0], 8);		 // In any of the case New No is added at the Head of the list
	diallist_head->cnt = NOT_FREE;						 // after asigning Phone no and time stamp, the node is marked as NOT_FREE

	uart0_tx_string("\r\nDiallist Head: ");
	uart0_tx_string(diallist_head->no);
	uart0_tx_string("   ");
	uart0_tx_string(diallist_head->time);

	uart0_tx_string("\r\nDiallist Tail: ");
	uart0_tx_string(diallist_tail->no);
	uart0_tx_string("   ");
	uart0_tx_string(diallist_tail->time);

	if(diallist_head->next == diallist_tail)			// This is the case when list is full and hence head->next is pointing to the tail 
	{
		diallist_tail = diallist_tail->next;			// Tail & Head are shifted further by one position, and we get new Head & Tail for our list
		diallist_head = diallist_head->next;
	}									   
	else 
	{
		diallist_head = diallist_head->next;			// Head is traversing forward when list is empty or Head->next is not tail
	}													// Tail will not change till the list gets full
	
}

/**********************************************************************************/
/* Function Name: GSM_APP_diallist_delete										  */
/* Arguments	: DIAL *del_node 										  		  */
/* Return Types	: NONE															  */
/* Description	: Deletes a node specified by del_node						      */
/**********************************************************************************/

void GSM_APP_diallist_delete(DIAL *del_node)
{
  	DIAL *delnext;										// delnext is the node next to del_node	& it is used while detaching the node from 
	DIAL *temp;											// existing list
  	
	if(del_node->cnt == NOT_FREE)		  				// The node to be deleted must be a valid node, deleting empty node is useless. 
	{
		delnext = del_node->next;
		if(diallist_head->next == diallist_tail)		// if Head->next is tail of list, it means that list is full
  		{
			if(del_node == diallist_head)				// case1: the deleted node itself is head,
			{ 											// In this case we must find a new Head & Tail for the list 
				diallist_tail = diallist_tail->next;	// Tail = Tail->next	  New Tail
 				diallist_head = diallist_head->next;	// Head = Head->next	  New Head
 			}
		}												/*What if list is full & del_node is Tail ?  <------ FIX this */ 
		else 
		{
			if(del_node == diallist_tail)				// case2: List is not full but del_node is Tail of list
			{ 											// In this case we must find a Tail for the list 
				diallist_tail = diallist_tail->next;	// Tail = Tail->next	  New Tail
														// When list partially filled the head is an empty node and one node ahead of last  
 			}											// entered number.
		}
		/* detaching del_node from its position */
 		delnext->prev = del_node->prev;
 		temp = del_node->prev;
		temp->next = delnext; 
		del_node->cnt  = FREE;
 		/****************************************/ 
 
		/* Adding the deleted node after head */
		del_node->next = diallist_head->next;			 // Copying head->next link to del->next		
		del_node->prev = diallist_head;					 // del's backlink will be Head
		diallist_head->next = del_node;					 // Now head->next will be del (new node)
		temp = del_node->next;							 // Assigning backlink of node next to del (new node) 
		temp->prev = del_node;							  
	}
}

/**********************************************************************************/
/* Function Name: GSM_APP_options												  */
/* Arguments	: U8 **opt_disp, U8 opt_cnt								  		  */
/* Return Types	: NONE															  */
/* Description	: 															      */
/**********************************************************************************/

U8 GSM_APP_options(U8 **opt_disp, U8 opt_cnt)			// *opt_disp is an array of pointers, were each pointer will point  
{														// to the option menu to be displayed
	U8 temp_key = 0;	
	U8 uc_cnt = 1;
	U8 **temp_ptr;

	while(temp_key != 'D')
	{
	 	lcd_line_disp("                    ", 0, 3);
		lcd_line_disp("                    ", 0, 4);
		temp_ptr = opt_disp + (uc_cnt - 1);
		lcd_line_disp(*temp_ptr, 0, 3);
		temp_ptr++;
		lcd_line_disp(*temp_ptr, 0, 4);
	 
	 	temp_key = get_key(1);
		ms_delay(200);
		if(temp_key == 'B')
		{
		 	if(uc_cnt >1)
			{
			 	uc_cnt -= 1;
			}
		}
		else if(temp_key == 'C')
		{
			if(uc_cnt < opt_cnt)
			{
			 	uc_cnt += 1;
			}
		}  
		else if(temp_key == 'E')
		{
		 	return uc_cnt;
		}
  	}
	clrscr();
	return 0;	  	
}





