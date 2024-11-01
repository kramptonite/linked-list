#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define LIST_LOG(a, ...) printf("%s(): %d : " a, __func__, __LINE__, ##__VA_ARGS__)

typedef enum LIST_ERROR_TYPE
{
	LIST_ERROR_TYPE_NO_ERROR = 1,
	LIST_ERROR_TYPE_MEMORY_ERROR = -94,
	LIST_ERROR_TYPE_NO_LIST_ERROR,
	LIST_ERROR_TYPE_VALUE_NOT_FOUND,
	LIST_ERROR_TYPE_NODE_NOT_FOUND,
  LIST_ERROR_TYPE_SOLO_REPLACE_ERROR,
  LIST_ERROR_TYPE_SAME_REPLACE_ERROR,
	LIST_ERROR_TYPE_GENEREIC_ERROR,
}LIST_ERROR_TYPE;

typedef enum LIST_FEATURE
{
  LIST_FEATURE_ADD_FIRST = 1,
  LIST_FEATURE_ADD_LAST = 2,
  LIST_FEATURE_ADD_BEFORE = 3,
  LIST_FEATURE_ADD_AFTER = 4,
  LIST_FEATURE_REMOVE_FIRST = 5,
  LIST_FEATURE_REMOVE_LAST = 6,
  LIST_FEATURE_REMOVE = 7, 
  LIST_FEATURE_EDIT = 8,
  LIST_FEATURE_DISPLAY = 9,
  LIST_FEATURE_SEARCH_BY_NODE = 10,
  LIST_FEATURE_SEARCH_BY_VALUE = 11,
  LIST_FEATURE_CLEAR_ALL = 12,
  LIST_FEATURE_REPLACE = 13,
  LIST_FEATURE_REVERSE = 14,
  LIST_FEATURE_EXIT = 15
}LIST_FEATURE;

/* linked-list operation totality list */
LIST_ERROR_TYPE list_add_first(int l_userInput);
LIST_ERROR_TYPE list_add_last(int l_userInput);
LIST_ERROR_TYPE list_add_before(unsigned int a_location, int a_nodeValue);
LIST_ERROR_TYPE list_add_after(unsigned int a_location, int a_nodeValue);
LIST_ERROR_TYPE list_remove_first();
LIST_ERROR_TYPE list_remove_last();
LIST_ERROR_TYPE list_remove(unsigned int a_location);
LIST_ERROR_TYPE list_node_edit(int l_userInput, unsigned int l_location);
LIST_ERROR_TYPE List_display();
LIST_ERROR_TYPE list_search_by_value(unsigned int l_checker);
LIST_ERROR_TYPE list_search_by_NodeNumber(unsigned int l_nodeNumber);
LIST_ERROR_TYPE list_clear_all();
LIST_ERROR_TYPE list_node_replacement(unsigned int a_location, unsigned int a_location_1);
LIST_ERROR_TYPE list_reverse();

struct node {
   int value;
   struct node *next;
 };
struct node *g_HEAD = NULL;

int main()
{
  printf("welcome to the linked list operation.\n");
  int l_option = 0, l_userInput = 0; 
  char l_confirm;
  unsigned int l_location = 0, l_location_1 = 0, l_nodeNumber = 0, l_checker = 0;
  while(1)
  {
    fflush(stdin);
    printf("Select your operation.  \
            \n1 add first           \
            \n2 add last            \
            \n3 add before          \
            \n4 add after           \
            \n5 remove first        \
            \n6 remove last         \
            \n7 remove              \
            \n8 edit a node         \
            \n9 display             \
            \n10 search by node     \
            \n11 search by value    \
            \n12 clear all          \
            \n13 replace a node     \
            \n14 reverse the list   \
            \n15 exit.\n");

    scanf("%d", &l_option);
    switch(l_option)
    {
      case LIST_FEATURE_ADD_FIRST:
        LIST_LOG("Please add Node value: ");
        scanf("%d", &l_userInput);
        list_add_first(l_userInput);
        break;

      case LIST_FEATURE_ADD_LAST:
        LIST_LOG("Please add Node value: ");
        scanf("%d", &l_userInput);
        list_add_last(l_userInput);
        break;
      case LIST_FEATURE_ADD_BEFORE:
        LIST_LOG("Please add location and node value: ");
        scanf("%d %d", &l_location, &l_userInput);
        LIST_LOG("location is %d\n", l_location);
        LIST_LOG("Node value is %d\n", l_userInput);
        list_add_before(l_location, l_userInput);
        break;
        
      case LIST_FEATURE_ADD_AFTER:
        LIST_LOG("Please add location and node value: ");
        scanf("%d %d", &l_location, &l_userInput);
        LIST_LOG("location is %d\n", l_location);
        LIST_LOG("Node value is %d\n", l_userInput);
        list_add_after(l_location, l_userInput);
        break;

      case LIST_FEATURE_REMOVE_FIRST:
        list_remove_first();
        break;

      case LIST_FEATURE_REMOVE_LAST:
        list_remove_last();
        break;

      case LIST_FEATURE_REMOVE:
        LIST_LOG("Please add location: ");
        scanf("%d", &l_location);
        list_remove(l_location);
        break;

      case LIST_FEATURE_EDIT:
        LIST_LOG("Please add updated value and location: ");
        scanf("%d \n%d", &l_userInput, &l_location);
        list_node_edit(l_userInput, l_location);
        break;

      case LIST_FEATURE_DISPLAY:
        List_display();
        break;

      case LIST_FEATURE_SEARCH_BY_NODE:
        LIST_LOG("Please add the node number you want to search: ");
        scanf("%d", &l_nodeNumber);
        list_search_by_NodeNumber(l_nodeNumber);
        break;

      case LIST_FEATURE_SEARCH_BY_VALUE:
        LIST_LOG("Please add the value you want to search: ");
        scanf("%d", &l_checker);
        list_search_by_value(l_checker);
        break;

      case LIST_FEATURE_CLEAR_ALL:
        LIST_LOG("are you sure?    \
                  \ntype y for yes \
                  \nn for no");
        fflush(stdin);
        scanf("%c", &l_confirm);

        if('y' == l_confirm)
          list_clear_all();
        else if('n' == l_confirm)
          printf("operation cancelled \n");
        break;

      case LIST_FEATURE_REPLACE:
        printf("Please enter the locations you wanna replace nodes around \n");
        scanf("%d %d", &l_location, &l_location_1);
        list_node_replacement(l_location, l_location_1);
        break;
        
      case LIST_FEATURE_REVERSE:
        list_reverse();
        break;

      case LIST_FEATURE_EXIT:
        list_clear_all();
        exit(1);

      default:
        LIST_LOG("There does not exist such an operational option \n");
    }
    printf("print any key to continue \n");
    getch();
    system("@cls||clear");
  }
  return 0;
}

LIST_ERROR_TYPE list_add_first(int a_nodeValue)
{
  struct node* l_newNode = NULL;
  l_newNode = (struct node*)malloc(sizeof(struct node));
  if(NULL == l_newNode)
  {
    LIST_LOG("malloc_error \n");
    return LIST_ERROR_TYPE_MEMORY_ERROR;
  }
  l_newNode->value = a_nodeValue;
  l_newNode->next = NULL;

  if(NULL == g_HEAD)
  {
    LIST_LOG("new node is being created \n");
    g_HEAD = l_newNode;
  }
  else
  {
    l_newNode->next = g_HEAD;
    g_HEAD = l_newNode;
  }
  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_add_last(int a_nodeValue)
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}

  struct node* l_tempNode = g_HEAD;
	while(NULL != l_tempNode->next)
	{
		l_tempNode = l_tempNode->next;
	}

  struct node* l_newNode = NULL;
	l_newNode = (struct node*)malloc(sizeof(struct node));
	if(NULL == l_newNode)
	{
	  LIST_LOG("malloc_error \n");
	  return LIST_ERROR_TYPE_MEMORY_ERROR;
	}
	l_newNode->value = a_nodeValue;
	l_newNode->next = NULL;
	l_tempNode->next = l_newNode;

  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_add_before(unsigned int a_location, int a_nodeValue)
{
  if(NULL == g_HEAD)
	{
		LIST_LOG("there is no linked list \n");
		return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
  int l_index;
  struct node* l_tempNode = g_HEAD;
	for(l_index = 1; l_index < a_location - 1; l_index++)
	{
    l_tempNode = l_tempNode->next;
    if(NULL == l_tempNode)// check for the existence of location
    {
      LIST_LOG("there is no linked list \n");
      return LIST_ERROR_TYPE_NO_LIST_ERROR;
    }
	}
  struct node* l_newNode = NULL;
	l_newNode = (struct node*)malloc(sizeof(struct node));
  if(NULL == l_newNode)
  {
    LIST_LOG("malloc_error \n");
    return LIST_ERROR_TYPE_MEMORY_ERROR;
  }
  l_newNode->value = a_nodeValue;
  if(l_tempNode == g_HEAD)// specific case for placing at the start
  {
    l_newNode->next = g_HEAD;
    g_HEAD = l_newNode;
  }
  else
  {
    l_newNode->next = l_tempNode->next;
    l_tempNode->next = l_newNode;
  }
  LIST_LOG("Node value is %d\n", a_nodeValue);
  LIST_LOG("position is %d\n", a_location);
  
  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_add_after(unsigned int a_location, int a_nodeValue)
{
	if(NULL == g_HEAD)
	{
		LIST_LOG("there is no linked list \n");
		return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
  int l_index;
  struct node* l_tempNode = g_HEAD;
	for(l_index = 1; l_index < a_location; l_index++)
	{
		l_tempNode = l_tempNode->next;
	}

  struct node* l_newNode = NULL;
	l_newNode = (struct node*)malloc(sizeof(struct node));
  if(NULL == l_newNode)
  {
    LIST_LOG("malloc_error \n");
    return LIST_ERROR_TYPE_MEMORY_ERROR;
  }
  l_newNode->value = a_nodeValue;
  LIST_LOG("Node value is %d\n", a_nodeValue);
  LIST_LOG("position is %d\n", a_location);
  l_newNode->next = l_tempNode->next;
  l_tempNode->next = l_newNode;

  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_remove_first()
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}

  LIST_LOG("%d value is deleted with the node \n", g_HEAD->value);

  struct node* l_tempNode = g_HEAD;
  g_HEAD = g_HEAD->next;
  free(l_tempNode);

  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_remove_last()
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}

  struct node* l_currNode = g_HEAD;
  struct node* l_prevNode = g_HEAD;
  while(NULL != l_currNode->next)
  {
    l_prevNode = l_currNode;
    l_currNode = l_currNode->next;
  }
  LIST_LOG("%d value is deleted with the node \n", l_currNode->value);
  if(l_currNode == g_HEAD)
    g_HEAD = NULL;
  else
    l_prevNode->next = NULL;

  free(l_currNode);

  return LIST_ERROR_TYPE_NO_ERROR;
}


LIST_ERROR_TYPE list_remove(unsigned int a_location)
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
  struct node* l_prevNode = g_HEAD;
  struct node* l_currNode = g_HEAD;
  unsigned int l_index;
  for(l_index = 1; l_index < a_location; l_index++)
  {
    l_prevNode = l_currNode;
    l_currNode = l_currNode->next;
    if(NULL == l_currNode)
    {
      LIST_LOG("Location does not exist \n");
      return LIST_ERROR_TYPE_NODE_NOT_FOUND;
    }
  }

  if(NULL == g_HEAD->next)
    g_HEAD = NULL;
  else if(l_currNode == g_HEAD)
    g_HEAD = g_HEAD->next;
  else
    l_prevNode->next = l_currNode->next;

  LIST_LOG("%d is deleted \n", l_currNode->value);
  free(l_currNode);

  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_node_edit(int a_updatedValue, unsigned int a_location)
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
  int l_index;
  struct node* l_tempNode = g_HEAD;
	for(l_index = 1; l_index < a_location; l_index++)
	{
    if(NULL == l_tempNode)
    {
      LIST_LOG("Location does not exist \n");
      return LIST_ERROR_TYPE_NODE_NOT_FOUND;
    }
		l_tempNode = l_tempNode->next;
	}
	LIST_LOG("%d is being changed by %d \n", l_tempNode->value, a_updatedValue);
	l_tempNode->value = a_updatedValue;
  LIST_LOG("Value of the node is changed \n");

  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE List_display()
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("There is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
	struct node* l_tempNode = NULL;
	l_tempNode = g_HEAD;
	while(l_tempNode != NULL)
	{
		printf("%d -> ", l_tempNode->value);
		l_tempNode = l_tempNode->next;
	}
	printf("NULL\n");
	return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_search_by_value(unsigned int a_checker)
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("there is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}
  struct node* l_tempNode = g_HEAD;
  unsigned int l_count1 = 1;

  while(a_checker != l_tempNode->value)
  {
    l_tempNode = l_tempNode->next;
    l_count1++;
  }
  if(a_checker == l_tempNode->value)
  {
    LIST_LOG("the value has been found in the node %d of the list \n", l_count1);
    return LIST_ERROR_TYPE_NO_ERROR;
  }
  else
  {
    LIST_LOG("the number has not been found in the list \n");
    return LIST_ERROR_TYPE_VALUE_NOT_FOUND;
  }
}

LIST_ERROR_TYPE list_search_by_NodeNumber(unsigned int l_nodeNumber)
{
	if(NULL == g_HEAD)
	{
	  LIST_LOG("there is no linked list \n");
	  return LIST_ERROR_TYPE_NO_LIST_ERROR;
	}

  struct node* l_tempNode = g_HEAD;
  unsigned int l_count1 = 1;
  while(l_count1 != l_nodeNumber)
  {
    l_tempNode = l_tempNode->next;
    l_count1++;
  }
    if(NULL == l_tempNode)
  {
    LIST_LOG("node number does not exist \n");
    return LIST_ERROR_TYPE_NODE_NOT_FOUND;
  }
  else
  {
    LIST_LOG("node %d has %d value \n", l_count1, l_tempNode->value);
    return LIST_ERROR_TYPE_NO_ERROR;
  }
}

LIST_ERROR_TYPE list_clear_all()
{
  if(NULL == g_HEAD)
  {
    LIST_LOG("no linked list exist \n");
    return LIST_ERROR_TYPE_NO_LIST_ERROR;
  }

  struct node* l_temp = g_HEAD;
  while(NULL != g_HEAD)
  {
    g_HEAD = g_HEAD->next;
    free(l_temp);
    l_temp = g_HEAD;
  }

  printf("list is cleared \n");
  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_node_replacement(unsigned int a_location, unsigned int a_location_1)
{
/* pre traverse error check begin */
  if(NULL == g_HEAD)
  {
    LIST_LOG("no linked list exist \n");
    return LIST_ERROR_TYPE_NO_LIST_ERROR;
  }
  if(NULL == g_HEAD->next)
  {
    printf("not enough nodes to replace \n");
    return LIST_ERROR_TYPE_SOLO_REPLACE_ERROR;
  }
  if(a_location == a_location_1)
  {
    printf("replacement locations can't be same \n");
    return LIST_ERROR_TYPE_SAME_REPLACE_ERROR;
  }
/* end of pre-traverse error checks */
/* 4 pointer for the operation creation */
  struct node *l_prevReplace_1 = g_HEAD, *l_prevReplace_2 = g_HEAD;
  struct node *l_replaced_1 = NULL, *l_replaced_2 = NULL, *l_temp = NULL;
  unsigned int index = 1 ,type = 0;
/* while to search for the first node */
  while(NULL != l_prevReplace_1)
  {
    if(1 == a_location)
    {
      l_prevReplace_1 = NULL;
      l_replaced_1 = g_HEAD;
      break;
    }

    if((index + 1) == a_location)
    {
      l_prevReplace_1 = l_prevReplace_2;
      l_replaced_1 = l_prevReplace_1->next;
      break;
    }
    l_prevReplace_1 = l_prevReplace_1->next;
    index++;
  }

/* while to search for the second node */
  while(NULL != l_prevReplace_2->next)
  {
    if(1 == a_location_1)
    {
      l_replaced_2 = l_prevReplace_2;
      break;
    }
    if((index + 1) == a_location_1)
    {
      l_replaced_2 = l_prevReplace_2->next;
      break;
    }
    l_prevReplace_2 = l_prevReplace_2->next;
    index++;
  }
/* post traverse error check begin */
  if(NULL == l_prevReplace_2)
  {
    printf("location %d does not exist \n", a_location_1);
    return LIST_ERROR_TYPE_NODE_NOT_FOUND;
  }
  
/* case determination */
  unsigned int case_maker_1 = 0, case_maker_2 = 0;
  if((NULL == l_replaced_1->next) ^ (NULL == l_replaced_2->next))
  {
    type = 2;
    case_maker_1 = 1;
  }
  if((l_replaced_1 == l_prevReplace_1) ^ (l_replaced_2 == l_prevReplace_2))
  {
    type = 2;
    case_maker_2 = 1;
  }
  if((case_maker_1 == 1) && (case_maker_2 == 1))
    type = 3;
  if((l_replaced_1->next == l_replaced_2) || (l_replaced_2->next == l_replaced_1))
    type = 4;

  struct node *l_temp1 = NULL;
  switch(type)
  {
    case 1:
    {
      if(l_replaced_1 == l_prevReplace_1)
      {
        l_temp = l_replaced_1->next;
        
        l_replaced_1->next = l_replaced_2->next;
        l_replaced_2->next = l_temp;
        l_prevReplace_2->next = l_replaced_1;
        g_HEAD = l_replaced_2;
        break;
      }
      else
      {
        l_temp = l_replaced_2->next;
        
        l_replaced_2->next = l_replaced_1->next;
        l_replaced_1->next = l_temp;
        l_prevReplace_1->next = l_replaced_2;
        g_HEAD = l_replaced_1;
        break;
      }
    }
    case 2:
    {
      if(l_replaced_1->next == NULL)
      {
        l_temp = l_replaced_2->next;
      }
      else
      {
        l_temp = l_replaced_1->next;
      }
      l_replaced_2->next = l_replaced_1->next;
      l_replaced_1->next = l_temp;
      
      l_prevReplace_1->next = l_replaced_2;
      l_prevReplace_2->next = l_replaced_1;
      break;
    }
    case 3:
    {    
      if(l_replaced_1 == l_prevReplace_1)
      {
      /* it means , here replaced_2->next is NULL */
        
        l_replaced_2->next = l_replaced_1->next;
        l_replaced_1->next = NULL;
        
        g_HEAD = l_replaced_2;
        l_prevReplace_2->next = l_replaced_1;
        break;
      }
      else if(NULL == l_replaced_1->next)
      {
        l_replaced_1->next = l_replaced_2->next;
        l_replaced_2->next = NULL;
        
        g_HEAD = l_replaced_1;
        l_prevReplace_1->next = l_replaced_2;
        break;
      }
    }  
    case 4:
    {
      l_temp = l_replaced_1;
      l_temp1 = l_replaced_2->next;
      
      l_prevReplace_1->next = l_replaced_2;
      l_replaced_2->next = l_temp;
      l_temp->next = l_temp1;
      break;
    } 
    default:
    {
      l_temp = l_replaced_1;
      
      l_replaced_1->next = l_replaced_2->next;
      l_replaced_2->next = l_temp;
      l_prevReplace_1->next = l_replaced_2;
      l_prevReplace_2->next = l_replaced_1;
      break;
    }
  }
  printf("replacement successful \n");
  return LIST_ERROR_TYPE_NO_ERROR;
}

LIST_ERROR_TYPE list_reverse()
{
  struct node *l_temp1 = g_HEAD;
  struct node *l_temp2 = l_temp1->next;
  if(NULL == l_temp2->next)
  {
    l_temp2->next = l_temp2;
    l_temp2->next = NULL;
  }
  else
  {
    struct node *temp3 = l_temp2->next;
    while(NULL != temp3)
    {
      if(l_temp1 == g_HEAD)
      {
        l_temp1->next = NULL;
      }
      l_temp2->next = l_temp1;
      
      l_temp1 = l_temp2;
      l_temp2 = temp3;
      temp3 = temp3->next;
    }
    l_temp2->next = l_temp1;
  }
  g_HEAD = l_temp2;
}
